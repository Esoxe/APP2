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


void ajout_groupe_pile( pile_t *p, sequence_t *seq){
    int cpt =1;
    cellule_t *current=seq->tete->suivant;
    empile(p,'{');
    while (cpt!=0)
    {
        if (current->command == '{'){
            cpt ++;
        }
        if(current->command=='}'){
            cpt--;
        }
        empile(p,current->command);
        if(cpt>0){
        seq->tete=current->suivant;
        current=current->suivant;
        }
    }
    
}

void insert_file (char *texte, sequence_t *seq)
{   
    if(strlen(texte)==1){
        cellule_t*new =nouvelleCellule();
        new->command=texte[0];
        new->suivant=seq->tete->suivant;
        seq->tete->suivant=new;
    }
    else{
    for(int i =1 ;i< (int) strlen(texte)-1;i++){
        cellule_t*new =nouvelleCellule();
        new->command=texte[i];
        new->suivant=seq->tete->suivant;
        seq->tete->suivant=new;
    }
    }
}

void parcours_groupe_pile(pile_t *p ,char texte[MAX_SIZE]){
    int cpt=1;
    char c;
    depile(p);
    texte[0]='}';
    int i =1;
    while (cpt>0){
        c =depile(p);
        if (c == '}'){
            cpt ++;
        }
        else if(c=='{'){
            cpt--;
        }
        texte[i]=c;
        i++;
    }
    texte[i]='\0';
}



void exec_groupe_de_commande( pile_t *p, sequence_t *seq){
    char groupe1[MAX_SIZE];
    char groupe2[MAX_SIZE];
    parcours_groupe_pile(p,groupe1);
    parcours_groupe_pile(p,groupe2);
    int val = depile(p);
    printf("%d",val);
    if(val==0){
        insert_file(groupe1,seq);
    }
    else{
        insert_file(groupe2,seq);
    }
}

void lecture_pile(pile_t *p,char texte[MAX_SIZE]){
    char c=depile(p);
    if (c=='}'){
        empile(p,c);
        parcours_groupe_pile(p,texte);
    }
    else{
        texte[0] =c;
        texte[1]='\0';
    }
}

void ajout_elem_pile(pile_t *p, char texte[MAX_SIZE]){
    if(strlen(texte)==1){
        empile(p,texte[0]);
    }
    else{
        for(int i=strlen(texte)-1;i>=0;i--){
            empile(p,texte[i]);
        }
    }
}

void echange_sommet(pile_t *p){
    char temp1[MAX_SIZE];
    char temp2[MAX_SIZE];
    lecture_pile(p,temp1);
    lecture_pile(p,temp2);
    ajout_elem_pile(p,temp1);
    ajout_elem_pile(p,temp2);
}

void pile_exec(pile_t *p,sequence_t *seq){
    char elem[MAX_SIZE];
    lecture_pile(p,elem);
    insert_file(elem,seq);
}

void clone(pile_t *p){
    char temp[MAX_SIZE];
    lecture_pile(p,temp);
    ajout_elem_pile(p, temp);  // Ajouter une copie du caractère à la pile
    ajout_elem_pile(p, temp);  // Ajouter une autre copie du caractère à la pile
}
void boucle(pile_t *p,sequence_t *seq){
    int n = depile(p);
    printf("%d\n",n);
    n--;
    if(n>0){ //Remet B dans la routine
        cellule_t *new = nouvelleCellule();
        new->command=seq->tete->command;
        new->suivant=seq->tete;
        seq->tete=new;
        char cmd[MAX_SIZE];
        lecture_pile(p,cmd); //recupere la suite de commande et la remet sur la pile
        ajout_elem_pile(p,cmd);
        pile_exec(p,seq); //execute la commande
        ajout_elem_pile(p,cmd);
        empile(p,n);
    }   
    else {
        pile_exec(p,seq);
    }
    
}


void rotation(pile_t *p){
    int x=depile(p);
    int n=depile(p);
    char * element_pile[100];
    for(int i=0;i<n;i++){
        element_pile[i]=malloc(MAX_SIZE*sizeof(char));
        lecture_pile(p,element_pile[i]);
    }
    for(int i=n-x-1;i>=0;i--){
        ajout_elem_pile(p,element_pile[i]);
        }
        afficherPile(p);
    for(int i=n-1;i>=n-x;i--){
        ajout_elem_pile(p,element_pile[i]);
        }
}