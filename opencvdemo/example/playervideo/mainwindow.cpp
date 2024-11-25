#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QPixmap>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this))
{
    ui->setupUi(this);

    videoLabel = new QLabel(this);      // 创建用于显示视频的 QLabel
    setCentralWidget(videoLabel);       // 设置为主窗口的中心部件

    // 加载视频文件
    std::string videoPath = "test2.mp4"; // 替换为您的 MP4 文件路径
    if (!video.open(videoPath)) {
        qDebug() << "Failed to open video file:" << QString::fromStdString(videoPath);
        return;
    }

    // 连接定时器信号到播放槽
    connect(timer, &QTimer::timeout, this, &MainWindow::playVideo);

    // 设置定时器间隔（帧间隔时间 = 1000 / FPS）
    double fps = video.get(cv::CAP_PROP_FPS);
    timer->start(static_cast<int>(1000 / fps));
}

MainWindow::~MainWindow()
{
    delete ui;
    timer->stop();
    video.release(); // 释放视频资源
}

void MainWindow::playVideo()
{
    cv::Mat frame;
    if (video.read(frame)) { // 读取视频帧
        displayFrame(frame); // 显示当前帧
    } else {
        timer->stop();       // 播放结束
        qDebug() << "Video playback finished.";
    }
}

void MainWindow::displayFrame(const cv::Mat &frame)
{
    if (frame.empty()) {
        qDebug() << "Empty frame!";
        return;
    }

    // 转换 BGR -> RGB
    cv::Mat rgb;
    cv::cvtColor(frame, rgb, cv::COLOR_BGR2RGB);

    // 转换为 QImage
    QImage img((const uchar*)rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);

    // 显示在 QLabel 上
    videoLabel->setPixmap(QPixmap::fromImage(img).scaled(videoLabel->size(), Qt::KeepAspectRatio));
}
