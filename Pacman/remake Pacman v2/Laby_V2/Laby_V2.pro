TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lGL -lX11 -lm

SOURCES += \
        InterfaceGraphique.c \
        Jeu.c \
        Liste.c \
        main.c

HEADERS += \
    InterfaceGraphique.h \
    Jeu.h \
    Liste.h
