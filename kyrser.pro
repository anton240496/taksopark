QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.0
QMAKE_TARGET_COMPANY = sql company
QMAKE_TARGET_PRODUCT = taxiproject
QMAKE_TARGET_DESCRIPTION = redactor taxi
QMAKE_TARGET_COPYRIGHT = Anton Ilinsky

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    info.cpp \
    main.cpp \
    mainwindow.cpp \
    spravka.cpp \
    vavto.cpp \
    wautopersonal.cpp \
    wjournal.cpp \
    wroutes.cpp

HEADERS += \
    info.h \
    mainwindow.h \
    spravka.h \
    vavto.h \
    wautopersonal.h \
    wjournal.h \
    wroutes.h

FORMS += \
    info.ui \
    mainwindow.ui \
    spravka.ui \
    vavto.ui \
    wautopersonal.ui \
    wjournal.ui \
    wroutes.ui

RC_ICONS = car.ico



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
