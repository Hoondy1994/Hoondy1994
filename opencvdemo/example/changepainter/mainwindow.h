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
    QLabel *imageLabel; // 显示图像的 QLabel

    void displayImage(const cv::Mat &image);  // 显示图片函数
    cv::Mat loadAndBeautifyImage(const std::string &path); // 加载并处理图片函数
};

#endif // MAINWINDOW_H
