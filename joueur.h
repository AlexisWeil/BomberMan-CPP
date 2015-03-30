#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString>

class Joueur
{
public:
    Joueur(int numero, QString pseudo);
    QString getPseudo();
    void setPseudo(QString pseudo);
    int getNbVictoires();
    void setNbVictoires(int nbVictoires);
    int getNumero();
    void setNumero(int numero);

private:
    QString pseudo;
    int nbVictoires;
    int numero;
};

#endif // JOUEUR_H
