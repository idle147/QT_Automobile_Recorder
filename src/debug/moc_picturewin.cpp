/****************************************************************************
** Meta object code from reading C++ file 'picturewin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../view/picturewin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'picturewin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CPictureWin_t {
    QByteArrayData data[10];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPictureWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPictureWin_t qt_meta_stringdata_CPictureWin = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CPictureWin"
QT_MOC_LITERAL(1, 12, 10), // "getAllFile"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "getTimeFile"
QT_MOC_LITERAL(4, 36, 7), // "curTime"
QT_MOC_LITERAL(5, 44, 9), // "searchPic"
QT_MOC_LITERAL(6, 54, 14), // "amplifyPicture"
QT_MOC_LITERAL(7, 69, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 86, 12), // "shinkPicture"
QT_MOC_LITERAL(9, 99, 7) // "exitFun"

    },
    "CPictureWin\0getAllFile\0\0getTimeFile\0"
    "curTime\0searchPic\0amplifyPicture\0"
    "QListWidgetItem*\0shinkPicture\0exitFun"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPictureWin[] = {

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
       1,    0,   44,    2, 0x0a /* Public */,
       3,    1,   45,    2, 0x0a /* Public */,
       5,    0,   48,    2, 0x0a /* Public */,
       6,    1,   49,    2, 0x0a /* Public */,
       8,    0,   52,    2, 0x0a /* Public */,
       9,    1,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,

       0        // eod
};

void CPictureWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CPictureWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getAllFile(); break;
        case 1: _t->getTimeFile((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 2: _t->searchPic(); break;
        case 3: _t->amplifyPicture((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->shinkPicture(); break;
        case 5: _t->exitFun((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CPictureWin::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CPictureWin.data,
    qt_meta_data_CPictureWin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CPictureWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPictureWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CPictureWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CPictureWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
