#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
/*-------------------------------------------------------------------------------------*/

typedef int *bits;
typedef int **matrice;
/*typedef struct Descripteur{
	char identifiant[5];
	int *Histogramme
}Descripteur;*/

int quantifierRGB(int composante_rouge,int composante_vert,int composante_bleue,int n);
//int taille_max =(int)pow(2,n*NombreComposantes);


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

void realiserHistogrammeRGB(matrice Image,matrice Rouge,matrice Verte,matrice Bleue,int lignes,int colonnes,int n,int *Histogramme,int taille_max){
	

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			Image[i][j] = quantifierRGB(Rouge[i][j],Verte[i][j],Bleue[i][j],n);
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

/*-------------------------------------------------------------------------------------*/

matrice libererMemoire(matrice m,int colonnes){
	for(int i=0;i<colonnes;i++)free(m[i]);
	free(m);
	return m;
}
/*-------------------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------------------*/
int main(void){

/*----------------------------partie commande unix pour le demarrage du programme------------------------------*/

	int NbLignes,NbColonnes,NombreComposantes,n,choix,nombre_fichiers,*Histogramme;
	char CHEMIN[100] = "../data/";
	char commande[1000];
	char titre_fichier[6];

	strcpy(commande,"ls ");
	strcat(commande, CHEMIN);
	strcat(commande, "TEST_IMAGES > ../data/liste_des_images");

	/*do{	
		printf("Choisir le type d'image \n1 - RGB \n2 - NB\n");
		scanf("%d",&choix);
		if(choix == 1)strcat(commande, "TEST_RGB > ../data/liste_des_images_RGB");
		else if(choix == 2)strcat(commande, "TEST_NB > ../data/liste_des_images_NB");
	}while(choix != 1 && choix != 2);*/

	//strcpy(CHEMIN2,"../data/TEST_IMAGES/");	

	printf("execution de %s\n",commande);
	system(commande);

	printf("commande reussie\n");

	/*------------------------------ouverture des fichiers cibles--------------------------------------------------*/

	FILE *entree;
	FILE *lecteur_fichier;
	FILE *compteur_fichiers;


	lecteur_fichier = fopen("../data/liste_des_images","r");
	system("wc -l ../data/liste_des_images > ../data/nombre_fichiers");
	compteur_fichiers = fopen("../data/nombre_fichiers","r");
	fscanf(compteur_fichiers," %d",&nombre_fichiers);


	printf("%d\n",nombre_fichiers);

	fclose(compteur_fichiers);

	do
	{
		printf("choisir le nombre de bits sur quoi quantifier\n");
		scanf("%d",&n);
	} while (n != 3 && n != 2);

/*-------------------------------------------------------------------------------------*/
	FILE *fichier_descripteur;
	//Descripteur D1;
	//int variable_de_test;

	fichier_descripteur = fopen("../data/base_descripteur_image.txt","w");// ouverture de la base des descripteurs en mode lecture ecriture à la fin
	/*variable_de_test = fgetc(fichier_descripteur);//tester avec une variable si la base des descripteurs est vide
	if(variable_de_test != EOF){ // elle n'est pas vide
		fscanf(fichier_descripteur,"%s",D1.identifiant);
		fscanf(fichier_descripteur,"%d",);
	}
	else{

	}
/*-------------------------------------------------------------------------------------*/
	for(int i=0;i<=nombre_fichiers;i++){
	fscanf(lecteur_fichier,"%s",titre_fichier);
	
	/*	do
		{
			fscanf(lecteur_fichier,"%s",titre_fichier);
			if(titre_fichier[5] != 't')nombre_fichiers--;
		} while(titre_fichier[5] != 't');*/
	
		//printf("titre fichier lu\n");

		//printf("\n%s\n",titre_fichier);
		char CHEMIN2[100]="../data/TEST_IMAGES/";
		strcat(CHEMIN2,titre_fichier);

		//printf("\n%s\n",CHEMIN2);

		//printf("changement de chemin reussi\n");

		entree = fopen(CHEMIN2,"r");
		
		fscanf(entree," %d%d%d",&NbLignes,&NbColonnes,&NombreComposantes);
		//printf("%d %d %d\n",NbLignes,NbColonnes,NombreComposantes);

		int taille_max =(int)pow(2,n*NombreComposantes);

		Histogramme = malloc(taille_max*sizeof(int));
		if(Histogramme == NULL)exit (EXIT_FAILURE);

		Histogramme[taille_max] =(int){0};

		if(NombreComposantes == 3){

			matrice Rouge,Verte,Bleue,ImageRGB;
			Rouge = allouerMemoire(Rouge,NbLignes,NbColonnes);
			Verte = allouerMemoire(Verte,NbLignes,NbColonnes);
			Bleue = allouerMemoire(Bleue,NbLignes,NbColonnes);
			ImageRGB = allouerMemoire(ImageRGB,NbLignes,NbColonnes);

			//printf("allouer memoire reussi\n");


			remplirMatrice(&entree,Rouge,NbLignes,NbColonnes);
			remplirMatrice(&entree,Verte,NbLignes,NbColonnes);
			remplirMatrice(&entree,Bleue,NbLignes,NbColonnes);

			//printf("matrices remplies reussi\n");

			realiserHistogrammeRGB(ImageRGB,Rouge,Verte,Bleue,NbLignes,NbColonnes,n,Histogramme,taille_max);

			//printf("histogramme reussi\n");

			Rouge = libererMemoire(Rouge,NbColonnes);
			Verte = libererMemoire(Verte,NbColonnes);
			Bleue = libererMemoire(Bleue,NbColonnes);
			ImageRGB = libererMemoire(ImageRGB,NbColonnes);

			printf("memoire liberee\n");
		}
		else if(NombreComposantes == 1){
			//printf("choix effectue\n");
			matrice Noire,ImageNB;

			Noire = allouerMemoire(Noire,NbLignes,NbColonnes);
			ImageNB = allouerMemoire(ImageNB,NbLignes,NbColonnes);
			//	printf("allocation memoire reussie\n");

			remplirMatrice(&entree,Noire,NbLignes,NbColonnes);
			//printf("matrices remplies reussi\n");

			realiserHistogrammeNB(ImageNB,Noire,NbLignes,NbColonnes,n,Histogramme,taille_max);

			Noire = libererMemoire(Noire,NbColonnes);
			ImageNB = libererMemoire(ImageNB,NbColonnes);
		}
		else printf("Image non prise en charge \n");

	/*fprintf(fichier_descripteur,"[ #id%d ]",i);

	for(int j=0;j<taille_max;j++){
		fprintf(fichier_descripteur,"%d ",Histogramme[j]);
		Histogramme[j] = (int)0;
	}
	fprintf(fichier_descripteur,"\n");*/

	int somme = 0;
	printf("[ #id%d ]",i);
	for(int j=0;j<taille_max;j++){
		printf("%d ",Histogramme[j]);
		somme = somme + Histogramme[j];
		//Histogramme[j] =(int)0;
	}
	printf("\n somme : %d\n",somme);
	somme = 0;
	free(Histogramme);
}
	
	fclose(fichier_descripteur);
	fclose(lecteur_fichier);
	fclose(entree);

	printf("fin programme\n");
	return 0;
}








	
