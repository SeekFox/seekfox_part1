#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef int * bits;
typedef struct descripteur
{
	char identifiant[10];
	int *Histogramme;
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
void generer_identifiant(int n,char titre_fichier[],descripteur *d){

char s[0] = "",s2[3] = "";
	int x = 0;
	
	toString(n,s);
	x = atoi(titre_fichier);
	sprintf(s2,"%d",x);
	
	strcpy(d->identifiant,s);
	strcat(d->identifiant,"[");
	strcat(d->identifiant,"#id");
	strcat(d->identifiant,s2);
	strcat(d->identifiant,"]");

}

void generer_descripteur(descripteur *d,char CHEMIN2[],char titre_fichier[],int *taille_max,int n){

	int nbLignes = 0,nbColonnes = 0,nbComposantes = 0;
	strcat(CHEMIN2,titre_fichier);
	FILE * lecteur_image;
	lecteur_image = fopen(CHEMIN2,"r"); // ouverture des fichiers .txt en mode lecture
				
	printf("%s\n",CHEMIN2);
	fscanf(lecteur_image," %d%d%d",&nbLignes,&nbColonnes,&nbComposantes); // lecture de la première lignes dimension de l'image et les composantes
	
	*taille_max =(int)pow(2,n*nbComposantes);
	int Histogramme[*taille_max];

	printf("%d\n",*taille_max);

	d->Histogramme = malloc((*taille_max)*sizeof(int));
	if(d->Histogramme == NULL){printf("erreur d'allcation dynamique;");exit(1);}

				
					int Rouge[nbLignes][nbColonnes],Verte[nbLignes][nbColonnes],Bleue[nbLignes][nbColonnes],ImageRGB[nbLignes][nbColonnes];

					//allocation dynamique des matrices représentant les composantes de l'image

					//printf("allouer memoire reussi\n");


					remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Rouge);
					remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Verte);
					remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Bleue);
					//lecture du contenu de l'image et remplissage des matrices

					//printf("matrices remplies reussi\n");

					realiserHistogrammeRGB(nbLignes,nbColonnes,ImageRGB,Rouge,Verte,Bleue,n,d->Histogramme,*taille_max);
					//realisation de l'histogramme avec passage en parametre du tableau Histogramme

					//printf("histogramme reussi\n");

	generer_identifiant(n,titre_fichier,d);
	for(int i=0;i<*taille_max;i++){
		printf("%d ",d->Histogramme[i]);
	}
	fclose(lecteur_image);
}

int main(void){

	FILE *comparateur;
	comparateur = fopen("../data/base_descripteur_image","r");
	char c[8];
	while(!feof(comparateur)){
		fscanf(comparateur,"%s",c);
		printf("%s\n",c);
		}
	fclose(comparateur);

	printf("\nfin du programme\n");
	return 0;
}