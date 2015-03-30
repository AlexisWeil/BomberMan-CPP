#ifndef BOMBE_H
#define BOMBE_H

#include <QTimer>

#include "partie.h"
#include "flamme.h"
#include "bombeexplosionthread.h"
#include "case.h"

class PartieGui;

class Bombe : public QWidget
{
    Q_OBJECT

public:
    Bombe(int proprietaire, PartieGui* partieGui);
    ~Bombe();
    void animation();

    int getProprietaire();
    void setProprietaire(int proprietaire);
    int getPosX();
    void setPosX(int posX);
    int getPosY();
    void setPosY(int posY);
    int getPortee();
    void setPortee(int portee);
    QLabel* getImage();
    void setImage(QString nomImage);
    bool isExplosee();
    void setExplosee(bool explosee);
    bool isFinExplosee();
    void setFinExplosee(bool finExplosee);

public slots:
    void explosion();
    void finExplosion();
    void animationFinExplosion();

private:
    int proprietaire;
    int posX, posY, posXCaseRempl, posYCaseRempl;
    int porteeExplosion;
    int tokenAnim;
    int tokenAnimFin;
    QLabel* image;
    bool explosee;
    bool finExplosee;
    QVector<Flamme*> flammes;
    PartieGui* partieGui;
    BombeExplosionThread* thread;
    void detruireCase(int posX, int posY);
};

#endif // BOMBE_H
