#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageLabel = new QLabel(this);
    setCentralWidget(imageLabel);

    // 训练 SVM 模型
    trainSVM();

    // 加载图片
    cv::Mat img = cv::imread("test.png"); // 替换为你的图像路径
    if (img.empty()) {
        qDebug() << "Failed to load image!";
        return;
    }

    // 对图像进行分类
    int label = classifyImage(img);
    qDebug() << "Image classified as:" << label;

    // 显示图像
    displayImage(img);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::trainSVM()
{
    // 创建训练数据
    cv::Mat labels = (cv::Mat_<int>(4, 1) << 0, 0, 1, 1); // 两类标签：0 和 1
    cv::Mat trainingData = (cv::Mat_<float>(4, 2) <<
                                50, 50,  // 第一类
                            60, 60,  // 第一类
                            200, 200, // 第二类
                            210, 210  // 第二类
                            );

    // 创建 SVM 模型
    svm = cv::ml::SVM::create();
    svm->setType(cv::ml::SVM::C_SVC);
    svm->setKernel(cv::ml::SVM::LINEAR);
    svm->train(trainingData, cv::ml::ROW_SAMPLE, labels);

    qDebug() << "SVM trained successfully!";
}

int MainWindow::classifyImage(const cv::Mat &image)
{
    // 提取图像的特征（这里为了简单，使用图像尺寸）
    float feature1 = static_cast<float>(image.cols);
    float feature2 = static_cast<float>(image.rows);

    cv::Mat sample = (cv::Mat_<float>(1, 2) << feature1, feature2);
    return static_cast<int>(svm->predict(sample));
}

void MainWindow::displayImage(const cv::Mat &image)
{
    if (image.empty()) {
        qDebug() << "Cannot display an empty image!";
        return;
    }

    cv::Mat rgb;
    if (image.channels() == 1) {
        rgb = image.clone();
    } else if (image.channels() == 3) {
        cv::cvtColor(image, rgb, cv::COLOR_BGR2RGB);
    } else {
        qDebug() << "Unsupported image format!";
        return;
    }

    QImage img((const uchar*)rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    if (img.isNull()) {
        qDebug() << "Failed to convert cv::Mat to QImage!";
        return;
    }

    imageLabel->setPixmap(QPixmap::fromImage(img));
    imageLabel->setAlignment(Qt::AlignCenter);
    qDebug() << "Image displayed successfully!";
}
