#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "test_image.h"

int quantifierRGB(int composante_rouge,int composante_vert,int composante_bleue,int n){
	int dim = n*3;
	
	bits b = malloc(dim*sizeof(float));
	if(b == NULL)exit(1);

	int rouge[8] = {0},vert[8] = {0},bleue[8] = {0};
	int i=0;
	
	for(int i=0;i<8;i++){
		rouge[i] = composante_rouge%2;
		composante_rouge = composante_rouge/2;
		vert[i] = composante_vert%2;
		composante_vert = composante_vert/2;
		bleue[i] = composante_bleue%2;
		composante_bleue = composante_bleue/2;
	}
		
	if(dim == 6){
		for(i = 0;i<dim;i++){
			if(i<2)b[i] = rouge[7-i];
			else if(i<4)b[i] = vert[9-i];
			else b[i] = bleue[11-i];
		}
	}
	else if(dim == 9){
		for(i=0;i<9;i++){
			if(i<3)b[i] = rouge[7-i];
			else if(i<6)b[i] = vert[10-i];
			else b[i] = bleue[13-i];}
	}
		
	int resultat = 0,a = 0;
	for(int j=0;j<dim;j++){
		a =(int)pow(2,dim-1-j);
		resultat = resultat + (b[j]*a);
		}
	//printf("%d\n",resultat);
	free(b);
return resultat;
}

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

		puissance = (int)(pow((int)2,(int)n-1-i));
		b[i] = noire[7-i];
		resultat = resultat + (b[i]*puissance);

	}
	free(b);
	return resultat;
}

/*-------------------------------------------------------------------------------------*/

void remplirMatrice(FILE **f,int lignes,int colonnes,int M[lignes][colonnes]){

	//fonction permettant de remplir la matrice passée en paramètre

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			fscanf(*f,"%d",&M[i][j]);
		}
	}
}

/*-------------------------------------------------------------------------------------*/

void realiserHistogrammeRGB(int lignes,int colonnes,int Image[lignes][colonnes],int Rouge[lignes][colonnes],int Verte[lignes][colonnes],int Bleue[lignes][colonnes],int n,int Histogramme[],int taille_max){
	
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

void realiserHistogrammeNB(int lignes,int colonnes,int Image[lignes][colonnes],int noire[lignes][colonnes],int n,int Histogramme[],int taille_max){
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

void mise_a_jour_base(int n,int i,int taille_max,int Histogramme[],char titre_fichier[]){
	
	//int somme = 0;

		FILE *ecrire_dans_base;
		ecrire_dans_base = fopen("../data/base_descripteur_image.txt","a+");
		if(ecrire_dans_base == NULL)printf("chemin errone\n");
		fprintf(ecrire_dans_base,"[ %d#id%d ]",n,i);

		for(int j=0;j<taille_max;j++){
			fprintf(ecrire_dans_base,"%d ",Histogramme[j]);
			//somme += Histogramme[j];
			Histogramme[j] = 0;
		}
		fprintf(ecrire_dans_base,"\n");
		/*// ecriture dans le fichier base_descripteur_image*/
		fclose(ecrire_dans_base);

		FILE *images_indexees;
		images_indexees = fopen("../data/liste_base_image.txt","a+");
		fprintf(images_indexees,"%s [ %d#id%d ]\n",titre_fichier,n,i);
		fclose(images_indexees);
		
}


/*-------------------------------------------------------------------------------------*/

int base_est_vide(){

	FILE *fichier_descripteur;
	char variable_de_test;

	fichier_descripteur = fopen("../data/base_descripteur_image.txt","r");// ouverture de la base des descripteurs en mode lecture
			
	variable_de_test = fgetc(fichier_descripteur);//tester avec une variable si la base des descripteurs est vide
	
	fclose(fichier_descripteur);

	return variable_de_test == EOF;
}

/*-------------------------------------------------------------------------------------*/

void lister_fichiers(){

}

/*-------------------------------------------------------------------------------------*/

void generer_descripteur(char chemin[],int Histogramme[]){

	int nbLignes = 0,nbColonnes = 0,nbComposantes = 0;

}

/*-------------------------------------------------------------------------------------*/

int fichier_traite(char titre_fichier[]);