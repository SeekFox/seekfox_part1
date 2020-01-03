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

	// cette fonction sert à quantifier un pixel à partir de 3 composantes rouge verte est bleue cf : cahier de charges annexe page 15-16

	int dim = n*3; // la dimension du tableau de bits

	bits b = malloc(dim*sizeof(int)); // allocation dynamique du tableau de bits
	if(b == NULL)exit(1);

	int rouge[8] = {0},vert[8] = {0},bleue[8] = {0}; 
	// les tableau cotenants les résultats des divisions successives des trois composantes -> 8 éléments puique la valeur maximale d'une composante est 255 = 2^8-1
	
	for(int i=0;i<8;i++){ // boucle pour la conversion des composantes en décimales en binaire

		rouge[i] = composante_rouge%2;
		composante_rouge = composante_rouge/2;

		vert[i] = composante_vert%2;
		composante_vert = composante_vert/2;

		bleue[i] = composante_bleue%2;
		composante_bleue = composante_bleue/2;

	}
		
	if(dim == 6){	// cas de la quantification sur 2 bits -> tableau de 6 bits
		for(int i = 0;i<dim;i++){

			if(i<2)b[i] = rouge[7-i];

			else if(i<4)b[i] = vert[9-i];

			else b[i] = bleue[11-i];
		}
	}
	else if(dim == 9){ // cas de la quantification sur 3 bits -> tableau de 3 bits
		for(int i=0;i<9;i++){

			if(i<3)b[i] = rouge[7-i];

			else if(i<6)b[i] = vert[10-i];

			else b[i] = bleue[13-i];}
	}
		
	int resultat = 0,a = 0;
	for(int j=0;j<dim;j++){// boucle pour le conversion binaire au décimal et récupération du résultat 

		a =(int)pow(2,dim-1-j);

		resultat = resultat + (b[j]*a);

		}

	free(b);

return resultat;
}
/*-------------------------------------------------------------------------------------*/

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
		puissance = (int)(pow(2,n-1-i));
		b[i] = noire[7-i];
		resultat = resultat + (b[i]*puissance);
	}
	free(b);
	return resultat;
}

/*-------------------------------------------------------------------------------------*/

int** allouerMemoire(matrice tab,int lignes,int colonnes){

	//fonction parmettant d'allouer une matrice dynamiquement

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

	//fonction permettant de remplir la matrice passée en paramètre

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			fscanf(*f,"%d",&M[i][j]); 		
		}
	}
}

/*-------------------------------------------------------------------------------------*/

void realiserHistogrammeRGB(matrice Image,matrice Rouge,matrice Verte,matrice Bleue,int lignes,int colonnes,int n,int *Histogramme,int taille_max){
	
	//fonction permettant de realiser l'hitogramme d'une image à partir des trois matrices de composantes rouges vertes et blueues

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){

			Image[i][j] = quantifierRGB(Rouge[i][j],Verte[i][j],Bleue[i][j],n); // appel de la fonction quantifierRGB et remplissage de l'image
		
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

	//fonction qui sert à libérer la mémoire allouée par la fonction allouermémoire

	for(int i=0;i<colonnes;i++)free(m[i]);
	free(m);
	m = NULL;
	return m;
}
/*-------------------------------------------------------------------------------------*/

void realiserHistogrammeNB(matrice Image,matrice noire,int lignes,int colonnes,int n,int *Histogramme,int taille_max){
	// fonction permettant de realiser l'hitogramme d'une image à partir de la matrice de la composante noire

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

/*----------------------------partie commande unix pour lister les noms des fichiers------------------------------*/

	int NbLignes = 0,NbColonnes = 0,NombreComposantes = 0,n = 0,nombre_fichiers = 0;
	char CHEMIN[100] = "../data/";
	char commande[1000];
	

	strcpy(commande,"ls ");
	strcat(commande, CHEMIN);
	strcat(commande, "TEST_IMAGES > ../data/liste_des_images");

	printf("execution de %s\n",commande);
	system(commande); // commande qui sert à mettre la liste des noms des fichiers(images) .txt à indexer

	// la commande est ls ../data/TEST_IMAGES > ../data/liste_des_images

	printf("commande reussie\n");

	/*------------------------------ouverture des fichiers à indexer--------------------------------------------------*/

	FILE *entree;
	FILE *lecteur_fichier;
	FILE *compteur_fichiers;


	lecteur_fichier = fopen("../data/liste_des_images","r");
	//ouverture du fichier contenant la liste des images.txt

	system("wc -l ../data/liste_des_images > ../data/nombre_fichiers");
	//commande unix wc -l pour compter le nombre de lignes dans la liste des images 

	compteur_fichiers = fopen("../data/nombre_fichiers","r");
	fscanf(compteur_fichiers," %d",&nombre_fichiers);
	//lecture du nombre de fichiers

	//printf("%d\n",nombre_fichiers); // affichage du nombre de fichiers

	fclose(compteur_fichiers);

/*-----------------------------choix des bits sur quoi quantifier-------------------------*/
	do
	{
		printf("choisir le nombre de bits sur quoi quantifier\n");
		scanf("%d",&n);
	} while (n != 3 && n != 2);

{/*-------------------------------------------------------------------------------------*/
	FILE *fichier_descripteur;
	//int variable_de_test;

	fichier_descripteur = fopen("../data/base_descripteur_image.txt","w");// ouverture de la base des descripteurs en mode lecture ecriture à la fin
	/*variable_de_test = fgetc(fichier_descripteur);//tester avec une variable si la base des descripteurs est vide
	if(variable_de_test != EOF){ // elle n'est pas vide 
		fscanf(fichier_descripteur,"%s",); //alors on vérifie les descripteurs existants suivant leurs identifiants puis on procède à autre chose
		fscanf(fichier_descripteur,"%d",); 
	}
	else{ //sinon on commence l'indexation

	}
/*-------------------------------------------------------------------------------------*/}
	
	for(int i=1;i<=nombre_fichiers;i++){ // boucle for qui dépend du nombre de fichiers
	char titre_fichier[6];
	fscanf(lecteur_fichier,"%s",titre_fichier);//lecture des titres des fichiers

	/*	do
		{
			fscanf(lecteur_fichier,"%s",titre_fichier);
			if(titre_fichier[5] != 't')nombre_fichiers--;
		} while(titre_fichier[5] != 't');*/ //verification du format du fichier .txt ou pas
	
		//printf("titre fichier lu\n");

		//printf("\n%s\n",titre_fichier);

		char CHEMIN2[100]="../data/TEST_IMAGES/"; // chemin d'ouverture des fichiers
		strcat(CHEMIN2,titre_fichier);

		printf("\n%s\n",CHEMIN2);


		entree = fopen(CHEMIN2,"r"); // ouverture des fichiers .txt en mode lecture
		
		fscanf(entree," %d%d%d",&NbLignes,&NbColonnes,&NombreComposantes); // lecture de la première lignes dimension de l'image et les composantes
		//printf("%d %d %d\n",NbLignes,NbColonnes,NombreComposantes);

		int taille_max =(int)pow(2,n*NombreComposantes);
		
		int *Histogramme = NULL;
		Histogramme = malloc(taille_max*sizeof(int));
		if(Histogramme == NULL)exit (EXIT_FAILURE);

		Histogramme[taille_max] =(int){0};
		// allocation dynamique et initialisation de l'histogramme


		if(NombreComposantes == 3){

			matrice Rouge = NULL,Verte = NULL,Bleue = NULL,ImageRGB = NULL;
			Rouge = allouerMemoire(Rouge,NbLignes,NbColonnes);
			Verte = allouerMemoire(Verte,NbLignes,NbColonnes);
			Bleue = allouerMemoire(Bleue,NbLignes,NbColonnes);
			ImageRGB = allouerMemoire(ImageRGB,NbLignes,NbColonnes);
			//allocation dynamique des matrices représentant les composantes de l'image

			//printf("allouer memoire reussi\n");


			remplirMatrice(&entree,Rouge,NbLignes,NbColonnes);
			remplirMatrice(&entree,Verte,NbLignes,NbColonnes);
			remplirMatrice(&entree,Bleue,NbLignes,NbColonnes);
			//lecture du contenu de l'image et remplissage des matrices

			//printf("matrices remplies reussi\n");

			realiserHistogrammeRGB(ImageRGB,Rouge,Verte,Bleue,NbLignes,NbColonnes,n,Histogramme,taille_max);
			//realisation de l'histogramme avec passage en parametre du tableau Histogramme

			//printf("histogramme reussi\n");

			Rouge = libererMemoire(Rouge,NbColonnes);
			Verte = libererMemoire(Verte,NbColonnes);
			Bleue = libererMemoire(Bleue,NbColonnes);
			ImageRGB = libererMemoire(ImageRGB,NbColonnes);
			//libération de la mémoire

		}
		else if(NombreComposantes == 1){
			//printf("choix effectue\n");
			matrice Noire = NULL,ImageNB = NULL;
			//allocation dynamique de la matrice représentant la composante noire et l'image pour réaliser l'histogramme

			Noire = allouerMemoire(Noire,NbLignes,NbColonnes);
			ImageNB = allouerMemoire(ImageNB,NbLignes,NbColonnes);
			//	printf("allocation memoire reussie\n");
			//allocation dynamique de la matrice noire représentant l'image

			remplirMatrice(&entree,Noire,NbLignes,NbColonnes);
			//printf("matrices remplies reussi\n");
			//lecture du contenu de l'image et remplissage de la matrice

			realiserHistogrammeNB(ImageNB,Noire,NbLignes,NbColonnes,n,Histogramme,taille_max);
			//realisation de l'histogramme avec passage en parametre du tableau Histogramme

			Noire = libererMemoire(Noire,NbLignes);
			ImageNB = libererMemoire(ImageNB,NbLignes);
			//libération de la mémoire

		}
		else printf("Image non prise en charge \n");

	/*fprintf(fichier_descripteur,"[ #id%d ]",i);

	for(int j=0;j<taille_max;j++){
		fprintf(fichier_descripteur,"%d ",Histogramme[j]);
		Histogramme[j] = (int)0;
	}
	fprintf(fichier_descripteur,"\n");*/ // ecriture dans le fichier base_descripteur_image

	int somme = 0;

	printf("[ #id%d ]",i);

	for(int j=0;j<taille_max;j++){
		printf("%d ",Histogramme[j]);
		somme = somme + Histogramme[j];
		Histogramme[j] = 0;
	}

	printf("\n somme : %d\n",somme);
	somme = 0;
	//affichage des descripteurs avec la somme des nombres de pixels pour vérification du résultat

	free(Histogramme);
}
	
	//fclose(fichier_descripteur);
	fclose(lecteur_fichier);
	fclose(entree);

	printf("fin programme\n");
	return 0;
}








	
