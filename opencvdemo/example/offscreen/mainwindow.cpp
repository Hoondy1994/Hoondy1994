#include "mainwindow.h"
#include <QPushButton>
#include <QTimer>
#include <QDateTime>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    videoLabel = new QLabel(this);  // 创建标签来显示视频
    setCentralWidget(videoLabel);   // 设置中央部件为视频标签

    // 打开摄像头
    cap.open(0);  // 0表示默认摄像头
    if (!cap.isOpened()) {
        qDebug() << "Error: Couldn't open the camera.";
        return;
    }

    // 创建并设置定时器来定期捕获摄像头帧
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::captureFrame);  // 每次定时器触发时捕获一帧
    timer->start(30);  // 每30毫秒捕获一次

    // 创建一个按钮，用于保存截图
    QPushButton *captureButton = new QPushButton("Capture Screenshot", this);
    captureButton->setGeometry(10, 10, 150, 40);  // 设置按钮大小和位置
    connect(captureButton, &QPushButton::clicked, [this]() {
        captureFrame();  // 按钮点击时捕获截图
    });
}

MainWindow::~MainWindow()
{
    // 析构函数
    cap.release();  // 释放摄像头
}

void MainWindow::captureFrame()
{
    cv::Mat frame;
    cap >> frame;  // 从摄像头获取一帧

    if (frame.empty()) {
        qDebug() << "Error: Empty frame.";
        return;  // 如果帧为空则返回
    }

    // 将 OpenCV Mat 转换为 QImage
    QImage img = matToQImage(frame);
    if (img.isNull()) {
        qDebug() << "Error: Failed to convert Mat to QImage.";
        return;  // 如果转换失败，则返回
    }
    videoLabel->setPixmap(QPixmap::fromImage(img));  // 显示图像
    videoLabel->setAlignment(Qt::AlignCenter);       // 图像居中显示

    // 每次捕获一帧时保存图像
    QString fileName = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".png";  // 使用当前时间命名截图
    cv::imwrite(fileName.toStdString(), frame);  // 保存截图为 PNG 文件
    qDebug() << "Screenshot saved to: " << fileName;
}

QImage MainWindow::matToQImage(const cv::Mat &mat)
{
    if (mat.empty()) {
        qDebug() << "Error: Empty OpenCV frame.";
        return QImage();  // 如果图像为空，返回空的 QImage
    }

    cv::Mat rgb;
    try {
        cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);  // OpenCV 默认是 BGR 格式，Qt 使用 RGB 格式
    } catch (cv::Exception& e) {
        qDebug() << "Error: Failed to convert Mat to RGB. " << e.what();
        return QImage();
    }

    return QImage(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
}
