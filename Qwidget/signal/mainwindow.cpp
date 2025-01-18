#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QAction>
#include <QMenu>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    // 创建一个 QAction 对象
    QAction *action = new QAction("Click Me", this);

    // 创建一个按钮，并将其设置为菜单
    QPushButton *button = new QPushButton("Press Me", this);
    button->setMenu(new QMenu(this));
    button->menu()->addAction(action);

    // 连接 QAction 的 triggered 信号到槽
    connect(action, &QAction::triggered, this, &MyWidget::onActionTriggered);

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(button);
    setLayout(layout);
}

void MyWidget::onActionTriggered() {
    qDebug() << "QAction triggered!";
}
