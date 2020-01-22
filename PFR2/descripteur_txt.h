#include <stdio.h>
#include <stdlib.h>
#include "FIFO.h"
#include <string.h>


#define TAILLE_MAX 1000

typedef struct Descripteur_txt{
	int nb_mots;
	int nb_lettres;
	FIFO_M *mot_cle;
}DESC;

typedef struct MotPourMotCle {
	int occurence;
	char[TAILLE_MAX] mot;
}MOT;

typedef struct CellulePourMotCle {
	typedef struct CellulePourMotCle* ptr_suiv;
	MOT mot_cle;
}Cell_M;

typedef struct FIFOMotCle {
	Cell_M *debut, *fin;
}FIFO_M;

DESC creerDescripteur_txt(FILE *fichier_txt);
float comparerDescripteurs(DESC d1, DESC d2);
FIFO descToString(DESC d);
int descripteursIdentiques(DESC d1, DESC d2);
void afficheTxt(FILE *fichier_txt);
int motIdentiques(MOT mot1, MOT mot2);

void MInit_File(FIFO_M f);
int MFile_estVide(FIFO_M f);
FIFO MEnfiler(FIFO_M* f, char e);
