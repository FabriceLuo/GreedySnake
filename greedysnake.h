#ifndef GREEDYSNAKE_H
#define GREEDYSNAKE_H

#include <QMainWindow>
#include <list>

using namespace std;

class QPoint;
class QMenu;
class QAction;

enum SNAKE_MOVE_DIRECTION {
    SNAKE_MOVE_LEFT,
    SNAKE_MOVE_DOWN,
    SNAKE_MOVE_RIGHT,
    SNAKE_MOVE_UP
};

class GreedySnake : public QMainWindow
{
    Q_OBJECT

public:
    GreedySnake(QWidget *parent = 0);
    ~GreedySnake();

    bool enableDebug(bool enable);
protected:
    list<QPoint> m_snake;
    list<QPoint> m_food;
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool generateSnake(list<QPoint> &ve, SNAKE_MOVE_DIRECTION m_snakeDirection);
    bool generateFood(list<QPoint> &food, list<QPoint> &snake);

    bool checkGameOver(list<QPoint> &ve, QPoint head);

private:
    QString         m_windowName;
    QSize           m_windowSize;
    QSize           m_windowUnitSize;
    QSize           m_menubarSize;
    int             m_edgeLength;
    int             m_memberInitLength;
    int             m_snakeMoveTimer;
    int             m_snakeMoveInterval;
    bool            m_enableDebug;
    bool            m_speedFlag;
    int             m_speedMoveInterval;

    SNAKE_MOVE_DIRECTION m_snakeDirection;


    QMenu           *controlMenu;
    QAction         *startAction;
    QAction         *pauseAction;
    QAction         *stopAction;

    void            initMenuBar();
    void            initStatusBar();
    void            initSnakeMember();
    void            drawSnake(QPainter *painter);
    void            gameOver();

    //debug info
    void            echoDebug(QPainter *painter);
    void            drawDebugLine(QPainter *painter);
    void            drawFood(QPainter *painter);


private slots:
    void startGame();
    void stopGame();
    void pauseGame();

};

#endif // GREEDYSNAKE_H
