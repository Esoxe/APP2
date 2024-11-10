
#define MAX_SIZE 10000
#include <stdbool.h>
#include "pile.h"

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

cellule_t* nouvelleCellule (void);

void detruireCellule (cellule_t*);

void conversion (char *texte, sequence_t *seq);

void ajout_groupe_pile(pile_t *p ,sequence_t *seq);

void exec_groupe_de_commande( pile_t *p, sequence_t *seq);

void insert_file (char *texte, sequence_t *seq);

void parcours_groupe_pile(pile_t *p ,char texte[MAX_SIZE]);

void ajout_elem_pile(pile_t *p, char texte[MAX_SIZE]);

void lecture_pile(pile_t *p,char texte[MAX_SIZE]);

void echange_sommet(pile_t *p);

void pile_exec(pile_t *p,sequence_t *seq);

void clone(pile_t *p);

void boucle(pile_t *p,sequence_t *seq);

void afficher (sequence_t* seq);

void rotation(pile_t *p);

