#ifndef PARTIEGUI_H
#define PARTIEGUI_H

#include <QWidget>
#include <QLabel>

#include "partie.h"
#include "menuprincipalgui.h"

class Partie;
class MenuPrincipalGui;

class PartieGui : public QWidget
{
    Q_OBJECT

public:
    PartieGui(int, int, int, QVector<QString>, MenuPrincipalGui*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void afficherTimer();
    void afficherAlertFinManche(QString texte, bool finPartie = false);

    Partie* getPartie();
    MenuPrincipalGui* getMenuPrincipalGui();
    void setMenuPrincipalGui(MenuPrincipalGui*);
    void getConteneurPoints();
    void setConteneurPoints(QWidget);
    QWidget getConteneurCentral();
    void setConteneurCentral(QWidget);
    void getConteneurBoutons();
    void setConteneurBoutons(QWidget);
    QWidget getConteneurPlateau();
    void setConteneurPlateau(QWidget);
    void genererPlateau();
    QWidget* getPlateau();
    void setPlateau(QWidget);
    QWidget* getWidgetExplosions();
    void setWidgetExplosions(QWidget);
    QWidget* getWidgetBomberMans();
    void setWidgetBomberMans(QWidget);

public slots :
    void compter();
    void recommencerManche();

private:
    Partie partie;
    MenuPrincipalGui* menuPrincipalGui;

    int nbMinutes;
    int nbJoueur;
    QVector<QString> skinJoueur;
    int compteur;
    QTimer *timer;
    QLabel *timerMinuteLabel;
    QLabel *timerDizaineSecondeLabel;
    QLabel *timerSecondeLabel;

    QWidget conteneurPoints;
    QWidget conteneurCentral;
    QWidget conteneurBoutons;
    QWidget conteneurPlateau;
    QWidget plateau;
    QWidget widgetExplosions;
    QWidget widgetBomberMans;
    QWidget widgetAlertFinManche;
};

#endif // PARTIEGUI_H
