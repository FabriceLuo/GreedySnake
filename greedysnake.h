#ifndef GREEDYSNAKE_H
#define GREEDYSNAKE_H

#include <QMainWindow>
#include <vector>

using namespace std;

class QPoint;
class QMenu;
class QAction;

class GreedySnake : public QMainWindow
{
    Q_OBJECT

public:
    GreedySnake(QWidget *parent = 0);
    ~GreedySnake();

    bool enableDebug(bool enable);
protected:
    vector<QPoint> m_snake;
    void paintEvent(QPaintEvent *event);

private:
    QString         m_windowName;
    QSize           m_windowSize;
    QSize           m_windowUnitSize;
    QSize           m_menubarSize;
    int             m_edgeLength;
    int             m_memberInitLength;
    bool            m_enableDebug;


    QMenu           *controlMenu;
    QAction         *startAction;
    QAction         *pauseAction;
    QAction         *stopAction;

    void            initMenuBar();
    void            initStatusBar();
    void            initSnakeMember();
    void            drawSnake(QPainter *painter);

    //debug info
    void            echoDebug(QPainter *painter);
    void            drawDebugLine(QPainter *painter);

private slots:
    void startGame();
    void stopGame();
    void pauseGame();

};

#endif // GREEDYSNAKE_H
