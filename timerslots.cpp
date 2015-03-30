#include "timerslots.h"
#include <QString>

TimerSlots::TimerSlots(QObject *parent) :
    QObject(parent)
{
    timer = new QTimer(this); // D�clar� dans le *.h
    timer->setInterval(1000); // Une seconde
    connect(timer, SIGNAL(timeout()), this, SLOT(compter()));
    timer->start();
    tonLabel->setText("Il reste 10 secondes"); // Note: c'est ici que la dur�e est d�finie

}

void TimerSlots::compter() // Un slot
{
    int rebours = 100;
    if(rebours > 1)
    {
        rebours--;
        tonLabel->setText("Il reste " + QString::number(rebours) + " secondes");
    }
    else
    {
        tonLabel->setText("Le temps est �coul�");
        timer->stop();
    }
}
