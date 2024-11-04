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

void ajout_groupe_pile( pile_t *p, sequence_t *seq){

    cellule_t *current=seq->tete->suivant;
    empile(p,'{');
    while (current->command !='}')
    {
        printf("%c",current->command);
        empile(p,current->command);
        seq->tete=current->suivant;
        current=current->suivant;
    }
    empile(p,'}');
    
}

void insert_pile (char *texte, sequence_t *seq)
{   

    for(int i = strlen(texte) -1 ;i>=0;i--){
        cellule_t*new =nouvelleCellule();
        new->command=texte[i];
        new->suivant=seq->tete->suivant;
        seq->tete->suivant=new;
    }
}


void ajout_groupe_file( pile_t *p, sequence_t *seq){
    char groupe1[256];
    char groupe2[256];
    char c = depile(p);
    c=depile(p);
    int i =0;
    while (c!='{')
    {
        groupe1[i]=c;
        c =depile(p);
        i++;
    }
    groupe1[i]='\0';
    i=0;
    c= depile(p);
    c= depile(p);
    while (c!='{')
    {
        groupe2[i]=c;
        c =depile(p);
        i++;
    }
    groupe2[i]='\0';
    int val = depile(p);
    if(val==0){
        insert_pile(groupe1,seq);
    }
    else{
        insert_pile(groupe2,seq);
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
