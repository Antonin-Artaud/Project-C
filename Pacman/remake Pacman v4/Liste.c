#include <stdio.h>
#include <stdlib.h>
#include <Liste.h>

//on crée notre liste de type liste
Liste creerListe(){
    Liste temp;
    temp.nbNoeuds = 0;
    temp.first = NULL;
    temp.last = NULL;

    return temp;
}

//On insert une valeur au début
void insertFirst(Liste *liste, int val){
    if(liste == NULL){
        printf("La liste \"insertFIrst\" est NULL !\n");
        exit(EXIT_FAILURE);
    } else {
        Noeud *noeunoeud = (Noeud*)malloc(sizeof(Noeud));
        noeunoeud->val = val;
        noeunoeud->next = liste->first;

        if(liste->first == NULL) {
            liste->last = noeunoeud;
        }
        liste->first = noeunoeud;

        liste->nbNoeuds++;
    }
}

//On insert une valeur à la fin
void insertLast(Liste *liste, int val){
    if(liste == NULL){
        printf("La liste \"insertLast\" est NULL !\n");
    } else {
        Noeud *gneugneu = (Noeud*) malloc (sizeof(Noeud));
        gneugneu->val = val;
        gneugneu->next = NULL;

        if(liste->last == NULL) {
            liste->first = gneugneu;
        }

        liste->last->next = gneugneu;
        liste->last = gneugneu;
        liste->nbNoeuds++;
    }
}

int getFirst(Liste *liste) {
    if(liste == NULL) {
        printf("La liste \"fetFirst\" est NULL !\n");
        return 0;
    } else {
        return liste->first->val;
    }
}

//On supprime un noeud
void deleteNoeud(Liste *liste) {
    Noeud *current = (Noeud*) malloc(sizeof(Noeud));

    if(liste == NULL ){
        exit(EXIT_FAILURE);
    }
    current = liste->first;
    liste->first = liste->first->next;
    free(current);
    liste->nbNoeuds--;
}

//On récup la taille de la liste
int getSize(Liste *liste)
{
    return liste->nbNoeuds;
}
