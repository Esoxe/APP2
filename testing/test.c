#include <stdio.h>
#include <stdlib.h>
#include "string.h"


/*
 *  Auteur(s) : Perret Florian
 *  Date : 09/10/2024
 *  Suivi des Modifications :
 *
 */

struct cellule {
    char   command;
    /* vous pouvez rajouter d'autres champs ici */
    struct cellule *suivant;
};
typedef struct cellule cellule_t;

struct sequence {
    cellule_t *tete;
};
typedef struct sequence sequence_t;



cellule_t* nouvelleCellule (void)
{
    cellule_t *new = malloc(sizeof( cellule_t));
    return new;
}


void detruireCellule (cellule_t* cel)
{
    free(cel);
}

void afficher (sequence_t* seq)
{
    cellule_t *current=seq->tete;
    while (current!= NULL)
    {
        printf("%c\n",current->command);
        current=current->suivant;
    }
}


void conversion (char *texte, sequence_t *seq)
{   

    for(int i = strlen(texte) -1 ;i>=0;i--){
        cellule_t*new =nouvelleCellule();
        new->command=texte[i];
        new->suivant=seq->tete;
        seq->tete=new;
        afficher(seq);
        printf("\n");
    }
}




int main(){
    sequence_t *l =malloc(sizeof(sequence_t));
    char texte[1000]="AGDADG";
    conversion(texte,l);
}