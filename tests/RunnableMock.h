/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#ifndef YATP_RUNNABLE_MOCK_H
#define YATP_RUNNABLE_MOCK_H


#include <gmock/gmock.h>
#include <QList>

#include "IRunnable.h"


class QObject;


namespace yatp
{

    class RunnableMock : public IRunnable
    {

    public:

        virtual ~RunnableMock() { }
        MOCK_METHOD0(run, void());
        MOCK_METHOD0(objects, QList<QObject *>());
        MOCK_CONST_METHOD0(load, unsigned());

    };

}


#endif
