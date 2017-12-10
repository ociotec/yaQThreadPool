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

    ThreadPool &ThreadPool::operator <<(const QSharedPointer<IRunnable> &runnable)
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
                Q_ASSERT(thread);
                if ((thread != lessBusyThread) and (thread->load() < lessBusyThread->load()))
                {
                    lessBusyThread = thread;
                }
            }
            *lessBusyThread << runnable;
        }
        return *this;
    }

}
