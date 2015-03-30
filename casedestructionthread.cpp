#include "casedestructionthread.h"

void CaseDestructionThread::run()
{
    // Le thread va appeler la fonction animationDestruction() de sa case toutes les 50 ms
    for(int i = 0 ; i < 7 ; i++)
    {
        emit signalAnimDestruction();

        this->msleep(50);
    }

    emit signalFinDestruction();
}
