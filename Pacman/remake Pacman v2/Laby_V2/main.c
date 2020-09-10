#include <stdio.h>
#include <Jeu.h>
#include <InterfaceGraphique.h>

int main(int argc, char** argv)
{
    creerFenetre("Laby", HAUTEUR * TAILLE, LARGEUR * TAILLE);
    specifierLimites(0, HAUTEUR * TAILLE, LARGEUR * TAILLE, 0);

    specifierGestionnaire( "PERIODIQUE"          , fonctionPeriodique);

    specifierGestionnaire ( "TOUCHE ENFONCEE"    , toucheEnfoncee      );
    specifierGestionnaire ( "TOUCHE RELACHEE"    , toucheRelachee      );

    initialiserIMG();
    initialiserTAb();

    initialiserTabRecherche();
    AfficherLabyFenetre();

    gererEvenements();

    detruireFenetre();
    return 0;
}
