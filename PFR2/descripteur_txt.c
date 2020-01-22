#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "descripteur_txt.h"
#include "FIFO.h"


DESC creerDescripteur_txt(FILE* fichier_txt) {
	DESC descripteur;
	FIFO FILE_MC;
	char[TAILLE_MAX] tempo;
	int j=0, i;
	descripteur.nb_lettres = 0;
	descripteur.nb_mots = 0;
	descripteur.mot_cle = NULL;
	do {
		fgets(chaine, TAILLE_MAX, fichier_txt);
	} while (chaine != "")
		for (i = 0; i < strlen(chaine); i++) {
			if (chaine[i] = '<') {
				while (chaine[i] != '>')
					i++;
			}
			while (chaine[i] != ' ') {
				tempo[j] = chaine[i];
				descripteur.nb_lettres++;
				j++;
			}
			if (!motExiste(&FILE_MC, tempo))
				Enfiler(&FILE_MC, tempo);
			else 

			j = 0;
			descripteur.nb_mots++;
		}
		
			descripteur.mot_cle = &FILE_MC;
		}


float comparerDescripteurs(DESC d1, DESC d2){
	FIFO fd1, fd2;
	float pourcentage, total;
	fd1 = descToString(d1);
	fd2 = descToString(d2);
	if (!FIFO_diff(&fd1, &fd2))
		pritnf("Les 2 descripteurs sont identiques");
	Cell* temp1 = fd1->debut_file, temp2 = fd2->debut_file;
	while (temp1 != NULL) {
		if (temp1->e == temp2->e) {
			pourcentage++;
		}
		temp1 = (*temp1).ptr_suiv;
		temp2 = (*temp2).ptr_suiv;
		total++;
	}
	return(100*pourcentage/total);

}


int motExiste(FIFO_M *file, char[] test) {
	int motexiste=0;
	int mem;
	mem = file->debut;
	Cell_M* temp = file;
	if (!MFile_estVide(file) {
		while (file != NULL ) {
			motexiste = strcoll(file->debut->mot_cle), test);
			file->debut = file->debut->ptr_suiv;
			if (motexiste) {

				file->debut->mem;
			}
		}
	}
	return( motexiste);
}

FIFO descToString(DESC d){
	FIFO f;
	Enfiler(&f, (char) d.nb_lettres);
	Enfiler(&f, (char) d.nb_mots);
	while (d.mot_cle->debut_file != NULL) {
		Enfiler(&f, d.mot_cle->debut_file->e);
		d.mot_cle = d.mot_cle->debut_file->ptr_suiv;
	}
	return(*f);
}

int descripteursIdentiques(DESC d1, DESC d2){
	return(comparerDescripteurs(d1, d2)==100);
}

void afficheTxt(FILE *fichier_txt) {
	char tab[TAILLE_MAX] = "";
	fgets(tab, TAILLE_MAX, fichier_txt);
	for (int i = 0; i < TAILLE_MAX; i++) {
		printf("%c", tab[i]);
	}
	fclose(fichier_txt);
}

void MInit_File(FIFO_M f) {
	f.debut_file = NULL;
	f.fin_file = NULL;
}

int MFile_estVide(FIFO_M f) {
	return(f.debut_file == NULL);
}

FIFO_M MEnfiler(FIFO_M* f, char[] e) {
	Cell_M* temp;
	temp = (Cell_M*)malloc(sizeof(Cell_M));
	memcpy((*temp).mot_cle, e, strlen(e));

	(*temp).ptr_suiv = f->fin_file;
	if (f->debut_file == NULL)
		f->debut_file = temp;
	else {
		Cell_M* actuel = f->debut_file;
		while (actuel->ptr_suiv != NULL)
			actuel = actuel->ptr_suiv;
		actuel->ptr_suiv = temp;
	}
	return(*f);
}


