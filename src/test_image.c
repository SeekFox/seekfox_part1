#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*-------------------------------------------------------------------------------------*/

typedef int *bits;
typedef int **matrice;

int quantifier(int composante_rouge,int composante_vert,int composante_bleue,int n);


/*-------------------------------------------------------------------------------------*/

int quantifier(int composante_rouge,int composante_vert,int composante_bleue,int n){
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
	
return resultat;
}

/*-------------------------------------------------------------------------------------*/

int** allouerMemoire(int **tab,int lignes,int colonnes){

	tab = malloc(lignes*sizeof(int));
	if(tab == NULL)exit(EXIT_FAILURE);

	for(int i=0;i<lignes;i++){
		tab[i] = malloc(colonnes*sizeof(int));
		if(tab[i] == NULL)exit(EXIT_FAILURE);
	}

	return tab;
}

/*-------------------------------------------------------------------------------------*/

/*void remplirMatrice(FILE **f,matrice *M,int lignes,int colonnes){
	printf("\n debug ici \n");
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			fscanf(*f,"%d",M[i][j]); 		
		}
	}
}

/*-------------------------------------------------------------------------------------*/

void realiserHistogramme(matrice Image,matrice Rouge,matrice Verte,matrice Bleue,int lignes,int colonnes,int n,int *Histogramme){

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			Image[i][j] = quantifier(Rouge[i][j],Verte[i][j],Bleue[i][j],n);
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
int main(void){
	
	int NbLignes,NbColonnes,NombreComposantes,Histogramme[64]={0},n=2;
	//char nomfichier[50];
	
/*	printf("saisir le nom du fichier\n");
	scanf("%10s",nomfichier);*/
	
	/*printf("saisir le nombre de bits sur quoi quantifier\n");
	scanf("%d",&n);*/

	FILE *entree;
	entree = fopen("01.txt","r");	

	fscanf(entree,"%d%d%d",&NbLignes,&NbColonnes,&NombreComposantes);
	

	matrice Rouge,Verte,Bleue,ImageTransformee;
	Rouge = allouerMemoire(Rouge,NbLignes,NbColonnes);
	Verte = allouerMemoire(Verte,NbLignes,NbColonnes);
	Bleue = allouerMemoire(Bleue,NbLignes,NbColonnes);
	ImageTransformee = allouerMemoire(ImageTransformee,NbLignes,NbColonnes);

for(int i=0;i<NbLignes;i++){
		for(int j=0;j<NbColonnes;j++){
			fscanf(entree,"%d",&Rouge[i][j]); 		
		}
	}

	/*remplirMatrice(&entree,&Rouge,NbLignes,NbColonnes);
	remplirMatrice(&entree,&Verte,NbLignes,NbColonnes);
	remplirMatrice(&entree,&Bleue,NbLignes,NbColonnes);*/

	printf("\n debug ici2 \n");
	fclose(entree);

	realiserHistogramme(ImageTransformee,Rouge,Verte,Bleue,NbLignes,NbColonnes,n,Histogramme);

	printf("%d %d %d\n",NbLignes,NbColonnes,NombreComposantes);
	
	return 0;
}








	
