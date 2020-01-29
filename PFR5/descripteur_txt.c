#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MOT.h"
#include "File_mots.h"
#include "descripteur_txt.h"

// Fonction principale, qui crée un descripteur 
DESCTXT creerDescripteur_txt(FILE* fichier_txt) {

	////////////////// INITIALISATION / DECLARATION DES VARIABLES /////////////////
	DESCTXT descripteur;
	Dinit(&descripteur);
	int j = 0, i = 0;
	char chaine[TAILLE_MAX] = "";
	char tempo[TAILLE_MAX] = "";
	
	//////////////////////////// BOUCLE PRINCIPALE /////////////////////////////////
	while (fgets(chaine, TAILLE_MAX, fichier_txt) != NULL) {	// Pour chaque ligne
		printf("test entree en boucle \n");
		for (i = 0; i < strlen(chaine); i++) {					//pour chaque lettre de cette ligne
			if (chaine[i] == '<') {								// supprimer les balises 
				printf("Balise detectee \n");
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
					printf("i : %d \n", i);
					printf("tempo %s\n", tempo);
				}
				tempo[j] = '\0';
				printf("tempo %s\n", tempo);
				j = 0;
				descripteur.nb_mots++;
				printf(" nb mots %d \n", descripteur.nb_mots);	
			// on exécute motExiste, qui incrémente le nombre d'occurence si le mot est déjà dans la File
			   	if (!motExiste((descripteur.fmot_cle), tempo)) {
					printf("nouveau mot \n");
					enfiler_M(descripteur.fmot_cle, tempo);		// si le mot récupéré n'est pas dans la file, on l'y rajoute
				}
			}			
		}
	}
	return(descripteur);
}


void Dinit(DESCTXT *descripteur) {
	descripteur->nb_lettres = 0;
	descripteur->nb_mots = 0;
	Finit(descripteur->fmot_cle);
}

//Comparer les descripteurs en les transformant en premier lieu en file pour
// utiliser la fonction fifodiff, codée précédemment. 
float comparerDescripteurstxt(DESCTXT d1, DESCTXT d2){
	return(comparerF(d1.fmot_cle, d2.fmot_cle));

}


// Transformer un descripteur en String
char* desctxtToString(DESCTXT d){
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
	strcat(tab, fToString(d.fmot_cle));
	return(tab);
}


// Les descripteurs donnés en paramètre sont ils identiques 
int descripteurstxtIdentiques(DESCTXT d1, DESCTXT d2){
	return(comparerDescripteurstxt(d1, d2)==100);	// comparerDescripteurs donne un pourcentage de ressemblance, 
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


DESCTXT stringToText(char* s) {
	DESCTXT de;
	Dinit(&de);
	int n = 0, j = 0;
	char* tempo = "";
	while (s[n] != '\0') {
		if (s[n] == ':') {
			tempo[j] = '\0';
			de.fmot_cle->debut->mot_cle = remplirMot(de.fmot_cle->debut->mot_cle, atoi(&(s[n+1])), tempo );
			n += 2;
			j = 0;
		}
		tempo[j] = s[n];
		n++;
		j++;
	}
}

