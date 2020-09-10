TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Jeu.c \
        Liste.c \
        main.c

HEADERS += \
    Jeu.h \
    Liste.h

unix: CONFIG	+= link_pkgconfig
unix: PKGCONFIG += gtk+-3.0
unix: PKGCONFIG += librsvg-2.0
