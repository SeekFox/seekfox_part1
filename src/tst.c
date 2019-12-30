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

int main(void){
	int rgb2bits = quantifierRGB(255,255,255,2);
	int rgb3bits = quantifierRGB(128,64,255,3);
	int nb2bits = quantifierNB(255,2);
	int nb3bits = quantifierNB(255,3);
	printf("%d	%d	%d	%d\n",rgb2bits ,rgb3bits,nb2bits,nb3bits);
return 0;
}