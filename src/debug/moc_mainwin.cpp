/****************************************************************************
** Meta object code from reading C++ file 'mainwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../view/mainwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CMainWin_t {
    QByteArrayData data[12];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CMainWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CMainWin_t qt_meta_stringdata_CMainWin = {
    {
QT_MOC_LITERAL(0, 0, 8), // "CMainWin"
QT_MOC_LITERAL(1, 9, 10), // "judgeLogin"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 10), // "updateTime"
QT_MOC_LITERAL(4, 32, 11), // "openSetList"
QT_MOC_LITERAL(5, 44, 10), // "reciveSlot"
QT_MOC_LITERAL(6, 55, 3), // "img"
QT_MOC_LITERAL(7, 59, 8), // "doOption"
QT_MOC_LITERAL(8, 68, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(9, 85, 7), // "savePic"
QT_MOC_LITERAL(10, 93, 14), // "hideMpShadeWin"
QT_MOC_LITERAL(11, 108, 12) // "hidePhotoWin"

    },
    "CMainWin\0judgeLogin\0\0updateTime\0"
    "openSetList\0reciveSlot\0img\0doOption\0"
    "QListWidgetItem*\0savePic\0hideMpShadeWin\0"
    "hidePhotoWin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMainWin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    1,   57,    2, 0x0a /* Public */,
       7,    1,   60,    2, 0x0a /* Public */,
       9,    0,   63,    2, 0x0a /* Public */,
      10,    0,   64,    2, 0x0a /* Public */,
      11,    0,   65,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    6,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CMainWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CMainWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->judgeLogin();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->updateTime(); break;
        case 2: _t->openSetList(); break;
        case 3: _t->reciveSlot((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 4: _t->doOption((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->savePic(); break;
        case 6: _t->hideMpShadeWin(); break;
        case 7: _t->hidePhotoWin(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CMainWin::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CMainWin.data,
    qt_meta_data_CMainWin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CMainWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CMainWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CMainWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CMainWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
