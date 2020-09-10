#ifndef LABY_BOT_H
#define LABY_BOT_H

#define HAUTEUR 25
#define LARGEUR 25
#define TAILLE 45

#define HAUT 5
#define BAS 1
#define GAUCHE 2
#define DROITE 3

#define MUR -1
#define SOL 0

#define nbRandom 4
#define nbFoxy 2

#include <stdint.h>
#include <stdbool.h>
#include <cairo/cairo.h>

typedef struct EntiteeStruct{
    int x;
    int y;
    char symbole;
    unsigned short int numIMG;
}entitee;

void initialiserIMG(void);
void initialiserTAb(void);
void initialiserTabRecherche(void);

//interfaceGraphique.h -> gtk.h
void AfficherMUR(int x, int y);
void AfficherSOL(int x, int y);
void AfficherJOUEUR(int x, int y);
void AfficherARRIVEE(int arvX, int arvY);
void AfficherENNEMI(int x, int y);
void AfficherFoxy(int x, int y);

void AfficherLaby(void);
void AfficherLabyFenetre(cairo_t* canvas);
void AfficherLabyRecherche(void);

void recherche(int x, int y, int cout);
void tracerChemin(int x, int y, int i);
void DeplacerJoueur(int dir);
void DeplacementEnnemi(int dir, entitee* monstre);
/*
void fonctionPeriodique(uint64_t a, uint64_t b, uint64_t c);
void toucheEnfoncee (uint64_t a, uint64_t b, uint64_t c);
void toucheRelachee(uint64_t a, uint64_t b, uint64_t c);*/

bool VerifVictoire(void);
bool VerifDefaite(void);

#endif // LABY_BOT_H
