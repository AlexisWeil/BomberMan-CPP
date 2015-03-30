#include "bombermanmortthread.h"

void BomberManMortThread::run()
{
    /**************************************************************
    * L'animation de mort du BomberMan commence apr�s 200 ms et
    * appelle la m�thode animationMort() du BomberMan correspondant
    * toutes les 75 ms
    **************************************************************/
    this->msleep(200);

    for(int i = 0 ; i < 7 ; i++)
    {
        this->msleep(75);

        emit signalAnimMort();
    }

    emit signalFinMort();
}
