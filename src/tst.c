#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef int **matrice;
typedef int *bits;

int quantifierRGB(int composante_rouge,int composante_vert,int composante_bleue,int n){
	int dim = n*3;
	bits b = malloc(dim*sizeof(float));
	if(b == NULL)exit(1);
	int rouge[8] = {0},vert[8] = {0},bleue[8] = {0};
	int i=0;
	
	while(composante_rouge > 0 || composante_vert > 0 || composante_bleue > 0){
		rouge[i] = composante_rouge%2;
		composante_rouge = composante_rouge/2;
		vert[i] = composante_vert%2;
		composante_vert = composante_vert/2;
		bleue[i] = composante_bleue%2;
		composante_bleue = composante_bleue/2;
		i++;
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
	free(b);
return resultat;
}
int quantifierNB(int ComposanteNoire,int n){
	int resultat = 0,i=0,noire[8] = {0},a=0;

	bits b = malloc(n*sizeof(float));
	if(b == NULL)exit(1);

	while(ComposanteNoire > 0){
		noire[i] = ComposanteNoire%2;
		ComposanteNoire = ComposanteNoire/2;
		i++;
	}

	for(i = 0;i<n;i++){
		b[i] = noire[i];
		a = (int)(pow(2,n-1-i));
		resultat = resultat + (b[i]*a);
	}
	free(b);
	return resultat;
}

int** allouerMemoire(matrice tab,int lignes,int colonnes){

	tab = malloc(lignes*sizeof(int*));
	if(tab == NULL)exit(EXIT_FAILURE);

	for(int i=0;i<lignes;i++){
		tab[i] = malloc(colonnes*sizeof(int));
		if(tab[i] == NULL)exit(EXIT_FAILURE);
	}
	return tab;
}
int** libererMemoire(matrice m,int colonnes){
	for(int i=0;i<colonnes;i++)free(m[i]);
	free(m);
	m = NULL;
	return m;
}

int main(void){
	/*int *x;
	x = malloc(3*sizeof(int));
	x[0] = 1;
	x[1] = 2;

	printf("%d %d %d\n",x[0],x[1],x[2]);
	free(x);
	printf("%d %d %d\n",x[0],x[1],x[2]);*/
	matrice m = NULL;
	if(m == NULL)printf("la matrice est nulle\n");
	m = allouerMemoire(m,3,3);
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			m[i][j] = 1;
			printf("%d \n",m[i][j]);
		}
	}
	m = libererMemoire(m,3);
	if(m == NULL)printf("la matrice est nulle\n");
	else printf("la matrice n'est pas nulle\n");
	//m[1][1] = 2;
	/*for(int i=0;i<3;i++)free(m[i]);
	free(m);*/
	//if(m == NULL)printf("la matrice est nulle\n");
	//printf("%d \n",m[1][1]);
return 0;
}