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
    : QMainWindow(parent), m_windowName("GreedySnake"), m_windowSize(800, 600), m_edgeLength(20)
{

    setWindowTitle(m_windowName);
    setFixedSize(m_windowSize);
    resize(m_windowSize);
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

    initMenuBar();
    initStatusBar();
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

}

void GreedySnake::pauseGame()
{

}

void GreedySnake::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.setPen(QPen(Qt::black, 12, Qt::DashLine, Qt::RoundCap));
    //painter.drawLine(QPoint(20,20), QPoint(200, 200));

    drawDebugLine(&painter);
}

void GreedySnake::echoDebug()
{
    if(!m_enableDebug)
    {
        return;
    }
    //drawDebugLine();
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











