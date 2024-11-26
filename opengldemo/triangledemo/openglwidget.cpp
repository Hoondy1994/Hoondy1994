#include "openglwidget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    // 构造函数，设置窗口初始化属性
}

OpenGLWidget::~OpenGLWidget()
{
    // 析构函数
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();  // 初始化 OpenGL 函数

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 设置背景颜色为黑色

    glEnable(GL_DEPTH_TEST);  // 启用深度测试
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);  // 设置视口大小
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 清除颜色和深度缓冲

    // 绘制一个彩色三角形
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);  // 红色
    glVertex3f(-0.6f, -0.6f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);  // 绿色
    glVertex3f( 0.6f, -0.6f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);  // 蓝色
    glVertex3f( 0.0f,  0.6f, 0.0f);
    glEnd();
}
