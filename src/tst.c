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
	printf("%d\n",resultat);
	free(b);
return resultat;
}

int quantifierNB(int ComposanteNoire,int n){
	int resultat = 0,noire[8] = {0},a = 0;

	bits b = malloc(n*sizeof(int));
	if(b == NULL)exit(EXIT_FAILURE);
	
	for(int i=0;i<8;i++){
		noire[i] = ComposanteNoire % 2;
		ComposanteNoire = ComposanteNoire/2;
		//printf("%d  ",noire[i]);
	}
	printf("\n");
	for(int i = 0;i<n;i++){
		b[i] = noire[7-i];
		//printf("%d  ",b[i]);
		a = (int)(pow(2,n-1-i));
		resultat = resultat + (b[i]*a);
	}
	//printf("\n%d \n",resultat);
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

void remplirMatrice(FILE **f,matrice M,int lignes,int colonnes){

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			fscanf(*f,"%d",&M[i][j]); 		
		}
	}
}
void realiserHistogrammeNB(matrice Image,matrice noire,int lignes,int colonnes,int n,int *Histogramme, int taille_max){

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			Image[i][j] = quantifierNB(noire[i][j],n);
		}
	}
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			for(int k=0;k<taille_max;k++){
				if(Image[i][j] == k)Histogramme[k]++;
			}
		}
	}
}

int main(void){
	printf("debut programme\n");
	int NbLignes,NbColonnes,NombreComposantes,n=3;
	FILE *f;
	f = fopen("../data/TEST_IMAGES/53.txt","r");
	fscanf(f," %d%d%d",&NbLignes,&NbColonnes,&NombreComposantes);
	
	int taille_max =(int)pow(2,n*NombreComposantes);
		
		int *Histogramme = NULL;
		Histogramme = malloc(taille_max*sizeof(int));
		if(Histogramme == NULL)exit (EXIT_FAILURE);

		Histogramme[taille_max] =(int){0};
printf("ici \n");
	matrice Noire = NULL,ImageNB = NULL;

			Noire = allouerMemoire(Noire,NbLignes,NbColonnes);
			ImageNB = allouerMemoire(ImageNB,NbLignes,NbColonnes);
			//	printf("allocation memoire reussie\n");

			remplirMatrice(&f,Noire,NbLignes,NbColonnes);
			//printf("matrices remplies reussi\n");

			realiserHistogrammeNB(ImageNB,Noire,NbLignes,NbColonnes,n,Histogramme,taille_max);

			
			Noire = libererMemoire(Noire,NbLignes);
			ImageNB = libererMemoire(ImageNB,NbLignes);

	int somme = 0;
	for(int j=0;j<taille_max;j++){
		printf("%d ",Histogramme[j]);
		somme = somme + Histogramme[j];
		Histogramme[j] = 0;
	}
	printf("\n somme : %d\n",somme);
	free(Histogramme);
	fclose(f);
return 0;
}