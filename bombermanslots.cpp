#include "bombermanslots.h"
#include "partiegui.h"

BomberManSlots::BomberManSlots(BomberMan* bomberMan)
{
    this->bomberMan = bomberMan;
    this->tokenMvt = 0;
    this->tokenMort = 1;
    this->direction = "Stable";

    // L'interval des timers est mise en fonction de la vitesse du BomberMan
    this->timerAnim = new QTimer(this);
    this->timerAnim->setInterval((10 - this->getBomberMan()->getVitesse()) * 25);
    QObject::connect(this->timerAnim, SIGNAL(timeout()), this, SLOT(animation()));

    this->timerMvt = new QTimer(this);
    this->timerMvt->setInterval((10 - this->getBomberMan()->getVitesse()) * 8);
    QObject::connect(this->timerMvt, SIGNAL(timeout()), this->getBomberMan(), SLOT(deplacer()));
}

BomberManSlots::~BomberManSlots()
{
    delete this->timerAnim;
    delete this->timerMvt;
}

void BomberManSlots::startTimers(QString direction)
{
    this->setDirection(direction);
    this->getTimerAnim()->start();
    this->getTimerMvt()->start();
    this->animation();
}

void BomberManSlots::animation()
{
    // Si le BomberMan n'est pas mort, on bouge son image pour créer un effet de mouvement
    if(!this->getBomberMan()->isMort())
    {
        int base;
        QString direction = this->getDirection();

        if(direction == "Down")
        {
            base = -45;
        }
        else if(direction == "Up")
        {
            base = -180;
        }
        else if(direction == "Right")
        {
            base = -315;
        }
        else if(direction == "Left")
        {
            base = -450;
        }

        this->getBomberMan()->getImage()->move((base - this->tokenMvt*45),0);

        if(this->tokenMvt == 0)
            this->tokenMvt++;
        else
            this->tokenMvt = 0;
    }
}

void BomberManSlots::animationMort()
{
    switch(this->tokenMort)
    {
    case 1:
        this->bomberMan->getImage()->move(-48,0);
        break;
    case 2:
        this->bomberMan->getImage()->move(-96,0);
        break;
    case 3:
        this->bomberMan->getImage()->move(-144,0);
        break;
    case 4:
        this->bomberMan->getImage()->move(-192,0);
        break;
    case 5:
        this->bomberMan->getImage()->move(-240,0);
        break;
    case 6:
        this->bomberMan->getImage()->move(-288,0);
        break;
    case 7:
        this->bomberMan->getImage()->move(-336,0);
        break;
    }

    this->tokenMort++;
}

void BomberManSlots::finMort()
{
    /*************************************************************************************
    * Si l'animation de mort est finie, on appelle la méthode bomberManMort() de Partie,
    * en précisant que c'est ce BomberMan qui est mort en passant son indice en paramètre.
    * On "cache" ensuite le BomberMan, et on indique que la case sur laquelle il était
    * ne contient plus de BomberMan.
    *************************************************************************************/

    this->bomberMan->getPartieGui()->getPartie()->bomberManMort(this->bomberMan->getJoueur()->getNumero());
    this->bomberMan->hide();

    int posX, posY;
    posX = this->bomberMan->getPosX();
    posY = this->bomberMan->getPosY();

    this->bomberMan->getPartieGui()->getPartie()->getPlateau()->value(posX).value(posY)->setBomberMan(-1);
}

void BomberManSlots::stopTimers()
{
    this->getTimerAnim()->stop();
    this->getTimerMvt()->stop();
    this->animationStop();
}

void BomberManSlots::animationStop()
{
    // Quand l'animation de mouvement s'arrête, on place l'image du BomberMan en fonction de sa direction
    int base;
    QString direction = this->getDirection();

    if(direction == "Down")
    {
        base = 0;
    }
    else if(direction == "Up")
    {
        base = -135;
    }
    else if(direction == "Right")
    {
        base = -270;
    }
    else if(direction == "Left")
    {
        base = -405;
    }

    this->getBomberMan()->getImage()->move(base, 0);
    this->setDirection("Stable");
}

BomberMan* BomberManSlots::getBomberMan()
{
    return this->bomberMan;
}

void BomberManSlots::setBomberMan(BomberMan *bomberMan)
{
    this->bomberMan = bomberMan;
}

QTimer* BomberManSlots::getTimerAnim()
{
    return this->timerAnim;
}

QTimer* BomberManSlots::getTimerMvt()
{
    return this->timerMvt;
}

QString BomberManSlots::getDirection()
{
    return this->direction;
}

void BomberManSlots::setDirection(QString direction)
{
    this->direction = direction;
}

int BomberManSlots::getTokenMvt()
{
    return this->tokenMvt;
}

void BomberManSlots::setTokenMvt(int tokenMvt)
{
    this->tokenMvt = tokenMvt;
}

int BomberManSlots::getTokenMort()
{
    return this->tokenMort;
}

void BomberManSlots::setTokenMort(int tokenMort)
{
    this->tokenMort = tokenMort;
}
