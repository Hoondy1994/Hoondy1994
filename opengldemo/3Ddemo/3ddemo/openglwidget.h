#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QTimer>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QOpenGLShaderProgram *program;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QTimer *timer;
    float angle;
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;
};

#endif // OPENGLWIDGET_H
