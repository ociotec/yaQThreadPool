/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#ifndef YATP_I_RUNNABLE_H
#define YATP_I_RUNNABLE_H


#include <QObject>


namespace yatp
{

    class IRunnable
    {

    public:

        virtual ~IRunnable() = default;

        virtual void run() = 0;
        virtual QList<QSharedPointer<QObject>> objects() = 0;
        virtual unsigned load() const = 0;

    };

}


#endif
