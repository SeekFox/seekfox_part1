#ifndef HEADER_IMAGE
#define HEADER_IMAGE
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef int * bits; // type qui sert à la quantification

typedef struct descriptor{ //structure d'un descripteur :
    char identifiant[20]; //une chaine representant un identifiant et un pointeur qui va prendre l'histogramme
    int *Histogramme;
}descripteur;

typedef struct structure{ // structure qui représente les résultats de la recherche elle comprend 
	char identifiant[20]; // l'identifiant du fichier
	float Valeur;	// la valeur de compatibilité avec le fichier à comparer
}Resultat;

int quantifierRGB(int composante_rouge,int composante_vert,int composante_bleue,int n);

int quantifierNB(int ComposanteNoire,int n);

void remplirMatrice(FILE **f,int lignes,int colonnes,int M[lignes][colonnes]);

void realiserHistogrammeRGB(int lignes,int colonnes,int Image[lignes][colonnes],int Rouge[lignes][colonnes],int Verte[lignes][colonnes],int Bleue[lignes][colonnes],int n,int Histogramme[],int taille_max);

void realiserHistogrammeNB(int lignes,int colonnes,int Image[lignes][colonnes],int noire[lignes][colonnes],int n,int Histogramme[],int taille_max);

void mise_a_jour_base(int n,int i,int taille_max,char titre_fichier[],descripteur d);

int base_est_vide();

void toString(int entier,char chaine[]);

void toInt(char chaine[],int *entier);

int equals(char string1[],char string2[],int taille);

int fichier_deja_indexe(char titre_fichier[]);

void generer_identifiant(int n,char titre_fichier[],descripteur *d,int taille_max);

void generer_descripteur(descripteur *d,char CHEMIN2[],char titre_fichier[],int *taille_max,int n);

void afficher_descripteur(descripteur d,int taille_max);

void lancer_indexation(int indice_indexation);

void tri_decroissant( Resultat tab[], int tab_size);

void ouvrir_image(char identifiant[]);

void afficher_les_resultats(Resultat r[]);

void ajouter_au_resultats(Resultat r[],int resultat,int *j,char identifiant[]);

void initialiser_resultat(Resultat r[]);

void rechercher_image(char chemin[],char titre_fichier[],int n);

void descripteur_image_to_string(descripteur d,char string[],int taille_max);

void string_to_descripteur_image(char string[],descripteur *d);
#endif