#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>
#include <QDebug>

class MyWidget : public QWidget {
public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Mouse Click to Display Image");
        setFixedSize(600, 400);

        // 创建一个 QLabel 来显示图片
        imageLabel = new QLabel(this);
        imageLabel->setAlignment(Qt::AlignCenter);  // 设置图片居中显示
        imageLabel->resize(400, 300);  // 设置 QLabel 的大小
    }

protected:
    // 处理鼠标点击事件
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {  // 判断是否是左键点击
            qDebug() << "Mouse clicked at position:" << event->pos();

            // 加载并显示图片
            QPixmap pixmap("test.jpg");  // 通过资源路径加载图片
            if (pixmap.isNull()) {
                qDebug() << "Failed to load image!";
            } else {
                imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio));
                imageLabel->show();
            }
        }
    }

private:
    QLabel *imageLabel;  // 用于显示图片的 QLabel
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWidget widget;
    widget.show();

    return app.exec();
}
