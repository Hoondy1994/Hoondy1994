#include "openglwidget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QKeyEvent>
#include <QTimer>
#include <QMatrix4x4>
#include <QDebug>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
    program(nullptr),
    vbo(QOpenGLBuffer::VertexBuffer)
{
    angle = 0.0f;  // 初始化角度
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        this->update();  // 显式调用 update
    }); // 连接 QTimer 的 timeout 信号和 update 槽
    timer->start(16);  // 每 16 毫秒更新一次 (~60fps)
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    vbo.destroy();
    vao.destroy();
    delete program;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();  // 初始化 OpenGL 函数

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // 设置背景颜色
    glEnable(GL_DEPTH_TEST);  // 启用深度测试

    // 加载着色器程序
    program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex_shader.glsl");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");
    program->link();
    program->bind();

    // 创建顶点数据
    GLfloat vertices[] = {
        // 顶点坐标         // 颜色
        0.0f,  0.5f,  0.0f,  1.0f, 0.0f, 0.0f,  // 顶部
        -0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  // 左下
        0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f   // 右下
    };

    // 创建并绑定 VBO 和 VAO
    vao.create();
    vbo.create();
    vao.bind();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));

    program->enableAttributeArray(1);
    program->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    vao.release();
    program->release();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);  // 设置视口大小
    projection.setToIdentity();
    projection.perspective(45.0f, (float)w / h, 0.1f, 100.0f);
    view.setToIdentity();
    view.lookAt(QVector3D(0.0f, 0.0f, 5.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 清除颜色和深度缓冲

    program->bind();
    vao.bind();

    model.setToIdentity();
    model.rotate(angle, 0.0f, 1.0f, 0.0f);  // 绕 Y 轴旋转

    // 设置投影、视图和模型矩阵
    program->setUniformValue("projection", projection);
    program->setUniformValue("view", view);
    program->setUniformValue("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 3);  // 绘制三角形

    vao.release();
    program->release();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();  // 按下 ESC 键退出
    }
}
