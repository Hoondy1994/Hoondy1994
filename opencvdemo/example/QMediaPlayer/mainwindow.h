#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QLabel>
#include <QTimer>
#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void playVideo(); // 播放视频

private:
    Ui::MainWindow *ui;
    QLabel *videoLabel;     // 显示视频的 QLabel
    QTimer *timer;          // 控制帧播放速度的定时器
    cv::VideoCapture video; // OpenCV 视频捕获对象

    void displayFrame(const cv::Mat &frame); // 显示帧的方法

    QMediaPlayer *player;    // 播放音频
    QVideoWidget *videoWidget; // 视频显示部件
};

#endif // MAINWINDOW_H
