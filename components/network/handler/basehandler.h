#ifndef BASEHANDLER_H
#define BASEHANDLER_H

#include <queue>
#include <QMutex>
#include <QObject>
#include <QThread>
#include <QWaitCondition>

#include "../../../utils/resulthandler.h"

template <typename T>
class BaseHandler {
protected:
    std::queue<T> queue;
    QMutex mutex;
    QThread* thread;
    QWaitCondition queueCondition;
    QWaitCondition processCondition;

    bool isProcessing;
    bool isExternalProcessElem = false;

    void do_process_loop(){
        while (isProcessing){
            QMutexLocker lock(&mutex);
            while (queue.empty()){
                if (!isProcessing)
                    return;
                queueCondition.wait(&mutex);
            }

            T item = queue.front();
            queue.pop();
            lock.unlock();

            process_elem(item);
            if (isExternalProcessElem)
                processCondition.wait(&mutex);
        }
    }
    virtual Result<> process_elem(T elem){return value();}
public:
    BaseHandler() : isProcessing(false) {}
    ~BaseHandler() {if (thread->isRunning()) stop_processing();}
    void add_new_elem(T elem){
        QMutexLocker lock(&mutex);
        queue.push(std::move(elem));
        queueCondition.notify_one();
    }
    void start_processing(){
        if (!isProcessing){
            isProcessing = true;
            thread = QThread::create([this](){do_process_loop();});
            thread->start();
        }
    }
    void stop_processing(){
        if (isProcessing){
            isProcessing = false;
            queueCondition.notify_one();
            thread->quit();
            thread->wait();
        }
    }
};

#endif // BASEHANDLER_H
