#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QPushButton>  // 包含 QPushButton

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 手动创建 QLabel 来显示视频
    videoLabel = new QLabel(this);
    videoLabel->setGeometry(10, 10, 640, 480);  // 设置位置和大小
    videoLabel->setAlignment(Qt::AlignCenter);   // 让图像居中显示

    // 手动创建一个启动按钮
    startButton = new QPushButton("Start Camera", this);
    startButton->setGeometry(10, 500, 120, 40);  // 设置按钮位置和大小

    // 连接按钮点击信号到槽函数
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startCamera);

    // 初始化摄像头和人脸检测
    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
        qDebug() << "Error loading face cascade";
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startCamera()
{
    // 打开默认的摄像头
    cap.open(0);
    if (!cap.isOpened()) {
        qDebug() << "Error opening video stream";
        return;
    }

    // 设置定时器每 30ms 采集一次图像
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        cv::Mat frame;
        cap >> frame;  // 从摄像头捕获一帧图像
        if (frame.empty()) {
            qDebug() << "Error capturing frame";
            return;
        }

        // 检测并显示人脸
        detectAndDisplay(frame);

        // 将 OpenCV 的 Mat 数据转换为 QImage
        QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        videoLabel->setPixmap(QPixmap::fromImage(img.rgbSwapped()));  // 设置 QLabel 显示图像
    });
    timer->start(30);  // 每 30 毫秒捕获一帧
}

void MainWindow::detectAndDisplay(cv::Mat &frame)
{
    std::vector<cv::Rect> faces;
    cv::Mat gray;

    // 将图像转换为灰度图像
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    // 均衡直方图以提高对比度
    cv::equalizeHist(gray, gray);

    // 检测人脸
    faceCascade.detectMultiScale(gray, faces);

    // 在检测到的人脸上绘制矩形框
    for (size_t i = 0; i < faces.size(); i++) {
        cv::Rect face = faces[i];
        cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);  // 绘制矩形框
    }
}
