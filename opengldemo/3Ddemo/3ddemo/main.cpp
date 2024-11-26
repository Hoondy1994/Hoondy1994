#include <QApplication>
#include "openglwidget.h"
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow mainWindow;
    OpenGLWidget *openGLWidget = new OpenGLWidget(&mainWindow);
    mainWindow.setCentralWidget(openGLWidget);
    mainWindow.resize(800, 600);
    mainWindow.setWindowTitle("Qt OpenGL 3D Example");

    mainWindow.show();
    return a.exec();
}

