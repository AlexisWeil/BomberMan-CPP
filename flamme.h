#ifndef FLAMME_H
#define FLAMME_H

#include <QWidget>
#include <QLabel>

class Flamme : public QWidget
{
public:
    enum TypeFlamme { CENTRE, HAUT, BAS, DROITE, GAUCHE, _NULL_ };
    Flamme(TypeFlamme type, int posX, int posY, bool fin = false);
    QLabel* getImage();
    void setImage(QString nomImage);
    int getPosX();
    void setPosX(int posX);
    int getPosY();
    void setPosY(int posY);

private:
    QLabel* image;
    int posX, posY;
};

#endif // FLAMME_H
