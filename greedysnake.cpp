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

GreedySnake::GreedySnake(QWidget *parent)
    : QMainWindow(parent), m_windowName("GreedySnake"), m_windowUnitSize(40, 30),
      m_edgeLength(20), m_memberInitLength(5)
{

    setWindowTitle(m_windowName);

    m_windowSize = QSize(m_windowUnitSize.width() * m_edgeLength, m_windowUnitSize.height() * m_edgeLength);
    setFixedSize(m_windowSize);

    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

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

}

void GreedySnake::stopGame()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Stop Game"));
    msgBox.setText("Are you sure to stop game");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes)
    {
        setStatusTip(tr("Please start game"));
    }
}

void GreedySnake::pauseGame()
{

}

void GreedySnake::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.setPen(QPen(Qt::black, 12, Qt::DashLine, Qt::RoundCap));
    //painter.drawLine(QPoint(20,20), QPoint(200, 200));

    echoDebug(&painter);
    drawSnake(&painter);
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
            m_snake.push_back(QPoint(i, 0));
        }
    }
}

void GreedySnake::drawSnake(QPainter *painter)
{
    vector<QPoint>::iterator start = m_snake.begin();
    vector<QPoint>::iterator end   = m_snake.end();
    painter->setBrush(QBrush(Qt::black));
    while(start != end)
    {
        painter->drawRect(start->x() * m_edgeLength, start->y() * m_edgeLength, m_edgeLength, m_edgeLength);
        start++;
    }
}








