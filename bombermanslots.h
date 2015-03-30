#ifndef BOMBERMANSLOTS_H
#define BOMBERMANSLOTS_H

#include <QObject>
#include <QString>
#include <QTimer>

#include "bomberman.h"

class BomberMan;

class BomberManSlots : public QObject
{
    Q_OBJECT
public:
    BomberManSlots(BomberMan* bomberMan);
    ~BomberManSlots();
    BomberMan* getBomberMan();
    void setBomberMan(BomberMan* bomberMan);
    QTimer* getTimerAnim();
    QTimer* getTimerMvt();
    QString getDirection();
    void setDirection(QString direction);
    int getTokenMvt();
    void setTokenMvt(int tokenMvt);
    int getTokenMort();
    void setTokenMort(int tokenMort);

public slots:
    void startTimers(QString direction);
    void animation();
    void stopTimers();
    void animationStop();
    void animationMort();
    void finMort();

private:
    BomberMan* bomberMan;
    int tokenMvt, tokenMort;
    QTimer *timerAnim;
    QTimer *timerMvt;
    QString direction;
};

#endif // BOMBERMANSLOTS_H

