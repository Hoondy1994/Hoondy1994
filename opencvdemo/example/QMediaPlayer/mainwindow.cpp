#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this)),
    player(new QMediaPlayer(this)),   // 创建 QMediaPlayer 对象
    videoWidget(new QVideoWidget(this)) // 创建 QVideoWidget 对象
{
    ui->setupUi(this);

    videoLabel = new QLabel(this);  // 创建用于显示视频的 QLabel
    setCentralWidget(videoLabel);   // 设置为主窗口的中央部件

    videoLabel->setAlignment(Qt::AlignCenter);

    // 加载视频文件
    std::string videoPath = "test.mp4"; // 替换为您的 MP4 文件路径
    if (!video.open(videoPath)) {
        qDebug() << "Failed to open video file:" << QString::fromStdString(videoPath);
        return;
    }

    // 播放器和视频部件的设置
    player->setVideoOutput(videoWidget);  // 设置视频输出为 QVideoWidget
    player->setMedia(QUrl::fromLocalFile(QString::fromStdString(videoPath)));  // 设置视频文件路径
    player->play(); // 播放音频和视频

    videoWidget->resize(640, 480); // 调整视频窗口大小

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
    player->stop();  // 停止播放音频
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
