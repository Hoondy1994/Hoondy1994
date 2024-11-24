#include "mainwindow.h"

#include <QApplication>
#include <QPainter>

#include <QImage>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QImage image("test.png");
    if (image.isNull()) {
        qDebug() << "Failed to load image!";
        return -1;
    }

    // 创建 QPainter 对象
    QPainter painter(&image);  // 修正后：确保 QPainter 类型完整
    painter.setRenderHint(QPainter::Antialiasing); // 开启抗锯齿

    // 设置字体和颜色
    QFont font("Arial", 30); // 字体：Arial，大小：30
    painter.setFont(font);
    painter.setPen(QColor(255, 0, 0)); // 文字颜色：红色

    // 在指定位置绘制文字
    painter.drawText(50, 100, "Hello, QImage!");

    // 保存结果图片
    image.save("output.png");

    qDebug() << "Text added successfully!";
    return a.exec();
}
