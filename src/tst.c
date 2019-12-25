#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef int **matrice;
typedef int *bits;

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
	int resultat = quantifierNB(0,2);
	printf("%d\n",resultat);
return 0;
}