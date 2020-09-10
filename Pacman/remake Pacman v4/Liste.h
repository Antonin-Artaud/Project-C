#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>

typedef struct noeudStruct Noeud;
struct noeudStruct{
    int val;
    Noeud *next;
};

typedef struct listeStruct Liste;
struct listeStruct{
    int nbNoeuds;
    Noeud *first;
    Noeud *last;
};

Liste creerListe(void);

void insertFirst(Liste *liste, int val);
void insertLast(Liste *liste, int val);

int getFirst(Liste *liste);

void deleteNoeud(Liste *liste);

int getSize(Liste *liste);
#endif // LISTE_H
