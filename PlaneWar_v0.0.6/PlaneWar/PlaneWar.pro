QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bomb.cpp \
    bullet.cpp \
    doublegame.cpp \
    enemy.cpp \
    intro.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    player.cpp \
    singleGame.cpp

HEADERS += \
    bomb.h \
    bullet.h \
    config.h \
    doublegame.h \
    enemy.h \
    intro.h \
    mainwindow.h \
    map.h \
    player.h \
    singleGame.h

FORMS += \
    intro.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    resource/321.gif
