#include "flamme.h"

Flamme::Flamme(TypeFlamme type, int posX, int posY, bool fin)
{
    this->posX = posX;
    this->posY = posY;
    this->setFixedSize(36,36);

    this->image = new QLabel(this);
    this->image->move(0,0);

    // On sélectionne l'image de la flamme en fonction de son type et si elle est la "fin" de la flamme
    if(fin)
    {
        switch(type)
        {
            case DROITE:
                this->image->setPixmap(QPixmap("images/FlammesDroiteFin.png"));
                break;
            case GAUCHE:
                this->image->setPixmap(QPixmap("images/FlammesGaucheFin.png"));
                break;
            case HAUT:
                this->image->setPixmap(QPixmap("images/FlammesHautFin.png"));
                break;
            case BAS:
                this->image->setPixmap(QPixmap("images/FlammesBasFin.png"));
                break;
        }
    }
    else
    {
        switch(type)
        {
            case CENTRE:
                this->image->setPixmap(QPixmap("images/FlammesCentre.png"));
                break;
            case DROITE:
                this->image->setPixmap(QPixmap("images/FlammesHorizontal.png"));
                break;
            case GAUCHE:
                this->image->setPixmap(QPixmap("images/FlammesHorizontal.png"));
                break;
            case HAUT:
                this->image->setPixmap(QPixmap("images/FlammesVertical.png"));
                break;
            case BAS:
                this->image->setPixmap(QPixmap("images/FlammesVertical.png"));
                break;
        }
    }
}

QLabel* Flamme::getImage()
{
    return this->image;
}

void Flamme::setImage(QString nomImage)
{
    this->image->setPixmap(QPixmap("images/"+nomImage));
}

int Flamme::getPosX()
{
    return this->posX;
}

void Flamme::setPosX(int posX)
{
    this->posX = posX;
}

int Flamme::getPosY()
{
    return this->posY;
}

void Flamme::setPosY(int posY)
{
    this->posY = posY;
}
