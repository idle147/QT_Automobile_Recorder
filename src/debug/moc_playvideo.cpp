/****************************************************************************
** Meta object code from reading C++ file 'playvideo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../view/playvideo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playvideo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CPlayVideo_t {
    QByteArrayData data[15];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPlayVideo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPlayVideo_t qt_meta_stringdata_CPlayVideo = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CPlayVideo"
QT_MOC_LITERAL(1, 11, 6), // "isPlay"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 8), // "stopPlay"
QT_MOC_LITERAL(4, 28, 7), // "exitWin"
QT_MOC_LITERAL(5, 36, 15), // "saveScreenShoot"
QT_MOC_LITERAL(6, 52, 10), // "reciveSlot"
QT_MOC_LITERAL(7, 63, 3), // "img"
QT_MOC_LITERAL(8, 67, 7), // "prePlay"
QT_MOC_LITERAL(9, 75, 8), // "nextPlay"
QT_MOC_LITERAL(10, 84, 11), // "changeSpeed"
QT_MOC_LITERAL(11, 96, 14), // "showListWidget"
QT_MOC_LITERAL(12, 111, 10), // "chooseFile"
QT_MOC_LITERAL(13, 122, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(14, 139, 14) // "hideMpShadeWin"

    },
    "CPlayVideo\0isPlay\0\0stopPlay\0exitWin\0"
    "saveScreenShoot\0reciveSlot\0img\0prePlay\0"
    "nextPlay\0changeSpeed\0showListWidget\0"
    "chooseFile\0QListWidgetItem*\0hideMpShadeWin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPlayVideo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    1,   73,    2, 0x0a /* Public */,
       8,    0,   76,    2, 0x0a /* Public */,
       9,    0,   77,    2, 0x0a /* Public */,
      10,    0,   78,    2, 0x0a /* Public */,
      11,    0,   79,    2, 0x0a /* Public */,
      12,    1,   80,    2, 0x0a /* Public */,
      14,    0,   83,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void,

       0        // eod
};

void CPlayVideo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CPlayVideo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->isPlay(); break;
        case 1: _t->stopPlay(); break;
        case 2: _t->exitWin(); break;
        case 3: _t->saveScreenShoot(); break;
        case 4: _t->reciveSlot((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 5: _t->prePlay(); break;
        case 6: _t->nextPlay(); break;
        case 7: _t->changeSpeed(); break;
        case 8: _t->showListWidget(); break;
        case 9: _t->chooseFile((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 10: _t->hideMpShadeWin(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CPlayVideo::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CPlayVideo.data,
    qt_meta_data_CPlayVideo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CPlayVideo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPlayVideo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CPlayVideo.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CPlayVideo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
