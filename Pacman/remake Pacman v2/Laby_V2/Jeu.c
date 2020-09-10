#include <stdlib.h>
#include <stdio.h>
#include <Jeu.h>
#include <InterfaceGraphique.h>
#include <time.h>
#include <Liste.h>

entitee Joueur;
entitee Arrivee;
entitee Mrandoms[nbRandom];
entitee Mfoxy[nbFoxy];

Liste cheminsFoxy[nbFoxy];

int OpenList[HAUTEUR][LARGEUR] = {0};
int Laby[HAUTEUR][LARGEUR] = {0};

char map[HAUTEUR][LARGEUR] =  {"#########################",
                               "#J#         # #         #",
                               "# # ####### # # # ##### #",
                               "#       #F      #       #",
                               "### ### # ##### ### ### #",
                               "#   #   #     # #     # #",
                               "# ### # # ### # # ### # #",
                               "# #   # #       #       #",
                               "# # # # ### ### # #### ##",
                               "#  F#      R  # #       #",
                               "# ### ##### # # # # ### #",
                               "#   #       #   # #     #",
                               "### # ### ### ### ##### #",
                               "#     #  R  # #         #",
                               "# ##### # # # # ### # ###",
                               "#       # #  R      #   #",
                               "# ##### # ### # ##### # #",
                               "# #           #   #     #",
                               "# # # # ##### # # # #####",
                               "#   # #       # #  R  # #",
                               "### # ##### # # # # # # #",
                               "#   #       #     # #   #",
                               "# ##### # # # ### # ### #",
                               "#       #   #     #    A#",
                               "#########################"};
/*
char map2[20][20] = {"####################",
                     "#J#         # #   R#",
                     "# # ####### # # # ##",
                     "#       #F      #  #",
                     "### ### # ##### ## #",
                     "#   #   #     # #  #",
                     "# ### # # ### # # ##",
                     "# #   # #       #  #",
                     "# # # # ### ### # ##",
                     "#  F#      R  # #  #",
                     "# ### ##### # # #  #",
                     "#   #       #   #  #",
                     "### # ### ### ### ##",
                     "#     #  R  # #    #",
                     "# ##### # # # # ####",
                     "#       # #  R     #",
                     "# ##### # ### # ####",
                     "# #           #    #",
                     "# # # # ##### # # A#",
                     "####################"};
*/


void initialiserIMG() {
    chargerImageBMP("./freddy-vue-face.bmp");       //Joueur 0
    chargerImageBMP("./freddy-vue-gauche.bmp");     //Joueur 1
    chargerImageBMP("./freddy-vue-droite.bmp");     //Joueur 2
    chargerImageBMP("./freddy-vue-derriere.bmp");   //Joueur 3
    chargerImageBMP("./Foxy-Face.bmp");             //Foxy 4
    chargerImageBMP("./Foxy-Gauche.bmp");           //Foxy 5
    chargerImageBMP("./Foxy-Droite.bmp");           //Foxy 6
    chargerImageBMP("./Foxy-Dos.bmp");              //Foxy 7
}
/**
 * @brief initialiserTAb
 * transfert du char en int
 * initialisation des entitées
 * map -> Laby
 */
void initialiserTAb() {
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
            switch (map[y][x]) {
                case '#' :
                    Laby[x][y] = MUR;
                break;

                case ' ':
                    Laby[x][y] = SOL;
                break;

                case 'J':
                    Joueur.x       = x;
                    Joueur.y       = y;
                    Joueur.symbole = 'J';
                    Laby[x][y]     = SOL;
                break;

                case 'R':
                    Mrandoms[i].x       = x;
                    Mrandoms[i].y       = y;
                    Mrandoms[i].symbole = 'R';
                    Laby[x][y]      = SOL;

                    i++;
                break;

                case 'A':
                    Arrivee.x       = x;
                    Arrivee.y       = y;
                    Arrivee.symbole = 'A';
                    Laby[x][y]      = SOL;
                break;

                case 'F':
                    Mfoxy[f].x       = x;
                    Mfoxy[f].y       = y;
                    Mfoxy[f].symbole = 'F';
                    Laby[x][y]       = SOL;

                    f++;
                break;
            }
        }
    }
}

/**
 * @brief initialiserTabRecherche
 * Copie Openlist && CloseList par rapport à Laby
 */
void initialiserTabRecherche() {
    for(int x = 0; x < LARGEUR; x++) {
        for(int y = 0; y < HAUTEUR; y++) {
            if(Laby[x][y] == MUR) {
               OpenList[x][y] = MUR;
            } else {
                OpenList[x][y] = SOL;
            }
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

/**
 * @brief AfficherMUR
 * Affiche un mur dans la fenetre
 * @param x
 * @param y
 */
void AfficherMUR(int x, int y){
     dessinerRectangle(x * TAILLE, y * TAILLE, (x + 1) * TAILLE, (y + 1) * TAILLE, 0, 0, 0, 0, 0, 0);
}

/**
 * @brief AfficherSOL
 * Affiche un sol dans la fenetre
 * @param x
 * @param y
 */
void AfficherSOL(int x, int y){
    dessinerRectangle(x * TAILLE, y * TAILLE, (x + 1) * TAILLE, (y + 1) * TAILLE, 0, 0, 0, 255, 255, 255);
}

/**
 * @brief AfficherJOUEUR
 * Affiche le Joueur dans la fenetre
 * @param posX
 * @param posY
 */
void AfficherJOUEUR(int posX, int posY){
   //dessinerRectangle(posX * TAILLE, posY * TAILLE, (posX + 1) * TAILLE, (posY + 1) * TAILLE, 0, 0, 0, 255, 0, 0);
   dessinerImage(posX * TAILLE, (posY + 1) * TAILLE, 1, 1, Joueur.numIMG);
}

/**
 * @brief AfficherARRIVEE
 * Affiche l'arrivée dans la fenetre
 * @param x
 * @param y
 */
void AfficherARRIVEE(int x, int y){
    dessinerRectangle(x * TAILLE, y * TAILLE, (x + 1) * TAILLE, (y + 1) * TAILLE, 0, 0, 0, 0, 255, 0);
}

/**
 * @brief AfficherENNEMI
 * Affiche l'ennemi dans la fenetre
 * @param x
 * @param y
 */
void AfficherENNEMI(int x, int y) {
    dessinerRectangle(x * TAILLE, y * TAILLE, (x + 1) * TAILLE, (y + 1) * TAILLE, 0, 0, 0, 126, 126, 0);
    //dessinerImage(x * TAILLE, (y + 1) * TAILLE, 1, 1, Mfoxy->numIMG);
}

/**
 * @brief AfficherFoxy
 * Afficher l'image de Foxy
 * @param x
 * @param y
 */
void AfficherFoxy(int x, int y) {
    //dessinerRectangle(x * TAILLE, y * TAILLE, (x + 1) * TAILLE, (y + 1) * TAILLE, 0, 0, 0, 255, 0, 0);
    dessinerImage(x * TAILLE, (y + 1) * TAILLE, 1, 1, Mfoxy->numIMG);
}

/**
 * @brief ASUDfficherLaby
 * Affiche le Laby dans la console
 **/
void AfficherLaby(){
    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++) {
            switch (Laby[x][y]) {
                case MUR:
                    printf("#");
                    break;
                case SOL:
                    if(x == Joueur.x && y == Joueur.y){
                        printf("J");
                    }else if(x == Arrivee.x && y == Arrivee.y){
                        printf("A");
                    }else {
                        int checkMonstre = 0;
                        for(int i = 0; i < nbRandom; i++) {
                            if(x == Mrandoms[i].x && y == Mrandoms[i].y){
                                printf("R");
                                checkMonstre = 1;
                            }
                        }

                        for(int i = 0; i < nbFoxy; i++) {
                            if(x == Mfoxy[i].x && y == Mfoxy[i].y){
                                printf("F");
                                checkMonstre = 1;
                            }
                        }

                        if (checkMonstre == 0) {
                            printf(" ");
                        }
                    }
                    break;
            }
        }
        printf("\n");
    }
}

/**
 * @brief AfficherLabyFenetre
 * Affiche la fenetre du laby
 * @param dir
 */
void AfficherLabyFenetre() {
    effacerDessin();
    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++) {
            //printf ("%2d",Laby[x][y]);
            switch (Laby[x][y]) {
                case MUR:
                    AfficherMUR(x, y);
                break;

                case SOL:
                    if(x == Joueur.x && y == Joueur.y){
                        AfficherJOUEUR(x, y);
                    }else if(x == Arrivee.x && y == Arrivee.y){
                        AfficherARRIVEE(x, y);
                    }else {
                       int checkMonstre = 0;
                        for(int i = 0; i < nbRandom; i++) {
                            if(x == Mrandoms[i].x && y == Mrandoms[i].y){
                                AfficherENNEMI(x, y);
                                checkMonstre = 1;
                            }
                        }
                        for(int i = 0; i < nbFoxy; i++) {
                            if(x == Mfoxy[i].x && y == Mfoxy[i].y){
                                AfficherFoxy(x, y);
                                checkMonstre = 1;
                            }
                        }
                        if (checkMonstre == 0) {
                            AfficherSOL(x, y);
                        }
                    }
                break;
            }
        }
        printf ("\n");
    }
}

/**
 * @brief AfficherLabyRecherche
 * affiche la propagation dans la console
 */
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

/**
 * @brief recherche
 * a* (very low cost)
 * @param x
 * @param y
 * @param cout
 */
void recherche(int x, int y, int cout)
{
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

/**
 * @brief tracerChemin
 * on trace le chemin du joueur jusqu'au monstre dans la liste
 * @param x
 * @param y
 * @param i
 */
void tracerChemin(int x, int y, int i) {
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

/**
 * @brief DeplacerJoueur
 * Deplacement du joueur
 * @param dir
 */
void DeplacerJoueur(int dir) {
    Joueur.numIMG = 0;
    switch (dir) {
        case HAUT:
            if(Laby[Joueur.x][Joueur.y - 1] != MUR) {
                Joueur.y--;
                Joueur.numIMG = 3;
            } else {
                Joueur.numIMG = 3;
            }break;
        case DROITE:
            if(Laby[Joueur.x + 1][Joueur.y] != MUR) {
                Joueur.x++;
                Joueur.numIMG = 2;
            } else {
                Joueur.numIMG = 2;
            }break;
        case BAS:
            if(Laby[Joueur.x][Joueur.y + 1] != MUR) {
                Joueur.y++;
                Joueur.numIMG = 0;
            } else {
                Joueur.numIMG = 0;
            }break;
        case GAUCHE:
            if(Laby[Joueur.x - 1][Joueur.y] != MUR) {
                Joueur.x--;
                Joueur.numIMG = 1;
            } else {
                Joueur.numIMG = 1;
            }break;
    }

    for(int i = 0; i < nbFoxy; i++) {
        insertLast(&cheminsFoxy[i], dir);
    }

    //AfficherLabyFenetre();
    //AfficherLabyRecherche();


    if((VerifVictoire() == true)){
        printf("GG\n");
        //arreterGestionEvenements();
    }
}

/**
 * @brief DeplacementEnnemi
 * Deplacement de l'ennemie
 * @param dir
 * @param monstre
 */
void DeplacementEnnemi(int dir, entitee* monstre){
    Mfoxy->numIMG = 4;
    switch (dir) {
        case HAUT:
            if(Laby[monstre->x][monstre->y - 1] != MUR) {
                monstre->y--;
                Mfoxy->numIMG = 7;
            } else {
                Mfoxy->numIMG = 7;
            }break;
        case DROITE:
            if(Laby[monstre->x + 1][monstre->y] != MUR) {
                monstre->x++;
                Mfoxy->numIMG = 6;
            } else {
                Mfoxy->numIMG = 6;
            }break;
        case BAS:
            if(Laby[monstre->x][monstre->y + 1] != MUR) {
                monstre->y++;
                Mfoxy->numIMG = 4;
            } else {
                Mfoxy->numIMG = 4;
            }break;
        case GAUCHE:
            if(Laby[monstre->x - 1][monstre->y] != MUR) {
                monstre->x--;
                Mfoxy->numIMG = 5;
            } else {
                Mfoxy->numIMG = 5;
            }break;
    }
    //AfficherLabyRecherche();
    AfficherLabyFenetre();

    if((VerifDefaite() == true)){
        printf("Perdu fin de partie...\n");
        arreterGestionEvenements();
    }
}

/**
 * @brief toucheEnfoncee
 * @param a
 */
void toucheEnfoncee (uint64_t a) {
    if(a == 9){
        printf("on ferme le jeu\n");
        arreterGestionEvenements();
    } else {
        DeplacerJoueur(a);
    }

    for(int i = 0; i < nbFoxy; i++) {
      int dir = getFirst(&cheminsFoxy[i]);

      srand((unsigned int)time(NULL));
      int bonusVitesse = rand() % 100 + 1;
      printf("bonusVitesse = %d\n", bonusVitesse);

      if(bonusVitesse == 7 || bonusVitesse == 5 || bonusVitesse == 3){     //A finir selon le mode de difficulté  30%
          DeplacementEnnemi(dir, &Mfoxy[i]);
          deleteNoeud(&cheminsFoxy[i]);
          DeplacementEnnemi(dir, &Mfoxy[i]);
          deleteNoeud(&cheminsFoxy[i]);
      } else {
      DeplacementEnnemi(dir, &Mfoxy[i]);
      deleteNoeud(&cheminsFoxy[i]);
      }

      initialiserTabRecherche();
  }
}

long date1 = 0;
long date2 = 0;



/**
 * @brief fonctionPeriodique
 * @param a
 */
void fonctionPeriodique(uint64_t a){
    int tab[4] = {25, 38, 39, 40};

    date1 = a;
    if ( date1 - date2 > 100000000 ) {
        date2 = date1;
        srand((unsigned int)time(NULL));
        for(int i = 0; i < nbRandom; i++) {
        DeplacementEnnemi(tab[rand() % 4], &(Mrandoms[i]));
        }
    }
}


/**
 * @brief toucheRelachee
 * @param a
 */
void toucheRelachee (uint64_t a) {
  //printf ("toucheRelachee      => a=%lu, b=%lu et c=%lu\n" , a, b, c);
 }

/**
 * @brief VerifVictoire
 * Condition de victoire avec un return true / false
 * @return
 */
bool VerifVictoire() {
    if (Joueur.x == Arrivee.x && Joueur.y == Arrivee.y) {
    printf("Vous avez gagné !\n");
    arreterGestionEvenements();
    }
    return false;
}

/**
 * @brief VerifDefaite
 * Condition de défaite avec un return true / false
 * @return
 */
bool VerifDefaite() {
    for(int i = 0; i < nbRandom; i++) {
        if (Joueur.x == Mrandoms[i].x && Joueur.y == Mrandoms[i].y) {
            printf("Vous avez perdu...  (Monstre randoms)\n");
            arreterGestionEvenements();
        }
    }
    for(int i = 0; i < nbFoxy; i++){
        if(Joueur.x == Mfoxy[i].x && Joueur.y == Mfoxy[i].y) {
           printf("Vous avez perdu...  (Foxy)\n");
           arreterGestionEvenements();
        }
    }
    return false;
}
