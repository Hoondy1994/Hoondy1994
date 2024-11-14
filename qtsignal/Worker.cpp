#include "Worker.h"
#include <QDebug>

void Worker::doWork() {
    // qDebug() << "Worker thread ID:" << QThread::currentThreadId();
    int result = 0;
    for (int i = 0; i < 100000000; ++i) {
        result += i;
    }
    _sleep(5000);
    emit resultReady(result); // 发射信号返回结果
    qDebug() << "Calculation complete, result:" << result;
}
