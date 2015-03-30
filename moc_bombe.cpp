/****************************************************************************
** Meta object code from reading C++ file 'bombe.h'
**
** Created: Mon May 31 09:22:34 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "bombe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bombe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Bombe[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x0a,
      19,    6,    6,    6, 0x0a,
      34,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Bombe[] = {
    "Bombe\0\0explosion()\0finExplosion()\0"
    "animationFinExplosion()\0"
};

const QMetaObject Bombe::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Bombe,
      qt_meta_data_Bombe, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Bombe::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Bombe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Bombe::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Bombe))
        return static_cast<void*>(const_cast< Bombe*>(this));
    return QWidget::qt_metacast(_clname);
}

int Bombe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: explosion(); break;
        case 1: finExplosion(); break;
        case 2: animationFinExplosion(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
