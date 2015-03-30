#include "case.h"

Case::Case(TypeCase type)
{
    this->typeCase = type;
    this->setContientBombe(false);
    this->setContientFlamme(false);
    this->setContientBonus(false);
    this->setBomberMan(-1);
    this->tokenAnim = 1;
    this->setStyleSheet("background-color: #24600a;");

    this->image = new QLabel(this);

    // On sélectionne l'image de la case en fonction de son type
    switch(this->typeCase)
    {
        case Case::VIDE:
            this->image->setPixmap(QPixmap("images/CaseVide.jpg"));
            break;
        case Case::DESTRUCTIBLE:
            this->image->setPixmap(QPixmap("images/CaseDestructible.png"));
            break;
        case Case::INDESTRUCTIBLE:
            this->image->setPixmap(QPixmap("images/CaseIndestructible.jpg"));
            break;
    }

    this->image->move(0,0);

    this->setFixedSize(36,36);

    // On initialise le thread de destruction de la case
    this->threadDestruction = new CaseDestructionThread;
    QObject::connect(this->threadDestruction, SIGNAL(signalAnimDestruction()), this, SLOT(animationDestruction()));
    QObject::connect(this->threadDestruction, SIGNAL(signalFinDestruction()), this, SLOT(finDestruction()));
}

void Case::animationDestruction()
{
    switch(this->tokenAnim)
    {
        case 1:
            this->image->move(-36,0);
            break;
        case 2:
            this->image->move(-72,0);
            break;
        case 3:
            this->image->move(-108,0);
            break;
        case 4:
            this->image->move(-144,0);
            break;
        case 5:
            this->image->move(-180,0);
            break;
        case 6:
            this->image->move(-216,0);
            break;
        case 7:
            this->image->move(-252,0);
            break;
    }

    this->tokenAnim++;
}

void Case::finDestruction()
{
    /**************************************************************
    * Lorsque l'animation de destruction de la case est finie,
    * on change le type de la case à Case::VIDE, et on définie
    * aléatoirement si la case va ensuite contenir un bonus, et,
    * si oui, quel va être son type.
    **************************************************************/
    int random;

    this->setType(Case::VIDE);

    random = rand()%2;

    if(random == 1)
    {
        Bonus::TypeBonus type;

        random = rand()%100;

        if(random < 20)
            type = Bonus::PUISSANCE_UP;
        else if(random < 30)
            type = Bonus::PUISSANCE_DOWN;
        else if(random < 50)
            type = Bonus::BOMBE_UP;
        else if(random < 60)
            type = Bonus::BOMBE_DOWN;
        else if(random < 80)
            type = Bonus::VITESSE_UP;
        else if(random < 90)
            type = Bonus::VITESSE_DOWN;
        else if(random < 95)
            type = Bonus::PUISSANCE_MAX;
        else if(random < 100)
            type = Bonus::BOMBE_MAX;

        this->setContientBonus(true);
        this->bonus = new Bonus(type);
        this->bonus->setPartieGui(this->partieGui);
        this->bonus->setCaseParente(this);
        this->bonus->show();
    }
}

// -------------------------------- //
//        GETTER ET SETTER          //
// -------------------------------- //

PartieGui* Case::getPartieGui()
{
    return this->partieGui;
}

void Case::setPartieGui(PartieGui *partieGui)
{
    this->partieGui = partieGui;
}

Case::TypeCase Case::getType(){
    return typeCase;
}

void Case::setType(TypeCase type)
{
    switch(type)
    {
        case Case::VIDE:
            this->image->setPixmap(QPixmap("images/CaseVide.jpg"));
            break;
        case Case::DESTRUCTIBLE:
            this->image->setPixmap(QPixmap("images/CaseDestructible.png"));
            break;
        case Case::INDESTRUCTIBLE:
            this->image->setPixmap(QPixmap("images/CaseIndestructible.jpg"));
            break;
    }

    this->typeCase = type;
}

QLabel* Case::getImage()
{
    return this->image;
}

void Case::setImage(QString nomImage)
{
    this->image->setPixmap(QPixmap("images/"+nomImage));
}

int Case::getBomberMan()
{
    return this->bomberMan;
}

void Case::setBomberMan(int number)
{
    this->bomberMan = number;
}

Bombe* Case::getBombe()
{
    return this->bombe;
}

void Case::setBombe(Bombe *bombe)
{
    this->bombe = bombe;
}

Bonus* Case::getBonus()
{
    return this->bonus;
}

void Case::setBonus(Bonus* bonus)
{
    this->bonus = bonus;
}

bool Case::getContientBombe()
{
    return this->contientBombe;
}

void Case::setContientBombe(bool contientBombe)
{
    this->contientBombe = contientBombe;
}

bool Case::getContientFlamme()
{
    return this->contientFlamme;
}

void Case::setContientFlamme(bool contientFlamme)
{
    this->contientFlamme = contientFlamme;
}

bool Case::getContientBonus()
{
    return this->contientBonus;
}

void Case::setContientBonus(bool contientBonus)
{
    this->contientBonus = contientBonus;
}

CaseDestructionThread* Case::getThreadDestruction()
{
    return this->threadDestruction;
}
