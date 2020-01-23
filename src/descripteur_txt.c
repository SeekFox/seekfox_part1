#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "descripteur_txt.h"
#include "FIFO.h"


DESCTXT creerDescripteur_txt(FILE* fichier_txt) {
	DESCTXT descripteur;
	FIFO_M FILE_MC;
	char tempo[TAILLE_MAX];
	int j=0, i=0;
	char chaine[TAILLE_MAX] = "";
	descripteur.nb_lettres = 0;
	descripteur.nb_mots = 0;
	descripteur.fmot_cle = NULL;

    /*do {
		fgets(chaine, TAILLE_MAX, fichier_txt);
	} while (strcmp(chaine, "")!=0);*/

	while(fgets(chaine, TAILLE_MAX, fichier_txt)!=NULL) {
        for (i = 0; i < strlen(chaine); i++) {
            printf("1\n");
            fflush;
		    if (chaine[i] == '<') {
			    while (chaine[i] != '>' && chaine[i] != '\0') i++;
		    }
            printf("2\n");
            fflush;
		    while (chaine[i] != ' ' && chaine[i] != '\0') {
			    tempo[j] = chaine[i];
			    descripteur.nb_lettres++;
			    i++;
			    j++;
		    }
            printf("3\n");
            fflush;
		    descripteur.nb_mots++;
		    if (!motExiste(&FILE_MC, tempo)) MEnfiler(&FILE_MC, tempo);
            printf("4\n");
            fflush;
        }
        printf("Sorti!\n");
        fflush;
    }
	descripteur.fmot_cle = &FILE_MC;
	return(descripteur);
}


float comparerDescripteurs(DESCTXT d1, DESCTXT d2){
	FIFO fd1, fd2;
	float pourcentage, total;
	fd1 = descToFIFO(d1);
	fd2 = descToFIFO(d2);
	if (!FIFO_diff(&fd1, &fd2))
		printf("Les 2 descripteurs sont identiques");
	Cell* temp1 = fd1.debut_file;
	Cell* temp2 = fd2.debut_file;
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

FIFO descToFIFO(DESCTXT d) {
	FIFO f;
	Cell_M* memoire = d.fmot_cle->debut;
	f = Enfiler(&f, d.nb_lettres);
	f = Enfiler(&f, d.nb_mots);
	while (d.fmot_cle->debut != NULL) {
		f = Enfiler(&f, d.fmot_cle->debut->mot_cle.mot);
		f = Enfiler(&f, '\n');
		f = Enfiler(&f, d.fmot_cle->debut->mot_cle.occurence);
		f = Enfiler(&f, '\n');
		d.fmot_cle->debut = d.fmot_cle->debut->ptr_suiv;
	}
	d.fmot_cle->debut = memoire;
	return(f);
}

int motExiste(FIFO_M *file, char test[]) {
	int motexiste=0;
	Cell_M* memoire;
	memoire = file->debut;
	Cell_M* temp = file->debut;
	if (!MFile_estVide(*file)) {
		while (file != NULL ) {
			motexiste = strcoll(file->debut->mot_cle.mot, test);
			file->debut = file->debut->ptr_suiv;
			if (motexiste) {
				file->debut->mot_cle.occurence++;
				file->debut=memoire;
			}
		}
	}
	return( motexiste);
}

char* descToString(DESCTXT d){
	char* tab = malloc(TAILLE_MAX * sizeof(char));
	int compt = 4;
	Cell_M* memoire = d.fmot_cle->debut;
	tab[0] = d.nb_lettres;
	tab[1] = ' ';
	tab[2] = d.nb_mots;
	tab[3] = ' ';
	while (d.fmot_cle->debut != NULL) {
		tab = strcat(tab, d.fmot_cle->debut->mot_cle.mot);
		compt++;
		tab[compt] = ':';
		compt++;
		tab[compt] = d.fmot_cle->debut->mot_cle.occurence;
		d.fmot_cle->debut = d.fmot_cle->debut->ptr_suiv;
		compt++;
	}
	tab[compt] = '\0';
	return(tab);
}

int descripteursIdentiques(DESCTXT d1, DESCTXT d2){
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
	f.debut= NULL;
	f.fin = NULL;
}

int MFile_estVide(FIFO_M f) {
	return(f.debut == NULL);
}

FIFO_M MEnfiler(FIFO_M* f, char e[]) {
	Cell_M* temp;
	temp = (Cell_M*)malloc(sizeof(Cell_M));
	memcpy((temp->mot_cle.mot), e, strlen(e));

	(*temp).ptr_suiv = f->fin;
	if (f->debut == NULL)
		f->debut = temp;
	else {
		Cell_M* actuel = f->debut;
		while (actuel->ptr_suiv != NULL)
			actuel = actuel->ptr_suiv;
		actuel->ptr_suiv = temp;
	}
	return(*f);
}