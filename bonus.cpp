#include "bonus.h"
#include "partiegui.h"

Bonus::Bonus(TypeBonus type)
{
    this->type = type;
    this->setFixedSize(36,36);
    this->move(0,0);

    this->image = new QLabel(this);
    this->image->setPixmap(QPixmap("images/Bonus.jpg"));

    // On bouge l'image en fonction du type du bonus
    switch(this->type)
    {
        case PUISSANCE_UP:
        this->image->move(0,0);
            break;
        case PUISSANCE_DOWN:
            this->image->move(-36,0);
            break;
        case BOMBE_UP:
            this->image->move(-72,0);
            break;
        case BOMBE_DOWN:
            this->image->move(-108,0);
            break;
        case VITESSE_UP:
            this->image->move(-144,0);
            break;
        case VITESSE_DOWN:
            this->image->move(-180,0);
            break;
        case PUISSANCE_MAX:
            this->image->move(-216,0);
            break;
        case BOMBE_MAX:
            this->image->move(-252,0);
            break;
    }
}

void Bonus::activer(int numBomberMan)
{
    this->caseParente->setContientBonus(false);

    BomberMan* bomberMan = this->partieGui->getPartie()->getBomberMans()->at(numBomberMan);

    // Quand un BomberMan active le bonus, on lui applique l'effet en fonction du type du bonus
    switch(this->type)
    {
        case PUISSANCE_UP:
            bomberMan->setPorteeExplosion(bomberMan->getPorteeExplosion() + 1);
            break;
        case PUISSANCE_DOWN:
            if(bomberMan->getPorteeExplosion() > 1)
                bomberMan->setPorteeExplosion(bomberMan->getPorteeExplosion() - 1);
            break;
        case BOMBE_UP:
            bomberMan->setNbBombesMax(bomberMan->getNbBombesMax() + 1);
            break;
        case BOMBE_DOWN:
            if(bomberMan->getNbBombesMax() > 1)
                bomberMan->setNbBombesMax(bomberMan->getNbBombesMax() - 1);
            break;
        case VITESSE_UP:
            bomberMan->setVitesse(bomberMan->getVitesse() + 1);
            bomberMan->getSlots()->getTimerAnim()->setInterval((10 - bomberMan->getVitesse()) * 25);
            bomberMan->getSlots()->getTimerMvt()->setInterval((10 - bomberMan->getVitesse()) * 8);
            break;
        case VITESSE_DOWN:
            if(bomberMan->getVitesse() > 1)
            {
                bomberMan->setVitesse(bomberMan->getVitesse() - 1);
                bomberMan->getSlots()->getTimerAnim()->setInterval((10 - bomberMan->getVitesse()) * 25);
                bomberMan->getSlots()->getTimerMvt()->setInterval((10 - bomberMan->getVitesse()) * 8);
            }
            break;
        case PUISSANCE_MAX:
            bomberMan->setPorteeExplosion(15);
            break;
        case BOMBE_MAX:
            bomberMan->setNbBombesMax(1000);
            break;
    }
}

// -------------------------------- //
//        GETTER ET SETTER          //
// -------------------------------- //

PartieGui* Bonus::getPartieGui()
{
    return this->partieGui;
}

void Bonus::setPartieGui(PartieGui *partieGui)
{
    this->partieGui = partieGui;
}

Bonus::TypeBonus Bonus::getType()
{
    return this->type;
}

void Bonus::setType(TypeBonus type)
{
    this->type = type;
}

QLabel* Bonus::getImage()
{
    return this->image;
}

void Bonus::setImage(QString nomImage)
{
    this->image->setPixmap(QPixmap("images/"+nomImage));
}

Case* Bonus::getCaseParente()
{
    return this->caseParente;
}

void Bonus::setCaseParente(Case *caseParente)
{
    this->setParent(caseParente);
    this->caseParente = caseParente;
}
