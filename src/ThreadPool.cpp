/** Yet another Qt thread pool (YATP).
    @copyright MIT License
    @author Emilio González Montaña <emilio@ociotec.com>
    @see https://github.com/ociotec/yaQThreadPool */


#include <QDebug>

#include "ThreadPool.h"


namespace yatp
{

    ThreadPool::ThreadPool(unsigned threadsCount, QObject *parent) :
        QObject(parent)
    {
        _threads.reserve(threadsCount);
        for (unsigned i = 1; i <= threadsCount; i++)
        {
            _threads.append(QSharedPointer<Thread>(new Thread(i)));
        }
    }

    ThreadPool::~ThreadPool()
    {
    }

    unsigned ThreadPool::threadsCount() const
    {
        return _threads.length();
    }

    ThreadPool &ThreadPool::operator <<(IRunnable &runnable)
    {
        if (_threads.isEmpty())
        {
            qCritical() << "No threads to run with";
        }
        else
        {
            auto lessBusyThread = _threads.first();
            for (auto thread : _threads)
            {
                if (thread->load() < lessBusyThread->load())
                {
                    lessBusyThread = thread;
                }
            }
        }
        return *this;
    }

}
