/****************************************************************************
** Meta object code from reading C++ file 'playvideowin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../view/playvideowin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playvideowin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CPlayVideo_t {
    QByteArrayData data[20];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPlayVideo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPlayVideo_t qt_meta_stringdata_CPlayVideo = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CPlayVideo"
QT_MOC_LITERAL(1, 11, 13), // "saveVideoName"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "VideoName"
QT_MOC_LITERAL(4, 36, 6), // "isPlay"
QT_MOC_LITERAL(5, 43, 8), // "stopPlay"
QT_MOC_LITERAL(6, 52, 7), // "exitWin"
QT_MOC_LITERAL(7, 60, 15), // "saveScreenShoot"
QT_MOC_LITERAL(8, 76, 9), // "saveVideo"
QT_MOC_LITERAL(9, 86, 10), // "reciveSlot"
QT_MOC_LITERAL(10, 97, 3), // "img"
QT_MOC_LITERAL(11, 101, 7), // "prePlay"
QT_MOC_LITERAL(12, 109, 8), // "nextPlay"
QT_MOC_LITERAL(13, 118, 11), // "changeSpeed"
QT_MOC_LITERAL(14, 130, 14), // "showListWidget"
QT_MOC_LITERAL(15, 145, 10), // "chooseFile"
QT_MOC_LITERAL(16, 156, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(17, 173, 14), // "hideMpShadeWin"
QT_MOC_LITERAL(18, 188, 12), // "hidePhotoWin"
QT_MOC_LITERAL(19, 201, 10) // "flashFrame"

    },
    "CPlayVideo\0saveVideoName\0\0VideoName\0"
    "isPlay\0stopPlay\0exitWin\0saveScreenShoot\0"
    "saveVideo\0reciveSlot\0img\0prePlay\0"
    "nextPlay\0changeSpeed\0showListWidget\0"
    "chooseFile\0QListWidgetItem*\0hideMpShadeWin\0"
    "hidePhotoWin\0flashFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPlayVideo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   92,    2, 0x0a /* Public */,
       5,    0,   93,    2, 0x0a /* Public */,
       6,    0,   94,    2, 0x0a /* Public */,
       7,    0,   95,    2, 0x0a /* Public */,
       8,    0,   96,    2, 0x0a /* Public */,
       9,    1,   97,    2, 0x0a /* Public */,
      11,    0,  100,    2, 0x0a /* Public */,
      12,    0,  101,    2, 0x0a /* Public */,
      13,    0,  102,    2, 0x0a /* Public */,
      14,    0,  103,    2, 0x0a /* Public */,
      15,    1,  104,    2, 0x0a /* Public */,
      17,    0,  107,    2, 0x0a /* Public */,
      18,    0,  108,    2, 0x0a /* Public */,
      19,    1,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void CPlayVideo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CPlayVideo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveVideoName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->isPlay(); break;
        case 2: _t->stopPlay(); break;
        case 3: _t->exitWin(); break;
        case 4: _t->saveScreenShoot(); break;
        case 5: _t->saveVideo(); break;
        case 6: _t->reciveSlot((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 7: _t->prePlay(); break;
        case 8: _t->nextPlay(); break;
        case 9: _t->changeSpeed(); break;
        case 10: _t->showListWidget(); break;
        case 11: _t->chooseFile((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 12: _t->hideMpShadeWin(); break;
        case 13: _t->hidePhotoWin(); break;
        case 14: _t->flashFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CPlayVideo::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPlayVideo::saveVideoName)) {
                *result = 0;
                return;
            }
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void CPlayVideo::saveVideoName(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
