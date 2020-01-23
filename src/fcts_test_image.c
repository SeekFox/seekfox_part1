#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "../include/header_image.h"


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
}	//une fonction qui sert à la quantification : entree composantes RGB sortie résultat cd : page 15 cahier de charges

/*-------------------------------------------------------------------------------------*/

int quantifierNB(int ComposanteNoire,int n){

	
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
} // la meme chose que la fonction quantifierRGB mais avec une seule composante

/*-------------------------------------------------------------------------------------*/

void remplirMatrice(FILE **f,int lignes,int colonnes,int M[lignes][colonnes]){


	for(int i=0;i<lignes;i++){
		for(int j=0;j<colonnes;j++){
			fscanf(*f,"%d",&M[i][j]);
		}
	}
} //focntion qui sert à extraire les matrices à partir d'un flux overt vers un fichier .txt

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
		ecrire_dans_base = fopen("../data/base_descripteur_image","a+"); // ouverture d'un chemin vers la base_descripteur_image
		if(ecrire_dans_base == NULL)printf("chemin ecrire dans base errone\n");
		fprintf(ecrire_dans_base,"%s ",d.identifiant);	//ecrire l'identifiant dans la base

		for(int j=0;j<taille_max;j++){
			fprintf(ecrire_dans_base,"%d ",d.Histogramme[j]); // ecrire l'histogramme
			//somme += Histogramme[j]; // une somme pondérée qui sert à vérifier le nombre de pixels
			d.Histogramme[j] = 0;
		}
		fprintf(ecrire_dans_base,"\n");
		fclose(ecrire_dans_base);

		FILE *images_indexees;
		images_indexees = fopen("../data/liste_base_image","a+"); //ouvrerture de flux sur le fichier liste_base_image
		fprintf(images_indexees,"%s %s\n",titre_fichier,d.identifiant); //écriture du titre du fichier et de l'identifiant du descripteur associé
		fclose(images_indexees);
		
} // fonction qui sert à ajouter(à la fin) un descripteur dans la base_descripteur_image


/*-------------------------------------------------------------------------------------*/

int base_est_vide(){

	FILE *fichier_descripteur;
	char variable_de_test;

	fichier_descripteur = fopen("../data/base_descripteur_image.txt","r");// ouverture de la base des descripteurs en mode lecture
			
	variable_de_test = fgetc(fichier_descripteur);//tester avec une variable si la base des descripteurs est vide
	
	fclose(fichier_descripteur);

	return variable_de_test == EOF;
}// fonction qui vérifie si la base_descripteur_image est vide renvoie 1 si la base est vide 0 sinon

/*-------------------------------------------------------------------------------------*/

void lister_fichiers(){

}//à ajouter ici les commandes unix dans la fonction lancer_indexation
/* j'ai pas ajouté cette fonction parce qu'elle marchait pas quand je l'ai testé du coup c'est à vous de jouer*/

/*-------------------------------------------------------------------------------------*/

void toString(int entier,char chaine[]){
	sprintf(chaine,"%d",entier);
} //fonction qui sert à convertir un entier en une chaine de caractère

/*-------------------------------------------------------------------------------------*/

void toInt(char chaine[],int *entier){
	*entier  = atoi(chaine);
} //fonction qui sert à convertir une chaine de caractères en entier

/*-------------------------------------------------------------------------------------*/

int equals(char string1[],char string2[],int taille){
	int isok=0;
	for(int i=0;i<taille;i++){
		if(string1[i] == string2[i])isok++;
	}
	return isok == taille;
} /*
	fonction qui compare deux parties de chaine de caractères retourne 1 si les deux chaines sont identiques 0 sinon
	elle prend les deux chaines en entree avec la taille des chaines à comparer
*/

/*-------------------------------------------------------------------------------------*/

int fichier_deja_indexe(char titre_fichier[]){

	char titre_aux[8] = "";

	FILE *f_indexe;
	f_indexe = fopen("../data/liste_base_image","r"); //ouverture d'un flux sur le fichier liste_base_image
	do{
		fscanf(f_indexe,"%s",titre_aux);	//lecture du titre du fichier sur une chaine auxilière

		if(equals(titre_fichier,titre_aux,7)){	//comparaison entre le titre passé en paramètre et le titre lu(titre_aux)
			printf("le fichier : %s est deja indexe\n",titre_fichier);	//affichage du titre du fichier et retour de 1
			fclose(f_indexe);
			return 1;	
		}
		
	}while(!feof(f_indexe));

	fclose(f_indexe);
	return 0;
}	// fonction qui retourne 1 si lefichier est déja indéxé et 0 sinon

/*-------------------------------------------------------------------------------------*/

void generer_identifiant(int n,char titre_fichier[],descripteur *d,int taille_max){
	int x = 0;

	char taille[4];
	taille[3] = '\0';
	toString(taille_max,taille);

	char c1[10] = "";
	toString(n,c1);
	c1[9] = '\0';

	char c2[5] = "";

	toInt(titre_fichier,&x);
	toString(x,c2);
	c2[4] = '\0';
	strcat(c1," ");
	strcat(c1,c2);
	
	strcpy(d->identifiant,"[ ");

	strcat(d->identifiant,taille);

	strcat(d->identifiant," #id ");

	strcat(d->identifiant,c1);

	strcat(d->identifiant," ]");

	d->identifiant[19] = '\0';


} /*	
Cette fonction sert à générer des identifiants de descripteurs à partir du nombre de bits de quantification,
du titre du fichier, de la taille max de l'histogramme du descripteur
le descripteur est passé par adresse pour qu'on puisse le modifier
la structure de l'identifiant est comme suit 

[ taille_max #id n c]
taille_max : la taille de l'histogramme
n : le nombre de bits sur quoi on va quantifier
c : le titre du fichier transformé en int

*/
	
/*-------------------------------------------------------------------------------------*/

void generer_descripteur(descripteur *d,char * fichier,int *taille_max,int n){

	int nbLignes = 0,nbColonnes = 0,nbComposantes = 0;
	FILE * lecteur_image;

	//printf("le chemin est %s\n",fichier);


	lecteur_image = fopen(fichier,"r"); // ouverture du fichier .txt en mode lecture
	

	fscanf(lecteur_image," %d%d%d",&nbLignes,&nbColonnes,&nbComposantes); 
	// lecture de la première ligne : dimensions de l'image et les composantes de l'image

	*taille_max =(int)pow(2,n*nbComposantes);
	d->Histogramme = malloc((*taille_max)*sizeof(int));
	//allocation dynamique du descripteur en fonction de sa taille

	if(d->Histogramme == NULL){
		printf("erreur d'allcation dynamique\n");
		exit(1);
	}
	//test d'allocation

	if(nbComposantes == 3){	
				
		int Rouge[nbLignes][nbColonnes],Verte[nbLignes][nbColonnes],Bleue[nbLignes][nbColonnes],ImageRGB[nbLignes][nbColonnes];

		//declaration des matrices représentant les composantes de l'image


		remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Rouge);

		remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Verte);

		remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Bleue);

		//lecture du contenu de l'image en remplissant les matrices

		//indexer_par_couleur_dominante(nbLignes,nbColonnes,Rouge,Verte,Bleue,titre_fichier);

		//printf("matrices remplies reussi\n");

		realiserHistogrammeRGB(nbLignes,nbColonnes,ImageRGB,Rouge,Verte,Bleue,n,d->Histogramme,*taille_max);

		//realisation de l'histogramme avec passage en parametre du tableau Histogramme

		//printf("histogramme reussi\n");

	}
	else if(nbComposantes == 1){

					//printf("choix effectue\n");

		int Noire[nbLignes][nbColonnes],ImageNB[nbLignes][nbColonnes];

		//delcaration de la matrice représentant la composante noire et l'image pour réaliser l'histogramme


		remplirMatrice(&lecteur_image,nbLignes,nbColonnes,Noire);

		//lecture du contenu de l'image et remplissage de la matrice

		realiserHistogrammeNB(nbLignes,nbColonnes,ImageNB,Noire,n,d->Histogramme,*taille_max);

		//realisation de l'histogramme avec passage en parametre du tableau Histogramme

	}
	generer_identifiant(n,fichier,d,*taille_max);
	//strcpy(d->identifiant,"identifiant ");
	//generation de l'identifiant du descripteur

	fclose(lecteur_image);
	printf("fin \n");
}

/*
		fonction qui sert à créer un descripteur(passé en paramètre) à partir du chemin et du titre du fichier
		(chaines en paramètre), le nombre de bits sur quoi on va quantifier(n) et qui modifie la taille_max de
		 l'histogramme du descripteur, celle-ci va être utile pour d'autre fonctions qui viennent après
	*/


/*-------------------------------------------------------------------------------------*/

void afficher_descripteur(descripteur d,int taille_max){

	printf("%s ",d.identifiant);
	for(int i=0;i<taille_max;i++){
		printf("%d ",d.Histogramme[i]);
	}
	printf("\n");
}
/* 
fonction qui sert à afficher un descripteur passé en paramètre avec sa taille maximale
*/

/*-------------------------------------------------------------------------------------*/

void lancer_indexation(int indice_indexation){ // vaut 0 pour une première indexation et 1 pour une mise à jour;
	
	//----------------------------partie commande unix pour lister les noms des fichiers------------------------------
	char path[16] = "../data/";
	char commande[100] = "";
	
	sprintf(commande,"%s %s%s","ls",path,"TEST_IMAGES > ../data/liste_des_images");

	printf("execution de %s\n",commande);
	system(commande); // commande qui sert à mettre la liste des noms des fichiers(images) .txt à indexer

	// la commande est ls ../data/TEST_IMAGES > ../data/liste_des_images

	printf("commande reussie\n");

	//------------------------------ouverture des fichiers à indexer--------------------------------------------------
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
	//---------------------------------------------------------------------------------------------------------------

	FILE * lecteur_fichier;
	
	lecteur_fichier = fopen("../data/liste_des_images","r");

		for(int n=2;n<4;n++){
			
			for(int i=1;i<=nbFichiers;i++){ // boucle for qui dépend du nombre de fichiers un while(!feof()) marchera tres bien aussi

				char titre_fichier[64];

				if(indice_indexation == 0)fscanf(lecteur_fichier,"%s",titre_fichier);
				else
				{
				
					do{
						fscanf(lecteur_fichier,"%s",titre_fichier);//lecture des titres des fichiers
						if(feof(lecteur_fichier)){
							printf("tous les fichiers sont indexes\n");
							break;
						}
					}while(fichier_deja_indexe(titre_fichier));

					if(feof(lecteur_fichier))break;
				}

				descripteur d;
				int taille_max = 0;
				sprintf(titre_fichier,"../data/TEST_IMAGES/%s",titre_fichier);

				generer_descripteur(&d,titre_fichier,&taille_max,n);	//création des descripteurs

				afficher_descripteur(d,taille_max);	//affichage des descripteurs(optionnel)

				//mise_a_jour_base(n,i,taille_max,titre_fichier,d); // ajout dans le fichier base descripteur_image

				free(d.Histogramme);
			}
		if(indice_indexation != 0){
			if(feof(lecteur_fichier))break;
			}
		rewind(lecteur_fichier);
		}
	
	fclose(lecteur_fichier);
	

}	
/*
	la fonction principale qui sert à lancer l'indexation de toutes les images si elle ne sont pas déja indéxées
	avec passage en paramètre d'un indice d'indexation qui vaut 0 quant on veut effectuer l'indexation 
	pour la première fois et 1 quand on veut juste ajouter un fichier

*/

/*-------------------------------------------------------------------------------------*/

void tri_decroissant( Resultat tab[], int tab_size){                                                                              
	int tmp = 0;
	char id_aux[20] = "";
	id_aux[19] = '\0';    

  for(int i = 0; i < tab_size; i++)                                         
    {                                                                          
      for(int j = 1; j < tab_size; j++)                        
        {                                                                      
          if(tab[i].Valeur > tab[j].Valeur)                                                        
            {  
			  
              tmp = tab[i].Valeur;  
			  strcpy(id_aux,tab[i].identifiant);

              tab[i].Valeur = tab[j].Valeur;   
			  strcpy(tab[i].identifiant,tab[j].identifiant);   

              tab[j].Valeur = tmp;   
			  strcpy(tab[j].identifiant,id_aux);            

              //j--;        

            }                                                                  
        }                                                                      
    }                                                                                                                                             
} // une focntion qui trie les elements d'un tableau de manière décroissante

void ouvrir_image(char identifiant[]){

	char titre_fichier[7] = "";
	titre_fichier[6] = '\0';

	char id[14] = "";
	char aux[7] = "";
	aux[6] = '\0';
	//strcpy(aux,".txt");
	//id[] = '\0';
	
	int b;

	char commande[50] = "";
	char titre_image[15] = "";
	titre_image[14] = '\0';
	commande[49] = '\0';
	strcpy(commande,"eog ../data/TEST_RGB_NB/");
	
	FILE *chercheur_image;
	chercheur_image = fopen("../data/liste_base_image","r");

	do{

		strcpy(id,"");

		for(int i=0;i<6;i++){
			if( i == 0 )fscanf(chercheur_image,"%s",titre_fichier);

			fscanf(chercheur_image,"%s",aux);
			if( i == 1)toInt(aux,&b);

			strcat(id,aux);
			strcat(id," ");
		}
		

		//printf("%s\n%s\n",id,identifiant);

		if(equals(id,identifiant,14)){

			strcpy(titre_image,"");

			titre_image[0] = titre_fichier[0];
			titre_image[1] = titre_fichier[1];

			if(b == 4 || b == 8){
				strcat(titre_image,".bmp");
			}
			else
			{
				strcat(titre_image,".jpg");
			}
			

			strcat(commande,titre_image);
			system(commande);
			break;
		}
	}while(!feof(chercheur_image));
	fclose(chercheur_image);
}
/*
fonction qui sert à ouvrir une image à partir de son identifiant
*/

void afficher_les_resultats(Resultat r[]){

	Resultat meilleur_resultat;
	meilleur_resultat.Valeur = 0;

	for(int i=0;i<100;i++){

		if(r[i].Valeur != 0){


			printf("%.2f%c   %s\n",r[i].Valeur,'%',r[i].identifiant);

			if(meilleur_resultat.Valeur < r[i].Valeur){

				meilleur_resultat.Valeur = r[i].Valeur;

				strcpy(meilleur_resultat.identifiant,r[i].identifiant);

				//printf("%f  %s",meilleur_resultat.Valeur,meilleur_resultat.identifiant);

				meilleur_resultat.identifiant[19] = '\0';
				}
		}
		
	}
	ouvrir_image(meilleur_resultat.identifiant);
}
/*
fonction qui sert à afficher les resultats de la recherche stockés dans le tableau passé en paramètre
*/

void ajouter_au_resultats(Resultat r[],int resultat,int *j,char identifiant[]){


	r[(*j)].Valeur = resultat;
	strcpy(r[(*j)].identifiant,"");
	strcat(r[(*j)].identifiant,identifiant);
	r[(*j)].identifiant[19] = '\0';
	//printf("%d  %f   %s\n",*j,r[*j].Valeur,r[*j].identifiant);
	(*j)++;
	

}/*
fonction qui sert à ajouter des resultats dans le tableau de résultats passé en paramètre
*/

void initialiser_resultat(Resultat r[]){
		for(int i=0;i<100;i++){
			r[i].Valeur = 0;
			strcpy(r[i].identifiant,"");
		}
}
// initialisation du tableau qui comporte les résultats de la recherche


void rechercher_image(char * fichier,int n){
	printf("debut recherche\n");
	int taille_max = 0,taille_aux,n_aux,j = 0,valeur = 0;
	float resultat = 0;
	descripteur d;
	Resultat resultat_comparaison[100];
	initialiser_resultat(resultat_comparaison);

	char identifiant[20] = "",valeur_histogramme[4];
	char c[10];
	char N[3];

	N[2] = '\0';
	c[9] = '\0';
	identifiant[19] = '\0';
	toString(n,N);
	generer_descripteur(&d,fichier,&taille_max,n);
	
	char string[1500] = "";
	FILE *comparateur;
	comparateur = fopen("data/base_descripteur_image","r");

	while(!feof(comparateur)){
		strcpy(identifiant,"");

		for(int i=0;i<6;i++){
			
			fscanf(comparateur,"%s",c);
			
			if(i == 0)strcpy(identifiant,"");
			if(i == 1)toInt(c,&taille_aux);
			if(i == 3)toInt(c,&n_aux);


			strcat(identifiant,c);
			strcat(identifiant," ");	//identifiant acquérit
			//printf("%s\n",c);
			
		}	//boucle qui sert à lire l'identifiant d'un descripteur et mettre à jour la taille max et le nombre de quantification n

			//printf("%s\n",identifiant);
		
		strcpy(resultat_comparaison[j].identifiant,identifiant);

		//printf("%s\n",resultat_comparaison[j].identifiant);
		
		if(taille_aux == taille_max){
			//printf("taille max is %d\n",taille_max);
			
			for(int i=0;i<taille_max;i++){
				
				fscanf(comparateur,"%s",valeur_histogramme);
				
				toInt(valeur_histogramme,&valeur);
				
				if(d.Histogramme[i] == valeur)resultat++;
				
			}//boucle qui sert à comparer deux Histogrammes

			resultat = (resultat*100)/(float)taille_max;
			
			//strcpy(resultat_comparaison[0].identifiant,identifiant);
			//printf("%s\n",resultat_comparaison[0].identifiant);

			printf("sdfg\n");
			ajouter_au_resultats(resultat_comparaison,resultat,&j,identifiant);
			resultat = 0;
		}else{
			fgets(string,1500,comparateur);
		}
		
	}
	fclose(comparateur);

	tri_decroissant(resultat_comparaison,100);
	afficher_les_resultats(resultat_comparaison);

}
/*une fonction qui sert à rechercher l'image et afficher les résultats 
en ordre décroissant avec ouverture de l'image la plus pertinante 
*/


void descripteur_image_to_string(descripteur d,char string[],int taille_max){

	char chaine[7] = "";
	chaine[6] = '\0';

	strcpy(string,d.identifiant);

	for(int i=0;i<taille_max;i++){
		toString(d.Histogramme[i],chaine);
		strcat(string," ");
		strcat(string,chaine);
	}

}

void string_to_descripteur_image(char string[],descripteur *d){

	int taille_max = 0;
	int longueur_chaine = 0,aux = 0,j=0;
	char c[4]="";
	c[3] = '\0';
	longueur_chaine = strlen(string);

	for(int i = 0;i<20;i++){
		if(i<15)d->identifiant[i] = string[i];
		if(i>=1 && i<5)c[i-1] = string[i];
		if(string[i] == ']')break;
	}

	toInt(c,&taille_max);
	//printf("la taille max est %d\n",taille_max);

	d->Histogramme = malloc(taille_max*sizeof(int));
	if(d->Histogramme == NULL){
		printf("erreur allocation dynamique\n");
		exit(1);
	}
	int i=0;

	char *p = string;
	while (*p) {
    if( isdigit(*p) || ( (*p=='-'||*p=='+') && isdigit(*(p+1)) )){
        // Found a number
        d->Histogramme[i] = strtol(p, &p, 10); // Read number
        printf("%d\n", d->Histogramme[i]); // and print it.
    } 
	else{
        p++;
    }
	i++;
	}
	
}
