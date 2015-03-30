#include <iostream>
#include <time.h>
#include <stdio.h>
#include <QString>
#include <stdlib.h>
#include <cstdlib>

#include "partie.h"
#include "partiegui.h"
#include "case.h"

using namespace std;

Partie::Partie(){
    srand (time(NULL)); // Pour avoir une génération du Plateau aléatoirement.
    this->tokenAnimBombes = 2;
    this->timerAnimBombes = new QTimer(this);
    this->timerAnimBombes->setInterval(300);
    QObject::connect(this->timerAnimBombes, SIGNAL(timeout()), this, SLOT(animationBombes()));
}

void Partie::genererPlateau(){
    int random;
    for(int i=0; i<15; i++){
        this->plateau.append(QVector <Case*>());
        for(int j=0; j<15; j++){
            if(i==0 || j==0 || i==14 || j==14){         // Creation des quatres coins (C.Indestructible)
                this->plateau[i].append(new Case(Case::INDESTRUCTIBLE));
            } else {
                if (i % 2 == 0 && j % 2 == 0){          // Creation des cases interieurs (C.Indestructible)
                    this->plateau[i].append(new Case(Case::INDESTRUCTIBLE));
                } else {
                    /*****************************************************************
                    * On fait les quatres espaces en forme de L pour que les joueurs
                    * puissent bouger au commencement de la partie.
                    *****************************************************************/

                    if(i==1 && (j==1 || j==2 || j==3 || j==12 || j==13)){
                        this->plateau[i].append(new Case(Case::VIDE));
                    } else if (i==2 && (j==1 || j==13)){
                        this->plateau[i].append(new Case(Case::VIDE));
                    } else if (i==3 && j==13){
                        this->plateau[i].append(new Case(Case::VIDE));
                    } else if (i==11 && j==1){
                        this->plateau[i].append(new Case(Case::VIDE));
                    } else if (i==12 && (j==1 || j==13)){
                        this->plateau[i].append(new Case(Case::VIDE));
                    } else if (i== 13 && (j==1 || j==2 || j==11 || j==12 || j==13)){
                        this->plateau[i].append(new Case(Case::VIDE));
                    } else {
                        /*****************************************************************
                        * On cree une variable random, qu'on initialise entre 0 et 4
                        * si la variable est egal a  0, on met une case vide
                        * sinon on met une case destructible.
                        *
                        * Ceci nous permet d'avoir une creation de plateau avec 80% de
                        * case destructible et 20% de case vide.
                        *****************************************************************/

                        random = rand()%5;
                        if(random >= 1){
                            this->plateau[i].append(new Case(Case::DESTRUCTIBLE));
                        } else {
                            this->plateau[i].append(new Case(Case::VIDE));
                        }
                    }
                }
            }
            this->plateau[i][j]->setPartieGui(this->partieGui);
        }
    }
}

void Partie::regenererPlateau()
{
    int random;

    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
            if(i==0 || j==0 || i==14 || j==14){         // Creation des quatres coins (C.Indestructible)
                this->plateau[i][j] = new Case(Case::INDESTRUCTIBLE);
            } else {
                if (i % 2 == 0 && j % 2 == 0){          // Creation des cases interieurs (C.Indestructible)
                    this->plateau[i][j] = new Case(Case::INDESTRUCTIBLE);
                } else {

        // On fait les quatres espaces en forme de L pour que les joueurs
        // Puisse bouger au commencement du jeu

                    if(i==1 && (j==1 || j==2 || j==3 || j==12 || j==13)){
                        this->plateau[i][j] = new Case(Case::VIDE);
                    } else if (i==2 && (j==1 || j==13)){
                        this->plateau[i][j] = new Case(Case::VIDE);
                    } else if (i==3 && j==13){
                        this->plateau[i][j] = new Case(Case::VIDE);
                    } else if (i==11 && j==1){
                        this->plateau[i][j] = new Case(Case::VIDE);
                    } else if (i==12 && (j==1 || j==13)){
                        this->plateau[i][j] = new Case(Case::VIDE);
                    } else if (i== 13 && (j==1 || j==2 || j==11 || j==12 || j==13)){
                        this->plateau[i][j] = new Case(Case::VIDE);
                    } else {

        // On cree une variable random, qu'on initialise entre 0 et 4
        // Si la variable est egal a  0, on met une case vide
        // Sinon on met une case destructible
        //
        // Ceci nous permet d'avoir une creation de plateau avec 80% de case destructible et
        // 20% de case vide.

                        random = rand()%5;
                        if(random >= 1){
                            this->plateau[i][j] = new Case(Case::DESTRUCTIBLE);
                        } else {
                            this->plateau[i][j] = new Case(Case::VIDE);
                        }
                    }
                }
            }
            this->plateau[i][j]->setPartieGui(this->partieGui);
        }
    }
}

void Partie::reinitialiserBomberMans()
{
    // Cette méthode sert lorsqu'une nouvelle manche commence
    this->morts.clear();
    for(int i = 0 ; i < this->nbJoueur ; i++)
    {
        this->bomberMans.at(i)->setMort(false);
        this->bomberMans.at(i)->reinitialiser();
    }
}

void Partie::animationBombes()
{
    /******************************************************************
    * Cette méthode sert à animer toutes les bombes à l'aide d'un
    * seul QTimer, afin d'améliorer les performances
    ******************************************************************/
    for(int i = 0 ; i < this->bombes.size() ; i++)
    {
        if(!this->bombes.at(i)->isExplosee())
        {
            this->bombes.at(i)->animation();
        }
        else if(this->bombes.at(i)->isFinExplosee())
        {
            /******************************************************************
            * Si la bombe a explosée, on la supprime et on l'enlève de QVector
            * afin de ne pas surcharger la mémoire
            ******************************************************************/
            int posX = this->bombes.at(i)->getPosX();
            int posY = this->bombes.at(i)->getPosY();

            this->getPlateau()->at(posX).at(posY)->setContientBombe(false);

            delete this->bombes.at(i);
            this->bombes.remove(i);
        }
    }
}

void Partie::bomberManMort(int victime)
{
    /******************************************************************
    * Si le BomberMan d'indice "victime" n'est pas déjà mort, on
    * l'ajoute à la liste des morts.
    ******************************************************************/
    if(this->morts.indexOf(victime) == -1)
        this->morts.append(victime);

    /******************************************************************
    * S'il ne reste plus qu'un BomberMan de vivant, on vérifie
    * lequel l'est encore, il devient le vainqueur de la manche,
    * ou de la partie s'il possède le nombre de victoires nécessaires
    * pour gagner la partie.
    * On affiche une alerte à l'écran pour signifier que la manche,
    * ou la partie, est finie.
    ******************************************************************/

    if(this->morts.size() == (this->nbJoueur - 1))
    {
        int vainqueur;

        for(int i = 0 ; i < this->nbJoueur ; i++)
        {
            if(this->morts.indexOf(i) == -1)
                vainqueur = i;
        }

        this->bomberMans.value(vainqueur)->getJoueur()->setNbVictoires(this->bomberMans.value(vainqueur)->getJoueur()->getNbVictoires() + 1);

        if(this->bomberMans.at(vainqueur)->getJoueur()->getNbVictoires() < this->nbManchesGagnantes)
        {
            QString texte = "Le joueur " + QString::number(vainqueur + 1) + " a gagné la manche !";
            this->partieGui->afficherAlertFinManche(texte);
        }
        else
        {
            QString texte = "Le joueur " + QString::number(vainqueur + 1) + " a gagné la partie !";
            this->partieGui->afficherAlertFinManche(texte, true);
        }
    }
}

// -------------------------------- //
//        GETTER ET SETTER          //
// -------------------------------- //

int Partie::getnbManchesGagnantes()
{
    return this->nbManchesGagnantes;
}

void Partie::setNbManchesGagnantes(int nbManchesGagnantes)
{
    this->nbManchesGagnantes = nbManchesGagnantes;
}

PartieGui* Partie::getPartieGui()
{
    return this->partieGui;
}

void Partie::setPartieGui(PartieGui *partieGui)
{
    this->partieGui = partieGui;
}

QVector< QVector <Case*> >* Partie::getPlateau(){
    if(this->plateau.size() == 0)
    {    // Si le plateau n'est pas remplit, on le genere avec genererPlateau();
        genererPlateau();
    }

    return &this->plateau;
}

QVector<BomberMan*>* Partie::getBomberMans(){
    if(this->bomberMans.size() == 0){
        for(int i = 0 ; i < this->getNbJoueur() ; i++){
            QString skin;
            QVector<Qt::Key> touches;

            switch(i){
                case 0:
                    skin = this->getSkinJoueur().at(i);
                    touches.append(Qt::Key_Down);
                    touches.append(Qt::Key_Up);
                    touches.append(Qt::Key_Right);
                    touches.append(Qt::Key_Left);
                    touches.append(Qt::Key_Control);
                    break;
                case 1:
                    skin = this->getSkinJoueur().at(i);
                    touches.append(Qt::Key_S);
                    touches.append(Qt::Key_Z);
                    touches.append(Qt::Key_D);
                    touches.append(Qt::Key_Q);
                    touches.append(Qt::Key_W);
                    break;
                case 2:
                    skin = this->getSkinJoueur().at(i);
                    touches.append(Qt::Key_B);
                    touches.append(Qt::Key_G);
                    touches.append(Qt::Key_N);
                    touches.append(Qt::Key_V);
                    touches.append(Qt::Key_Space);
                    break;
                case 3:
                    skin = this->getSkinJoueur().at(i);
                    touches.append(Qt::Key_L);
                    touches.append(Qt::Key_O);
                    touches.append(Qt::Key_M);
                    touches.append(Qt::Key_K);
                    touches.append(Qt::Key_Shift);
                    break;
            }

            this->bomberMans.append(new BomberMan((i), skin));
            this->bomberMans.at(i)->setTouches(touches);
        }
    }

    return &this->bomberMans;
}

QVector<Bombe*>* Partie::getBombes()
{
    return &this->bombes;
}

QTimer* Partie::getTimerAnimBombes()
{
    return this->timerAnimBombes;
}

void Partie::setNbJoueur(int _nbJoueur){
    this->nbJoueur = _nbJoueur;
}

int Partie::getNbJoueur(){
    return this->nbJoueur;
}

void Partie::setSkinJoueur(QVector<QString> _skinJoueur){
    this->skinJoueur = _skinJoueur;
}

QVector<QString> Partie::getSkinJoueur(){
    return this->skinJoueur;
}

bool Partie::isMancheTerminee()
{
    return this->mancheTerminee;
}

void Partie::setMancheTerminee(bool mancheTerminee)
{
    this->mancheTerminee = mancheTerminee;
}
