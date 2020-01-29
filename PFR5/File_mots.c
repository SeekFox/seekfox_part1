#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MOT.h"
#include "File_mots.h"

// Initialisation d'une file de mots
void Finit(FIFO_M* f) {
	printf("finit\n");
	f->debut = (Cell_M*)malloc(sizeof(Cell_M));
	printf("finit\n");
	Cinit(f->debut);
}

void Cinit(Cell_M* c) {
	c->ptr_suiv = NULL;
	//c->ptr_suiv = (Cell_M*)malloc(sizeof(Cell_M));
	MOT m;
	Minit(&m);
	c->mot_cle = m;
}

// File de mots vide
int FestVide(FIFO_M* f) {
	return(motEstVide(f->debut->mot_cle));
}

// Enfiler des mots dans une file de mots. 
void enfiler_M(FIFO_M* f, char* e) {
	Cell_M* temp = (Cell_M*)malloc(sizeof(Cell_M));
	Cinit(temp);
	temp->mot_cle = remplirMot(temp->mot_cle, 1, e);
	if (FestVide(f)) {
		printf("F bien vidie 1er empilage\n");
		f->debut = temp;
	}
	else {
		Cell_M* actuel = f->debut;
		while (actuel->ptr_suiv != NULL)
			actuel = actuel->ptr_suiv;
		actuel->ptr_suiv = temp;
	}
}

// Transformer une File mot clé en String
char* fToString(FIFO_M *f) {
	char* tab = (char*)malloc(sizeof(char));
	strcpy(tab, "");
	Cell_M* temp = f->debut;
	char* tempo= "";
	int i = 1;
	while (temp != NULL) {
		tempo = motToString(temp->mot_cle); 
		tab = (char*)realloc(tab, strlen(tempo) * sizeof(char));
		sprintf(tab, "%s%s",tab,tempo);
		temp = temp->ptr_suiv;
	}
	return(tab);
}

void Affiche_file(FIFO_M* f) {
	if (FestVide(f))
		printf("File est Vide");
	else {
		Cell_M* temp = f->debut;
		while (temp != NULL) {
			printf("%s ", motToString(temp->mot_cle));
			temp = temp->ptr_suiv;
		}
		printf("\n");
	}
}

// Un mot mis en paramètre existe-t-il déjà dans la file de mots, si oui on incrémente le nombre d'occurence de ce mot. 
int motExiste(FIFO_M* file, char* test) {
	int motexiste = 0;
	char convert[TAILLE_MAX] = "";
	Cell_M* memoire = file->debut;
	if (!FestVide(file)) {
		while (memoire != NULL && !motexiste) {
			motexiste = motsIdentiques((memoire->mot_cle).mot, test);
			if (motexiste == 0) {
				memoire->mot_cle.occurence++;
			}
			memoire = memoire->ptr_suiv;
		}
	}
	return(motexiste);

}

//Comparer les descripteurs en les transformant en premier lieu en file pour
// utiliser la fonction fifodiff, codée précédemment. 
float comparerF(FIFO_M *f1, FIFO_M *f2){
	float areturn=0;
	int compteur = 0;
	Cell_M* temp1 = f1->debut;
	Cell_M* temp2 = f2->debut;
	while (temp1 != NULL && temp2 !=NULL) {
		areturn += comparerMots(temp1->mot_cle.mot, temp2->mot_cle.mot);
		temp1 = temp1->ptr_suiv;
		temp2 = temp2->ptr_suiv;
		compteur++;
	}
	if (temp1 != NULL) {
		while (temp1 != NULL) {
			compteur++;
			temp1 = temp1->ptr_suiv;
		}
	}
	if (temp2 != NULL) {
		while (temp2 != NULL) {
			compteur++;
			temp2 = temp2->ptr_suiv;
		}
	}

	return(areturn/compteur); 
}