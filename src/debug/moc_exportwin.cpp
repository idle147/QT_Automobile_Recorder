/****************************************************************************
** Meta object code from reading C++ file 'exportwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../view/exportwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'exportwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CExportWin_t {
    QByteArrayData data[14];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CExportWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CExportWin_t qt_meta_stringdata_CExportWin = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CExportWin"
QT_MOC_LITERAL(1, 11, 10), // "getAllFile"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "getTimeFile"
QT_MOC_LITERAL(4, 35, 7), // "curTime"
QT_MOC_LITERAL(5, 43, 11), // "searchVideo"
QT_MOC_LITERAL(6, 55, 11), // "chooseVideo"
QT_MOC_LITERAL(7, 67, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 84, 15), // "chooseExportUrl"
QT_MOC_LITERAL(9, 100, 8), // "doExport"
QT_MOC_LITERAL(10, 109, 10), // "flashFrame"
QT_MOC_LITERAL(11, 120, 11), // "curFrameNum"
QT_MOC_LITERAL(12, 132, 14), // "flashExportUrl"
QT_MOC_LITERAL(13, 147, 7) // "exitFun"

    },
    "CExportWin\0getAllFile\0\0getTimeFile\0"
    "curTime\0searchVideo\0chooseVideo\0"
    "QListWidgetItem*\0chooseExportUrl\0"
    "doExport\0flashFrame\0curFrameNum\0"
    "flashExportUrl\0exitFun"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CExportWin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    1,   60,    2, 0x0a /* Public */,
       5,    0,   63,    2, 0x0a /* Public */,
       6,    1,   64,    2, 0x0a /* Public */,
       8,    0,   67,    2, 0x0a /* Public */,
       9,    0,   68,    2, 0x0a /* Public */,
      10,    1,   69,    2, 0x0a /* Public */,
      12,    1,   72,    2, 0x0a /* Public */,
      13,    1,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 7,    2,

       0        // eod
};

void CExportWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CExportWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getAllFile(); break;
        case 1: _t->getTimeFile((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 2: _t->searchVideo(); break;
        case 3: _t->chooseVideo((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->chooseExportUrl(); break;
        case 5: _t->doExport(); break;
        case 6: _t->flashFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->flashExportUrl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->exitFun((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CExportWin::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CExportWin.data,
    qt_meta_data_CExportWin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CExportWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CExportWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CExportWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CExportWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
