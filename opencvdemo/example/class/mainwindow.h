#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp> // 添加机器学习模块头文件

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
    cv::Ptr<cv::ml::SVM> svm; // SVM 模型

    void displayImage(const cv::Mat &image);
    void trainSVM();  // 训练 SVM 模型
    int classifyImage(const cv::Mat &image); // 对图像分类
};

#endif // MAINWINDOW_H
