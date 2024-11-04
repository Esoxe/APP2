#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "pile.h"
#include "string.h"
#include "listes.h"


element_t* nouvelleElement (void)
{
    element_t *new = malloc(sizeof( element_t));
    return new;
}


void detruireElement (element_t* cel)
{
    free(cel);
}

void empile(pile_t *p,char elem){
        element_t*new =nouvelleElement();
        new->command=elem;
        new->suivant=p->sommet;
        p->sommet=new;
}

char depile(pile_t *p){
        element_t*new =p->sommet;
        if (p->sommet != NULL && p!=NULL){
        p->sommet=new->suivant;
        return new->command;
        }
        else 
            return 'E';
}

void calcul(pile_t *p, char opp){
    int b= depile(p) ;
    int a=(int) depile(p);
    int res ;
    if (opp == '+'){
        res = a +b ;
        empile(p, (char) res ) ;
    }

    else if (opp == '-'){
        res = a - b ;
        empile(p,(char) res) ;
    }

    else {
        res = a * b ;
        empile(p,(char) res) ;
    }
}



char * groupe(pile_t *p,char groupe1[256],char groupe2[256]){
    char c = depile(p);
    int i =0;
    while (c!='{')
    {
        printf("%c",c);
        groupe1[i]=c;
        c =depile(p);
        i++;
    }
    i=0;
    c= depile(p);
    while (c!='{')
    {
        printf("%c",c);
        groupe1[i]=c;
        c =depile(p);
        i++;
    }
    int val = depile(p);
    if(val==0){

        return groupe2;
    }
    else{
        return groupe1;
    }
}



void afficherPile(pile_t *p){
    if (p!=NULL){
        element_t *actuel = p->sommet;
        while (actuel != NULL){
            printf("Pile : %d %c  \n",actuel->command,actuel->command);
            actuel=actuel->suivant;
        }
        }
}