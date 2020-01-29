#ifndef FILE_MOTS_H
#define FILE_MOTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MOT.h"

typedef struct CellulePourMotCle {
	struct CellulePourMotCle* ptr_suiv;
	MOT mot_cle;
}Cell_M;

typedef struct FIFOMotCle {
	Cell_M *debut, *fin;
}FIFO_M;

void Cinit(Cell_M* c);
void Finit(FIFO_M* f);
char* fToString(FIFO_M *f);
float comparerF(FIFO_M *f1, FIFO_M *f2);
void enfiler_M(FIFO_M* f, char* e);
int FestVide(FIFO_M* f);
int motExiste(FIFO_M* file, char* test);
void Affiche_file(FIFO_M* f);

#endif