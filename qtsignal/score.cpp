#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

class CatchGame : public QWidget {
public:
    CatchGame(QWidget *parent = nullptr) : QWidget(parent), score(0), targetSize(50) {
        setWindowTitle("Catch the Moving Target!");
        resize(600, 400);

        // 定时器，用于定时移动目标
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &CatchGame::moveTarget);
        timer->start(1000); // 每隔 1 秒移动一次目标

        // 初始化目标位置
        moveTarget();
    }

protected:
    // 鼠标点击事件
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) { // 只响应左键点击
            if (isTargetHit(event->pos())) {
                score++;
                qDebug() << "Target hit! Current score:" << score;
                moveTarget(); // 点击成功后，立即移动目标
            } else {
                qDebug() << "Missed! Current score:" << score;
            }
        }
    }

    // 绘图事件
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);

        // 绘制目标
        painter.setBrush(Qt::red);
        painter.drawRect(targetRect);

        // 显示得分
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(rect(), Qt::AlignTop | Qt::AlignRight, QString("Score: %1").arg(score));
    }

private:
    QRect targetRect;      // 目标的矩形区域
    int score;             // 当前得分
    const int targetSize;  // 目标大小

    // 判断鼠标点击是否命中目标
    bool isTargetHit(const QPoint &pos) {
        return targetRect.contains(pos);
    }

    // 随机移动目标
    void moveTarget() {
        int x = QRandomGenerator::global()->bounded(width() - targetSize);
        int y = QRandomGenerator::global()->bounded(height() - targetSize);
        targetRect = QRect(x, y, targetSize, targetSize); // 更新目标区域
        update(); // 触发重绘
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CatchGame game;
    game.show();

    return app.exec();
}
