#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef int **matrice;
typedef int *bits;

int quantifierNB(int ComposanteNoire,int n){
	int resultat,i=0,noire[8],a;

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
	int x;
	x = quantifierNB(255,2);
	printf("%d\n",x);
return 0;
}