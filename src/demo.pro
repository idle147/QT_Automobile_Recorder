QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#设置C++11的标准版本
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#设置源码
SOURCES += \
    controller/ctool.cpp \
    controller/dateedit.cpp \
    controller/decodevideo.cpp \
    controller/encodevideo.cpp \
    controller/filetool.cpp \
    controller/getsetinfo.cpp \
    controller/myController.cpp \
    controller/recodevideo.cpp \
    main.cpp \
    model/userModel.cpp \
    dataclass/dataopt.cpp \
    dataclass/user.cpp \
    view/exportwidget.cpp \
    view/exportwin.cpp \
    view/hischoosewin.cpp \
    view/item/caritem.cpp \
    view/item/peopleitem.cpp \
    view/item/titleitem.cpp \
    view/loginwin.cpp \
    view/mainwin.cpp \
    view/managewin.cpp \
    view/menulistwidget.cpp \
    view/pagewidget.cpp \
    view/picturewin.cpp \
    view/playvideowin.cpp \
    view/registwin.cpp \
    view/setwin.cpp \
    view/startwin.cpp

#设置头文件
HEADERS += \
    controller/ctool.h \
    controller/dateedit.h \
    controller/decodevideo.h \
    controller/encodevideo.h \
    controller/filetool.h \
    controller/getsetinfo.h \
    controller/myController.h \
    controller/recodevideo.h \
    dataclass/dataopt.h \
    dataclass/sqlite3.h \
    dataclass/user.h \
    model/userModel.h \
    view/exportwidget.h \
    view/exportwin.h \
    view/hischoosewin.h \
    view/item/caritem.h \
    view/item/peopleitem.h \
    view/item/titleitem.h \
    view/loginwin.h \
    view/mainwin.h \
    view/managewin.h \
    view/menulistwidget.h \
    view/pagewidget.h \
    view/peopleitem.h \
    view/picturewin.h \
    view/playvideowin.h \
    view/registwin.h \
    view/setwin.h \
    view/startwin.h

#可供多语言翻译的文本
TRANSLATIONS += \
    zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#加入资源文件夹
RESOURCES += ../resources/resources.qrc

#设置输入文件夹
DESTDIR = ../bin/

#导入sqlite3动态库
LIBS += -L$$PWD/../lib/ -lsqlite3

#导入ffmpeg动态库
LIBS += -L$$PWD/../lib/ffmpeglib/lib/ -lavcodec
LIBS += -L$$PWD/../lib/ffmpeglib/lib/ -lavdevice
LIBS += -L$$PWD/../lib/ffmpeglib/lib/ -lavfilter
LIBS += -L$$PWD/../lib/ffmpeglib/lib/ -lavformat
LIBS += -L$$PWD/../lib/ffmpeglib/lib/ -lavutil
LIBS += -L$$PWD/../lib/ffmpeglib/lib/ -lswresample
LIBS += -L$$PWD/../lib/ffmpeglib/lib/ -lswscale

#导入头文件
INCLUDEPATH += $$PWD/../lib/ffmpeglib/include
DEPENDPATH += $$PWD/../lib/ffmpeglib/include

