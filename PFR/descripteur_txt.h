#include <stdio.h>
#include <stdlib.h>
#include "FIFO.h"
#include <string.h>


#define TAILLE_MAX 1000

typedef struct Descripteur_txt{
	int nb_mots;
	int nb_lettres;
	FIFO *mot_cle;

}DESC;

typedef struct MotPourMotCle {
	int occurence;
	FIFO *file_mot;
}MOT;

DESC creerDescripteur_txt(FILE *fichier_txt);
float comparerDescripteurs(DESC d1, DESC d2);
FIFO descToString(DESC d);
int descripteursIdentiques(DESC d1, DESC d2);
FIFO getMotCle(FILE *contenu_fichier_txt);
void afficheTxt(FILE fichier_txt);
int motIdentiques(MOT mot1, MOT mot2);

