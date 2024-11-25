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

    // 创建卡通风格的"美女"图像
    cv::Mat img = drawWoman();

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

cv::Mat MainWindow::drawWoman()
{
    // 创建一张空白画布
    cv::Mat canvas(500, 400, CV_8UC3, cv::Scalar(255, 255, 255)); // 白色背景

    // 绘制脸部（椭圆）
    cv::ellipse(canvas, cv::Point(200, 200), cv::Size(100, 120), 0, 0, 360, cv::Scalar(240, 200, 180), -1);

    // 绘制眼睛
    cv::circle(canvas, cv::Point(160, 180), 10, cv::Scalar(255, 255, 255), -1); // 左眼白
    cv::circle(canvas, cv::Point(160, 180), 5, cv::Scalar(0, 0, 0), -1);       // 左眼黑
    cv::circle(canvas, cv::Point(240, 180), 10, cv::Scalar(255, 255, 255), -1); // 右眼白
    cv::circle(canvas, cv::Point(240, 180), 5, cv::Scalar(0, 0, 0), -1);       // 右眼黑

    // 绘制嘴巴
    cv::ellipse(canvas, cv::Point(200, 240), cv::Size(40, 20), 0, 0, 180, cv::Scalar(0, 0, 255), 2);

    // 绘制头发（长方形 + 椭圆）
    cv::rectangle(canvas, cv::Point(100, 100), cv::Point(300, 170), cv::Scalar(0, 0, 0), -1); // 上方头发
    cv::ellipse(canvas, cv::Point(200, 160), cv::Size(120, 150), 0, 180, 360, cv::Scalar(0, 0, 0), -1);

    // 绘制鼻子
    cv::line(canvas, cv::Point(200, 190), cv::Point(200, 220), cv::Scalar(0, 0, 0), 2);

    // 添加眉毛
    cv::line(canvas, cv::Point(140, 160), cv::Point(180, 170), cv::Scalar(0, 0, 0), 2); // 左眉毛
    cv::line(canvas, cv::Point(220, 170), cv::Point(260, 160), cv::Scalar(0, 0, 0), 2); // 右眉毛

    return canvas;
}
