#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject {
    Q_OBJECT

public slots:
    void doWork(); // 执行耗时计算

signals:
    void resultReady(int result); // 计算完成后的信号
};

#endif // WORKER_H
