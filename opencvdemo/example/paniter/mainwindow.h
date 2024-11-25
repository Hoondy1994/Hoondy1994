#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
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

private:
    Ui::MainWindow *ui;
    QLabel *imageLabel; // 用于显示图像

    void displayImage(const cv::Mat &image); // 显示图像函数
    cv::Mat drawWoman(); // 绘制卡通风格的“美女”
};

#endif // MAINWINDOW_H
