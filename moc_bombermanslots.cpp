/****************************************************************************
** Meta object code from reading C++ file 'bombermanslots.h'
**
** Created: Mon May 31 09:14:27 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "bombermanslots.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bombermanslots.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BomberManSlots[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   16,   15,   15, 0x0a,
      47,   15,   15,   15, 0x0a,
      59,   15,   15,   15, 0x0a,
      72,   15,   15,   15, 0x0a,
      88,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BomberManSlots[] = {
    "BomberManSlots\0\0direction\0"
    "startTimers(QString)\0animation()\0"
    "stopTimers()\0animationStop()\0"
    "animationMort()\0"
};

const QMetaObject BomberManSlots::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BomberManSlots,
      qt_meta_data_BomberManSlots, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BomberManSlots::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BomberManSlots::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BomberManSlots::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BomberManSlots))
        return static_cast<void*>(const_cast< BomberManSlots*>(this));
    return QObject::qt_metacast(_clname);
}

int BomberManSlots::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: startTimers((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: animation(); break;
        case 2: stopTimers(); break;
        case 3: animationStop(); break;
        case 4: animationMort(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
