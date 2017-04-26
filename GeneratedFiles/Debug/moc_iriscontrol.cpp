/****************************************************************************
** Meta object code from reading C++ file 'iriscontrol.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../iriscontrol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iriscontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IRIScontrol[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      30,   12,   12,   12, 0x0a,
      48,   12,   12,   12, 0x0a,
      71,   12,   12,   12, 0x0a,
      86,   12,   12,   12, 0x0a,
     107,   12,   12,   12, 0x0a,
     125,   12,   12,   12, 0x0a,
     148,  143,   12,   12, 0x0a,
     182,  143,   12,   12, 0x0a,
     217,  143,   12,   12, 0x0a,
     252,  143,   12,   12, 0x0a,
     287,   12,   12,   12, 0x0a,
     322,   12,  317,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_IRIScontrol[] = {
    "IRIScontrol\0\0OnButtonEnable()\0"
    "OnButtonDisable()\0OnButtonEnableTeleop()\0"
    "OnButtonMove()\0OnButtonMoveToPose()\0"
    "OnRadioRelative()\0OnRadioAbsolute()\0"
    "text\0UpdateTargetPositionText(QString)\0"
    "UpdateTargetPositionText2(QString)\0"
    "UpdateTargetPositionText3(QString)\0"
    "UpdateTargetPositionText4(QString)\0"
    "UpdateTargetRollText(QString)\0BOOL\0"
    "UpdateStatus()\0"
};

void IRIScontrol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IRIScontrol *_t = static_cast<IRIScontrol *>(_o);
        switch (_id) {
        case 0: _t->OnButtonEnable(); break;
        case 1: _t->OnButtonDisable(); break;
        case 2: _t->OnButtonEnableTeleop(); break;
        case 3: _t->OnButtonMove(); break;
        case 4: _t->OnButtonMoveToPose(); break;
        case 5: _t->OnRadioRelative(); break;
        case 6: _t->OnRadioAbsolute(); break;
        case 7: _t->UpdateTargetPositionText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->UpdateTargetPositionText2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->UpdateTargetPositionText3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->UpdateTargetPositionText4((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->UpdateTargetRollText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: { BOOL _r = _t->UpdateStatus();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IRIScontrol::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IRIScontrol::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_IRIScontrol,
      qt_meta_data_IRIScontrol, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IRIScontrol::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IRIScontrol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IRIScontrol::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IRIScontrol))
        return static_cast<void*>(const_cast< IRIScontrol*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int IRIScontrol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
