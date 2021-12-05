QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alarmw.cpp \
    element_alarm.cpp \
    elemet_timer.cpp \
    main.cpp \
    mainwindow.cpp \
    ring.cpp \
    timerw.cpp

HEADERS += \
    alarmw.h \
    element_alarm.h \
    elemet_timer.h \
    mainwindow.h \
    ring.h \
    timerw.h

FORMS += \
    alarmw.ui \
    element_alarm.ui \
    elemet_timer.ui \
    mainwindow.ui \
    ring.ui \
    timerw.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
