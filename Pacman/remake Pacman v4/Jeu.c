#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <Jeu.h>
#include <Liste.h>

#include <cairo/cairo.h>

entitee Joueur;
entitee Arrivee;
entitee Mrandoms[nbRandom];
entitee Mfoxy[nbFoxy];

Liste cheminsFoxy[nbFoxy];

int OpenList[HAUTEUR][LARGEUR] = {0};
int Laby[HAUTEUR][LARGEUR] = {0};

char Level[HAUTEUR][LARGEUR] = {"#########################",
                   "#J#         # #         #",
                   "# # ####### # # # ##### #",
                   "#       #F      #       #",
                   "### ### # ##### ### ### #",
                   "#   #   #     # #     # #",
                   "# ### # # ### # # ### # #",
                   "# #   # #      R        #",
                   "# # # # ### ### # #### ##",
                   "#  F#      R  # #       #",
                   "# ### ##### # # # # ### #",
                   "#   #       #   # #     #",
                   "### # ### ### ### ##### #",
                   "#     #  R  # #         #",
                   "# ##### # # # # ### # ###",
                   "#       # #  R      #   #",
                   "# ##### # ### # ### # # #",
                   "# #           #   #     #",
                   "# # # # ##### # # # #####",
                   "#   # #       # #  R  # #",
                   "### # ##### # # # # # # #",
                   "#   #       #     # #   #",
                   "# ##### # # # ### # ### #",
                   "#       #   #     #    A#",
                   "#########################"};

void initialiserTAb(){
    int i, f;
    for(i = 0 ; i < nbRandom ; i++){
        entitee monstre;
        Mrandoms[i] = monstre;
    }

    for(f = 0; f < nbFoxy; f++) {
        entitee monstre;
        Mfoxy[f] = monstre;
    }
    i = f = 0;

    for (int y = 0; y < LARGEUR; y++) {
        for (int x = 0; x < HAUTEUR; x++) {
            switch (Level[y][x]) {
                case '#' :
                    Laby[x][y] = MUR;
                break;

                case ' ':
                    Laby[x][y] = SOL;
                break;

                case 'J':
                    Joueur.x = x;
                    Joueur.y = y;
                    Joueur.symbole = 'J';
                    Laby[x][y] = SOL;
                break;

                case 'R':
                    Mrandoms[i].x = x;
                    Mrandoms[i].y = y;
                    Mrandoms[i].symbole = 'R';
                    Laby[x][y] = SOL;

                    i++;
                break;

                case 'A':
                    Arrivee.x = x;
                    Arrivee.y = y;
                    Arrivee.symbole = 'A';
                    Laby[x][y] = SOL;
                break;

                case 'F':
                    Mfoxy[f].x = x;
                    Mfoxy[f].y = y;
                    Mfoxy[f].symbole = 'F';
                    Laby[x][y] = SOL;

                    f++;
                break;
            }
        }
    }
}

void initialiserTabRecherche(){
    for(int x = 0; x < LARGEUR; x++) {
        for(int y = 0; y < HAUTEUR; y++) {
            (Laby[x][y] == MUR)?(OpenList[x][y] = MUR):(OpenList[x][y] = SOL);
        }
    }

    for(int i = 0; i < nbFoxy; i++) {
        recherche(Mfoxy[i].x, Mfoxy[i].y, 1);

        //insertFirst(&cheminsFoxy[i], 1);
        cheminsFoxy[i] = creerListe();
        //insertFirst(&cheminsFoxy[i], 1);
        tracerChemin(Joueur.x, Joueur.y, i);
    }
}

void AfficherMUR(int x, int y, cairo_t* canvas){
    cairo_set_source_rgb  (canvas, 0, 0, 0);
    cairo_rectangle       (canvas, x*TAILLE,  y*TAILLE, TAILLE, TAILLE);
    cairo_stroke_preserve (canvas);

    cairo_set_source_rgb  (canvas, 0.5, 0.5, 0.5);
    cairo_fill            (canvas);
    cairo_stroke          (canvas);
}

void AfficherSOL(int x, int y, cairo_t* canvas){
    cairo_set_source_rgb  (canvas, 0, 0, 0);
    cairo_rectangle       (canvas, x*TAILLE,  y*TAILLE, TAILLE, TAILLE);
    cairo_stroke_preserve (canvas);

    cairo_set_source_rgb  (canvas, 0, 0, 0);
    cairo_fill            (canvas);
    cairo_stroke          (canvas);
}

void AfficherJOUEUR(int x, int y, cairo_t* canvas){
    cairo_set_source_rgb  (canvas, 0, 0, 1);
    cairo_rectangle       (canvas, x*TAILLE,  y*TAILLE, TAILLE, TAILLE);
    cairo_stroke_preserve (canvas);

    cairo_set_source_rgb  (canvas, 0, 0, 1);
    cairo_fill            (canvas);
    cairo_stroke          (canvas);
}

void AfficherARRIVEE(int x, int y, cairo_t* canvas){
    cairo_set_source_rgb  (canvas, 0, 1, 0);
    cairo_rectangle       (canvas, x*TAILLE,  y*TAILLE, TAILLE, TAILLE);
    cairo_stroke_preserve (canvas);

    cairo_set_source_rgb  (canvas, 0, 1, 0);
    cairo_fill            (canvas);
    cairo_stroke          (canvas);
}

void AfficherENNEMI(int x, int y, cairo_t* canvas){
    cairo_set_source_rgb  (canvas, 1, 1, 0);
    cairo_rectangle       (canvas, x*TAILLE,  y*TAILLE, TAILLE, TAILLE);
    cairo_stroke_preserve (canvas);

    cairo_set_source_rgb  (canvas, 1, 1, 0);
    cairo_fill            (canvas);
    cairo_stroke          (canvas);
}

void AfficherFoxy(int x, int y, cairo_t* canvas){
    cairo_set_source_rgb  (canvas, 0, 0, 0);
    cairo_rectangle       (canvas, x*TAILLE,  y*TAILLE, TAILLE, TAILLE);
    cairo_stroke_preserve (canvas);

    cairo_set_source_rgb  (canvas, 1, 0, 0);
    cairo_fill            (canvas);
    cairo_stroke          (canvas);
}

void AfficherLabyFenetre(cairo_t* canvas) {
    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++) {
            switch (Laby[x][y]) {
                case MUR:
                    AfficherMUR(x, y, canvas);
                    //printf("#");
                break;

                case SOL:
                    if(x == Joueur.x && y == Joueur.y){
                        AfficherJOUEUR(x, y, canvas);
                        //printf("J");
                    }else if(x == Arrivee.x && y == Arrivee.y){
                        AfficherARRIVEE(x, y, canvas);
                        //printf("A");
                    }else {
                       int checkMonstre = 0;
                        for(int i = 0; i < nbRandom; i++) {
                            if(x == Mrandoms[i].x && y == Mrandoms[i].y){
                                AfficherENNEMI(x, y, canvas);
                                //printf("R");
                                checkMonstre = 1;
                            }
                        }
                        for(int i = 0; i < nbFoxy; i++) {
                            if(x == Mfoxy[i].x && y == Mfoxy[i].y){
                                AfficherFoxy(x, y, canvas);
                                //printf("F");
                                checkMonstre = 1;
                            }
                        }
                        if (checkMonstre == 0) {
                            AfficherSOL(x, y, canvas);
                            //printf(" ");
                        }
                    }
                break;
            }
        }
        printf ("\n");
    }
}

void AfficherLabyRecherche(){
    for(int x = 0; x < LARGEUR; x++) {
        for(int y = 0; y < HAUTEUR; y++) {
            if(OpenList[y][x] == MUR) {
                printf("\033[0;31m");
                printf(" # ");
                printf("\033[0;0m");
            } else {
                if(OpenList[y][x] < 10){
                    printf(" ");
                }
            printf("%d ", OpenList[y][x]);
            }
        }
    printf("\n");
    }
}

void recherche(int x, int y, int cout){
    OpenList[x][y] = cout;
    cout++;

    //haut
    if(OpenList[x][y - 1] > cout || OpenList[x][y - 1] == SOL) {
        recherche(x, y - 1, cout);
    }

    //gauche
    if(OpenList[x - 1][y] > cout || OpenList[x - 1][y] == SOL) {
        recherche(x - 1, y, cout);
    }

    //bas
    if(OpenList[x][y + 1] > cout || OpenList[x][y + 1] == SOL) {
        recherche(x, y + 1, cout);
    }

    //droite
    if(OpenList[x + 1][y] > cout || OpenList[x + 1][y] == SOL) {
        recherche(x + 1, y, cout);
    }
}

void tracerChemin(int x, int y, int i){
    if(OpenList[x][y] != 1) {

        //Haut
        if(OpenList[x][y - 1] == (OpenList[x][y] - 1)) {
           insertFirst(&cheminsFoxy[i], BAS);
           tracerChemin(x, y - 1, i);

        //Gauche
        }else if(OpenList[x - 1][y] == (OpenList[x][y] - 1)) {
            insertFirst(&cheminsFoxy[i], DROITE);
            tracerChemin(x - 1, y, i);

        //Bas
        }else if (OpenList[x][y + 1] == (OpenList[x][y] - 1)) {
            insertFirst(&cheminsFoxy[i], HAUT);
            tracerChemin(x, y + 1, i);

        //Droite
        }else if(OpenList[x + 1][y] == (OpenList[x][y] - 1)) {
            insertFirst(&cheminsFoxy[i], GAUCHE);
            tracerChemin(x + 1, y, i);
        }
    }

}

void DeplacerJoueur(int dir){
    switch(dir){
        case HAUT :
            if(Laby[Joueur.x][Joueur.y - 1] != MUR) {
                Joueur.y--;
            }break;
        case DROITE :
            if(Laby[Joueur.x + 1][Joueur.y] != MUR) {
                Joueur.x++;
            }break;
        case BAS :
            if(Laby[Joueur.x][Joueur.y + 1] != MUR) {
                Joueur.y++;
            }break;
        case GAUCHE :
            if(Laby[Joueur.x - 1][Joueur.y] != MUR) {
                Joueur.x--;
            }break;
        case RESET :
            initialiserTAb();
            break;
    }
}

void DeplacerEnnemi(int dir, entitee* monstre){
    switch (dir) {
        case HAUT:
            if(Laby[monstre->x][monstre->y - 1] != MUR) {
                monstre->y--;
            }
        break;

        case DROITE:
            if(Laby[monstre->x + 1][monstre->y] != MUR) {
                monstre->x++;
            }
        break;

        case BAS:
            if(Laby[monstre->x][monstre->y + 1] != MUR) {
                monstre->y++;
            }
        break;

        case GAUCHE:
            if(Laby[monstre->x - 1][monstre->y] != MUR) {
                monstre->x--;
            }
        break;
    }
}

void DeplacerPeriodique(){
    int tab[4] = {HAUT, BAS, GAUCHE, DROITE};
    srand((unsigned int)time(NULL));

    for(int i = 0; i < nbRandom; i++) {
        DeplacerEnnemi(tab[rand() % 4], &(Mrandoms[i]));
    }
}

void DeplacerPeriodiqueFoxy(){
    for(int i = 0; i < nbFoxy; i++) {
        int dir = getFirst(&cheminsFoxy[i]);

        srand((unsigned int)time(NULL));
        int bonusVitesse = rand() % 1000000 + 1;
        printf("bonusVitesse = %d\n", bonusVitesse);

        if(bonusVitesse == 7 || bonusVitesse == 5 || bonusVitesse == 3){     //A finir selon le mode de difficulté  30%
            DeplacerEnnemi(dir, &Mfoxy[i]);
            deleteNoeud(&cheminsFoxy[i]);
            DeplacerEnnemi(dir, &Mfoxy[i]);
            deleteNoeud(&cheminsFoxy[i]);
        } else {
            DeplacerEnnemi(dir, &Mfoxy[i]);
            deleteNoeud(&cheminsFoxy[i]);
        }
        initialiserTabRecherche();
        AfficherLabyRecherche();
    }
}

bool VerifFinParti() {
    for(int i = 0; i < nbRandom; i++) {
        if (Joueur.x == Mrandoms[i].x && Joueur.y == Mrandoms[i].y) {
            printf("Vous avez perdu...  (Monstre randoms)\n");
            return FALSE;
        }
    }

    for(int i = 0; i < nbFoxy; i++){
        if(Joueur.x == Mfoxy[i].x && Joueur.y == Mfoxy[i].y) {
            printf("Vous avez perdu...  (Foxy)\n");
            return FALSE;
       }
    }
    if (Joueur.x == Arrivee.x && Joueur.y == Arrivee.y) {
        printf("Vous avez gagné !\n");
        return FALSE;
    }

    return TRUE;
}
