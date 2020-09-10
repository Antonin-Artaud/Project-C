#ifndef Jeu_H
#define Jeu_H

//Taille de la fenetre
#define HAUTEUR 25
#define LARGEUR 25
#define TAILLE 45

//Direction pour le joueur, ennemi, foxy
#define HAUT 5
#define BAS 1
#define GAUCHE 2
#define DROITE 3

//Reset map
#define RESET 6

//Labyrinthe
#define MUR -1
#define SOL 0

//Entitee
#define nbRandom 5
#define nbFoxy 2

#include <stdint.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <cairo/cairo.h>

cairo_t *canvas;

typedef struct EntiteeStruct{
    int x;
    int y;
    char symbole;
    unsigned short int numIMG;
}entitee;

//Initialisation map
void initialiserTAb(void);
void initialiserTabRecherche(void);

//Affichage du labyrinthe
void AfficherLaby(void);
void AfficherLabyFenetre(cairo_t* canvas);
void AfficherLabyRecherche(void);

//interfaceGraphique.h -> gtk.h
void AfficherMUR(int x, int y, cairo_t* canvas);
void AfficherSOL(int x, int y, cairo_t* canvas);
void AfficherJOUEUR(int x, int y, cairo_t* canvas);
void AfficherARRIVEE(int x, int y, cairo_t* canvas);
void AfficherENNEMI(int x, int y, cairo_t* canvas);
void AfficherFoxy(int x, int y, cairo_t* canvas);

//Recherche du chemins le plus court entre le joueur et l'entitee
void recherche(int x, int y, int cout);
void tracerChemin(int x, int y, int i);

//Deplacement entitee
void DeplacerJoueur(int dir);
void DeplacerEnnemi(int dir, entitee* monstre);
void DeplacerPeriodique(void);
void DeplacerPeriodiqueFoxy(void);

//Condition de fin de parti
bool VerifFinParti(void);

#endif // Jeu_H
