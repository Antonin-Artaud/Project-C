#include <stdio.h>
#include <Jeu.h>
#include <gtk/gtk.h>

GtkWidget* contexte;

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data){
    switch (event->keyval) {
        case GDK_KEY_z:
            DeplacerJoueur(HAUT);
            break;

        case GDK_KEY_d:
            DeplacerJoueur(DROITE);
            break;

        case GDK_KEY_s:
            DeplacerJoueur(BAS);
            break;

        case GDK_KEY_q:
            DeplacerJoueur(GAUCHE);
            break;
            
        case GDK_KEY_r:
            DeplacerJoueur(RESET);
            break;
    }
    return VerifFinParti();
}

gboolean periodique(gpointer user_data){

    DeplacerPeriodique();
    GdkRectangle update_rect;

    update_rect.x = 0;
    update_rect.y = 0;
    update_rect.width = LARGEUR * TAILLE;
    update_rect.height = HAUTEUR * TAILLE;

    gdk_window_invalidate_rect (gtk_widget_get_window(contexte), &update_rect, FALSE);

    return VerifFinParti();

}

gboolean periodiqueFoxy(gpointer user_data){
    DeplacerPeriodiqueFoxy();

    return VerifFinParti();
}

gboolean on_draw_event (GtkWidget* widget, cairo_t* contexte, gpointer user_data)
{
    canvas = contexte;
    AfficherLabyFenetre(canvas);

    return VerifFinParti();
}

int main(int argc, char **argv)
{
    GtkWidget* fenetre;

    gtk_init (&argc, &argv);

    fenetre = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position      (GTK_WINDOW (fenetre), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size  (GTK_WINDOW (fenetre), HAUTEUR * TAILLE, LARGEUR * TAILLE);
    gtk_window_set_title         (GTK_WINDOW (fenetre), "Laby avec Foxy, Monstre random v3");

    g_signal_connect (G_OBJECT (fenetre), "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(fenetre), "key_press_event", G_CALLBACK(on_key_press), NULL);

    contexte  = gtk_drawing_area_new ();

    gtk_container_add (GTK_CONTAINER (fenetre), contexte);

    g_timeout_add(60, periodique, NULL);
    g_timeout_add(180, periodiqueFoxy, NULL);
    g_signal_connect (G_OBJECT (contexte), "draw", G_CALLBACK (on_draw_event), NULL);

    gtk_widget_show_all (fenetre);

    initialiserTAb();
    initialiserTabRecherche();

    gtk_main();
    return 0;
}
