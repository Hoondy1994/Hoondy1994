#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QPixmap>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageLabel = new QLabel(this);
    setCentralWidget(imageLabel);

    // 加载和美化图像
    std::string imagePath = "test.png"; // 替换为美女图片的路径
    cv::Mat img = loadAndBeautifyImage(imagePath);

    // 显示图像
    displayImage(img);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayImage(const cv::Mat &image)
{
    if (image.empty()) {
        qDebug() << "Cannot display an empty image!";
        return;
    }

    cv::Mat rgb;
    if (image.channels() == 3) {
        cv::cvtColor(image, rgb, cv::COLOR_BGR2RGB);
    } else {
        rgb = image.clone();
    }

    QImage img((const uchar*)rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    if (img.isNull()) {
        qDebug() << "Failed to convert cv::Mat to QImage!";
        return;
    }

    imageLabel->setPixmap(QPixmap::fromImage(img));
    imageLabel->setAlignment(Qt::AlignCenter);
}

cv::Mat MainWindow::loadAndBeautifyImage(const std::string &path)
{
    // 加载图像
    cv::Mat img = cv::imread(path);
    if (img.empty()) {
        qDebug() << "Failed to load image at path:" << QString::fromStdString(path);
        return img;
    }

    // 图像处理 - 美化
    cv::Mat result;
    cv::GaussianBlur(img, result, cv::Size(5, 5), 0); // 应用轻微模糊
    cv::addWeighted(img, 1.5, result, -0.5, 0, result); // 增强对比度
    cv::cvtColor(result, result, cv::COLOR_BGR2HSV); // 转换到 HSV 颜色空间
    std::vector<cv::Mat> channels;
    cv::split(result, channels);
    channels[2] += 20; // 提升亮度
    cv::merge(channels, result);
    cv::cvtColor(result, result, cv::COLOR_HSV2BGR); // 转换回 BGR 空间

    // 添加滤镜效果
    cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
                          1, 1, 1,
                      1, -7, 1,
                      1, 1, 1); // 锐化滤镜
    cv::filter2D(result, result, -1, kernel);

    return result;
}
