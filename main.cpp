#include <QtGui/QApplication>

#include "partiegui.h"
#include "menuprincipalgui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuPrincipalGui m;
    return a.exec();
}
