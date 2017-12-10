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
        moveToThread(&_thread);
        connect(&_thread, &QThread::started, [this]()
        {
            qInfo().noquote() << "Thread" << *this << "has started";
            emit threadStarted();
        });
        connect(&_thread, &QThread::finished, [this]()
        {
            qInfo().noquote() << "Thread" << *this << "has stopped";
            emit threadStopped();
        });
    }

    Thread::~Thread()
    {
        if (isStarted())
        {
            stop();
        }
    }

    unsigned Thread::id() const
    {
        return _id;
    }

    bool Thread::start()
    {
        bool ok = false;

        if (isStarted())
        {
            qCritical().noquote() << "Thread" << *this << "is already started";
        }
        else
        {
            _thread.start();
            ok = true;
        }

        return ok;
    }

    bool Thread::stop()
    {
        bool ok = false;

        if (not isStarted())
        {
            qCritical().noquote() << "Thread" << *this << "is not running";
        }
        else
        {
            _thread.quit();
            _thread.wait();
            emit threadStopped();
            ok = true;
        }

        return ok;
    }

    bool Thread::isStarted() const
    {
        return _thread.isRunning();
    }

    Thread &Thread::operator <<(const QSharedPointer<IRunnable> &runnable)
    {
        if (runnable)
        {
            QMutexLocker lock(&_runnablesMutex);
            for (auto object : runnable->objects())
            {
                if (nullptr != object)
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

}


QDebug operator <<(QDebug debug, const yatp::Thread::Thread &thread)
{
    QDebugStateSaver debugStateSaver(debug);
    debug.noquote().nospace() << "#" << thread.id();
    return debug;
}
