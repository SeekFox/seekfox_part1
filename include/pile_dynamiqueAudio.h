#ifndef DYNAMIQUE_H
#define DYNAMIQUE_H
#include "../include/elementAudio.h"

typedef struct CELLULE{
	ELEMENT valeur;
	struct CELLULE* nextCell;
}CELLULE;

typedef CELLULE* PILE;

PILE init_PILE();
void affiche_PILE(PILE display);
int PILE_estVide(PILE pileVide);
PILE emPILE(PILE newPile, ELEMENT e);
PILE dePILE(PILE newPile, double* oldTete);

#endif