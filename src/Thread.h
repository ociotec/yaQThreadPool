/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#ifndef YATP_THREAD_H
#define YATP_THREAD_H


#include <QMutex>
#include <QObject>
#include <QThread>

#include "IRunnable.h"


namespace yatp
{

    class Thread : public QObject
    {

        Q_OBJECT

    public:

        Thread(unsigned id, QObject *parent = nullptr);
        virtual ~Thread();

        virtual bool run();
        virtual bool stop();
        virtual bool isRunning() const;
        virtual unsigned id() const;

        virtual Thread &operator <<(const QSharedPointer<IRunnable> &runnable);
        virtual unsigned load() const;

    private slots:

        void threadStarted();

    private:

        unsigned _id;
        QThread _thread;
        QList<QSharedPointer<IRunnable>> _runnables;
        mutable QMutex _runnablesMutex;

    };

}


QDebug operator <<(QDebug debug, const yatp::Thread &thread);


#endif
