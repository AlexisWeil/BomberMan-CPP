#include "menuprincipalgui.h"
#include "partie.h"
#include "partiegui.h"
#include "bomberman.h"

#include <QPixmap>
#include <QPushButton>
#include <QComboBox>

#define _XBUTTON_ 300
#define _YBUTTON_ 70

MenuPrincipalGui::MenuPrincipalGui(QWidget *parent) :
    QWidget(parent)
{
    this->mainWidget.setFixedSize(800,600); // On met notre valeur 800x600
    QPushButton *jeuLocalBouton = new QPushButton("Jouer en local", &menuPrincipalWidget);
    QPushButton *quitterBouton = new QPushButton("Quitter", &menuPrincipalWidget);

    jeuLocalBouton->resize(_XBUTTON_, _YBUTTON_);
    quitterBouton->resize(_XBUTTON_, _YBUTTON_);

    int x = 300;
    jeuLocalBouton->move((this->mainWidget.size().width() - jeuLocalBouton->size().width())/2, x);
    x+=(_YBUTTON_ + 10);
    quitterBouton->move((this->mainWidget.size().width() - quitterBouton->size().width())/2, x);

    connect(jeuLocalBouton, SIGNAL(clicked()), this, SLOT(previewJeuLocalSlot()));
    connect(quitterBouton, SIGNAL(clicked()), &mainWidget , SLOT(close()));

    this->menuPrincipalWidget.setParent(&mainWidget);
    this->mainWidget.show();
}

/* ******************************************* */
/*                   Slots                     */
/* ******************************************* */

void MenuPrincipalGui::previewJeuLocalSlot(){
    QPushButton *twoPlayerBouton = new QPushButton("Deux Joueurs", &previewJeuLocalWidget);
    QPushButton *threePlayerBouton = new QPushButton("Trois Joueurs", &previewJeuLocalWidget);
    QPushButton *fourPlayerBouton = new QPushButton("Quatre Joueurs", &previewJeuLocalWidget);
    QPushButton *retourBouton = new QPushButton("Retour", &previewJeuLocalWidget);

    twoPlayerBouton->resize(_XBUTTON_, _YBUTTON_);
    threePlayerBouton->resize(_XBUTTON_, _YBUTTON_);
    fourPlayerBouton->resize(_XBUTTON_, _YBUTTON_);
    retourBouton->resize(_XBUTTON_, _YBUTTON_);

    int x = 200;
    twoPlayerBouton->move((this->mainWidget.size().width() - twoPlayerBouton->size().width())/2, x);
    x+=(_YBUTTON_ + 10);
    threePlayerBouton->move((this->mainWidget.size().width() - threePlayerBouton->size().width())/2, x);
    x+=(_YBUTTON_ + 10);
    fourPlayerBouton->move((this->mainWidget.size().width() - fourPlayerBouton->size().width())/2, x);
    x+=(_YBUTTON_ + 10);
    retourBouton->move((this->mainWidget.size().width() - retourBouton->size().width())/2, x);

    connect(twoPlayerBouton, SIGNAL(clicked()), this, SLOT(jeuLocalSlot2()));
    connect(threePlayerBouton, SIGNAL(clicked()), this, SLOT(jeuLocalSlot3()));
    connect(fourPlayerBouton, SIGNAL(clicked()), this, SLOT(jeuLocalSlot4()));
    connect(retourBouton, SIGNAL(clicked()), this, SLOT(retourMain()));

    previewJeuLocalWidget.setParent(&mainWidget);
    previewJeuLocalWidget.show();
    menuPrincipalWidget.hide();
}

void MenuPrincipalGui::jeuLocalSlot2(){
    jeuLocal(2);
}
void MenuPrincipalGui::jeuLocalSlot3(){
    jeuLocal(3);
}
void MenuPrincipalGui::jeuLocalSlot4(){
    jeuLocal(4);
}

void MenuPrincipalGui::jeuLocal(int nbJoueur){
    this->jeuLocalWidget = new QWidget;

    this->nbJoueur = nbJoueur;

    QLabel *nombreTimerLabel = new QLabel(this->jeuLocalWidget);
    nombreTimerLabel->setText("Durée d'une manche : ");
    nombreTimerLabel->resize(130, 30);
    nombreTimerLabel->move(5, 10);
    QLabel *nombreMancheLabel = new QLabel(this->jeuLocalWidget);
    nombreMancheLabel->setText("Nombre de manche(s) gagnante(s) :");
    nombreMancheLabel->resize(130, 30);
    nombreMancheLabel->move(300, 10);

    QStringList listeTimer;
    listeTimer << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";
    this->nombreTimer = new QComboBox(this->jeuLocalWidget);
    this->nombreTimer->addItems(listeTimer);
    this->nombreTimer->move(nombreTimerLabel->width(), 10);
    this->nombreTimer->setCurrentIndex(2);

    QStringList listeNombre;
    listeNombre << "1" << "2" << "3" << "4" << "5" ;
    this->nombreManche = new QComboBox(this->jeuLocalWidget);
    this->nombreManche->addItems(listeNombre);
    this->nombreManche->setCurrentIndex(1);
    this->nombreManche->move(420, 10);

    // QStringList des couleurs
    QStringList listeCouleur;
    listeCouleur << "Blanc" << "Bleu" << "Cyan" << "Jaune" << "Noir" << "Rose" << "Rouge" << "Vert";

    int widthCommandePixmap = 350;
    int heightCommandePixmap = 80;

    int posXLabel = 20;
    int poxYLabel = 75;
    int posXCouleur = 160;
    int posYCouleur = 70;
    int poxXCommandeLabel = 300;
    int poxYCommandeLabel = 45;
    int variancePosY = 100;

    // affichages des bombermans
    QLabel *bomberManOneLabel = new QLabel(this->jeuLocalWidget);
    this->bomberManOneCouleur = new QComboBox(this->jeuLocalWidget);
    QLabel *bomberManOneCommandeLabel = new QLabel(this->jeuLocalWidget);

    bomberManOneLabel->setText("Joueur 1 ");
    bomberManOneLabel->move(posXLabel, poxYLabel);
    this->bomberManOneCouleur->addItems(listeCouleur);
    this->bomberManOneCouleur->setCurrentIndex(0);
    this->bomberManOneCouleur->move(posXCouleur, posYCouleur);
    bomberManOneCommandeLabel->resize(widthCommandePixmap, heightCommandePixmap);
    bomberManOneCommandeLabel->setPixmap(QPixmap("images/CommandeBomberManOne.jpg"));
    bomberManOneCommandeLabel->move(poxXCommandeLabel, poxYCommandeLabel);

    QLabel *bomberManTwoLabel = new QLabel(this->jeuLocalWidget);
    this->bomberManTwoCouleur = new QComboBox(this->jeuLocalWidget);
    QLabel *bomberManTwoCommandeLabel = new QLabel(this->jeuLocalWidget);

    bomberManTwoLabel->setText("Joueur 2 ");
    bomberManTwoLabel->move(posXLabel, poxYLabel+variancePosY);
    this->bomberManTwoCouleur->addItems(listeCouleur);
    this->bomberManTwoCouleur->setCurrentIndex(1);
    this->bomberManTwoCouleur->move(posXCouleur,posYCouleur+variancePosY);
    bomberManTwoCommandeLabel->resize(widthCommandePixmap, heightCommandePixmap);
    bomberManTwoCommandeLabel->setPixmap(QPixmap("images/CommandeBomberManTwo.jpg"));
    bomberManTwoCommandeLabel->move(poxXCommandeLabel, poxYCommandeLabel+variancePosY);

    if (nbJoueur >= 3){
        QLabel *bomberManThreeLabel = new QLabel(this->jeuLocalWidget);
        this->bomberManThreeCouleur = new QComboBox(this->jeuLocalWidget);
        QLabel *bomberManThreeCommandeLabel = new QLabel(this->jeuLocalWidget);

        bomberManThreeLabel->setText("Joueur 3 ");
        bomberManThreeLabel->move(posXLabel, poxYLabel+(variancePosY*(2)));
        this->bomberManThreeCouleur->addItems(listeCouleur);
        this->bomberManThreeCouleur->setCurrentIndex(2);
        this->bomberManThreeCouleur->move(posXCouleur,posYCouleur+(variancePosY*(2)));
        bomberManThreeCommandeLabel->resize(widthCommandePixmap, heightCommandePixmap);
        bomberManThreeCommandeLabel->setPixmap(QPixmap("images/CommandeBomberManThree.jpg"));
        bomberManThreeCommandeLabel->move(poxXCommandeLabel, poxYCommandeLabel+(variancePosY*(2)));

    } if (nbJoueur >= 4){
        QLabel *bomberManFourLabel = new QLabel(this->jeuLocalWidget);
        this->bomberManFourCouleur = new QComboBox(this->jeuLocalWidget);
        QLabel *bomberManFourCommandeLabel = new QLabel(this->jeuLocalWidget);

        bomberManFourLabel->setText("Joueur 4 ");
        bomberManFourLabel->move(posXLabel, poxYLabel+(variancePosY*(3)));
        this->bomberManFourCouleur->addItems(listeCouleur);
        this->bomberManFourCouleur->setCurrentIndex(3);
        this->bomberManFourCouleur->move(posXCouleur,posYCouleur+(variancePosY*(3)));
        bomberManFourCommandeLabel->resize(widthCommandePixmap, heightCommandePixmap);
        bomberManFourCommandeLabel->setPixmap(QPixmap("images/CommandeBomberManFour.jpg"));
        bomberManFourCommandeLabel->move(poxXCommandeLabel, poxYCommandeLabel+(variancePosY*(3)));
    }

    QPushButton *jouerBouton = new QPushButton("Jouer", this->jeuLocalWidget);
    QPushButton *retourBouton = new QPushButton("Retour", this->jeuLocalWidget);

    jouerBouton->resize(_XBUTTON_, _YBUTTON_);
    jouerBouton->move(200, 500);
    retourBouton->resize(_XBUTTON_, _YBUTTON_);
    retourBouton->move(500, 500);

    QObject::connect(jouerBouton, SIGNAL(clicked()), this, SLOT(lancerJeuSlot()));
    QObject::connect(retourBouton, SIGNAL(clicked()), this, SLOT(retourPreviewJeuLocal()));

    this->jeuLocalWidget->setParent(&mainWidget);
    this->jeuLocalWidget->show();
    this->previewJeuLocalWidget.hide();
}

void MenuPrincipalGui::lancerJeuSlot(){

    this->skinJoueur.clear();
    this->skinJoueur.append(this->bomberManOneCouleur->currentText());
    this->skinJoueur.append(this->bomberManTwoCouleur->currentText());
    if (this->nbJoueur >= 3)
        this->skinJoueur.append(this->bomberManThreeCouleur->currentText());
    if (this->nbJoueur >= 4)
        this->skinJoueur.append(this->bomberManFourCouleur->currentText());

    p = new PartieGui(this->nbJoueur, this->nombreTimer->currentText().toInt(), this->nombreManche->currentText().toInt(), this->skinJoueur, this);

    this->p->setParent(&mainWidget);
    this->p->setFocus();
    this->p->show();
    this->jeuLocalWidget->hide();
}

void MenuPrincipalGui::retourMain(){
    this->menuPrincipalWidget.show();
    this->previewJeuLocalWidget.hide();
}

void MenuPrincipalGui::retourPreviewJeuLocal()
{
    delete this->jeuLocalWidget;
    this->previewJeuLocalWidget.show();
}

void MenuPrincipalGui::quitterJeuEnCours()
{
    delete this->p;
    delete this->jeuLocalWidget;
    this->menuPrincipalWidget.show();
}
