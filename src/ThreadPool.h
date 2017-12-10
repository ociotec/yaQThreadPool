/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#ifndef YATP_THREAD_POOL_H
#define YATP_THREAD_POOL_H


#include <QList>
#include <QObject>
#include <QSharedPointer>

#include "IRunnable.h"
#include "Thread.h"


namespace yatp
{

    class ThreadPool : public QObject
    {

        Q_OBJECT

    public:

        ThreadPool(unsigned threadsCount = QThread::idealThreadCount(), QObject *parent = nullptr);
        virtual ~ThreadPool();

        virtual unsigned threadsCount() const;
        virtual ThreadPool &operator <<(const QSharedPointer<IRunnable> &runnable);

    private:

        QList<QSharedPointer<Thread>> _threads;

    };

}


#endif
