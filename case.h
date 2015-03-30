#ifndef CASE_H
#define CASE_H

#include <QString>
#include <QWidget>
#include <QLabel>

#include "bombe.h"
#include "casedestructionthread.h"
#include "bonus.h"

class Bombe;
class PartieGui;
class Bonus;

class Case : public QWidget
{
    Q_OBJECT
public:
    enum TypeCase { VIDE, DESTRUCTIBLE, INDESTRUCTIBLE };
    Case(TypeCase type);
    PartieGui* getPartieGui();
    void setPartieGui(PartieGui* partieGui);
    TypeCase getType();
    void setType(TypeCase type);
    QLabel* getImage();
    void setImage(QString nomImage);
    Bombe* getBombe();
    void setBombe(Bombe* bombe);
    int getBomberMan();
    void setBomberMan(int numero);
    Bonus* getBonus();
    void setBonus(Bonus* bonus);
    bool getContientBombe();
    void setContientBombe(bool contientBombe);
    bool getContientFlamme();
    void setContientFlamme(bool contientFlamme);
    bool getContientBonus();
    void setContientBonus(bool contientBonus);
    CaseDestructionThread* getThreadDestruction();

public slots:
    void animationDestruction();
    void finDestruction();

private:
    PartieGui* partieGui;
    TypeCase typeCase;
    QLabel* image;
    Bombe* bombe;
    int bomberMan;
    Bonus* bonus;
    bool contientBombe;
    bool contientFlamme;
    bool contientBonus;
    int tokenAnim;
    CaseDestructionThread* threadDestruction;

};

#endif // CASE_H
