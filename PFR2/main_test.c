#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descripteur_txt.h"
#include "FIFO.h"

void main(void){
	FILE* fichier = NULL;
	FILE* fichier2 = NULL;
	FIFO file;
	int nb_mot,nb_lettres;
	DESCTXT Descri,Descri2;

	printf("TEST DESCRIPTEUR\n");
	fichier = fopen("test_txt.txt", "r");
	if (fichier == NULL)
		printf("impossible de localiser le fichier \n");
	else 
		Descri = creerDescripteur_txt(fichier);		
	fclose(fichier);
	printf("%d>>\n", Descri.nb_lettres);
	printf("TEST toString \n");
	char* test="";
	test = descToString(Descri);

	strcpy(test, descToString(Descri));
	printf("%s",test);
	/*printf("TEST COMPARAISON \n");
	if(descripteursIdentiques(Descri, Descri))
		printf("le descripteur test est bien identique à lui meme");
	fichier2 = fopen("test2.txt", "r");
	if (fichier2 == NULL)
		printf("impossible de localiser le fichier \n");
	else
		Descri = creerDescripteur_txt(fichier2);
	fclose(fichier2);
	if(!descripteursIdentiques(Descri, Descri2)){
		printf("2 fichiers différents ont bien un descripteur différent");
		printf("la valeur de ressemblance entre les 2 est de %.2f",comparerDescripteurs(Descri, Descri2));
	}*/
}
