#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "descripteur_txt.h"
#include "FIFO.h"


DESCTXT creerDescripteur_txt(FILE* fichier_txt) {
	DESCTXT descripteur;
	FIFO_M* FILE_MC = (FIFO_M*)malloc(sizeof(FIFO_M));
	(FILE_MC)->debut = (Cell_M*)malloc(sizeof(Cell_M));
	char tempo[TAILLE_MAX];
	int j=0, i=0;
	char chaine[TAILLE_MAX] = "";
	descripteur.fmot_cle = FILE_MC;
	descripteur.nb_lettres = 0;
	descripteur.nb_mots = 0;
	(descripteur.fmot_cle->debut)->mot_cle.occurence = 0;


	while (fgets(chaine, TAILLE_MAX, fichier_txt) != NULL) {
		for (i = 0; i < strlen(chaine); i++) {
			if (chaine[i] == '<') {
				while (chaine[i] != '>' && chaine[i]!='\0')
					i++;
			}
			
			while (chaine[i] != ' ' && chaine[i]!='\0') {
				tempo[j] = chaine[i];
				descripteur.nb_lettres++;
				i++;
				j++;
			}
			descripteur.nb_mots++;
			if (!motExiste(FILE_MC, tempo)) {
				MEnfiler(FILE_MC, tempo);
			}
		}
	}
	
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
	while (memoire != NULL) {
		for (int j = 0; j < strlen(memoire->mot_cle.mot); j++) {
			f = Enfiler(&f, memoire->mot_cle.mot[j]);
		}
		f = Enfiler(&f, '\n');
		f = Enfiler(&f, (char) (memoire->mot_cle.occurence));
		f = Enfiler(&f, '\n');
		memoire = memoire->ptr_suiv;
	}
	return(f);
}

int motExiste(FIFO_M *file, char test[]) {
	int motexiste=0;
	Cell_M* memoire = file->debut;
	if (!MFile_estVide(*file)) {
		while (memoire != NULL  ) {
			motexiste = strcoll(memoire->mot_cle.mot, test);
			if (motexiste) {
				memoire->mot_cle.occurence++;
				break;
			}
			memoire = memoire->ptr_suiv;
		}
	}
	return( motexiste);
}

char* descToString(DESCTXT d){
	char * tab = (char* )malloc(TAILLE_MAX * sizeof(char));
	char* stock = (char*)malloc(TAILLE_MAX * sizeof(char));
	//printf("<%d %d\n", strlen(tab), TAILLE_MAX);
//	int compt = 4;
	Cell_M* memoire = d.fmot_cle->debut;
	tab[0] = (char) d.nb_lettres;
	tab[1] = ' ';
	tab[2] = (char) d.nb_mots;
	tab[3] = '\n';
	while (memoire != NULL) {
		printf(">%d\n",memoire->ptr_suiv==NULL);
		tab = strcat(tab, (memoire->mot_cle).mot);
		tab = strcat(tab, ":");
		sprintf(stock,"%d", memoire->mot_cle.occurence);
		tab = strcat(tab, stock);
		/*compt++;
		tab[compt] = ':';
		compt++;
		tab[compt] = memoire->mot_cle.occurence;*/
		memoire = memoire->ptr_suiv;
		//compt++;
	
	}
	printf(">>%d %s\n", strlen(tab),tab);
	//tab=strcat(tab, '\0');
	printf("dfgr\n");
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


