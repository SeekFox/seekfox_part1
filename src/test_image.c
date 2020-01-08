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

/*-------------------------------------------------------------------------------------*/

int quantifierRGB(int composante_rouge,int composante_vert,int composante_bleue,int n){ 

	// cette fonction sert à quantifier un pixel à partir de 3 composantes rouge verte est bleue cf : cahier de charges annexe page 15-16

	int dim = n*3; // la dimension du tableau de bits
	int resultat = 0;

	bits b = malloc(dim*sizeof(int)); // allocation dynamique du tableau de bits
	if(b == NULL)exit(1);

	int rouge[8];
	int vert[8];
	int bleue[8];
	// les tableau contenants les résultats des divisions successives des trois composantes -> 8 éléments puique la valeur maximale d'une composante est 255 = 2^8-1

	for(int i=0;i<8;i++){ // boucle pour la conversion des composantes en décimales en binaire

		rouge[i] = composante_rouge%2;
		composante_rouge = composante_rouge/2;

		vert[i] = composante_vert%2;
		composante_vert = composante_vert/2;

		bleue[i] = composante_bleue%2;
		composante_bleue = composante_bleue/2;
	}

	for(int i=0; i<n; i++){
		resultat+=rouge[8-i]*(int)pow((int)2,(int)(3*n-1-i));
		resultat+=vert[8-i] *(int)pow((int)2,(int)(2*n-1-i));
		resultat+=bleue[8-i]*(int)pow((int)2,(int)(1*n-1-i));
	}

return resultat;
}
/*-------------------------------------------------------------------------------------*/

int quantifierNB(int ComposanteNoire,int n){

	// la meme chose que la fonction quantifierRGB mais avec une seule composante

	int resultat = 0,noire[8] = {0},puissance=0;

	bits b = malloc(n*sizeof(int));
	if(b == NULL)exit(1);

	for(int i=0;i<8;i++){
		noire[i] = ComposanteNoire%2;
		ComposanteNoire = ComposanteNoire/2;
	}

	for(int i = 0;i<n;i++){
		puissance = (int)(pow(2,n-1-i));
		b[i] = noire[7-i];
		resultat = resultat + (b[i]*puissance);
	}
	free(b);
	return resultat;
}

/*-------------------------------------------------------------------------------------*/

int** allouerMemoire(matrice tab,int lignes,int colonnes){

	//fonction parmettant d'allouer une matrice dynamiquement

	tab = malloc(lignes*sizeof(int*));
	if(tab == NULL)exit(EXIT_FAILURE);

	for(int i=0;i<lignes;i++){

		tab[i] = malloc(colonnes*sizeof(int));

		if(tab[i] == NULL)exit(EXIT_FAILURE);
	}

	return tab;
}

/*-------------------------------------------------------------------------------------*/

void remplirMatrice(FILE **f,matrice M,int lignes,int colonnes){

	//fonction permettant de remplir la matrice passée en paramètre

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			fscanf(*f,"%d",&M[i][j]);
		}
	}
}

/*-------------------------------------------------------------------------------------*/

void realiserHistogrammeRGB(matrice Image,matrice Rouge,matrice Verte,matrice Bleue,int lignes,int colonnes,int n,int Histogramme[],int taille_max){
	
	//fonction permettant de realiser l'hitogramme d'une image à partir des trois matrices de composantes rouges vertes et blueues

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){

			Image[i][j] = quantifierRGB(Rouge[i][j],Verte[i][j],Bleue[i][j],n); // appel de la fonction quantifierRGB et remplissage de l'image
		
		}
	}

	//Mise à 0 des compososantes de l'histogramme
	for(int k=0; k<taille_max;k++){
		Histogramme[k]=0;
	}

	//remplissage de l'histogramme
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			Histogramme[Image[i][j]]++;
		}
	}
}

/*-------------------------------------------------------------------------------------*/

matrice libererMemoire(matrice m,int colonnes){

	//fonction qui sert à libérer la mémoire allouée par la fonction allouermémoire

	for(int i=0;i<colonnes;i++)free(m[i]);
	free(m);
	m = NULL;
	return m;
}
/*-------------------------------------------------------------------------------------*/

void realiserHistogrammeNB(matrice Image,matrice noire,int lignes,int colonnes,int n,int *Histogramme,int taille_max){
	// fonction permettant de realiser l'hitogramme d'une image à partir de la matrice de la composante noire

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){

			Image[i][j] = quantifierNB(noire[i][j],n);

		}
	}

	//Mise à 0 des compososantes de l'histogramme
	for(int k=0; k<taille_max;k++){
		Histogramme[k]=0;
	}

	//Remplissage de l'histogramme
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			Histogramme[Image[i][j]]++;
		}
	}
}

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

	printf("commande reussie\n");

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

/*-----------------------------choix des bits sur quoi quantifier-------------------------*/
	do
	{
		printf("choisir le nombre de bits sur quoi quantifier\n");
		scanf("%d",&n);
	} while (n != 3 && n != 2);
{/*-------------------------------------------------------------------------------------*/
			/*FILE *fichier_descripteur;
			//int variable_de_test;

			fichier_descripteur = fopen("../data/base_descripteur_image.txt","r");// ouverture de la base des descripteurs en mode lecture ecriture à la fin
			
			variable_de_test = fgetc(fichier_descripteur);//tester avec une variable si la base des descripteurs est vide
			
			if(variable_de_test != EOF){ // elle n'est pas vide 
			
			}
			else{

			}
/*-------------------------------------------------------------------------------------*/}
	
	for(int i=1;i<=nbFichiers;i++){ // boucle for qui dépend du nombre de fichiers
		char titre_fichier[6];
		fscanf(lecteur_fichier,"%s",titre_fichier);//lecture des titres des fichiers

		/*	do
			{
				fscanf(lecteur_fichier,"%s",titre_fichier);
				if(titre_fichier[5] != 't')nbFichiers--;
			} while(titre_fichier[5] != 't');*/ //verification du format du fichier .txt ou pas
		
			//printf("titre fichier lu\n");

			//printf("\n%s\n",titre_fichier);

			char CHEMIN2[100]="../data/TEST_IMAGES/"; // chemin d'ouverture des fichiers
			strcat(CHEMIN2,titre_fichier);

			/*FILE *images_indexees;
			images_indexees = fopen("../data/liste_base_image.txt","r+");
			fprintf(images_indexees,"%s [ #id%d ]\n",titre_fichier,i);*/ // ?

			

			entree = fopen(CHEMIN2,"r"); // ouverture des fichiers .txt en mode lecture
			
			fscanf(entree," %d%d%d",&nbLignes,&nbColonnes,&nbComposantes); // lecture de la première lignes dimension de l'image et les composantes
			printf("%d %d %d\n",nbLignes,nbColonnes,nbComposantes);

			int taille_max =(int)pow(2,n*nbComposantes);
			printf("%d\n",taille_max);
			
			int Histogramme[taille_max];


			/*l'histogramme a une dimention de 2^nbComposantes*nombre de bits sur quoi quantifier donc
			RBG(trois composantes) sur 2 bits Histogramme de 64 valeurs
			RGB(trois composantes) sur 3 bits Histogramme de 512 valeurs
			NB(une composante) sur 2 bits Histogramme de 4 valeurs
			NB(une composante) sur 3 bits Histogramme de 8 valeurs
			cf : cahier de charges page 17
			*/

			if(nbComposantes == 3){

				matrice Rouge = NULL,Verte = NULL,Bleue = NULL,ImageRGB = NULL;
				Rouge = allouerMemoire(Rouge,nbLignes,nbColonnes);
				Verte = allouerMemoire(Verte,nbLignes,nbColonnes);
				Bleue = allouerMemoire(Bleue,nbLignes,nbColonnes);
				ImageRGB = allouerMemoire(ImageRGB,nbLignes,nbColonnes);
				//allocation dynamique des matrices représentant les composantes de l'image

				//printf("allouer memoire reussi\n");


				remplirMatrice(&entree,Rouge,nbLignes,nbColonnes);
				remplirMatrice(&entree,Verte,nbLignes,nbColonnes);
				remplirMatrice(&entree,Bleue,nbLignes,nbColonnes);
				//lecture du contenu de l'image et remplissage des matrices

				//printf("matrices remplies reussi\n");

				realiserHistogrammeRGB(ImageRGB,Rouge,Verte,Bleue,nbLignes,nbColonnes,n,Histogramme,taille_max);
				//realisation de l'histogramme avec passage en parametre du tableau Histogramme

				//printf("histogramme reussi\n");

				Rouge = libererMemoire(Rouge,nbColonnes);
				Verte = libererMemoire(Verte,nbColonnes);
				Bleue = libererMemoire(Bleue,nbColonnes);
				ImageRGB = libererMemoire(ImageRGB,nbColonnes);
				//libération de la mémoire

			}
			else if(nbComposantes == 1){
				//printf("choix effectue\n");
				matrice Noire = NULL,ImageNB = NULL;
				//allocation dynamique de la matrice représentant la composante noire et l'image pour réaliser l'histogramme

				Noire = allouerMemoire(Noire,nbLignes,nbColonnes);
				ImageNB = allouerMemoire(ImageNB,nbLignes,nbColonnes);
				//	printf("allocation memoire reussie\n");
				//allocation dynamique de la matrice noire représentant l'image

				remplirMatrice(&entree,Noire,nbLignes,nbColonnes);
				//printf("matrices remplies reussi\n");
				//lecture du contenu de l'image et remplissage de la matrice

				realiserHistogrammeNB(ImageNB,Noire,nbLignes,nbColonnes,n,Histogramme,taille_max);
				//realisation de l'histogramme avec passage en parametre du tableau Histogramme

				Noire = libererMemoire(Noire,nbLignes);
				ImageNB = libererMemoire(ImageNB,nbLignes);
				//libération de la mémoire

			}
			else printf("Image non prise en charge \n");

		/*fprintf(fichier_descripteur,"[ #id%d ]",i);
		for(int j=0;j<taille_max;j++){
			fprintf(fichier_descripteur,"%d ",Histogramme[j]);
			Histogramme[j] = 0;
		}
		fprintf(fichier_descripteur,"\n");*/ // ecriture dans le fichier base_descripteur_image

		

		int somme = 0;

		printf("[ #id%d ]",i);

		for(int j=0;j<taille_max;j++){
			printf("%d ",Histogramme[j]);
			somme += Histogramme[j];
			Histogramme[j] = 0;
		}

		printf("\n somme : %d\n",somme);
		somme = 0;
		//affichage des descripteurs avec la somme des nombres de pixels pour vérification du résultat
	}
	
	//fclose(fichier_descripteur);
	fclose(lecteur_fichier);
	fclose(entree);

	printf("fin programme\n");
	return 0;
}