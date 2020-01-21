#include <stdlib.h>
#include <stdio.h>
#include "FIFO.h"
#include <string.h>
#include "descripteur_txt.h"



DESC creerDescripteur_txt(FILE *fichier_txt){
	DESC descripteur;
	descripteur.nb_lettres = 0;
	descripteur.nb_mots = 0;
	descripteur.mot_cle = NULL;
	do {
		fgets(chaine, TAILLE_MAX, fichier_txt);
	} while (chaine != "")
	for (int i = 0; i < TAILLE_MAX; i++) {
		if (chaine[i] != ' ')
			descripteur.nb_lettres++;
		else
			descripteur.nb_mots++;
	}
	descripteur.mot_cle = &getMotCle(fichier_txt);
}

float comparerDescripteurs(DESC d1, DESC d2){
	FIFO fd1, fd2;
	float pourcentage, total;
	fd1 = descToString(d1);
	fd2 = descToString(d2);
	if (FIFO_diff(&fd1, &fd2))
		pritnf("Les 2 descripteurrs sont identiques");
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

int motIdentiques(MOT mot1, MOT mot2) {
	return(FIFO_diff(&(mot1.file_mot), &(mot2.file_mot)));
}

FIFO descToString(DESC d){
	FIFO f;
	Enfiler(&f, d.nb_lettres);
	Enfiler(&f, d.nb_mots);
	while (d.mot_cle->debut_file != NULL) {
		Enfiler(&f, d.mot_cle->debut_file->e);
		d.mot_cle = d.mot_cle->debut_file->ptr_suiv;
	}
	return(*f);
}

int descripteursIdentiques(DESC d1, DESC d2){
	return(comparerDescripteurs(d1, d2)==100);
}

FIFO getMotCle(FILE *fichier_txt){
	MOT mot1, mot2;
	if (fichier_txt == NULL)
		printf("impossible de localiser le fichier \n");
	else {
		do {
			fgets(chaine, TAILLE_MAX, fichier_txt);
		} while (chaine != "")
		


		
	fclose(fichier_txt);
}

void afficheTxt(FILE *fichier_txt) {
	char tab[TAILLE_MAX] = "";
	fgets(tab, TAILLE_MAX, fichier_txt);
	for (int i = 0; i < TAILLE_MAX; i++) {
		printf("%c", tab[i]);
	}
	fclose(fichieir_txt);
}
