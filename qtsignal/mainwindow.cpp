#include "MainWindow.h"
#include "Worker.h"
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), worker(new Worker) {
    // 设置窗口布局
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    resultLabel = new QLabel("Result will be shown here", this);
    startButton = new QPushButton("Start Calculation", this);

    layout->addWidget(resultLabel);
    layout->addWidget(startButton);
    setCentralWidget(centralWidget);

    // 将 worker 移动到独立的线程
    worker->moveToThread(&workerThread);

    // 连接信号槽
    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(this, &MainWindow::startCalculation, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &MainWindow::updateResult);

    // 启动后台线程
    workerThread.start();
}

MainWindow::~MainWindow() {
    workerThread.quit();
    workerThread.wait();
    delete worker;
}

void MainWindow::onStartButtonClicked() {
    startButton->setEnabled(false); // 禁用按钮，避免重复点击
    resultLabel->setText("Calculating...");
    emit startCalculation(); // 发射信号启动计算
}

void MainWindow::updateResult(int result) {
    resultLabel->setText("Result: " + QString::number(result));
    startButton->setEnabled(true); // 重新启用按钮
}
