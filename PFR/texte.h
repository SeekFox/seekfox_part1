#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FIFO.h"

typedef struct Descripteur_txt{
	int nb_mots;
	int nb_lettres;
	string titre;
	string adresseDuFichier;

}DESC;

typedef struct Cellule_FIFO{
	string mot;
	struct Cellule_FIFO *ptr_prochain_mot; 

}CELL;

typedef CELL *FIFO;

DESC creerDescripteur(DOSS dossier_txt);
float comparerDescripteurs(DESC d1, DESC d2);
FIFO conversionDescripteurString(DESC d);
DESC conversionStringDescripteur(FIFO f);
int descripteursIdentiques(DESC d1, DESC d2);

