/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#ifndef YATP_I_RUNNABLE_H
#define YATP_I_RUNNABLE_H


#include <QList>


class QObject;


namespace yatp
{

    class IRunnable
    {

    public:

        virtual ~IRunnable() { }

        virtual QList<QObject *> objects() = 0;
        virtual unsigned load() const = 0;

    };

}


#endif
