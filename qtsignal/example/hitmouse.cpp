#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

class WhackAMoleGame : public QWidget {
public:
    WhackAMoleGame(QWidget *parent = nullptr) : QWidget(parent), score(0), activeHole(-1) {
        setWindowTitle("Whack-A-Mole!");
        resize(600, 400);

        // 定时器用于更新地鼠位置
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &WhackAMoleGame::updateMolePosition);
        timer->start(1000); // 每秒随机切换地鼠位置

        // 初始化洞的位置
        initializeHoles();
    }

protected:
    // 鼠标点击事件
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) { // 只响应左键点击
            if (isMoleHit(event->pos())) {
                score++;
                qDebug() << "Mole hit! Current score:" << score;
                activeHole = -1; // 隐藏地鼠
                update();        // 刷新界面
            } else {
                qDebug() << "Missed! Current score:" << score;
            }
        }
    }

    // 绘图事件
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);

        // 绘制洞
        painter.setBrush(Qt::darkGray);
        for (const QRect &hole : holes) {
            painter.drawEllipse(hole);
        }

        // 绘制地鼠
        if (activeHole != -1) {
            painter.setBrush(Qt::red);
            painter.drawEllipse(holes[activeHole]);
        }

        // 显示得分
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(rect(), Qt::AlignTop | Qt::AlignRight, QString("Score: %1").arg(score));
    }

private:
    QVector<QRect> holes; // 洞的位置列表
    int activeHole;       // 当前有地鼠的洞索引
    int score;            // 得分

    // 初始化洞的位置
    void initializeHoles() {
        int holeRadius = 50;
        int rows = 3, cols = 3;
        int spacingX = width() / (cols + 1);
        int spacingY = height() / (rows + 1);

        for (int row = 1; row <= rows; ++row) {
            for (int col = 1; col <= cols; ++col) {
                int x = col * spacingX - holeRadius / 2;
                int y = row * spacingY - holeRadius / 2;
                holes.append(QRect(x, y, holeRadius, holeRadius));
            }
        }
    }

    // 更新地鼠位置
    void updateMolePosition() {
        activeHole = QRandomGenerator::global()->bounded(holes.size()); // 随机选择一个洞
        update(); // 刷新界面
    }

    // 判断鼠标点击是否命中地鼠
    bool isMoleHit(const QPoint &pos) {
        if (activeHole != -1 && holes[activeHole].contains(pos)) {
            return true;
        }
        return false;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    WhackAMoleGame game;
    game.show();

    return app.exec();
}
