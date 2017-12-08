/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#include <QDebug>
#include <QMutexLocker>

#include "Thread.h"


namespace yatp
{

    Thread::Thread(unsigned id, QObject *parent) :
        QObject(parent),
        _id(id),
        _runnablesMutex(QMutex::Recursive)
    {
    }

    Thread::~Thread()
    {
        if (isRunning())
        {
            stop();
        }
    }

    bool Thread::run()
    {
        bool ok = false;

        this->moveToThread(&_thread);
        if (isRunning())
        {
            qCritical().noquote() << "Thread" << *this << "is already running";
        }
        else
        {
            _thread.start();
        }

        return ok;
    }

    bool Thread::stop()
    {
        bool ok = false;

        if (not isRunning())
        {
            qCritical().noquote() << "Thread" << *this << "is not running";
        }
        else
        {
            _thread.quit();
            _thread.wait();
            ok = true;
        }

        return ok;
    }

    bool Thread::isRunning() const
    {
        return _thread.isRunning();
    }

    unsigned Thread::id() const
    {
        return _id;
    }

    Thread &Thread::operator <<(const QSharedPointer<IRunnable> &runnable)
    {
        if (runnable)
        {
            QMutexLocker lock(&_runnablesMutex);
            for (auto object : runnable->objects())
            {
                if (object)
                {
                    object->moveToThread(&_thread);
                }
            }
            _runnables << runnable;
        }
        return *this;
    }

    unsigned Thread::load() const
    {
        unsigned loadsSum = 0;
        QMutexLocker lock(&_runnablesMutex);
        for (auto runnable : _runnables)
        {
            if (runnable)
            {
                loadsSum += runnable->load();
            }
        }
        return loadsSum;
    }

    void Thread::threadStarted()
    {
        qInfo().noquote() << "Thread" << *this << "has started";
    }

}


QDebug operator <<(QDebug debug, const yatp::Thread::Thread &thread)
{
    QDebugStateSaver debugStateSaver(debug);
    debug.noquote().nospace() << "#" << thread.id();
    return debug;
}
