/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#include <QDebug>
#include <QSemaphore>
#include <QSharedPointer>

#include "RunnableMock.h"
#include "TestThread.h"
#include "Thread.h"


using ::testing::_;
using ::testing::Return;


#define TIMEOUT_SIGNALS 1000


namespace yatp
{

    void TestThread::SetUp()
    {
    }

    void TestThread::TearDown()
    {
    }

    TEST_F(TestThread, Constructor)
    {
        Thread thread;
        EXPECT_EQ(thread.id(), 0);
        EXPECT_FALSE(thread.isStarted());
    }

    TEST_F(TestThread, Id)
    {
        Thread thread(123);
        EXPECT_EQ(thread.id(), 123);
    }

    TEST_F(TestThread, StartAndStopSignalThreadEvents)
    {
        Thread thread;
        QSemaphore threadRunning, threadStopped;
        QObject::connect(&thread, &Thread::threadStarted, [&threadRunning]()
        {
            threadRunning.release();
        });
        QObject::connect(&thread, &Thread::threadStopped, [&threadStopped]()
        {
            threadStopped.release();
        });
        EXPECT_FALSE(thread.isStarted());
        EXPECT_TRUE(thread.start());
        EXPECT_TRUE(thread.isStarted());
        EXPECT_TRUE(threadRunning.tryAcquire(1, TIMEOUT_SIGNALS));
        EXPECT_TRUE(thread.stop());
        EXPECT_FALSE(thread.isStarted());
        EXPECT_TRUE(threadStopped.tryAcquire(1, TIMEOUT_SIGNALS));
    }

    TEST_F(TestThread, StartFailsIfAlreadyStarted)
    {
        Thread thread;
        EXPECT_TRUE(thread.start());
        EXPECT_FALSE(thread.start());
    }

    TEST_F(TestThread, StopIsCalledAtDestructorIfNeeded)
    {
        QSemaphore threadStopped;
        {
            Thread thread;
            QObject::connect(&thread, &Thread::threadStopped, [&threadStopped]()
            {
                threadStopped.release();
            });
            EXPECT_TRUE(thread.start());
        }
        EXPECT_TRUE(threadStopped.tryAcquire(1, TIMEOUT_SIGNALS));
    }

    TEST_F(TestThread, StopFailsIfThreadIsNotStarted)
    {
        Thread thread;
        EXPECT_FALSE(thread.stop());
    }

    TEST_F(TestThread, StopFailsIfAlreadyStopped)
    {
        Thread thread;
        EXPECT_TRUE(thread.start());
        EXPECT_TRUE(thread.stop());
        EXPECT_FALSE(thread.stop());
    }

    TEST_F(TestThread, AddRunnableRunObjectsInThread)
    {
        Thread thread;
        auto runnableMock = QSharedPointer<RunnableMock>(new RunnableMock);
        QObject object1, object2, object3;
        EXPECT_CALL(*runnableMock, objects()).Times(1)
                .WillOnce(Return(QList<QObject *>({&object1, &object2, &object3})));
        auto initialObjectThread = object1.thread();
        thread << runnableMock;
        EXPECT_NE(object1.thread(), initialObjectThread);
    }

    TEST_F(TestThread, LoadSumsAllRunnablesLoads)
    {
        Thread thread;
        auto runnableMock1 = QSharedPointer<RunnableMock>(new RunnableMock);
        EXPECT_CALL(*runnableMock1, objects()).Times(1)
                .WillOnce(Return(QList<QObject *>({})));
        EXPECT_CALL(*runnableMock1, load()).Times(2).WillRepeatedly(Return(3));
        thread << runnableMock1;
        EXPECT_EQ(thread.load(), 3);
        auto runnableMock2 = QSharedPointer<RunnableMock>(new RunnableMock);
        EXPECT_CALL(*runnableMock2, objects()).Times(1)
                .WillOnce(Return(QList<QObject *>({})));
        EXPECT_CALL(*runnableMock2, load()).Times(1).WillRepeatedly(Return(5));
        thread << runnableMock2;
        EXPECT_EQ(thread.load(), 8);
    }

    TEST_F(TestThread, DebugOperator)
    {
        Thread thread(123);
        QString text;
        QDebug debug(&text);
        debug.noquote().nospace() << thread;
        EXPECT_TRUE(text == "#123");
    }

}
