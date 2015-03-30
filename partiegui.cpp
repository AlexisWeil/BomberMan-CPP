#include <QLabel>
#include <QPushButton>
#include <iostream>

#include "partiegui.h"
#include "partie.h"
#include "menuprincipalgui.h"

using namespace std;

PartieGui::PartieGui(int nbJoueur, int nbMinutes, int nombreManche, QVector<QString> skinJoueur, MenuPrincipalGui* menuPrincipalGui){
    this->nbMinutes = nbMinutes;
    this->menuPrincipalGui = menuPrincipalGui;

    resize(800,600); // On met notre valeur 800x600
    this->compteur = (nbMinutes*60);
    this->nbJoueur = nbJoueur;
    this->skinJoueur = skinJoueur;

    partie.setPartieGui(this);
    partie.setNbJoueur(nbJoueur);
    partie.setSkinJoueur(skinJoueur);
    partie.setNbManchesGagnantes(nombreManche);
    genererPlateau();   // On obtient le plateau

    getConteneurPoints();
    this->conteneurPoints.move(0,0);

    getConteneurBoutons();
    this->conteneurBoutons.move(0, 60);
}


/***************************************************************************************************************
 * keyPressEvent(QKeyEvent* event) : Méthode servant à la gestion des évènements liés au clavier
 * On va pouvoir, grâce à cette méthode, gérer le déplacement et la pose de bombe du BomberMan
 ***************************************************************************************************************/

void PartieGui::keyPressEvent(QKeyEvent* event)
{
    if(!event->isAutoRepeat())
    {
        QVector<BomberMan*>* bomberMans = this->partie.getBomberMans();

        for(int i = 0 ; i < bomberMans->size() ; i++)
        {
            if(!bomberMans->at(i)->isMort())
            {
                QVector<Qt::Key> touches = bomberMans->at(i)->getTouches();

                if(event->key() == touches.at(0))
                    bomberMans->at(i)->deplacement("Down");
                else if(event->key() == touches.at(1))
                    bomberMans->at(i)->deplacement("Up");
                else if(event->key() == touches.at(2))
                    bomberMans->at(i)->deplacement("Right");
                else if(event->key() == touches.at(3))
                    bomberMans->at(i)->deplacement("Left");
                else if(event->key() == touches.at(4))
                {
                    int posX = bomberMans->at(i)->getPosX();
                    int posY = bomberMans->at(i)->getPosY();

                    /******************************************************************
                    * Si la touche servant à poser des bombes est pressée, on vérifie
                    * si la case sur laquelle devrait être posée la bombe n'en contient
                    * pas déjà une. Si c'est bon, on ajoute une bombe au QVector les
                    * contenantn, et si le timer gérant l'animation des bombes n'est
                    * pas activé, alors on l'active.
                    ******************************************************************/
                    if(!this->partie.getPlateau()->at(posX).at(posY)->getContientBombe())
                    {
                        if((bomberMans->at(i)->getNbBombesMax() - bomberMans->at(i)->getNbBombesPosees()) > 0)
                        {
                            this->partie.getBombes()->append(new Bombe(i, this));

                            bomberMans->at(i)->setNbBombesPosees(bomberMans->at(i)->getNbBombesPosees() + 1);

                            if(!this->partie.getTimerAnimBombes()->isActive())
                            {
                                this->partie.getTimerAnimBombes()->start();
                            }
                        }
                    }
                }
            }
        }
    }
}

void PartieGui::keyReleaseEvent(QKeyEvent* event)
{
    if(!event->isAutoRepeat())
    {
        QVector<BomberMan*>* bomberMans = this->partie.getBomberMans();

        for(int i = 0 ; i < bomberMans->size() ; i++)
        {
            if(!bomberMans->at(i)->isMort())
            {
                QString direction = bomberMans->at(i)->getSlots()->getDirection();

                if(direction != "Stable")
                {
                    QVector<Qt::Key> touches = bomberMans->at(i)->getTouches();
                    Qt::Key touche;

                    if(direction == "Down")
                        touche = touches.at(0);
                    else if(direction == "Up")
                        touche = touches.at(1);
                    else if(direction == "Right")
                        touche = touches.at(2);
                    else if(direction == "Left")
                        touche = touches.at(3);

                    if(event->key() == touche)
                        bomberMans->at(i)->stopDeplacement();
                }
            }
        }
    }
}

/***************************************************************************************************************
 * Slot Compter pour la Timer
 * Décompte et affiche les temps restant aux participants
 ***************************************************************************************************************/
void PartieGui::compter(){
    this->compteur--;
    if (this->compteur >= 1){
        afficherTimer();
    } else {
        afficherTimer();
        this->timer->stop();

        QVector< QVector < Case* > >* plateau  = this->getPartie()->getPlateau();

        for(int i = 0 ; i < 15 ; i++)
        {
            for(int j = 0 ; j < 15 ; j++)
            {
                if(plateau->at(i).at(j)->getType() == Case::DESTRUCTIBLE)
                    plateau->at(i).at(j)->getThreadDestruction()->start();
            }
        }

        for(int i = 0 ; i < this->getPartie()->getNbJoueur() ; i++)
        {
            this->getPartie()->getBomberMans()->at(i)->setNbBombesMax(1000);
            this->getPartie()->getBomberMans()->at(i)->setPorteeExplosion(15);
        }
    }
}

void PartieGui::afficherTimer(){
    int x = 74;
    timerMinuteLabel->resize(24,24);
    timerMinuteLabel->setPixmap(QPixmap("images/HeaderChar" + QString::number(this->compteur / 60)));
    timerMinuteLabel->move(x, 18);
    x += 48;

    timerDizaineSecondeLabel->resize(24,24);
    timerDizaineSecondeLabel->setPixmap(QPixmap("images/HeaderChar" + QString::number((this->compteur % 60) / 10)));
    timerDizaineSecondeLabel->move(x, 18);
    x += 24;

    timerSecondeLabel->resize(24,24);
    timerSecondeLabel->setPixmap(QPixmap("images/HeaderChar" + QString::number(this->compteur % 10)));
    timerSecondeLabel->move(x, 18);
}

void PartieGui::afficherAlertFinManche(QString texte, bool finPartie)
{
    /******************************************************************
    * Cette méthode sert à afficher une alerte à l'écran indiquant
    * que la manche, ou la partie, est terminée.
    * Si la partie n'est pas encore finie, on appelle la méthode
    * recommencerManche après 5 secondes, à l'aide d'un QTimer.
    ******************************************************************/
    this->widgetAlertFinManche.setFixedSize(540, 540);
    this->widgetAlertFinManche.setParent(this);
    this->widgetAlertFinManche.move((800 - this->plateau.size().height()),(600-this->plateau.size().width()));

    QLabel* texteFinManche = new QLabel(texte, &this->widgetAlertFinManche);
    texteFinManche->setFixedSize(300,50);
    texteFinManche->move((540 - texteFinManche->width())/2, (540 - texteFinManche->height())/2);
    texteFinManche->setStyleSheet("background-color: White; border: 1px solid black; font-weight: bold;");
    texteFinManche->setAlignment(Qt::AlignCenter);

    this->widgetAlertFinManche.show();

    if(!finPartie)
        QTimer::singleShot(5000, this, SLOT(recommencerManche()));
}

void PartieGui::recommencerManche()
{
    /*********************************************************************
    * Cette méthode sert à réinitialiser le plateau, les caractéristiques
    * et à redémarrer le timer de la manche.
    *********************************************************************/
    this->widgetAlertFinManche.hide();
    this->widgetBomberMans.setStyleSheet("");

    this->conteneurPoints.hide();
    this->timer->stop();
    this->compteur = (nbMinutes*60);

    for(int i = 0 ; i < 15 ; i++)
    {
        for(int j = 0 ; j < 15 ; j++)
        {
            delete this->partie.getPlateau()->at(i).at(j);
        }
    }


    this->partie.regenererPlateau();
    this->partie.reinitialiserBomberMans();
    this->getConteneurPoints();
    this->conteneurPoints.show();
    this->genererPlateau();
}

/***************************************************************************************************************
 * Partie des Setters, ainsi que des getters
 ***************************************************************************************************************/

Partie* PartieGui::getPartie()
{
    return &this->partie;
}

MenuPrincipalGui* PartieGui::getMenuPrincipalGui()
{
    return this->menuPrincipalGui;
}

void PartieGui::setMenuPrincipalGui(MenuPrincipalGui* menuPrincipalGui)
{
    this->menuPrincipalGui = menuPrincipalGui;
}

void PartieGui::getConteneurPoints(){
    QLabel *labelHorloge = new QLabel(&conteneurPoints);
    labelHorloge->setPixmap(QPixmap("images/HeaderHorloge2.jpg"));

    timerMinuteLabel = new QLabel(&conteneurPoints);
    timerDizaineSecondeLabel = new QLabel(&conteneurPoints);
    timerSecondeLabel = new QLabel(&conteneurPoints);

    // QTimer pour le compte a rebours
    timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), this, SLOT(compter()) );
    timer->start(1000); // Il s'actualise toute les secondes

    // On affiche le compte a rebours pour le demarrage du programme
    // Si on ne le fait pas ici, on obtient un timer vide dans le GUI au départ du programme
    afficherTimer();
    // On affiche le double point, qu'on n'actualise pas, puisqu'il ne change jamais !
    QLabel *timerDoublePointLabel = new QLabel(&conteneurPoints);
    timerDoublePointLabel->setPixmap(QPixmap("images/HeaderCharDoublePoint.jpg"));
    timerDoublePointLabel->move(98,18);

    int x = 192;
    // boucle pour ajouter les scores de tous les bomberman
    for(int i=0; i < this->skinJoueur.size() ; i++){
        // Affichage du portrait du BomberMan
        QLabel *label = new QLabel(&conteneurPoints);
        label->setPixmap(QPixmap("images/HeaderBomberMan" + this->skinJoueur.at(i) + ".jpg"));
        label->move(x,0);
        x += 48;

        // Affichage du BackGround Score, avec le Score
        QLabel *labelScore = new QLabel(&conteneurPoints);
        labelScore->setPixmap(QPixmap("images/HeaderScoreMiddle.jpg"));
        labelScore->move(x,0);

        int nbVictoires = this->getPartie()->getBomberMans()->at(i)->getJoueur()->getNbVictoires();

        QLabel *score = new QLabel(&conteneurPoints);
        score->setPixmap(QPixmap("images/HeaderChar" + QString::number(nbVictoires) + ".jpg"));
        score->move(x,18);
        x += 48;

        // Ajout d'un background entre les portaits
        QLabel *labelMiddle = new QLabel(&conteneurPoints);
        labelMiddle->setPixmap(QPixmap("images/HeaderMiddle.jpg"));
        labelMiddle->move(x,0);
        x += 50;
    }
    // On affiche un Header vide si le nombre de joueur est inférieur à 4
    for(int i=0; i < (4 - this->skinJoueur.size()); i++){
        QLabel *labelVide = new QLabel(&conteneurPoints);
        labelVide->setPixmap(QPixmap("images/HeaderVide.jpg"));
        labelVide->move(x,0);
        x += 96;

        QLabel *labelMiddle = new QLabel(&conteneurPoints);
        labelMiddle->setPixmap(QPixmap("images/HeaderMiddle.jpg"));
        labelMiddle->move(x,0);
        x += 50;
    }
    QLabel *label = new QLabel(&conteneurPoints);
    label->setPixmap(QPixmap("images/HeaderEnd.jpg"));
    label->move(x,0);


    this->conteneurPoints.resize(800,60);
    this->conteneurPoints.setParent(this);
}

void PartieGui::setConteneurPoints(QWidget){

}

QWidget PartieGui::getConteneurCentral(){

}

void PartieGui::setConteneurCentral(QWidget){

}

void PartieGui::getConteneurBoutons(){
    QLabel *labelBomberMan = new QLabel(&conteneurBoutons);
    labelBomberMan->setPixmap(QPixmap("images/BomberMan.jpg"));

    QPushButton *boutonQuitter = new QPushButton("Quitter", &conteneurBoutons);
    boutonQuitter->resize(200, 70);
    boutonQuitter->move(30, 435);

    QObject::connect(boutonQuitter, SIGNAL(clicked()), this->menuPrincipalGui, SLOT(quitterJeuEnCours()));

    this->conteneurBoutons.resize(260, 540);
    this->conteneurBoutons.setParent(this);
}

void PartieGui::setConteneurBoutons(QWidget){

}

QWidget PartieGui::getConteneurPlateau(){

}

void PartieGui::setConteneurPlateau(QWidget){

}

void PartieGui::genererPlateau(){

    // Boucle pour placer les images en fonction du QVector 2D <Case*>
    for (int i=0; i<15; i++){
        for (int j=0; j<15; j++){
            this->partie.getPlateau()->at(i).at(j)->setParent(&this->plateau);
            this->partie.getPlateau()->at(i).at(j)->move(i*36, j*36);
            this->partie.getPlateau()->at(i).at(j)->show();
        }
    }

    for(int i = 0 ; i < this->nbJoueur ; i++)
    {
        BomberMan* bomberMan = this->partie.getBomberMans()->at(i);

        bomberMan->setPartieGui(this);

        this->partie.getPlateau()->at(bomberMan->getPosX()).at(bomberMan->getPosY())->setBomberMan(i);
        bomberMan->move((bomberMan->getPosX()*36 - 5), ((bomberMan->getPosY() - 1)*36 + 5));
        bomberMan->show();
    }

    this->plateau.resize(540,540);
    this->plateau.setParent(this);
    this->plateau.move((800 - this->plateau.size().height()),(600-this->plateau.size().width()));
    this->plateau.setFocus();       // On met le focus sur le plateau

    this->widgetExplosions.resize(540,540);
    this->widgetExplosions.setParent(this);
    this->widgetExplosions.move((800 - this->plateau.size().height()),(600-this->plateau.size().width()));

    this->widgetBomberMans.resize(540,540);
    this->widgetBomberMans.setParent(this);
    this->widgetBomberMans.move((800 - this->plateau.size().height()),(600-this->plateau.size().width()));
}

QWidget* PartieGui::getPlateau()
{
    return &this->plateau;
}

void PartieGui::setPlateau(QWidget){

}

QWidget* PartieGui::getWidgetExplosions()
{
    return &this->widgetExplosions;
}

QWidget* PartieGui::getWidgetBomberMans()
{
    return &this->widgetBomberMans;
}
