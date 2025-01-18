#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QAction>

class MyWidget : public QWidget
{
    Q_OBJECT  // 必须有这个宏

public:
    explicit MyWidget(QWidget *parent = nullptr);

private slots:
    // QAction 被触发时的槽函数
    void onActionTriggered();
};

#endif // MYWIDGET_H
