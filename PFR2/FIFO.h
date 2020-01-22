#include <stdio.h>
#include <stdlib.h>

typedef struct MaCellule{
	char e;
	struct MaCellule *ptr_suiv;
}Cell;

typedef struct MaFifo{
	Cell *debut_file, *fin_file;
}FIFO;


void Init_File(FIFO f);
void Affiche_file(FIFO *f);
int File_estVide(FIFO f);
FIFO Enfiler(FIFO *f, char e);
FIFO Defiler(FIFO *f, char *adr);
int FIFO_diff(FIFO *f1, FIFO *f2);