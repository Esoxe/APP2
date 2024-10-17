#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "string.h"


/*
 *  Auteur(s) : Perret Florian
 *  Date : 09/10/2024
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;


cellule_t* nouvelleCellule (void)
{
    cellule_t *new = malloc(sizeof( cellule_t));
    return new;
}


void detruireCellule (cellule_t* cel)
{
    free(cel);
}


void conversion (char *texte, sequence_t *seq)
{   

    for(int i = strlen(texte) -1 ;i>=0;i--){
        cellule_t*new =nouvelleCellule();
        new->command=texte[i];
        new->suivant=seq->tete;
        seq->tete=new;
    }
}

void afficher (sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */
    cellule_t *current=seq->tete;
    while (current!= NULL)
    {
        printf("%c",current->command);
        current=current->suivant;
    }
}
