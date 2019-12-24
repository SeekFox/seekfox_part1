#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
/*-------------------------------------------------------------------------------------*/

typedef int *bits;
typedef int **matrice;

int quantifierRGB(int composante_rouge,int composante_vert,int composante_bleue,int n);


/*-------------------------------------------------------------------------------------*/

int quantifierRGB(int composante_rouge,int composante_vert,int composante_bleue,int n){
	int dim = n*3;
	bits b = malloc(dim*sizeof(float));
	if(b == NULL)exit(1);
	int rouge[8],vert[8],bleue[8];
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
/*-------------------------------------------------------------------------------------*/

int quantifierNB(int ComposanteNoire,int n){
	int resultat,i=0,noire[8],a=0;

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

/*-------------------------------------------------------------------------------------*/

int** allouerMemoire(matrice tab,int lignes,int colonnes){

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

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			fscanf(*f,"%d",&M[i][j]); 		
		}
	}
}

/*-------------------------------------------------------------------------------------*/

void realiserHistogramme(matrice Image,matrice Rouge,matrice Verte,matrice Bleue,int lignes,int colonnes,int n,int *Histogramme){

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			Image[i][j] = quantifierRGB(Rouge[i][j],Verte[i][j],Bleue[i][j],n);
		}
	}

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			for(int k=0;k<64;k++){
				if(Image[i][j] == k)Histogramme[k]++;
			}
		}
	}
}

/*-------------------------------------------------------------------------------------*/

void libererMemoire(matrice m,int colonnes){
	for(int i=0;i<colonnes;i++)free(m[i]);
	free(m);
}

/*-------------------------------------------------------------------------------------*/
int main(void){
	
	int NbLignes,NbColonnes,NombreComposantes,Histogramme[64]={0},n=2,element,choix;
	char CHEMIN[100] = "../data/";
	char commande[1000];

	strcpy(commande,"ls ");
	strcat(commande, CHEMIN);
	do{	
		printf("Choisir le type d'image \n1 - RGB \n2 - NB\n");
		scanf("%d",&choix);
		if(choix == 1)strcat(commande, "TEST_RGB > ../data/liste_des_images_RGB");
		else if(choix == 2)strcat(commande, "TEST_NB > ../data/liste_des_images_NB");
	}while(choix != 1 && choix != 2);

	printf("execution de %s\n",commande);
	fflush(stdout);
	system(commande);

/*	printf("saisir le nombre de bits sur quoi quantifier\n");
	scanf("%d",&n);*/

	FILE *entree;
	entree = fopen("../data/TEST_RGB/01.txt","r");	

	fscanf(entree,"%d%d%d",&NbLignes,&NbColonnes,&NombreComposantes);
	printf("%d %d %d\n",NbLignes,NbColonnes,NombreComposantes);

	matrice Rouge,Verte,Bleue,ImageTransformee;
	Rouge = allouerMemoire(Rouge,NbLignes,NbColonnes);
	Verte = allouerMemoire(Verte,NbLignes,NbColonnes);
	Bleue = allouerMemoire(Bleue,NbLignes,NbColonnes);
	ImageTransformee = allouerMemoire(ImageTransformee,NbLignes,NbColonnes);


	remplirMatrice(&entree,Rouge,NbLignes,NbColonnes);
	remplirMatrice(&entree,Verte,NbLignes,NbColonnes);
	remplirMatrice(&entree,Bleue,NbLignes,NbColonnes);

	printf("\n remplissage réussi\n");

	fclose(entree);

	realiserHistogramme(ImageTransformee,Rouge,Verte,Bleue,NbLignes,NbColonnes,n,Histogramme);

	printf("\n histogramme reussi \n");

	int somme = 0;
	for(int i=0;i<64;i++){
		printf("il y a %d de %d\n",Histogramme[i],i);
		somme = somme + Histogramme[i];
	}
	printf("%d\n",somme);
	printf("%d %d %d\n",NbLignes,NbColonnes,NombreComposantes);

	libererMemoire(Rouge,NbColonnes);
	libererMemoire(Verte,NbColonnes);
	libererMemoire(Bleue,NbColonnes);
	libererMemoire(ImageTransformee,NbColonnes);

	return 0;
}








	
