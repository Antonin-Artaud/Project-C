#ifndef LISTE_H
#define LISTE_H


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

Liste creerListe();


void insertFirst(Liste *liste, int val);
void insertLast(Liste *liste, int val);

int getSize(Liste *liste);
void deleteNoeud(Liste *liste);
int getFirst(Liste *liste);

#endif // LISTE_H
