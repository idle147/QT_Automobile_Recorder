/****************************************************************************
** Meta object code from reading C++ file 'hischoosewin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../view/hischoosewin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hischoosewin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CHisChoose_t {
    QByteArrayData data[11];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CHisChoose_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CHisChoose_t qt_meta_stringdata_CHisChoose = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CHisChoose"
QT_MOC_LITERAL(1, 11, 14), // "listWinAddItem"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "num"
QT_MOC_LITERAL(4, 31, 10), // "getAllFile"
QT_MOC_LITERAL(5, 42, 11), // "getTimeFile"
QT_MOC_LITERAL(6, 54, 7), // "curTime"
QT_MOC_LITERAL(7, 62, 11), // "searchVideo"
QT_MOC_LITERAL(8, 74, 9), // "playVideo"
QT_MOC_LITERAL(9, 84, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(10, 101, 7) // "exitFun"

    },
    "CHisChoose\0listWinAddItem\0\0num\0"
    "getAllFile\0getTimeFile\0curTime\0"
    "searchVideo\0playVideo\0QListWidgetItem*\0"
    "exitFun"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CHisChoose[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       4,    0,   47,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,
       8,    1,   52,    2, 0x0a /* Public */,
      10,    1,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 9,    2,

       0        // eod
};

void CHisChoose::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CHisChoose *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->listWinAddItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->getAllFile(); break;
        case 2: _t->getTimeFile((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 3: _t->searchVideo(); break;
        case 4: _t->playVideo((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->exitFun((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CHisChoose::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CHisChoose.data,
    qt_meta_data_CHisChoose,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CHisChoose::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CHisChoose::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CHisChoose.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CHisChoose::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
