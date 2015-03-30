#ifndef MENUPRINCIPALGUI_H
#define MENUPRINCIPALGUI_H

#include <QWidget>
#include <QComboBox>
#include <QVector>

#include "partiegui.h"

class PartieGui;

class MenuPrincipalGui : public QWidget
{
Q_OBJECT
public:
    explicit MenuPrincipalGui(QWidget *parent = 0);
    void jeuLocal(int nbJoueur);

signals:

public slots:
    void previewJeuLocalSlot();
    void jeuLocalSlot2();
    void jeuLocalSlot3();
    void jeuLocalSlot4();
    void lancerJeuSlot();
    void retourMain();
    void retourPreviewJeuLocal();
    void quitterJeuEnCours();

private:
    int nbJoueur;
    QVector <QString> skinJoueur;
    QWidget mainWidget;
    QWidget menuPrincipalWidget;
    QWidget previewJeuLocalWidget;
    QWidget* jeuLocalWidget;

    QComboBox *nombreTimer;
    QComboBox *nombreManche;
    QComboBox *bomberManOneCouleur;
    QComboBox *bomberManTwoCouleur;
    QComboBox *bomberManThreeCouleur;
    QComboBox *bomberManFourCouleur;
    PartieGui *p;
};

#endif // MENUPRINCIPALGUI_H
