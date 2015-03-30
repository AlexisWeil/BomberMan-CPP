#include "bombe.h"
#include "partiegui.h"


Bombe::Bombe(int proprietaire, PartieGui *partieGui)
{
    this->proprietaire = proprietaire;
    this->partieGui = partieGui;
    this->posX = this->partieGui->getPartie()->getBomberMans()->at(proprietaire)->getPosX();
    this->posY = this->partieGui->getPartie()->getBomberMans()->at(proprietaire)->getPosY();
    this->porteeExplosion = this->partieGui->getPartie()->getBomberMans()->at(proprietaire)->getPorteeExplosion();
    this->tokenAnim = 1;
    this->tokenAnimFin = 1;
    this->explosee = false;
    this->finExplosee = false;

    this->image = new QLabel(this);
    this->image->setPixmap(QPixmap("images/BombeAnimation.png"));
    this->image->move(0,0);

    this->partieGui->getPartie()->getPlateau()->at(this->posX).at(this->posY)->setBombe(this);
    this->partieGui->getPartie()->getPlateau()->at(this->posX).at(this->posY)->setContientBombe(true);

    this->setFixedSize(36,36);
    this->move(this->posX*36, this->posY*36);
    this->setParent(this->partieGui->getPlateau());
    this->show();

    QTimer::singleShot(3000, this, SLOT(explosion()));
}

Bombe::~Bombe()
{
    delete this->image;
    this->flammes.clear();
}

void Bombe::animation()
{
    switch(this->tokenAnim)
    {
        case 1:
            this->image->move(0,0);
            break;
        case 2:
            this->image->move(-36,0);
            break;
        case 3:
            this->image->move(-72,0);
            break;
        case 4:
            this->image->move(-36,0);
            break;
    }

    switch(this->tokenAnim)
    {
        case 1:
            this->tokenAnim++;
            break;
        case 2:
            this->tokenAnim++;
            break;
        case 3:
            this->tokenAnim++;
            break;
        case 4:
            this->tokenAnim = 1;
            break;
    }
}

void Bombe::explosion()
{
    if(!this->explosee) //Si la bombe n'a pas encore explosée
    {
        bool allowDroite = true, allowGauche = true, allowHaut = true, allowBas = true;
        Case::TypeCase typeCase;
        Flamme::TypeFlamme typeFlamme;
        int posX = this->posX, posY = this->posY;
        this->setExplosee(true);
        this->hide();
        this->flammes.append(new Flamme(Flamme::CENTRE, posX, posY));
        this->flammes.at(0)->setParent(this->partieGui->getWidgetExplosions());
        this->flammes.at(0)->move(this->posX*36, this->posY*36);
        this->flammes.at(0)->show();

        //Si un BomberMan se trouve au centre de l'explosion, il meurt
        int bomberManTouche = this->partieGui->getPartie()->getPlateau()->at(posX).at(posY)->getBomberMan();

        if(bomberManTouche != -1)
        {
            if(!this->partieGui->getPartie()->getBomberMans()->at(bomberManTouche)->isMort())
                this->partieGui->getPartie()->getBomberMans()->at(bomberManTouche)->mourir();
        }

        /********************************************************************
        * On fait une boucle en fonction de la portée de l'explosion
        * Pour chaque direction, on vérifie si la flamme peut s'étendre dans
        * cette direction.
        * Si c'est bon, on indique via la variable typeFlamme que la flamme
        * sera en fonction de cette direction.
        * Sinon, on indique que la flamme ne s'étend plus dans cette
        * direction en mettant typeFlamme à Flamme::_NULL_
        ********************************************************************/
        for(int i = 1 ; i <= this->porteeExplosion ; i++)
        {
            for(int j = 0 ; j < 4 ; j++)
            {
                switch(j)
                {
                    case 0: //Gestion de la flamme à droite
                        if(allowDroite)
                        {
                            typeFlamme = Flamme::DROITE;
                            posX += i;
                        }
                        else
                            typeFlamme = Flamme::_NULL_;
                        break;

                    case 1: //Gestion de la flamme à gauche
                        if(allowGauche)
                        {
                            typeFlamme = Flamme::GAUCHE;
                            posX -= i;
                        }
                        else
                            typeFlamme = Flamme::_NULL_;
                        break;

                    case 2: //Gestion de la flamme en haut
                        if(allowHaut)
                        {
                            typeFlamme = Flamme::HAUT;
                            posY -= i;
                        }
                        else
                            typeFlamme = Flamme::_NULL_;
                        break;

                    case 3: //Gestion de la flamme en bas
                        if(allowBas)
                        {
                            typeFlamme = Flamme::BAS;
                            posY += i;
                        }
                        else
                            typeFlamme = Flamme::_NULL_;
                        break;
                }

                /********************************************************************
                * On vérifie si la flamme peut continuer à s'étendre dans la
                * direction donnée par j.
                * Si elle le peut et que la case suivante est vide, on vérifie
                * si elle contient un bonus, un BomberMan, ou une bombe, et on
                * déclanche les actions appropriées.
                * Si la case suivante est une case destructible ou indestructible,
                * on indique que la flamme ne peut plus s'étendre dans cette
                * direction.
                ********************************************************************/

                if(typeFlamme != Flamme::_NULL_)
                    typeCase = this->partieGui->getPartie()->getPlateau()->at(posX).at(posY)->getType();
                else
                    typeCase = this->partieGui->getPartie()->getPlateau()->at(this->posX).at(this->posY)->getType();

                if(typeCase == Case::VIDE && typeFlamme != Flamme::_NULL_)
                {
                    if(this->partieGui->getPartie()->getPlateau()->at(posX).at(posY)->getContientBonus())
                    {
                        delete this->partieGui->getPartie()->getPlateau()->at(posX).at(posY)->getBonus();
                        this->partieGui->getPartie()->getPlateau()->at(posX).at(posY)->setContientBonus(false);
                    }

                    if(this->partieGui->getPartie()->getPlateau()->at(posX).at(posY)->getContientBombe())
                    {
                        for(int i = 0 ; i < this->partieGui->getPartie()->getBombes()->size() ; i++)
                        {
                            Bombe* bombe = this->partieGui->getPartie()->getBombes()->at(i);

                            if(!bombe->isExplosee() && (bombe->getPosX() == posX) && (bombe->getPosY() == posY))
                                bombe->explosion();
                        }
                    }

                    if(i < this->porteeExplosion)
                        this->flammes.append(new Flamme(typeFlamme, posX, posY));
                    else
                        this->flammes.append(new Flamme(typeFlamme, posX, posY, true));

                    this->partieGui->getPartie()->getPlateau()->value(posX).value(posY)->setContientFlamme(true);
                    this->flammes.at(this->flammes.size() - 1)->setParent(this->partieGui->getWidgetExplosions());
                    this->flammes.at(this->flammes.size() - 1)->move(posX*36, posY*36);
                    this->flammes.at(this->flammes.size() - 1)->show();

                    int bomberManTouche = this->partieGui->getPartie()->getPlateau()->at(posX).at(posY)->getBomberMan();

                    if(bomberManTouche != -1)
                    {
                        if(!this->partieGui->getPartie()->getBomberMans()->at(bomberManTouche)->isMort())
                        {
                            this->partieGui->getPartie()->getBomberMans()->at(bomberManTouche)->mourir();
                            this->partieGui->getPartie()->bomberManMort(bomberManTouche);
                        }
                    }
                }
                else if(typeCase == Case::DESTRUCTIBLE)
                {
                    this->detruireCase(posX, posY);

                    switch(typeFlamme)
                    {
                        case Flamme::DROITE:
                            allowDroite = false;
                            break;
                        case Flamme::GAUCHE:
                            allowGauche = false;
                            break;
                        case Flamme::HAUT:
                            allowHaut = false;
                            break;
                        case Flamme::BAS:
                            allowBas = false;
                            break;
                    }
                }
                else if(typeCase == Case::INDESTRUCTIBLE)
                {
                    switch(typeFlamme)
                    {
                        case Flamme::DROITE:
                            allowDroite = false;
                            break;
                        case Flamme::GAUCHE:
                            allowGauche = false;
                            break;
                        case Flamme::HAUT:
                            allowHaut = false;
                            break;
                        case Flamme::BAS:
                            allowBas = false;
                            break;
                    }
                }
                posX = this->posX;
                posY = this->posY;
            }
        }

        //On crée le thread correspondant à l'animation des flammes et on le lance

        this->thread = new BombeExplosionThread;

        QObject::connect(this->thread, SIGNAL(signalAnimFinExplosion()), this, SLOT(animationFinExplosion()));
        QObject::connect(this->thread, SIGNAL(signalFinExplosion()), this, SLOT(finExplosion()));

        this->thread->start();
    }
}

void Bombe::animationFinExplosion()
{
    for(int i = 0 ; i < this->flammes.size(); i++)
    {
        //En fonction du tokenAnimFin, on change l'image des flammes
        switch(this->tokenAnimFin)
        {
            case 1:
                this->flammes.at(i)->getImage()->move(-36, 0);
                break;
            case 2:
                this->flammes.at(i)->getImage()->move(-72, 0);
                break;
            case 3:
                this->flammes.at(i)->getImage()->move(-108, 0);
                break;
        }
    }

    this->tokenAnimFin++;
}

void Bombe::finExplosion()
{
    int posX, posY;

    // Quand la bombe a finie d'exploser, on supprime les flammes et on indique
    // que la case sur laquelle elle était ne contient plus de bombe
    for(int i = 0 ; i < this->flammes.size() ; i++)
    {
        posX = this->flammes.at(i)->getPosX();
        posY = this->flammes.at(i)->getPosY();

        this->flammes.at(i)->hide();
        this->partieGui->getPartie()->getPlateau()->at(posX).at(posY)->setContientFlamme(false);

        this->finExplosee = true;
    }
    BomberMan* bomberMan = this->partieGui->getPartie()->getBomberMans()->at(this->proprietaire);

    bomberMan->setNbBombesPosees(bomberMan->getNbBombesPosees() - 1);
}

void Bombe::detruireCase(int posX, int posY)
{
    this->posXCaseRempl = posX;
    this->posYCaseRempl = posY;

    this->partieGui->getPartie()->getPlateau()->at(posX).at(posY)->getThreadDestruction()->start();
}

int Bombe::getProprietaire()
{
    return this->proprietaire;
}

void Bombe::setProprietaire(int proprietaire)
{
    this->proprietaire = proprietaire;
}

int Bombe::getPosX()
{
    return this->posX;
}

void Bombe::setPosX(int posX)
{
    this->posX = posX;
}

int Bombe::getPosY()
{
    return this->posY;
}

void Bombe::setPosY(int posY)
{
    this->posY = posY;
}

int Bombe::getPortee()
{
    return this->porteeExplosion;
}

void Bombe::setPortee(int portee)
{
    this->porteeExplosion = portee;
}

QLabel* Bombe::getImage()
{
    return this->image;
}

void Bombe::setImage(QString nomImage)
{
    this->image->setPixmap(QPixmap("images/"+nomImage));
}

bool Bombe::isExplosee()
{
    return this->explosee;
}

void Bombe::setExplosee(bool explosee)
{
    this->explosee = explosee;
}

bool Bombe::isFinExplosee()
{
    return this->finExplosee;
}

void Bombe::setFinExplosee(bool finExplosee)
{
    this->finExplosee = finExplosee;
}



