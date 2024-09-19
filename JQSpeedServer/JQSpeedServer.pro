PRO_PATH = $$PWD
TARGET = JQSpeedServer

QT *= websockets

CONFIG += console

include( $$PWD/../JQWeb/JQWebCommon/JQWebCommon.pri )

HEADERS += \
    $$PWD/cpp/helper.h

SOURCES += \
    $$PWD/cpp/helper.cpp \
    $$PWD/cpp/main.cpp

win32-msvc {
    RC_ICONS = $$PWD/icon/icon.ico
}
