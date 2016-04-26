#include "greedysnake.h"

#include <QDesktopWidget>
#include <QApplication>

GreedySnake::GreedySnake(QWidget *parent)
    : QMainWindow(parent), m_windowName("GreedySnake"), m_windowSize(800, 600)
{

    setWindowTitle(m_windowName);
    setFixedSize(m_windowSize);
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
}

GreedySnake::~GreedySnake()
{

}
