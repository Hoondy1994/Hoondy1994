#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageLabel = new QLabel(this);  // 创建 QLabel 用来显示图像
    setCentralWidget(imageLabel);   // 将 QLabel 设置为中央部件

    // 加载并显示图像
    cv::Mat img = cv::imread("test.png"); // 读取图像
    if (!img.empty()) {
        cv::Mat gray, edges;
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);  // 转换为灰度图像
        cv::Canny(gray, edges, 100, 200);  // 使用 Canny 算法进行边缘检测

        displayImage(edges);  // 显示处理后的图像
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayImage(const cv::Mat &image)
{
    // 将 OpenCV 图像转换为 QImage
    cv::Mat rgb;
    cv::cvtColor(image, rgb, cv::COLOR_BGR2RGB);  // OpenCV 默认使用 BGR，Qt 使用 RGB

    QImage img((const uchar*)rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    imageLabel->setPixmap(QPixmap::fromImage(img));  // 设置 QLabel 显示图像
    imageLabel->setAlignment(Qt::AlignCenter);       // 图像居中显示
}
