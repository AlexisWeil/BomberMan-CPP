#include "joueur.h"

Joueur::Joueur(int numero, QString pseudo)
{
    this->numero = numero;
    this->pseudo = pseudo;
    this->nbVictoires = 0;
}

QString Joueur::getPseudo()
{
    return this->pseudo;
}

void Joueur::setPseudo(QString pseudo)
{
    this->pseudo = pseudo;
}

int Joueur::getNbVictoires()
{
    return this->nbVictoires;
}

void Joueur::setNbVictoires(int nbVictoires)
{
    this->nbVictoires = nbVictoires;
}

int Joueur::getNumero()
{
    return this->numero;
}

void Joueur::setNumero(int numero)
{
    this->numero = numero;
}
