#include "bombeexplosionthread.h"

void BombeExplosionThread::run()
{
    /**************************************************************
    * L'animation de disparition des flammes d�bute apr�s 200 ms
    * et d�clanche la m�thode animationFinExplosion() de la bombe
    * correspondant � ce thread toutes les 50 ms
    **************************************************************/
    this->msleep(200);

    for(int i = 0 ; i < 3 ; i++)
    {
        this->msleep(50);

        emit signalAnimFinExplosion();
    }

    emit signalFinExplosion();
}

