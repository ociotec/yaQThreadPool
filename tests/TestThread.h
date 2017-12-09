/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#ifndef YATP_TEST_THREAD_H
#define YATP_TEST_THREAD_H


#include <gtest/gtest.h>


namespace yatp
{

    class TestThread : public ::testing::Test
    {

    protected:

      virtual void SetUp();
      virtual void TearDown();

    };

}


#endif
