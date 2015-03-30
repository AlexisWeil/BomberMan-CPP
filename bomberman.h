#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include <QPainter>
#include <math.h>

#include "joueur.h"
#include "bombermanslots.h"
#include "bombermanmortthread.h"

class BomberManSlots;
class PartieGui;

class BomberMan : public QWidget
{
    Q_OBJECT
public:
    BomberMan(int numero, QString skin);
    BomberMan(int numero, QString skin, QString pseudo);
    ~BomberMan();
    void reinitialiser();
    void deplacement(QString);
    void stopDeplacement();
    void mourir();

    PartieGui* getPartieGui();
    void setPartieGui(PartieGui* partieGui);
    Joueur* getJoueur();
    void setJoueur(Joueur* joueur);
    BomberManSlots* getSlots();
    void setSlots(BomberManSlots* bomberManSlots);
    bool isMort();
    void setMort(bool mort);
    int getNbBombesMax();
    void setNbBombesMax(int nb);
    int getNbBombesPosees();
    void setNbBombesPosees(int nb);
    int getPorteeExplosion();
    void setPorteeExplosion(int portee);
    bool hasPorteeMax();
    void setPorteeMax(bool porteeMax);
    int getPosX();
    void setPosX(int posX);
    int getPosY();
    void setPosY(int posY);
    QString getSkin();
    void setSkin(QString skin);
    QLabel* getImage();
    void setImage(QString nomImage);
    int getVitesse();
    void setVitesse(int vitesse);
    QVector<Qt::Key> getTouches();
    void setTouches(QVector<Qt::Key> touches);

public slots:
    void deplacer();

private:
    void initialisation();
    PartieGui* partieGui;
    Joueur* joueur;
    BomberManSlots* bomberManSlots;
    BomberManMortThread* threadMort;
    bool mort;
    int nbBombesMax, nbBombesPosees, porteeExplosion;
    bool porteeMax;
    int posX, posY;
    QString skin;
    QLabel* image;
    int vitesse;
    QVector<Qt::Key> touches;
};

#endif // BOMBERMAN_H
