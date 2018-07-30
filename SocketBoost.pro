QT += core
QT -= gui

CONFIG += c++11\
CONFIG += no_keywords

TARGET = SocketBoost
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    tcpsocket.cpp \
    ThreadBase.cpp \
    unvhandledata.cpp \
    plcs7.cpp \
    snap7.cpp \
    udpReceiver.cpp \
    plc_tuthu.cpp \
    plc_tuDKTC.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
LIBS    += -lstdc++ \
                -lboost_thread \
                -lboost_system \
                -lboost_date_time \
                -lboost_signals \
                -lsnap7
HEADERS += \
    tcpsocket.h \
    ThreadBase.h \
    unvhandledata.h \
    powerandcontrol.h \
    plcs7.h \
    snap7.h \
    udpReceiver.h \
    unv_ipaddress.h \
    plc_tuthu.h \
    plc_tuDKTC.h


