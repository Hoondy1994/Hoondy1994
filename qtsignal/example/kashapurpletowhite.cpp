#include "mainwindow.h"

#include <QApplication>
#include <QPainter>
#include <QImage>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QImage image("test.png");
    if (image.isNull()) {
        qDebug() << "Failed to load image!";
        return -1;
    }

    // 定义目标颜色范围（紫色）
    QColor targetColor(128, 0, 128); // 紫色
    int tolerance = 50; // 颜色容忍度，根据实际图片调整范围

    // 定义替换颜色（白色）
    QColor newColor(255, 255, 255); // 白色

    // 遍历每个像素
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor pixelColor = image.pixelColor(x, y);

            // 判断是否在目标颜色范围内
            if (qAbs(pixelColor.red() - targetColor.red()) <= tolerance &&
                qAbs(pixelColor.green() - targetColor.green()) <= tolerance &&
                qAbs(pixelColor.blue() - targetColor.blue()) <= tolerance) {
                // 替换颜色
                image.setPixelColor(x, y, newColor);
            }
        }
    }

    // 保存修改后的图片
    image.save("output.png");
    qDebug() << "Purple color replaced with white successfully!";
    return 0;
}
