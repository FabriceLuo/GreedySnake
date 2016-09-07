#include "greedysnake.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QMenuBar>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QStyle>
#include <QPaintEvent>
#include <QWidget>
#include <cstdlib>
#include <ctime>

GreedySnake::GreedySnake(QWidget *parent)
    : QMainWindow(parent), m_windowName("GreedySnake"), m_windowUnitSize(40, 30),
      m_edgeLength(20), m_memberInitLength(5), m_snakeMoveInterval(1000),
      m_snakeDirection(SNAKE_MOVE_RIGHT),m_speedMoveInterval(100)
{

    setWindowTitle(m_windowName);

    m_windowSize = QSize(m_windowUnitSize.width() * m_edgeLength, m_windowUnitSize.height() * m_edgeLength);
    setFixedSize(m_windowSize);

    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

    m_food.empty();

    initMenuBar();
    initStatusBar();
    initSnakeMember();

    enableDebug(true);
}

GreedySnake::~GreedySnake()
{

}

void GreedySnake::initMenuBar()
{
    QMenuBar *menu=menuBar();

    controlMenu = new QMenu("Control");

    startAction= new QAction("Start", this);
    connect(startAction, SIGNAL(triggered(bool)),this, SLOT(startGame()));
    controlMenu->addAction(startAction);

    pauseAction= new QAction("Pause", this);
    connect(pauseAction, SIGNAL(triggered(bool)),this, SLOT(pauseGame()));
    controlMenu->addAction(pauseAction);

    stopAction= new QAction("Stop", this);
    connect(stopAction, SIGNAL(triggered(bool)),this, SLOT(stopGame()));
    controlMenu->addAction(stopAction);

    menu->addMenu(controlMenu);
}

void GreedySnake::startGame()
{

    pauseAction->setDisabled(false);
    stopAction->setDisabled(false);
    if(0 == QString::compare(startAction->text(), tr("Restart")))
    {
        m_snake.clear();
        m_food.clear();

        initSnakeMember();
    }
    else
    {
        startAction->setText(tr("Restart"));
    }
    m_snakeMoveTimer = startTimer(m_snakeMoveInterval);
}

void GreedySnake::stopGame()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Stop Game"));
    msgBox.setText("Are you sure to stop game");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if(msgBox.exec() != QMessageBox::Yes)
    {
        return;
    }

    m_snake.clear();
    m_food.clear();
    if(m_snakeMoveTimer > 0)
    {
        killTimer(m_snakeMoveTimer);
        m_snakeMoveTimer = 0;

        startAction->setText(tr("start"));
        pauseAction->setDisabled(true);
        stopAction->setDisabled(true);
    }
    setStatusTip(tr("Please start game"));
}

void GreedySnake::pauseGame()
{
    if(m_snakeMoveTimer > 0)
    {
        killTimer(m_snakeMoveTimer);
        m_snakeMoveTimer = 0;

        startAction->setText(tr("Continue"));
    }
}

void GreedySnake::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.setPen(QPen(Qt::black, 12, Qt::DashLine, Qt::RoundCap));
    //painter.drawLine(QPoint(20,20), QPoint(200, 200));

    echoDebug(&painter);
    drawSnake(&painter);
    drawFood(&painter);
}

void GreedySnake::echoDebug(QPainter *painter)
{
    if(!m_enableDebug)
    {
        return;
    }
    drawDebugLine(painter);
}

void GreedySnake::drawDebugLine(QPainter *painter)
{
    QPoint startPoint(0, 0), endPoint(0, 0);
    //draw raw
    endPoint.setX(m_windowSize.width());

    while(startPoint.y() < m_windowSize.height())
    {
        endPoint.setY(startPoint.y());
        painter->drawLine(startPoint, endPoint);
        startPoint.setY(startPoint.y() + m_edgeLength);
    }

    //draw col
    startPoint.setX(m_edgeLength);
    //style()->pixelMetric(QStyle::PM_TitleBarHeight)
    startPoint.setY(0);

    while(startPoint.x() < m_windowSize.width())
    {
        endPoint.setX(startPoint.x());
        painter->drawLine(startPoint, endPoint);
        startPoint.setX(startPoint.x() + m_edgeLength);
    }


}

void GreedySnake::initStatusBar()
{
    statusBar()->showMessage("Ready");
}

bool GreedySnake::enableDebug(bool enable)
{
    m_enableDebug = enable;
    return m_enableDebug;
}

void GreedySnake::initSnakeMember()
{
    for(int i = 0; i < m_memberInitLength; i++)
    {
        if(i < m_windowUnitSize.width())
        {
            m_snake.push_front(QPoint(i, 0));
        }
    }
}

void GreedySnake::drawSnake(QPainter *painter)
{
    list<QPoint>::iterator start = m_snake.begin();
    list<QPoint>::iterator end   = m_snake.end();
    painter->setBrush(QBrush(Qt::black));
    while(start != end)
    {
        painter->drawRect(start->x() * m_edgeLength, start->y() * m_edgeLength, m_edgeLength, m_edgeLength);
        start++;
    }
}

void GreedySnake::timerEvent(QTimerEvent *event)
{
    int timerId = event->timerId();
    if(timerId == m_snakeMoveTimer)
    {
        generateSnake(m_snake, m_snakeDirection);
        //QMessageBox::aboutQt(this, tr("xxxxxxxx"));
        if(m_food.size() == 0)
        {
            //QMessageBox::aboutQt(this, tr("xxxxxxxx"));
            generateFood(m_food, m_snake);
        }
        repaint();
    }
}

bool GreedySnake::generateSnake(list<QPoint> &li, SNAKE_MOVE_DIRECTION m_snakeDirection)
{
    QPoint head = li.front();

    switch (m_snakeDirection) {
    case SNAKE_MOVE_LEFT:
        head.setX(head.x() -1 );
        break;
    case SNAKE_MOVE_DOWN:
        head.setY(head.y() +1 );
        break;
    case SNAKE_MOVE_RIGHT:
        head.setX(head.x() +1 );
        break;
    case SNAKE_MOVE_UP:
        head.setY(head.y() -1 );
        break;
    default:
        break;
    }
    //check game over
    if(checkGameOver(m_snake, head))
    {
        gameOver();
        return true;
    }

    li.push_front(head);
    //check snake eat food
    list<QPoint>::iterator start = m_food.begin();
    list<QPoint>::iterator end = m_food.end();
    while(start != end)
    {
        if(*start == head)
        {
            m_food.erase(start);
            return true;
        }
        start++;
    }

    li.pop_back();
    return true;
}

void GreedySnake::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        m_snakeDirection = SNAKE_MOVE_LEFT;
        m_speedFlag = true;
        break;
    case Qt::Key_Right:
        m_snakeDirection = SNAKE_MOVE_RIGHT;
        m_speedFlag = true;
        break;
    case Qt::Key_Up:
        m_snakeDirection = SNAKE_MOVE_UP;
        m_speedFlag = true;
        break;
    case Qt::Key_Down:
        m_snakeDirection = SNAKE_MOVE_DOWN;
        m_speedFlag = true;
        break;
    default:
        break;
    }
    if(m_speedFlag && m_snakeMoveTimer > 0)
    {
        killTimer(m_snakeMoveTimer);
        m_snakeMoveTimer = startTimer(m_speedMoveInterval);
    }
}

bool GreedySnake::generateFood(list<QPoint> &food, list<QPoint> &snake)
{
    int foodMaxCount = 1;
    int foodNowCount = 0;

    srand(time(0));
    while(foodNowCount < foodMaxCount)
    {

        int x = (int)(rand() * 1.0 / RAND_MAX * m_windowUnitSize.width());
        int y = (int)(rand() * 1.0 / RAND_MAX * m_windowUnitSize.height());

        list<QPoint>::iterator start = snake.begin();
        list<QPoint>::iterator end   = snake.end();

        while(start != end)
        {
            if(start->x() == x && start->y() == y)
            {
                break;
            }
            start++;
        }
        if(start == end)
        {
            food.push_back(QPoint(x, y));
            foodNowCount++;
        }
    }

    return true;
}

bool GreedySnake::checkGameOver(list<QPoint> &ve, QPoint head)
{
    //check eat self
    list<QPoint>::iterator start = ve.begin();
    list<QPoint>::iterator end   = ve.end();

    while(start != end)
    {
        if(start->x() == head.x() && start->y() == head.y())
        {
            return true;
        }
        start++;
    }

    //check zzzzz
    if(head.x() > m_windowUnitSize.width() || head.x() < 0 || head.y() > m_windowUnitSize.height() || head.y() < 0)
    {
        return true;
    }
    return false;
}

void GreedySnake::gameOver()
{

    killTimer(m_snakeMoveTimer);

    m_snake.empty();

    pauseAction->setDisabled(true);
    stopAction->setDisabled(true);

    setStatusTip(tr("the game is over, please to restart"));
    QMessageBox::information(this, tr("GreedySnake"), tr("Game Over"));
}

void GreedySnake::drawFood(QPainter *painter)
{

    list<QPoint>::iterator start = m_food.begin();
    list<QPoint>::iterator end   = m_food.end();

    painter->setBrush(QBrush(Qt::red));
    while(start != end)
    {
        painter->drawRect(start->x() * m_edgeLength, start->y() * m_edgeLength, m_edgeLength, m_edgeLength);
        start++;
    }
}

void GreedySnake::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        if(m_speedFlag && m_snakeMoveTimer > 0)
        {
            m_speedFlag = false;
            killTimer(m_snakeMoveTimer);
            m_snakeMoveTimer = startTimer(m_snakeMoveInterval);
        }
        break;
    default:
        break;
    }
}


























