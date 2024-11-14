#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QLabel>
#include <QPushButton>

// 前置声明 Worker 类
class Worker;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void startCalculation();  // 发出信号以启动计算

private slots:
    void onStartButtonClicked();  // 启动计算槽函数
    void updateResult(int result);  // 更新结果槽函数

private:
    Worker *worker;        // Worker 实例
    QThread workerThread;  // 工作线程
    QLabel *resultLabel;   // 显示结果的标签
    QPushButton *startButton; // 启动按钮
};

#endif // MAINWINDOW_H
