#include <QApplication>
#include <QAction>
#include <QWidget>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include "mainwindow.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建并显示主窗口
    MyWidget widget;
    widget.resize(300, 500);
    widget.show();

    return app.exec();
}


