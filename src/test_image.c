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

/*-------------------------------------------------------------------------------------*/
int main(void){

/*----------------------------partie commande unix pour lister les noms des fichiers------------------------------*/

	int nbLignes = 0,nbColonnes = 0,nbComposantes = 0,n = 0,nbFichiers = 0;
	char path[16] = "../data/";
	char commande[64] = "";
	
	sprintf(commande,"%s %s%s","ls",path,"TEST_IMAGES > ../data/liste_des_images");

	printf("execution de %s\n",commande);
	system(commande); // commande qui sert à mettre la liste des noms des fichiers(images) .txt à indexer

	// la commande est ls ../data/TEST_IMAGES > ../data/liste_des_images

	//printf("commande reussie\n");

	/*------------------------------ouverture des fichiers à indexer--------------------------------------------------*/

	FILE * entree;
	FILE * lecteur_fichier;
	FILE * compteur_fichiers;


	lecteur_fichier = fopen("../data/liste_des_images","r");
	//ouverture du fichier contenant la liste des images.txt

	system("wc -l ../data/liste_des_images > ../data/nbFichiers");
	//commande unix wc -l pour compter le nombre de lignes dans la liste des images 

	compteur_fichiers = fopen("../data/nbFichiers","r");
	fscanf(compteur_fichiers," %d",&nbFichiers);
	//lecture du nombre de fichiers

	//printf("%d\n",nbFichiers); // affichage du nombre de fichiers

	fclose(compteur_fichiers);
	FILE *fichier_descripteur;
	int variable_de_test;

	fichier_descripteur = fopen("../data/base_descripteur_image.txt","r");// ouverture de la base des descripteurs en mode lecture
			
	variable_de_test = fgetc(fichier_descripteur);//tester avec une variable si la base des descripteurs est vide
			
	if(variable_de_test == EOF){

		for(int n=2;n<4;n++){
	
			for(int i=1;i<=nbFichiers;i++){ // boucle for qui dépend du nombre de fichiers

				char titre_fichier[6];
				fscanf(lecteur_fichier,"%s",titre_fichier);//lecture des titres des fichiers

				char CHEMIN2[100]="../data/TEST_IMAGES/"; // chemin d'ouverture des fichiers
				strcat(CHEMIN2,titre_fichier);


				entree = fopen(CHEMIN2,"r"); // ouverture des fichiers .txt en mode lecture
			
				fscanf(entree," %d%d%d",&nbLignes,&nbColonnes,&nbComposantes); // lecture de la première lignes dimension de l'image et les composantes

				int taille_max =(int)pow(2,n*nbComposantes);
			
				int Histogramme[taille_max];


				if(nbComposantes == 3){	
				
					int Rouge[nbLignes][nbColonnes],Verte[nbLignes][nbColonnes],Bleue[nbLignes][nbColonnes],ImageRGB[nbLignes][nbColonnes];

					//allocation dynamique des matrices représentant les composantes de l'image

					//printf("allouer memoire reussi\n");


					remplirMatrice(&entree,nbLignes,nbColonnes,Rouge);
					remplirMatrice(&entree,nbLignes,nbColonnes,Verte);
					remplirMatrice(&entree,nbLignes,nbColonnes,Bleue);
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


					remplirMatrice(&entree,nbLignes,nbColonnes,Noire);
					//printf("matrices remplies reussi\n");
					//lecture du contenu de l'image et remplissage de la matrice

					realiserHistogrammeNB(nbLignes,nbColonnes,ImageNB,Noire,n,Histogramme,taille_max);
					//realisation de l'histogramme avec passage en parametre du tableau Histogramme

				}

			mise_a_jour_base(n,i,taille_max,Histogramme,titre_fichier);

			}
			rewind(lecteur_fichier);
		}
	}
	
	fclose(fichier_descripteur);
	fclose(lecteur_fichier);
	fclose(entree);

	printf("fin programme\n");
	return 0;
}