#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

class SnakeGame : public QWidget {
public:
    SnakeGame(QWidget *parent = nullptr)
        : QWidget(parent), direction(Right), gameOver(false), score(0) {
        setWindowTitle("Snake Game");
        resize(400, 400);

        // 初始化蛇
        snake.append(QPoint(5, 5));
        snake.append(QPoint(4, 5));
        snake.append(QPoint(3, 5));

        // 初始化食物位置
        generateFood();

        // 设置定时器，控制蛇的移动
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &SnakeGame::moveSnake);
        timer->start(200); // 200 毫秒移动一次
    }

protected:
    // 键盘事件
    void keyPressEvent(QKeyEvent *event) override {
        if (gameOver) return; // 游戏结束后禁用控制

        switch (event->key()) {
        case Qt::Key_Up:
            if (direction != Down) direction = Up;
            break;
        case Qt::Key_Down:
            if (direction != Up) direction = Down;
            break;
        case Qt::Key_Left:
            if (direction != Right) direction = Left;
            break;
        case Qt::Key_Right:
            if (direction != Left) direction = Right;
            break;
        }
    }

    // 绘图事件
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);

        // 绘制背景
        painter.fillRect(rect(), Qt::white);

        // 绘制蛇
        painter.setBrush(Qt::green);
        for (const QPoint &point : snake) {
            painter.drawRect(point.x() * gridSize, point.y() * gridSize, gridSize, gridSize);
        }

        // 绘制食物
        painter.setBrush(Qt::red);
        painter.drawRect(food.x() * gridSize, food.y() * gridSize, gridSize, gridSize);

        // 显示得分
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(rect(), Qt::AlignTop | Qt::AlignRight, QString("Score: %1").arg(score));

        // 游戏结束提示
        if (gameOver) {
            painter.setPen(Qt::red);
            painter.setFont(QFont("Arial", 20, QFont::Bold));
            painter.drawText(rect(), Qt::AlignCenter, "Game Over");
        }
    }

private:
    enum Direction { Up, Down, Left, Right };

    QList<QPoint> snake;   // 蛇的身体，存储每节的坐标
    QPoint food;           // 食物的坐标
    Direction direction;   // 当前移动方向
    bool gameOver;         // 游戏是否结束
    int score;             // 当前得分
    const int gridSize = 20; // 单位格大小

    // 生成随机食物
    void generateFood() {
        int maxX = width() / gridSize;
        int maxY = height() / gridSize;
        food = QPoint(QRandomGenerator::global()->bounded(maxX),
                      QRandomGenerator::global()->bounded(maxY));
        // 确保食物不生成在蛇的身体上
        while (snake.contains(food)) {
            food = QPoint(QRandomGenerator::global()->bounded(maxX),
                          QRandomGenerator::global()->bounded(maxY));
        }
    }

    // 移动蛇
    void moveSnake() {
        if (gameOver) return;

        // 计算新蛇头位置
        QPoint newHead = snake.first();
        switch (direction) {
        case Up:    newHead.ry() -= 1; break;
        case Down:  newHead.ry() += 1; break;
        case Left:  newHead.rx() -= 1; break;
        case Right: newHead.rx() += 1; break;
        }

        // 判断是否撞墙或撞到自己
        if (newHead.x() < 0 || newHead.x() >= width() / gridSize ||
            newHead.y() < 0 || newHead.y() >= height() / gridSize ||
            snake.contains(newHead)) {
            gameOver = true;
            update();
            return;
        }

        // 添加新蛇头
        snake.prepend(newHead);

        // 判断是否吃到食物
        if (newHead == food) {
            score++;
            generateFood();
        } else {
            snake.removeLast(); // 未吃到食物则移除尾巴
        }

        update(); // 刷新界面
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SnakeGame game;
    game.show();

    return app.exec();
}
