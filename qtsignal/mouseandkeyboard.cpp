#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

class MyWidget : public QWidget {
public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("QEvent Example");
        setFixedSize(400, 300);
    }

protected:
    // 处理鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override {
        qDebug() << "Mouse pressed at position:" << event->pos();

        if (event->button() == Qt::LeftButton) {
            qDebug() << "Left mouse button clicked!";
        } else if (event->button() == Qt::RightButton) {
            qDebug() << "Right mouse button clicked!";
        }

        // 事件已被接受，不再传递给其他控件
        event->accept();
    }

    // 处理鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event) override {
        qDebug() << "Mouse moved to position:" << event->pos();
    }

    // 处理鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event) override {
        qDebug() << "Mouse released at position:" << event->pos();

        // 如果鼠标右键释放，触发一个自定义操作
        if (event->button() == Qt::RightButton) {
            qDebug() << "Right mouse button released!";
        }

        event->accept();
    }

    // 处理键盘按下事件
    void keyPressEvent(QKeyEvent *event) override {
        qDebug() << "Key pressed:" << event->key();

        // 如果按下的是空格键，打印一条消息
        if (event->key() == Qt::Key_Space) {
            qDebug() << "Space key pressed!";
        }

        event->accept();  // 事件已被处理
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建并显示自定义的窗口
    MyWidget widget;
    widget.show();

    return app.exec();
}
