#include "bomberman.h"
#include "partiegui.h"

BomberMan::BomberMan(int numero, QString skin)
{
    QString pseudo = "Joueur "+numero;
    this->joueur = new Joueur(numero, pseudo);
    this->setSkin(skin);
    this->initialisation();
}

BomberMan::BomberMan(int numero, QString skin, QString pseudo)
{
    this->joueur = new Joueur(numero, pseudo);
    this->setSkin(skin);
    this->initialisation();
}

BomberMan::~BomberMan()
{
    delete this->joueur;
    delete this->image;
    delete this->bomberManSlots;
}

/***************************************************************************************************************
 * initialisation() : Méthode servant à l'initialisation du BomberMan (variables, connections, etc etc ...)
 ***************************************************************************************************************/
void BomberMan::initialisation()
{
    this->nbBombesMax = 1;
    this->nbBombesPosees = 0;
    this->porteeExplosion = 2;
    this->vitesse = 2;
    this->mort = false;

    this->bomberManSlots = new BomberManSlots(this);

    //Initialisation de la position du BomberMan sur le plateau en fonction de son numéro (de 1 à 4)
    switch(this->joueur->getNumero())
    {
        case 0:
            this->posX = 1;
            this->posY = 1;
            break;
        case 1:
            this->posX = 13;
            this->posY = 13;
            break;
        case 2:
            this->posX = 13;
            this->posY = 1;
            break;
        case 3:
            this->posX = 1;
            this->posY = 13;
            break;
    }

    //Initialisation et affichage de l'image du BomberMan
    this->image = new QLabel(this);
    this->image->setPixmap(QPixmap("images/BomberMan"+ this->skin +".png"));
    this->image->move(0,0);
    this->setFixedSize(45, 57);

    this->threadMort = new BomberManMortThread;
    QObject::connect(this->threadMort, SIGNAL(signalAnimMort()), this->bomberManSlots, SLOT(animationMort()));
    QObject::connect(this->threadMort, SIGNAL(signalFinMort()), this->bomberManSlots, SLOT(finMort()));
}

/***************************************************************************************************************
 * Réinitialisation() : Méthode ressemblant à initialisation() et appelée quand une nouvelle manche commence
 ***************************************************************************************************************/
void BomberMan::reinitialiser()
{
    this->nbBombesMax = 1;
    this->nbBombesPosees = 0;
    this->porteeExplosion = 2;
    this->vitesse = 2;
    this->mort = false;

    //Réinitialisation de la position du BomberMan sur le plateau en fonction de son numéro (de 1 à 4)
    switch(this->joueur->getNumero())
    {
        case 0:
            this->posX = 1;
            this->posY = 1;
            break;
        case 1:
            this->posX = 13;
            this->posY = 13;
            break;
        case 2:
            this->posX = 13;
            this->posY = 1;
            break;
        case 3:
            this->posX = 1;
            this->posY = 13;
            break;
    }

    this->image->hide();
    this->image = new QLabel(this);
    this->image->setPixmap(QPixmap("images/BomberMan"+ this->skin +".png"));
    this->image->move(0,0);
    this->image->show();

    this->setFixedSize(45, 57);

    // Les tokens du BomberManSlots sont réinitialisés, et les timers arrêtés
    this->bomberManSlots->setTokenMort(1);
    this->bomberManSlots->setTokenMvt(0);
    this->bomberManSlots->getTimerAnim()->setInterval(200);
    this->bomberManSlots->getTimerAnim()->setInterval(64);
    this->bomberManSlots->getTimerAnim()->stop();
    this->bomberManSlots->getTimerMvt()->stop();
}

void BomberMan::deplacement(QString direction)
{
    this->getSlots()->startTimers(direction);
}

void BomberMan::stopDeplacement()
{
    this->getSlots()->stopTimers();
}

void BomberMan::deplacer()
{
    /*********************************************************************************
    * Cette méthode sert à gérer les collisions quand le BomberMan se déplace dans
    * une direction donnée (si la case suivante est bien vide, si elle ne contient
    * pas une bombe, si elle contient un bonus ...)
    *********************************************************************************/
    if(!this->isMort())
    {
        QString direction = this->getSlots()->getDirection();

        QPoint pos = this->pos();
        int posXCourante = pos.x();
        int posYCourante = pos.y();
        QVector< QVector <Case*> >* plateau = this->partieGui->getPartie()->getPlateau();

        if(direction == "Down")
        {            
            Case* case1 = plateau->at((posXCourante + 22)/36).at((posYCourante + 68)/36);
            Case* case2 = plateau->at((posXCourante + 24)/36).at((posYCourante + 68)/36);

            Case::TypeCase typeCase1 = case1->getType();
            Case::TypeCase typeCase2 = case2->getType();

            bool case1ContientBombe = case1->getContientBombe();
            bool case2ContientBombe = case2->getContientBombe();

            bool case1ContientFlamme = case1->getContientFlamme();
            bool case2ContientFlamme = case2->getContientFlamme();

            bool case1ContientBonus = case1->getContientBonus();
            bool case2ContientBonus = case2->getContientBonus();

            if(typeCase1 == Case::VIDE && typeCase2 == Case::VIDE && !case1ContientBombe && !case2ContientBombe)
                this->move(posXCourante, posYCourante+18);

            if(case1ContientFlamme && case2ContientFlamme)
                this->mourir();

            if(case1ContientBonus && case2ContientBonus)
            {
                case1->getBonus()->activer(this->joueur->getNumero());
                delete case1->getBonus();
            }
        }
        else if(direction == "Up")
        {
            Case* case1 = plateau->at((posXCourante + 22)/36).at((posYCourante + 30)/36);
            Case* case2 = plateau->at((posXCourante + 23)/36).at((posYCourante + 30)/36);

            Case::TypeCase typeCase1 = case1->getType();
            Case::TypeCase typeCase2 = case2->getType();

            bool case1ContientBombe = case1->getContientBombe();
            bool case2ContientBombe = case2->getContientBombe();

            bool case1ContientFlamme = case1->getContientFlamme();
            bool case2ContientFlamme = case2->getContientFlamme();

            bool case1ContientBonus = case1->getContientBonus();
            bool case2ContientBonus = case2->getContientBonus();

            if(typeCase1 == Case::VIDE && typeCase2 == Case::VIDE && !case1ContientBombe && !case2ContientBombe)
                this->move(posXCourante, posYCourante-18);

            if(case1ContientFlamme && case2ContientFlamme)
                this->mourir();

            if(case1ContientBonus && case2ContientBonus)
            {
                case1->getBonus()->activer(this->joueur->getNumero());
                delete case1->getBonus();
            }
        }
        else if(direction == "Right")
        {
            Case* case1 = plateau->at((posXCourante + 42)/36).at((posYCourante + 48)/36);
            Case* case2 = plateau->at((posXCourante + 42)/36).at((posYCourante + 53)/36);

            Case::TypeCase typeCase1 = case1->getType();
            Case::TypeCase typeCase2 = case2->getType();

            bool case1ContientBombe = case1->getContientBombe();
            bool case2ContientBombe = case2->getContientBombe();

            bool case1ContientFlamme = case1->getContientFlamme();
            bool case2ContientFlamme = case2->getContientFlamme();

            bool case1ContientBonus = case1->getContientBonus();
            bool case2ContientBonus = case2->getContientBonus();

            if(typeCase1 == Case::VIDE && typeCase2 == Case::VIDE && !case1ContientBombe && !case2ContientBombe)
                this->move(posXCourante+18, posYCourante);

            if(case1ContientFlamme && case2ContientFlamme)
                this->mourir();

            if(case1ContientBonus && case2ContientBonus)
            {
                case1->getBonus()->activer(this->joueur->getNumero());
                delete case1->getBonus();
            }
        }
        else if(direction == "Left")
        {
            Case* case1 = plateau->at((posXCourante + 3)/36).at((posYCourante + 48)/36);
            Case* case2 = plateau->at((posXCourante + 3)/36).at((posYCourante + 53)/36);

            Case::TypeCase typeCase1 = case1->getType();
            Case::TypeCase typeCase2 = case2->getType();

            bool case1ContientBombe = case1->getContientBombe();
            bool case2ContientBombe = case2->getContientBombe();

            bool case1ContientFlamme = case1->getContientFlamme();
            bool case2ContientFlamme = case2->getContientFlamme();

            bool case1ContientBonus = case1->getContientBonus();
            bool case2ContientBonus = case2->getContientBonus();

            if(typeCase1 == Case::VIDE && typeCase2 == Case::VIDE && !case1ContientBombe && !case2ContientBombe)
                this->move(posXCourante-18, posYCourante);

            if(case1ContientFlamme && case2ContientFlamme)
                this->mourir();

            if(case1ContientBonus && case2ContientBonus)
            {
                case1->getBonus()->activer(this->joueur->getNumero());
                delete case1->getBonus();
            }
        }

        plateau->at(this->getPosX()).at(this->getPosY())->setBomberMan(-1);

        if((this->pos().x() + 5)%36 == 0)
            this->setPosX(floor((this->pos().x() + 23)/36));
        if((this->pos().y() - 5)%36 == 0)
            this->setPosY(floor((this->pos().y() + 53)/36));

        plateau->at(this->getPosX()).at(this->getPosY())->setBomberMan(this->getJoueur()->getNumero());
    }
}

void BomberMan::mourir()
{
    this->mort = true;
    //On aggrandit le bomberMan de 3 pixels à cause de la taille de la nouvelle image
    this->setFixedSize(48,57);

    //On déplace le bomberman de deux pixels vers la gauche étant donné que l'image est plus grande de 3 pixels
    this->move((this->pos().x() - 2), this->pos().y());

    //On change l'image du BomberMan et on démarre le thread gérant l'animation de mort
    this->image->hide();
    this->image = new QLabel(this);
    this->image->setPixmap(QPixmap("images/BomberManMort.png"));
    this->image->move(0,0);
    this->image->show();

    this->threadMort->start();
}

PartieGui* BomberMan::getPartieGui()
{
    return this->partieGui;
}

void BomberMan::setPartieGui(PartieGui *partieGui)
{
    this->partieGui = partieGui;
    this->setParent(this->partieGui->getWidgetBomberMans());
}

Joueur* BomberMan::getJoueur()
{
    return this->joueur;
}

void BomberMan::setJoueur(Joueur *joueur)
{
    this->joueur = joueur;
}

BomberManSlots* BomberMan::getSlots()
{
    return this->bomberManSlots;
}

void BomberMan::setSlots(BomberManSlots *bomberManSlots)
{
    this->bomberManSlots = bomberManSlots;
}

bool BomberMan::isMort()
{
    return this->mort;
}

void BomberMan::setMort(bool mort)
{
    this->mort = mort;
}

int BomberMan::getNbBombesMax()
{
    return this->nbBombesMax;
}

void BomberMan::setNbBombesMax(int nb)
{
    this->nbBombesMax = nb;
}

int BomberMan::getNbBombesPosees()
{
    return this->nbBombesPosees;
}

void BomberMan::setNbBombesPosees(int nb)
{
    this->nbBombesPosees = nb;
}

int BomberMan::getPorteeExplosion()
{
    return this->porteeExplosion;
}

void BomberMan::setPorteeExplosion(int portee)
{
    this->porteeExplosion = portee;
}

bool BomberMan::hasPorteeMax()
{
    return this->porteeMax;
}

void BomberMan::setPorteeMax(bool porteeMax)
{
    this->porteeMax = porteeMax;
}

int BomberMan::getPosX()
{
    return this->posX;
}

void BomberMan::setPosX(int posX)
{
    this->posX = posX;
}

int BomberMan::getPosY()
{
    return this->posY;
}

void BomberMan::setPosY(int posY)
{
    this->posY = posY;
}

QString BomberMan::getSkin()
{
    if(this->skin == QString::null)
    {
        switch(this->getJoueur()->getNumero())
        {
            case 1:
                this->skin = "Blanc";
                break;
            case 2:
                this->skin = "Bleu";
                break;
            case 3:
                this->skin = "Jaune";
                break;
            case 4:
                this->skin = "Noir";
                break;
        }
    }
    return this->skin;
}

void BomberMan::setSkin(QString skin)
{
    this->skin = skin;
}

QLabel* BomberMan::getImage()
{
    return this->image;
}

void BomberMan::setImage(QString nomImage)
{
    this->image->setPixmap(QPixmap("images/"+nomImage));
}

int BomberMan::getVitesse()
{
    return this->vitesse;
}

void BomberMan::setVitesse(int vitesse)
{
    this->vitesse = vitesse;
}

QVector<Qt::Key> BomberMan::getTouches()
{
    return this->touches;
}

void BomberMan::setTouches(QVector<Qt::Key>touches)
{
    this->touches = touches;
}















