/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#include "TestThreadPool.h"
#include "ThreadPool.h"


namespace yatp
{

    TestThreadPool::TestThreadPool()
    {
    }

    TestThreadPool::~TestThreadPool()
    {
    }

    void TestThreadPool::SetUp()
    {
    }

    void TestThreadPool::TearDown()
    {
    }

    TEST_F(TestThreadPool, Constructor)
    {
        ThreadPool threadPool;
        EXPECT_EQ(threadPool.threadsCount(), QThread::idealThreadCount());
    }

}
