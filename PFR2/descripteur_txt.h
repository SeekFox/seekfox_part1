#ifndef TEXTE_H
#define TEXTE_H

#include <stdio.h>
#include <stdlib.h>
#include "FIFO.h"
#include <string.h>


#define TAILLE_MAX 1000

typedef struct MotPourMotCle {
	int occurence;
	char mot[TAILLE_MAX];
}MOT;

typedef struct CellulePourMotCle {
	struct CellulePourMotCle* ptr_suiv;
	MOT mot_cle;
}Cell_M;

typedef struct FIFOMotCle {
	Cell_M* debut, * fin;
}FIFO_M;
typedef struct Descripteur_txt{
	int nb_mots;
	int nb_lettres;
	FIFO_M *mot_cle;
}DESC;



DESC creerDescripteur_txt(FILE *fichier_txt);
float comparerDescripteurs(DESC d1, DESC d2);
FIFO descToString(DESC d);
int descripteursIdentiques(DESC d1, DESC d2);
void afficheTxt(FILE *fichier_txt);
int motExiste(FIFO_M* file, char* test);

void MInit_File(FIFO_M f);
int MFile_estVide(FIFO_M f);
FIFO_M MEnfiler(FIFO_M* f, char* e);

#endif