/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#include "RunnableMock.h"
#include "TestThreadPool.h"
#include "ThreadPool.h"


using ::testing::AtLeast;
using ::testing::Return;


namespace yatp
{

    void TestThreadPool::SetUp()
    {
    }

    void TestThreadPool::TearDown()
    {
    }

    TEST_F(TestThreadPool, ConstructorCreatesAsManyThreadsIdealThreadCount)
    {
        ThreadPool threadPool;
        EXPECT_EQ(threadPool.threadsCount(), QThread::idealThreadCount());
    }

    TEST_F(TestThreadPool, ConstructorCreatesAsManyThreadsAsRequired)
    {
        ThreadPool threadPool(5);
        EXPECT_EQ(threadPool.threadsCount(), 5);
    }

    TEST_F(TestThreadPool, AddRunnableIsIgnoredIfThreasCountIsZero)
    {
        ThreadPool threadPool(0);
        auto runnableMock = new RunnableMock();
        QSharedPointer<IRunnable> runnable(runnableMock);
        EXPECT_CALL(*runnableMock, objects()).Times(0);
        threadPool << runnable;
    }

    TEST_F(TestThreadPool, AddRunnableIsAddedToANewThread)
    {
        ThreadPool threadPool(4);
        QObject object1, object2, object3;
        auto runnableMock = new RunnableMock();
        QSharedPointer<IRunnable> runnable(runnableMock);
        EXPECT_CALL(*runnableMock, objects()).Times(1)
                .WillOnce(Return(QList<QObject *>({&object1, &object2, &object3})));
        auto initialObjectThread = object1.thread();
        threadPool << runnable;
        EXPECT_NE(object1.thread(), initialObjectThread);
    }

    TEST_F(TestThreadPool, AddRunnableChecksThreadsLoad)
    {
        ThreadPool threadPool(2);

        QObject object1;
        auto runnableMock1 = new RunnableMock();
        QSharedPointer<IRunnable> runnable1(runnableMock1);
        EXPECT_CALL(*runnableMock1, objects()).Times(1).WillOnce(Return(QList<QObject *>({&object1})));
        EXPECT_CALL(*runnableMock1, load()).Times(AtLeast(1)).WillRepeatedly(Return(5));
        threadPool << runnable1;

        QObject object2;
        auto runnableMock2 = new RunnableMock();
        QSharedPointer<IRunnable> runnable2(runnableMock2);
        EXPECT_CALL(*runnableMock2, objects()).Times(1).WillOnce(Return(QList<QObject *>({&object2})));
        EXPECT_CALL(*runnableMock2, load()).Times(AtLeast(1)).WillRepeatedly(Return(3));
        threadPool << runnable2;

        QObject object3;
        auto runnableMock3 = new RunnableMock();
        QSharedPointer<IRunnable> runnable3(runnableMock3);
        EXPECT_CALL(*runnableMock3, objects()).Times(1).WillOnce(Return(QList<QObject *>({&object3})));
        EXPECT_CALL(*runnableMock3, load()).Times(0);
        threadPool << runnable3;

        EXPECT_NE(object1.thread(), object2.thread());
        EXPECT_NE(object1.thread(), object3.thread());
        EXPECT_EQ(object2.thread(), object3.thread());
    }

}
