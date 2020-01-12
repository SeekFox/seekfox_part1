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