#include "mainwindow.h"
#include "openglwidget.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Qt OpenGL Window Example");

    // 创建一个 OpenGL 渲染区域
    openGLWidget = new OpenGLWidget(this);

    // 设置窗口的布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(openGLWidget);
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    resize(800, 600);  // 设置窗口初始大小
}

MainWindow::~MainWindow()
{
    // 析构函数
}
