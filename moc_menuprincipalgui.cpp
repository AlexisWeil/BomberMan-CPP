/****************************************************************************
** Meta object code from reading C++ file 'menuprincipalgui.h'
**
** Created: Mon May 31 11:14:42 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "menuprincipalgui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menuprincipalgui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MenuPrincipalGui[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      37,   17,   17,   17, 0x0a,
      52,   17,   17,   17, 0x0a,
      74,   17,   17,   17, 0x0a,
      90,   17,   17,   17, 0x0a,
     106,   17,   17,   17, 0x0a,
     122,   17,   17,   17, 0x0a,
     138,   17,   17,   17, 0x0a,
     152,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MenuPrincipalGui[] = {
    "MenuPrincipalGui\0\0menuPrincipalGui()\0"
    "tutorielSlot()\0previewJeuLocalSlot()\0"
    "jeuLocalSlot2()\0jeuLocalSlot3()\0"
    "jeuLocalSlot4()\0jeuReseauSlot()\0"
    "optionsSlot()\0lancerJeuSlot()\0"
};

const QMetaObject MenuPrincipalGui::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MenuPrincipalGui,
      qt_meta_data_MenuPrincipalGui, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MenuPrincipalGui::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MenuPrincipalGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MenuPrincipalGui::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MenuPrincipalGui))
        return static_cast<void*>(const_cast< MenuPrincipalGui*>(this));
    return QWidget::qt_metacast(_clname);
}

int MenuPrincipalGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: menuPrincipalGui(); break;
        case 1: tutorielSlot(); break;
        case 2: previewJeuLocalSlot(); break;
        case 3: jeuLocalSlot2(); break;
        case 4: jeuLocalSlot3(); break;
        case 5: jeuLocalSlot4(); break;
        case 6: jeuReseauSlot(); break;
        case 7: optionsSlot(); break;
        case 8: lancerJeuSlot(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
