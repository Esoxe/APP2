#ifndef LISTES_H
#define LISTES_H

#include <stdbool.h>

/*
 * Pour réaliser des tests de performance, désactiver tous les 
 * affichages.
 * Pour cela, le plus simple est de redefinir les fonctions principales 
 * en decommentant les 3 lignes suivantes et en commentant l'ancienne 
 * definition de 'eprintf' juste dessous.
 */

#ifdef SILENT

#define printf(fmt, ...) (0)
#define eprintf(fmt, ...) (0)
#define putchar(c) (0)

#else

#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#endif

extern bool silent_mode;


struct element {
    char command;
    struct element *suivant;
};
typedef struct element element_t;

struct pile {
    element_t *sommet;
};
typedef struct pile pile_t;

element_t* nouvelleElement (void);

void detruireElement (element_t*);

void empile(pile_t *p,char elem);

char depile(pile_t *p);

void calcul(pile_t *p ,char opp);

void afficherPile(pile_t *p);

#endif
