#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int main(void){
	FILE *lecteur_fichier;
	for(int i=0;i<5;i++){
		char titre_fichier[6],x[6];
	
	lecteur_fichier = fopen("../data/liste_des_images","r");
				fscanf(lecteur_fichier,"%s",titre_fichier);//lecture des titres des fichiers
				printf("%s\n",titre_fichier);
	}
	fclose(lecteur_fichier);
}