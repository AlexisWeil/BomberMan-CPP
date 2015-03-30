#ifndef CASEDESTRUCTIONTHREAD_H
#define CASEDESTRUCTIONTHREAD_H

#include<QThread>

class CaseDestructionThread : public QThread
{
    Q_OBJECT
public:
    void run();

signals:
    void signalAnimDestruction();
    void signalFinDestruction();
};

#endif // CASEDESTRUCTIONTHREAD_H
