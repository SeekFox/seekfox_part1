#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
/*-------------------------------------------------------------------------------------*/

typedef int *bits;
typedef int **matrice;
typedef struct Descripteur{
	char identifiant[10];
	int *Histogramme
}Descripteur;

int quantifierRGB(int composante_rouge,int composante_vert,int composante_bleue,int n);
int taille_max =(int)pow(2,n*NombreComposantes);


/*-------------------------------------------------------------------------------------*/

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
/*-------------------------------------------------------------------------------------*/

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

void realiserHistogrammeRGB(matrice Image,matrice Rouge,matrice Verte,matrice Bleue,int lignes,int colonnes,int n,int *Histogramme){

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

matrice libererMemoire(matrice m,int colonnes){
	for(int i=0;i<colonnes;i++)free(m[i]);
	free(m);
	return m;
}
/*-------------------------------------------------------------------------------------*/

void realiserHistogrammeNB(matrice Image,matrice noire,int lignes,int colonnes,int n,int *Histogramme){

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			Image[i][j] = quantifierNB(noire[i][j],n);
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
	
	int NbLignes,NbColonnes,NombreComposantes,n,element,choix,nombre_fichiers;
	char CHEMIN[100] = "../data/";
	char commande[1000];
	char titre_fichier[6];
	char CHEMIN2[100];

	strcpy(commande,"ls ");
	strcat(commande, CHEMIN);
	do{	
		printf("Choisir le type d'image \n1 - RGB \n2 - NB\n");
		scanf("%d",&choix);
		if(choix == 1)strcat(commande, "TEST_RGB > ../data/liste_des_images_RGB");
		else if(choix == 2)strcat(commande, "TEST_NB > ../data/liste_des_images_NB");
	}while(choix != 1 && choix != 2);

	printf("execution de %s\n",commande);
	system(commande);

	printf("commande reussie\n");

	FILE *entree;
	FILE *lecteur_fichier;
	FILE *compteur_fichiers;
	FILE *fichier_descripteur;

	if(choix == 1){

		lecteur_fichier = fopen("../data/liste_des_images_RGB","r");
		system("wc -l ../data/liste_des_images_RGB > ../data/nombre_fichiers_RGB");
		compteur_fichiers = fopen("../data/nombre_fichiers_RGB","r");
		fscanf(compteur_fichiers," %d",&nombre_fichiers);
		printf("choix 1 reussi\n");

	}
	else if(choix == 2){

		lecteur_fichier = fopen("../data/liste_des_images_NB","r");
		system("wc -l ../data/liste_des_images_NB > ../data/nombre_fichiers_NB");
		compteur_fichiers = fopen("../data/nombre_fichiers_NB","r");
		fscanf(compteur_fichiers," %d",&nombre_fichiers);
		printf("choix 2 reussi\n");

	}

	//printf("%d\n",nombre_fichiers);

	fclose(compteur_fichiers);

	do
	{
	printf("choisir le nombre de bits sur quoi quantifier\n");
		scanf("%d",&n);
	} while (n != 1 && n != 2);

	Descripteur D1;
	
	fichier_descripteur = fopen("../data/base_descripteur_image","wr");
	fscanf(fichier_descripteur,"%s%d",nom_descripteur,numero_descripteur);
	fscanf(fichier_descripteur,"%d",);

	for(int i=0;i<=nombre_fichiers;i++){

		if(choix ==1)strcpy(CHEMIN2,"../data/TEST_RGB/");
		else if(choix == 2)strcpy(CHEMIN2,"../data/TEST_NB/");

		do
		{
			fscanf(lecteur_fichier,"%s",titre_fichier);
			if(titre_fichier[5] != 't')nombre_fichiers--;
		} while(titre_fichier[5] != 't');
	
		//printf("titre fichier lu\n");

		//printf("\n%s\n",titre_fichier);

		strcat(CHEMIN2,titre_fichier);

		//printf("\n%s\n",CHEMIN2);

		//printf("changement de chemin reussi\n");


		entree = fopen(CHEMIN2,"r");

		fscanf(entree," %d%d%d",&NbLignes,&NbColonnes,&NombreComposantes);
		//printf("%d %d %d\n",NbLignes,NbColonnes,NombreComposantes);

		if(choix == 1){

			matrice Rouge,Verte,Bleue,ImageTransformee;
			Rouge = allouerMemoire(Rouge,NbLignes,NbColonnes);
			Verte = allouerMemoire(Verte,NbLignes,NbColonnes);
			Bleue = allouerMemoire(Bleue,NbLignes,NbColonnes);
			ImageTransformee = allouerMemoire(ImageTransformee,NbLignes,NbColonnes);

			//printf("allouer memoire reussi\n");


			remplirMatrice(&entree,Rouge,NbLignes,NbColonnes);
			remplirMatrice(&entree,Verte,NbLignes,NbColonnes);
			remplirMatrice(&entree,Bleue,NbLignes,NbColonnes);

			//printf("matrices remplies reussi\n");

			realiserHistogrammeRGB(ImageTransformee,Rouge,Verte,Bleue,NbLignes,NbColonnes,n,Histogramme);

			//printf("histogramme reussi\n");

			Rouge = libererMemoire(Rouge,NbColonnes);
			Verte = libererMemoire(Verte,NbColonnes);
			Bleue = libererMemoire(Bleue,NbColonnes);
			ImageTransformee = libererMemoire(ImageTransformee,NbColonnes);

			//printf("memoire liberee\n");
		}
		else if(choix == 2){
			//printf("choix effectue\n");
			matrice Noire,ImageNB;

			Noire = allouerMemoire(Noire,NbLignes,NbColonnes);
			ImageNB = allouerMemoire(ImageNB,NbLignes,NbColonnes);
			//	printf("allocation memoire reussie\n");

			remplirMatrice(&entree,Noire,NbLignes,NbColonnes);
			//printf("matrices remplies reussi\n");

			realiserHistogrammeNB(ImageNB,Noire,NbLignes,NbColonnes,n,Histogramme);
			/*for(int i=0;i<NbLignes;i++){
				for(int j=0;j<NbColonnes;j++){
					printf("%d ",Noire[i][j]);
				}
				printf("\n");
			}*/
			//printf("histogramme reussi\n");
			
			/*Noire = libererMemoire(Noire,NbColonnes);
			ImageNB = libererMemoire(ImageNB,NbColonnes);*/
		}

	
	printf("%d ",i);

	for(int j=0;j<64;j++){
		printf("%d ",Histogramme[j]);
		Histogramme[j] = 0;
	}
	printf("\n");
}

	fclose(lecteur_fichier);
	fclose(entree);

	return 0;
}








	
