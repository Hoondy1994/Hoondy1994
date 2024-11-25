#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <QImage>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void captureFrame();  // 捕获摄像头帧并保存

private:
    cv::VideoCapture cap;  // 摄像头对象
    QLabel *videoLabel;    // 显示视频的标签
    QImage matToQImage(const cv::Mat &mat);  // 将 cv::Mat 转换为 QImage
};

#endif // MAINWINDOW_H
