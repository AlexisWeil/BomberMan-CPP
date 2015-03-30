#ifndef BOMBERMANMORTTHREAD_H
#define BOMBERMANMORTTHREAD_H

#include <QThread>

class BomberManMortThread : public QThread
{
    Q_OBJECT
public:
    void run();

signals:
    void signalAnimMort();
    void signalFinMort();
};

#endif // BOMBERMANMORTTHREAD_H
