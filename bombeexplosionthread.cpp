#include "bombeexplosionthread.h"

void BombeExplosionThread::run()
{
    /**************************************************************
    * L'animation de disparition des flammes débute après 200 ms
    * et déclanche la méthode animationFinExplosion() de la bombe
    * correspondant à ce thread toutes les 50 ms
    **************************************************************/
    this->msleep(200);

    for(int i = 0 ; i < 3 ; i++)
    {
        this->msleep(50);

        emit signalAnimFinExplosion();
    }

    emit signalFinExplosion();
}

