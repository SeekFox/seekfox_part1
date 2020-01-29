#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "descripteur_txt.h"
#include "FIFO.h"

// Fonction principale, qui crée un descripteur 
DESCTXT creerDescripteur_txt(FILE* fichier_txt) {

	////////////////// INITIALISATION / DECLARATION DES VARIABLES /////////////////
	DESCTXT descripteur;
	Dinit(&descripteur);
	descripteur.fmot_cle = (FIFO_M*)malloc(sizeof(FIFO_M));
	if (descripteur.fmot_cle == NULL)
		printf("Erreur d'allocation\n");

	FIFO_M FIFO;
	MInit_File(&FIFO);
	FIFO.debut = (Cell_M*)malloc(sizeof(Cell_M));
	FIFO.fin = (Cell_M*)malloc(sizeof(Cell_M));
	if (FIFO.debut == NULL || FIFO.fin == NULL)
		printf("Erreur d'allocation  \n");
	//*(descripteur.fmot_cle) = FIFO;
	

	//Cell_M Cell;
	Cinit(FIFO.debut);
	//descripteur.fmot_cle->debut = &Cell;
	//descripteur.fmot_cle->fin->ptr_suiv = (Cell_M*)malloc(sizeof(Cell_M));

	//if (descripteur.fmot_cle->debut->ptr_suiv == NULL|| descripteur.fmot_cle->fin == NULL)
	//	printf("Erreur d'allocation\n");

	//descripteur.fmot_cle->debut = &Cell;

	int j = 0, i = 0;
	char chaine[TAILLE_MAX] = "";
	char tempo[TAILLE_MAX] = "";
	
	//////////////////////////// BOUCLE PRINCIPALE /////////////////////////////////
	while (fgets(chaine, TAILLE_MAX, fichier_txt) != NULL) {	// Pour chaque ligne
		//printf("test entree en boucle \n");
		for (i = 0; i < strlen(chaine); i++) {					//pour chaque lettre de cette ligne
			if (chaine[i] == '<') {								// supprimer les balises 
				//printf("Balise detectee \n");
				while (chaine[i] != '>') {
					i++;										//en incrémentant le compteur sans les prendre en compte
				}
				i++;
			}
			else {
				while (chaine[i] != ' ' && chaine[i] != '\0') {	// pour chaque mot
					tempo[j] = chaine[i];			// on récupere le mot dans un tableau séparé
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
				//printf(" nb mots %d \n", descripteur.nb_mots);	
			// on exécute motExiste, qui incrémente le nombre d'occurence si le mot est déjà dans la File
			   	if (!motExiste((descripteur.fmot_cle), tempo)) {
					printf("test");
					MEnfiler(descripteur.fmot_cle, tempo);		// si le mot récupéré n'est pas dans la file, on l'y rajoute
				}
			}			
		}
	}
	return(descripteur);
}

void Minit(MOT *m) {
	m->mot = malloc(sizeof(char) * TAILLE_MAX);
	m->occurence = 0;
}

void Cinit(Cell_M *c) {
	c->ptr_suiv = NULL;
	MOT* m = (MOT*)malloc(sizeof(MOT));
	Minit(m);
	c->mot_cle = *m;
}

void Dinit(DESCTXT *descripteur) {
	descripteur->nb_lettres = 0;
	descripteur->nb_mots = 0;
	descripteur->fmot_cle = NULL;
}

//Comparer les descripteurs en les transformant en premier lieu en file pour
// utiliser la fonction fifodiff, codée précédemment. 
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


// Transformer un descripteur en File, utilisé dans la comparaison des descripteurs
// Vestige remanié de la première version 
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


// Un mot mis en paramètre existe-t-il déjà dans la file de mots, si oui on incrémente le nombre d'occurence de ce mot. 
int motExiste(FIFO_M *file, char* test) {
	printf("mot_existe test ");
	int motexiste = 0;
	char convert[TAILLE_MAX]="";
	Cell_M * memoire = file->debut;
	printf("%p", memoire->mot_cle);
	
	if (!MFile_estVide(file)) {
		while (memoire != NULL && !motexiste) {
			motexiste = strcoll((memoire->mot_cle).mot, test);
			printf("motexiqste %d\n", motexiste);
			if (motexiste == 0) {
				memoire->mot_cle.occurence++;
			}
			memoire = memoire->ptr_suiv;
		}
	}
	return(motexiste);

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
	while (memoire->mot_cle.mot != "" ) {		// Pour tous les mots contenus dans la file de mot
	//	if (memoire->mot_cle.occurence >= getTailleMin) {
			strcat(tab, (memoire->mot_cle).mot);	// On ajoute le mot et son occurence convertie en char*
			strcat(tab, ":");						// dans le "String" renvoyé. 
			sprintf(stock, "%d", memoire->mot_cle.occurence);
			strcat(tab, stock);
			strcat(tab, " ");
			memoire = memoire->ptr_suiv;
	//	}
	}
	strcat(tab, "\0");
	return(tab);
}


// Les descripteurs donnés en paramètre sont ils identiques 
int descripteursIdentiques(DESCTXT d1, DESCTXT d2){
	return(comparerDescripteurs(d1, d2)==100);	// comparerDescripteurs donne un pourcentage de ressemblance, 
												// Ce pourcentage est il 100 ?
}


// Test d'affichage du texte reçu en paramètre
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
	temp->mot_cle.mot = malloc(sizeof(char) * TAILLE_MAX);
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
}


