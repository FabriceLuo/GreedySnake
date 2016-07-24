#ifndef GREEDYSNAKE_H
#define GREEDYSNAKE_H

#include <QMainWindow>
#include <vector>

using namespace std;

class QPoint;


class GreedySnake : public QMainWindow
{
    Q_OBJECT

public:
    GreedySnake(QWidget *parent = 0);
    ~GreedySnake();
protected:
    vector<QPoint> *m_snake;
    //debug info
    void printDebugLine();
    void paintEvent(QPaintEvent *event);

private:
    QString     m_windowName;
    QSize       m_windowSize;
    int         m_edgeLength;
    void        initMenuBar();
private slots:
    void startGame();

};

#endif // GREEDYSNAKE_H
