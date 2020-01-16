#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef int * bits;
typedef struct descripteur
{
	char identifiant[10];
	int* Histogramme;
}descripteur;

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
	//printf("%d\n",resultat);
	free(b);
return resultat;
}

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

		puissance = (int)(pow((int)2,(int)n-1-i));
		b[i] = noire[7-i];
		resultat = resultat + (b[i]*puissance);

	}
	free(b);
	return resultat;
}

/*-------------------------------------------------------------------------------------*/

void remplirMatrice(FILE **f,int lignes,int colonnes,int M[lignes][colonnes]){

	//fonction permettant de remplir la matrice passée en paramètre

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			fscanf(*f,"%d",&M[i][j]);
		}
	}
}

/*-------------------------------------------------------------------------------------*/

void realiserHistogrammeRGB(int lignes,int colonnes,int Image[lignes][colonnes],int Rouge[lignes][colonnes],int Verte[lignes][colonnes],int Bleue[lignes][colonnes],int n,int Histogramme[],int taille_max){
	
	//fonction permettant de realiser l'hitogramme d'une image à partir des trois matrices de composantes rouges vertes et blueues

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){

			Image[i][j] = quantifierRGB(Rouge[i][j],Verte[i][j],Bleue[i][j],n); // appel de la fonction quantifierRGB et remplissage de l'image
		
		}
	}

	//Mise à 0 des compososantes de l'histogramme
	for(int k=0; k<taille_max;k++){
		Histogramme[k]=0;
	}

	//remplissage de l'histogramme
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			Histogramme[Image[i][j]]++;
		}
	}
}


/*-------------------------------------------------------------------------------------*/

void realiserHistogrammeNB(int lignes,int colonnes,int Image[lignes][colonnes],int noire[lignes][colonnes],int n,int Histogramme[],int taille_max){
	// fonction permettant de realiser l'hitogramme d'une image à partir de la matrice de la composante noire

	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){

			Image[i][j] = quantifierNB(noire[i][j],n);

		}
	}

	//Mise à 0 des compososantes de l'histogramme
	for(int k=0; k<taille_max;k++){
		Histogramme[k]=0;
	}

	//Remplissage de l'histogramme
	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			Histogramme[Image[i][j]]++;
		}
	}
}

/*-------------------------------------------------------------------------------------*/

void mise_a_jour_base(int n,int i,int taille_max,char titre_fichier[],descripteur d){
	
		FILE *ecrire_dans_base;
		ecrire_dans_base = fopen("../data/base_descripteur_image","a+");
		if(ecrire_dans_base == NULL)printf("chemin ecrire dans base errone\n");
		fprintf(ecrire_dans_base,"%s",d.identifiant);

		for(int j=0;j<taille_max;j++){
			fprintf(ecrire_dans_base,"%d ",d.Histogramme[j]);
			//somme += Histogramme[j];
			d.Histogramme[j] = 0;
		}
		fprintf(ecrire_dans_base,"\n");
		/*// ecriture dans le fichier base_descripteur_image*/
		fclose(ecrire_dans_base);

		FILE *images_indexees;
		images_indexees = fopen("../data/liste_base_image","a+");
		fprintf(images_indexees,"%s %s\n",titre_fichier,d.identifiant);
		fclose(images_indexees);
		
}


/*-------------------------------------------------------------------------------------*/

int base_est_vide(){

	FILE *fichier_descripteur;
	char variable_de_test;

	fichier_descripteur = fopen("../data/base_descripteur_image.txt","r");// ouverture de la base des descripteurs en mode lecture
			
	variable_de_test = fgetc(fichier_descripteur);//tester avec une variable si la base des descripteurs est vide
	
	fclose(fichier_descripteur);

	return variable_de_test == EOF;
}

/*-------------------------------------------------------------------------------------*/

void lister_fichiers(){

}

/*-------------------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------------------*/


void toString(int entier,char chaine[]){
	sprintf(chaine,"%d",entier);
}

void toInt(char chaine[],int *entier){
	*entier  = atoi(chaine);
}

int equals(char string1[],char string2[],int taille){
	int isok=0;
	for(int i=0;i<taille;i++){
		if(string1[i] == string2[i])isok++;
	}
	return isok == taille;
}

int fichier_deja_indexe(char titre_fichier[]){
	char titre_aux[6] = "";

	FILE *f_indexe;
	f_indexe = fopen("../data/liste_base_image","r");
	do{
		fscanf(f_indexe,"%s",titre_aux);//lecture des titres des fichiers

		if(equals(titre_fichier,titre_aux,6)){
			printf("le fichier : %s est deja indexe\n",titre_fichier);
			fclose(f_indexe);
			return 1;
		}
		
	}while(!feof(f_indexe));

	fclose(f_indexe);
	return 0;
}
void generer_identifiant(int n,char CHEMIN2[],descripteur *d){

	char s[1],s2[1];
	toString(n,s);
	s2[0] = CHEMIN2[21];
	s2[1] = CHEMIN2[22];
	strcpy(d->identifiant,s);
	strcat(d->identifiant,"[");
	strcat(d->identifiant,"#id");
	strcat(d->identifiant,s2);
	strcat(d->identifiant,"]");

}

descripteur generer_descripteur(char CHEMIN2[],int *taille_max,int n){
	int nbLignes = 0,nbColonnes = 0,nbComposantes = 0;
	descripteur d;
	FILE * lecteur_image;
	lecteur_image = fopen(CHEMIN2,"r"); // ouverture des fichiers .txt en mode lecture
				
	fscanf(lecteur_image," %d%d%d",&nbLignes,&nbColonnes,&nbComposantes); // lecture de la première lignes dimension de l'image et les composantes
	*taille_max =(int)pow(2,n*nbComposantes);
	int Histogramme[*taille_max];

	if(nbComposantes == 3){	
				
					int Rouge[nbLignes][nbColonnes],Verte[nbLignes][nbColonnes],Bleue[nbLignes][nbColonnes],ImageRGB[nbLignes][nbColonnes];

					//allocation dynamique des matrices représentant les composantes de l'image

					//printf("allouer memoire reussi\n");


					remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Rouge);
					remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Verte);
					remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Bleue);
					//lecture du contenu de l'image et remplissage des matrices

					//printf("matrices remplies reussi\n");

					realiserHistogrammeRGB(nbLignes,nbColonnes,ImageRGB,Rouge,Verte,Bleue,n,d.Histogramme,*taille_max);
					//realisation de l'histogramme avec passage en parametre du tableau Histogramme

					//printf("histogramme reussi\n");

	}
	else if(nbComposantes == 1){
					//printf("choix effectue\n");
					int Noire[nbLignes][nbColonnes],ImageNB[nbLignes][nbColonnes];
					//delcaration de la matrice représentant la composante noire et l'image pour réaliser l'histogramme


					remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Noire);
					//printf("matrices remplies reussi\n");
					//lecture du contenu de l'image et remplissage de la matrice

					realiserHistogrammeNB(nbLignes,nbColonnes,ImageNB,Noire,n,d.Histogramme,*taille_max);
					//realisation de l'histogramme avec passage en parametre du tableau Histogramme

	}
	generer_identifiant(n,CHEMIN2,&d);

	fclose(lecteur_image);
	return d;
}

void lancer_indexation(){
	
 /*----------------------------partie commande unix pour lister les noms des fichiers------------------------------*/
	char path[16] = "../data/";
	char commande[100] = "";
	
	sprintf(commande,"%s %s%s","ls",path,"TEST_IMAGES > ../data/liste_des_images");

	printf("execution de %s\n",commande);
	system(commande); // commande qui sert à mettre la liste des noms des fichiers(images) .txt à indexer

	// la commande est ls ../data/TEST_IMAGES > ../data/liste_des_images

	printf("commande reussie\n");

 /*------------------------------ouverture des fichiers à indexer--------------------------------------------------*/
	int n = 0,nbFichiers = 0;
	
	FILE * compteur_fichiers;

	//ouverture du fichier contenant la liste des images.txt

	system("wc -l ../data/liste_des_images > ../data/nbFichiers");
	//commande unix wc -l pour compter le nombre de lignes dans la liste des images 

	compteur_fichiers = fopen("../data/nbFichiers","r");
	fscanf(compteur_fichiers," %d",&nbFichiers);
	//lecture du nombre de fichiers

	//printf("%d\n",nbFichiers); // affichage du nombre de fichiers

	fclose(compteur_fichiers);
 /*---------------------------------------------------------------------------------------------------------------*/

	FILE * lecteur_fichier;
	
	lecteur_fichier = fopen("../data/liste_des_images","r");
	

	

		for(int n=2;n<4;n++){
			
			for(int i=1;i<=nbFichiers;i++){ // boucle for qui dépend du nombre de fichiers

				char titre_fichier[6];

				do{
					fscanf(lecteur_fichier,"%s",titre_fichier);//lecture des titres des fichiers
					if(feof(lecteur_fichier)){
						printf("tous les fichiers sont indexes\n");
						break;
					}
				}while(fichier_deja_indexe(titre_fichier));

				if(feof(lecteur_fichier))break;
				

				char CHEMIN2[100]="../data/TEST_IMAGES/"; // chemin d'ouverture des fichiers
				strcat(CHEMIN2,titre_fichier);
				
				int taille_max;
				descripteur d = generer_descripteur(CHEMIN2,&taille_max,n);

				mise_a_jour_base(n,i,taille_max,titre_fichier,d);

			}
		if(feof(lecteur_fichier))break;
		rewind(lecteur_fichier);
		}
	
	fclose(lecteur_fichier);
	

}

int main(void){
	descripteur d1;
	char chemin[100] = "../data/TEST_IMAGES/01.txt";
	int taille_max = 0,nblig = 0,nbcol = 0,nombre_composantes = 0,n=2;
	FILE *f;
	f = fopen(chemin,"r");
	fscanf(f,"%d%d%d",&nblig,&nbcol,&nombre_composantes);

	taille_max =(int)pow(2,n*nombre_composantes);
	int Histogramme[taille_max];
	int Rouge[nblig][nbcol],Verte[nblig][nbcol],Bleue[nblig][nbcol],ImageRGB[nblig][nbcol];

					//allocation dynamique des matrices représentant les composantes de l'image

					//printf("allouer memoire reussi\n");


					remplirMatrice(&f,nblig,nbcol,Rouge);
					remplirMatrice(&f,nblig,nbcol,Verte);
					remplirMatrice(&f,nblig,nbcol,Bleue);
					//lecture du contenu de l'image et remplissage des matrices

					//printf("matrices remplies reussi\n");

					realiserHistogrammeRGB(nblig,nbcol,ImageRGB,Rouge,Verte,Bleue,n,Histogramme,taille_max);
	strcpy(d1.identifiant,"identifiant 1");
	&Histogramme = d1->Histogramme;
	//d1 = generer_descripteur(chemin,&taille_max,2);
	printf("isok ici \n");
	printf("%s\n",d1.identifiant);
	for(int i=0;i<taille_max;i++){
		printf("%d ",Histogramme[i]);
	}
	return 0;
}