#include "greedysnake.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QPen>

GreedySnake::GreedySnake(QWidget *parent)
    : QMainWindow(parent), m_windowName("GreedySnake"), m_windowSize(800, 600), m_edgeLength(20)
{

    setWindowTitle(m_windowName);
    //setFixedSize(m_windowSize);
    resize(m_windowSize);
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

    initMenuBar();
}

GreedySnake::~GreedySnake()
{

}

void GreedySnake::initMenuBar()
{
    QMenuBar *menu=menuBar();

    QMenu *controlMenu = new QMenu("Control");
    QAction *startAction= new QAction("Start", this);
    connect(startAction, SIGNAL(triggered(bool)),this, SLOT(startGame()));
    controlMenu->addAction(startAction);

    menu->addMenu(controlMenu);
}

void GreedySnake::startGame()
{

}

void GreedySnake::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 12, Qt::DashLine, Qt::RoundCap));
    painter.drawLine(QPoint(20,20), QPoint(200, 200));
}












