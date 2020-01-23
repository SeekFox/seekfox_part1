#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descripteur_txt.h"
#include "FIFO.h"

void main(void){
	FILE *fichier=NULL;
	FIFO file;
	int nb_mot,nb_lettres;
	char[1000] String ;
	DESC descri; 
	printf("TEST DESCRIPTEURv\n");
	fichier = fopen("test.txt", "r");
	if (fichier_txt == NULL)
		printf("impossible de localiser le fichier \n");
	else 
		Descri = creerDescripteur(&fichier);
	fclose(fichier);
	printf("TEST toString \n");
	String = descToString(Descri);
	printf("%s",&String);
	printf("TEST COMPARAISON \n");
	if(descripteursIdentiques(Descri, Descri)
		printf("le descripteur test est bien identique à lui meme");
	if(!descripteursIdentiques(Descri, Descri2){
		printf("2 fichiers différents ont bien un descripteur différent");
		printf("la valeur de ressemblance entre les 2 est de %.2f",comparerDescripteurs(Descri, Descri2));
	}
}
