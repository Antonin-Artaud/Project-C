#ifndef LABY_BOT_H
#define LABY_BOT_H

#define HAUTEUR 25
#define LARGEUR 25
#define TAILLE 32

#define HAUT 25
#define BAS 39
#define GAUCHE 38
#define DROITE 40

#define MUR -1
#define SOL 0

#define nbRandom 4
#define nbFoxy 2

#include <stdint.h>
#include <stdbool.h>

typedef struct EntiteeStruct{
    int x;
    int y;
    char symbole;
    unsigned short numIMG;
}entitee;

void initialiserIMG();
void initialiserTAb();
void initialiserTabRecherche();

void AfficherMUR(int x, int y);
void AfficherSOL(int x, int y);
void AfficherJOUEUR(int x, int y);
void AfficherARRIVEE(int x, int y);
void AfficherENNEMI(int x, int y);
void AfficherFoxy(int x, int y);

void AfficherLaby();
void AfficherLabyFenetre();
void AfficherLabyRecherche();

void recherche(int x, int y, int cout);
void tracerChemin(int x, int y, int i);

void DeplacerJoueur(int dir);
void DeplacementEnnemi(int dir, entitee* monstre);

void fonctionPeriodique(uint64_t a);
void toucheEnfoncee (uint64_t a);
void toucheRelachee(uint64_t a);

bool VerifVictoire();
bool VerifDefaite();

#endif // LABY_BOT_H
