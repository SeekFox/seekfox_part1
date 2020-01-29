#ifndef TEXTE_H
#define TEXTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MOT.h"
#include "File_mots.h"

#define TAILLE_MAX 1000000

typedef struct Descripteur_txt{
	int nb_mots;
	int nb_lettres;
	FIFO_M *fmot_cle;
}DESCTXT;


void Dinit(DESCTXT *d);
DESCTXT creerDescripteur_txt(FILE *fichier_txt);
float comparerDescripteurstxt(DESCTXT d1, DESCTXT d2);
char* desctxtToString(DESCTXT d);
// Un mot mis en paramètre existe-t-il déjà dans la file de mots, si oui on incrémente le nombre d'occurence de ce mot. 
int motExiste(FIFO_M* file, char* test);
int descripteurstxtIdentiques(DESCTXT d1, DESCTXT d2);
void afficheTxt(FILE *fichier_txt);
DESCTXT stringToText(char* s);


#endif