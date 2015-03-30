#ifndef PARTIE_H
#define PARTIE_H

#include <QVector>
#include <QString>
#include <string>

#include "case.h"
#include "bomberman.h"
#include "bombe.h"

class BomberMan;
class Case;
class Bombe;

class Partie : public QObject
{
    Q_OBJECT
public:
    Partie();
    void genererPlateau();
    void regenererPlateau();
    void reinitialiserBomberMans();
    void bomberManMort(int victime);
    int getnbManchesGagnantes();
    void setNbManchesGagnantes(int);
    PartieGui* getPartieGui();
    void setPartieGui(PartieGui* partieGui);
    QVector< QVector <Case*> >* getPlateau();
    QVector<BomberMan*>* getBomberMans();
    QVector<Bombe*>* getBombes();
    QTimer* getTimerAnimBombes();
    void setNbJoueur(int);
    int getNbJoueur();
    void setSkinJoueur(QVector <QString>);
    QVector <QString> getSkinJoueur();
    bool isMancheTerminee();
    void setMancheTerminee(bool mancheTerminee);

public slots:
    void animationBombes();

private:
    PartieGui* partieGui;
    QVector< QVector<Case*> > plateau;
    int nbManchesGagnantes;
    QVector<BomberMan*> bomberMans;
    QVector<Bombe*> bombes;
    QVector<int> morts;
    int tokenAnimBombes;
    QTimer* timerAnimBombes;
    int nbJoueur;
    QVector<QString> skinJoueur;
    bool mancheTerminee;
};

#endif // PARTIE_H
