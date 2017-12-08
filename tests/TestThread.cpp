/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#include "TestThread.h"
#include "Thread.h"


namespace yatp
{

    TestThread::TestThread()
    {
    }

    TestThread::~TestThread()
    {
    }

    void TestThread::SetUp()
    {
    }

    void TestThread::TearDown()
    {
    }

    TEST_F(TestThread, Constructor)
    {
        Thread thread(123);
        EXPECT_EQ(thread.id(), 123);
        EXPECT_FALSE(thread.isRunning());
    }

}
