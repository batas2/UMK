/****************************************************************************
** Meta object code from reading C++ file 'MyWidget.h'
**
** Created: Tue Apr 6 22:40:27 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MyWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      31,    9,    9,    9, 0x0a,
      52,    9,    9,    9, 0x0a,
      73,    9,    9,    9, 0x0a,
      94,    9,    9,    9, 0x0a,
     115,    9,    9,    9, 0x0a,
     136,    9,    9,    9, 0x0a,
     157,    9,    9,    9, 0x0a,
     178,    9,    9,    9, 0x0a,
     199,    9,    9,    9, 0x0a,
     220,    9,    9,    9, 0x0a,
     241,    9,    9,    9, 0x0a,
     262,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyWidget[] = {
    "MyWidget\0\0setRSliderValue(int)\0"
    "setGSliderValue(int)\0setBSliderValue(int)\0"
    "setHSliderValue(int)\0setSSliderValue(int)\0"
    "setVSliderValue(int)\0setCSliderValue(int)\0"
    "setMSliderValue(int)\0setYSliderValue(int)\0"
    "setKSliderValue(int)\0setLSliderValue(int)\0"
    "setaSliderValue(int)\0setbSliderValue(int)\0"
};

const QMetaObject MyWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyWidget,
      qt_meta_data_MyWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyWidget))
        return static_cast<void*>(const_cast< MyWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setRSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setGSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: setBSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setHSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setSSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: setVSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: setCSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: setMSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: setYSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: setKSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: setLSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: setaSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: setbSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
