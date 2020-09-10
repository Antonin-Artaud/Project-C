#include <stdio.h>
#include <stdlib.h>
#include <Liste.h>

/**
 * @brief creerListe
 * @return liste crée
 */
Liste creerListe(){
    Liste temp;
    temp.nbNoeuds = 0;
    temp.first = NULL;
    temp.last = NULL;

    return temp;
}

/**
 * @brief insertFirst
 * insert une valeur au début
 * @param liste
 * @param val
 */
void insertFirst(Liste *liste, int val){
    if(liste == NULL){
        printf("La liste \"insertFIrst\" est NULL !\n");
    } else {
        Noeud *noeunoeud = (Noeud*) malloc (sizeof(Noeud));
        noeunoeud->val = val;
        noeunoeud->next = liste->first;

        if(liste->first == NULL) {
            liste->last = noeunoeud;
        }
        liste->first = noeunoeud;

        liste->nbNoeuds++;
    }
}

/**
 * @brief insertLast
 * insert la derniere valeur
 * @param liste
 * @param val
 */
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

/**
 * @brief getSize
 * Récupère la taille de la liste
 * @param liste
 * @return
 */
int getSize(Liste *liste)
{
    return liste->nbNoeuds;
}

int getFirst(Liste *liste) {
    if(liste == NULL) {
        printf("La liste \"fetFirst\" est NULL !\n");
        return 0;
    } else {
        return liste->first->val;
    }
}

/**
 * @brief deleteNoeud
 * @param liste
 */
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
