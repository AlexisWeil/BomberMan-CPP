#ifndef BOMBEEXPLOSIONTHREAD_H
#define BOMBEEXPLOSIONTHREAD_H

#include <QThread>

class BombeExplosionThread : public QThread
{
    Q_OBJECT
public:
    void run();

signals:
    void signalFinExplosion();
    void signalAnimFinExplosion();
};

#endif // BOMBEEXPLOSIONTHREAD_H
