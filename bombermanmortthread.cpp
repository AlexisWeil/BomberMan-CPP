#include "bombermanmortthread.h"

void BomberManMortThread::run()
{
    /**************************************************************
    * L'animation de mort du BomberMan commence après 200 ms et
    * appelle la méthode animationMort() du BomberMan correspondant
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
