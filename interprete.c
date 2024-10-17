#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include "pile.h"

/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop (void)
{
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}



int interprete (sequence_t* seq, bool debug,pile_t *p)
{
    // Version temporaire a remplacer par une lecture des commandes dans la
    // liste chainee et leur interpretation.
    char commande;


    debug = true; /* À enlever par la suite et utiliser "-d" sur la ligne de commandes */

    printf ("Programme:");
    afficher(seq);
    printf ("\n");
    if (debug) stop();

    // À partir d'ici, beaucoup de choses à modifier dans la suite.
    commande = seq->tete->command ; //à modifier: premiere commande de la sequence
    int ret;         //utilisée pour les valeurs de retour

    while ( seq->tete !=NULL ) { //à modifier: condition de boucle

        switch (commande) {
            /* Ici on avance tout le temps, à compléter pour gérer d'autres commandes */

            case 'A':
                ret = avance();
                if (ret == VICTOIRE) return VICTOIRE; /* on a atteint la cible */
                if (ret == RATE)     return RATE;     /* tombé dans l'eau ou sur un rocher */
                break; /* à ne jamais oublier !!! */
            case 'G':
                gauche();
                break; /* à ne jamais oublier !!! */
            case 'D':
                droite();
                break; /* à ne jamais oublier !!! */
            case '0'...'9':
                empile(p,commande - 48 );
                break;
            case '+':
            case '-':
            case '*':
                calcul(p,commande);
                break;
            default:
                eprintf("Caractère inconnu: '%c'\n", commande);
        }
        seq->tete=seq->tete->suivant;
        commande = seq->tete->command ;
        /* Affichage pour faciliter le debug */
        afficherCarte();
        afficherPile(p);
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
        if (debug) stop();
    }

    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */

    return CIBLERATEE;
}
