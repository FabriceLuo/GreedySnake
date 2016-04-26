#ifndef GREEDYSNAKE_H
#define GREEDYSNAKE_H

#include <QMainWindow>

class GreedySnake : public QMainWindow
{
    Q_OBJECT

public:
    GreedySnake(QWidget *parent = 0);
    ~GreedySnake();
protected:

private:
    QString m_windowName;
    QSize m_windowSize;

};

#endif // GREEDYSNAKE_H
