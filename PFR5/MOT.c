#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MOT.h"

void Minit(MOT *m) {
	//m->mot = malloc(sizeof(char) * TAILLE_MAX);
	m->mot = NULL;
	m->occurence = 0;
}

// Transformer un descripteur en String
char* motToString(MOT m){
	char* tab = (char* )malloc(sizeof(MOT));
	//char* stock = (char*)malloc(TAILLE_MAX * sizeof(char));
	
	snprintf(tab, strlen(m.mot)+sizeof(m.occurence),"%s:%d ",m.mot,m.occurence);
	
	/*strcat(tab, m.mot);						// On ajoute le mot et son occurence convertie en char*
	strcat(tab, ":");						// dans le "String" renvoyé. 
	sprintf(stock,"%d", m.occurence);
	strcat(tab, stock);
	strcat(tab, " ");*/
	return(tab);
}


// Les descripteurs donnés en paramètre sont ils identiques 
float comparerMots(char *m1, char* m2) {
	int max_taille;
	int pourcentage=0;
	int total=0;
	if (strlen(m1) > strlen(m2))
		max_taille = strlen(m1);
	else
		max_taille = strlen(m2);

	for (int i = 0; i < max_taille; i++){						// comparerMots donne un pourcentage de ressemblance, 
		if (m1[i] == m2[i]) {							// Ce pourcentage est il 100 ?
			pourcentage++;
		}
		total++;
	}
	return(100*pourcentage/total);
}

int motsIdentiques(char* m1, char* m2){
	return(comparerMots(m1, m2)==100.00);	
}

// File de mots vide
int motEstVide(MOT m) {
	return(  m.occurence == 0);
}


MOT remplirMot(MOT m, int occurence, char* tab) {
	m.mot = (char*)malloc(sizeof(char));
	strcpy(m.mot, tab);
	m.occurence = occurence;
	return(m);
}