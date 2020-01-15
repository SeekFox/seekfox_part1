/*
C'est corrigé normalement !
J'ai fais 2/3 petites modifications qui permettent au programme d'être un poil plus compact lisible mais rien de bien méchants.
Le nombre de bit à quantifier sera disponible dans le fichier config, t'aura pas à le demander à l'utilisateur dans la version finale
Tu as plus qu'à faire la fonction de création d'un descripteur (à partir d'un fichier)
	Transformation de ce descripteur en string (et l'inverse)
	Et comparaison
	Il faudrait aussi que tu crée un fichier image.h avec les prototypes de tes fonctions :)
Mais globalement, tu as fais le plus compliqué.
Si tu as un probleme, n'hesite pas ^^
Bonne chance !
Clément :)
*/

/*	
Le probleme est que mes descripteurs affichent d'importe quoi après la première image
dans le cas des images RGB en quatification sur 3 bits.
et la meme chose pour les images NB en quatification sur 2 bits.
on peut le voir si on compile le programme avec la commande
	gcc -o test_image.out test_image.c -lm
et l'exécution du programme 
	./test_image.out
Le programme est assez commenté(enfin je pense)
s'il y a des parties incompréhensibles envoyez moi un message
Merci ^_^
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "test_image.h"
#include "fcts_test_image.c"

int equals(char string1[],char string2[],int taille){
	int isok=0;
	for(int i=0;i<taille;i++){
		if(string1[i] == string2[i])isok++;
	}
	return isok == taille;
}

int fichier_deja_indexe(char titre_fichier[]){
	char titre_aux[6];

	FILE *f_indexe;
	f_indexe = fopen("../data/liste_base_image","r");

	do{
		fscanf(f_indexe,"%s",titre_aux);//lecture des titres des fichiers

		if(equals(titre_fichier,titre_aux,6)){
			printf("le fichier : %s est deja indexe\n",titre_fichier);
			fclose(f_indexe);
			return 1;
		}
		
	}while(!feof(f_indexe));

	fclose(f_indexe);
	return 0;
}

void lancer_indexation(){
	
/*----------------------------partie commande unix pour lister les noms des fichiers------------------------------*/
	char path[16] = "../data/";
	char commande[100] = "";
	
	sprintf(commande,"%s %s%s","ls",path,"TEST_IMAGES > ../data/liste_des_images");

	printf("execution de %s\n",commande);
	system(commande); // commande qui sert à mettre la liste des noms des fichiers(images) .txt à indexer

	// la commande est ls ../data/TEST_IMAGES > ../data/liste_des_images

	printf("commande reussie\n");

/*------------------------------ouverture des fichiers à indexer--------------------------------------------------*/
	int n = 0,nbFichiers = 0;
	
	FILE * compteur_fichiers;

	//ouverture du fichier contenant la liste des images.txt

	system("wc -l ../data/liste_des_images > ../data/nbFichiers");
	//commande unix wc -l pour compter le nombre de lignes dans la liste des images 

	compteur_fichiers = fopen("../data/nbFichiers","r");
	fscanf(compteur_fichiers," %d",&nbFichiers);
	//lecture du nombre de fichiers

	//printf("%d\n",nbFichiers); // affichage du nombre de fichiers

	fclose(compteur_fichiers);
/*---------------------------------------------------------------------------------------------------------------*/

	FILE * lecteur_fichier;
	lecteur_fichier = fopen("../data/liste_des_images","r");
	FILE * lecteur_image;

	int nbLignes = 0,nbColonnes = 0,nbComposantes = 0;

		for(int n=2;n<4;n++){
			
			for(int i=1;i<=nbFichiers;i++){ // boucle for qui dépend du nombre de fichiers

				char titre_fichier[6];

				do{
					fscanf(lecteur_fichier,"%s",titre_fichier);//lecture des titres des fichiers
					if(feof(lecteur_fichier)){
						printf("tous les fichiers sont indexes\n");
						break;
					}
				}while(fichier_deja_indexe(titre_fichier));

				
				if(feof(lecteur_fichier))break;
				

				char CHEMIN2[100]="../data/TEST_IMAGES/"; // chemin d'ouverture des fichiers
				strcat(CHEMIN2,titre_fichier);


				lecteur_image = fopen(CHEMIN2,"r"); // ouverture des fichiers .txt en mode lecture
				
				fscanf(lecteur_image," %d%d%d",&nbLignes,&nbColonnes,&nbComposantes); // lecture de la première lignes dimension de l'image et les composantes
				int taille_max =(int)pow(2,n*nbComposantes);
				int Histogramme[taille_max];


				if(nbComposantes == 3){	
				
					int Rouge[nbLignes][nbColonnes],Verte[nbLignes][nbColonnes],Bleue[nbLignes][nbColonnes],ImageRGB[nbLignes][nbColonnes];

					//allocation dynamique des matrices représentant les composantes de l'image

					//printf("allouer memoire reussi\n");


					remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Rouge);
					remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Verte);
					remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Bleue);
					//lecture du contenu de l'image et remplissage des matrices

					//printf("matrices remplies reussi\n");

					realiserHistogrammeRGB(nbLignes,nbColonnes,ImageRGB,Rouge,Verte,Bleue,n,Histogramme,taille_max);
					//realisation de l'histogramme avec passage en parametre du tableau Histogramme

					//printf("histogramme reussi\n");

				}
				else if(nbComposantes == 1){
					//printf("choix effectue\n");
					int Noire[nbLignes][nbColonnes],ImageNB[nbLignes][nbColonnes];
					//delcaration de la matrice représentant la composante noire et l'image pour réaliser l'histogramme


					remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Noire);
					//printf("matrices remplies reussi\n");
					//lecture du contenu de l'image et remplissage de la matrice

					realiserHistogrammeNB(nbLignes,nbColonnes,ImageNB,Noire,n,Histogramme,taille_max);
					//realisation de l'histogramme avec passage en parametre du tableau Histogramme

				}

				mise_a_jour_base(n,i,taille_max,Histogramme,titre_fichier);

			}
		if(feof(lecteur_fichier))break;
		rewind(lecteur_fichier);
		}
	
	fclose(lecteur_fichier);
	fclose(lecteur_image);

}

/*-------------------------------------------------------------------------------------*/
int main(void){
	char chemin[100];
	printf("debut programme\n");
	lancer_indexation();
	printf("saisir chemin\n");
	scanf("%s",chemin);
	comparer_image();
	printf("fin programme\n");
	return 0;
}