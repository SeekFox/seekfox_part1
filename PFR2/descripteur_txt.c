#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "descripteur_txt.h"
#include "FIFO.h"

// Fonction principale, qui cr�e un descripteur 
DESCTXT creerDescripteur_txt(FILE* fichier_txt) {

	////////////////// INITIALISATION / DECLARATION DES VARIABLES /////////////////
	DESCTXT descripteur;
	//FIFO_M* FILE_MC = (FIFO_M*)malloc(sizeof(FIFO_M));
	descripteur.fmot_cle = (FIFO_M*)malloc(sizeof(FIFO_M));
	descripteur.fmot_cle->debut = (Cell_M*)malloc(sizeof(Cell_M));
	//char* tempo = (char*)malloc(sizeof(char));
	int j = 0, i = 0;
	char chaine[TAILLE_MAX] = "";
	char tempo[TAILLE_MAX] = "";
	//	descripteur.fmot_cle = FILE_MC;
	descripteur.nb_lettres = 0;
	descripteur.nb_mots = 0;
	MInit_File(descripteur.fmot_cle);

	//////////////////////////// BOUCLE PRINCIPALE /////////////////////////////////
	while (fgets(chaine, TAILLE_MAX, fichier_txt) != NULL) {	// Pour chaque ligne
		//printf("test entree en boucle \n");
		for (i = 0; i < strlen(chaine); i++) {					//pour chaque lettre de cette ligne
			if (chaine[i] == '<') {								// supprimer les balises 
				//printf("Balise detectee \n");
				while (chaine[i] != '>') {
					i++;										//en incr�mentant le compteur sans les prendre en compte
				//	printf("elimination de la balise\n");
					//printf(" i : %d\n",i);
				//	printf("car elimine : %c\n", chaine[i]);
				}
				i++;
			}
			else {
			//	printf("carac interessant %c\n", chaine[i]);
				while (chaine[i] != ' ' && chaine[i] != '\0') {	// pour chaque mot
					tempo[j] = chaine[i];	
					//printf("dans chaine %c \n", chaine[i]);		// on r�cupere le mot dans un tableau s�par�
					descripteur.nb_lettres++;
					i++;
					j++;
				//	printf("i : %d \n", i);
				//	printf("tempo %s\n", tempo);
				}
				tempo[j] = '\0';
			//	printf("tempo %s\n", tempo);
				j = 0;
				descripteur.nb_mots++;
				//motExiste(descripteur.fmot_cle, tempo);
			//	printf(" nb mots%d \n", descripteur.nb_mots);	
				printf("%d \n", a);

			// on ex�cute motExiste, qui incr�mente le nombre d'occurence si le mot est d�j� dans la File
			   	if (!motExiste(descripteur.fmot_cle, tempo)) {
					MEnfiler(descripteur.fmot_cle, tempo);		// si le mot r�cup�r� n'est pas dans la file, on l'y rajoute
				}
			}			
		}
	}
	return(descripteur);
}

//Comparer les descripteurs en les transformant en premier lieu en file pour
// utiliser la fonction fifodiff, cod�e pr�c�demment. 
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


// Transformer un descripteur en File, utilis� dans la comparaison des descripteurs
// Vestige remani� de la premi�re version 
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


// Un mot mis en param�tre existe-t-il d�j� dans la file de mots, si oui on incr�mente le nombre d'occurence de ce mot. 
int motExiste(FIFO_M *file, char* test) {
	int motExiste(FIFO_M * file, char* test) {
		int motexiste = 0;
		Cell_M* memoire = file->debut;
		if (!MFile_estVide(file)) {
			while (memoire != NULL && !motexiste) {
				motexiste = strcoll((memoire->mot_cle).mot, test);
				printf("%d\n", motexiste);
				if (motexiste == 0) {
					memoire->mot_cle.occurence++;
				}
				memoire = memoire->ptr_suiv;
			}
		}
		return(motexiste);

	}
}


// Transformer un descripteur en String
char* descToString(DESCTXT d){
	char * tab = (char* )malloc(TAILLE_MAX * sizeof(char));
	char* stock = (char*)malloc(TAILLE_MAX * sizeof(char));
	Cell_M* memoire = (Cell_M*)malloc(sizeof(Cell_M));
	memoire= d.fmot_cle->debut;
	sprintf(stock, "%d", d.nb_lettres);
	strcat(tab, stock);
	strcat(tab, " ");
	sprintf(stock, "%d", d.nb_mots);
	strcat(tab, stock);
	strcat(tab, "\n");
	while (memoire != NULL) {		// Pour tous les mots contenus dans la file de mot
	//	if (memoire->mot_cle.occurence >= getTailleMin) {
			strcat(tab, (memoire->mot_cle).mot);	// On ajoute le mot et son occurence convertie en char*
			strcat(tab, ":");						// dans le "String" renvoy�. 
			sprintf(stock, "%d", memoire->mot_cle.occurence);
			strcat(tab, stock);
			strcat(tab, " ");
			memoire = memoire->ptr_suiv;
	//	}
	}
	strcat(tab, "\0");
	return(tab);
}


// Les descripteurs donn�s en param�tre sont ils identiques 
int descripteursIdentiques(DESCTXT d1, DESCTXT d2){
	return(comparerDescripteurs(d1, d2)==100);	// comparerDescripteurs donne un pourcentage de ressemblance, 
												// Ce pourcentage est il 100 ?
}


// Test d'affichage du texte re�u en param�tre
void afficheTxt(FILE *fichier_txt) {
	char tab[TAILLE_MAX] = "";
	fgets(tab, TAILLE_MAX, fichier_txt);
	for (int i = 0; i < TAILLE_MAX; i++) {
		printf("%c", tab[i]);
	}
	fclose(fichier_txt);
}


// Initialisation d'une file de mots
void MInit_File(FIFO_M* f) {
	f->debut= NULL;
	f->fin = NULL;
}


// File de mots vide
int MFile_estVide(FIFO_M* f) {
	return(f->debut == NULL);
}


// Enfiler des mots dans une file de mots. 
void MEnfiler(FIFO_M* f, char* e) {
	Cell_M* temp;
	temp = (Cell_M*)malloc(sizeof(Cell_M));
	temp->mot_cle.mot = malloc(sizeof(MOT));
	strcat((temp->mot_cle).mot, e );
	temp->mot_cle.occurence = 1;
	temp->ptr_suiv = f->fin;
	if (f->debut == NULL)
		f->debut = temp;
	else {
		Cell_M* actuel = f->debut;
		while (actuel->ptr_suiv != NULL)
			actuel = actuel->ptr_suiv;
		actuel->ptr_suiv = temp;
	}
	//return(*f);
}


