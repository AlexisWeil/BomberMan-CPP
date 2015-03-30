#ifndef BONUS_H
#define BONUS_H

#include <QWidget>
#include <QLabel>
#include "case.h"

class PartieGui;
class Case;

class Bonus : public QWidget
{
public:
    enum TypeBonus { PUISSANCE_UP, PUISSANCE_DOWN, BOMBE_UP, BOMBE_DOWN, PUISSANCE_MAX, BOMBE_MAX, VITESSE_UP, VITESSE_DOWN };
    Bonus(TypeBonus type);
    void activer(int numBomberMan);
    PartieGui* getPartieGui();
    void setPartieGui(PartieGui* partieGui);
    TypeBonus getType();
    void setType(TypeBonus type);
    QLabel* getImage();
    void setImage(QString nomImage);
    Case* getCaseParente();
    void setCaseParente(Case* caseParente);

private:
    PartieGui* partieGui;
    TypeBonus type;
    QLabel* image;
    Case* caseParente;
};

#endif // BONUS_H
