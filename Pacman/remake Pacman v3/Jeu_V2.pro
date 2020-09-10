TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lGL -lX11 -lm

SOURCES += \
        InterfaceGraphique.c \
        Jeu.c \
        Liste.c

HEADERS += \
    InterfaceGraphique.h \
    Jeu.h \
    Liste.h

unix: CONFIG    += link_pkgconfig
unix: PKGCONFIG += gtk+-3.0
