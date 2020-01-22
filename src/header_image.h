#ifndef HEADER_IMAGE
#define HEADER_IMAGE
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef int * bits;

typedef struct descriptor{
    char identifiant[6];
    int* Histogramme;
}descripteur;

void remplirMatrice(FILE **f,int lignes,int colonnes,int M[lignes][colonnes]);

int quantifierRGB(int composante_rouge,int composante_vert,int composante_bleue,int n);

int quantifierNB(int ComposanteNoire,int n);

void realiserHistogrammeRGB(int lignes,int colonnes,int Image[lignes][colonnes],int Rouge[lignes][colonnes],int Verte[lignes][colonnes],int Bleue[lignes][colonnes],int n,int Histogramme[],int taille_max);

void realiserHistogrammeNB(int lignes,int colonnes,int Image[lignes][colonnes],int noire[lignes][colonnes],int n,int Histogramme[],int taille_max);

void mise_a_jour_base(int n,int i,int taille_max,char titre_fichier[],descripteur d);

int base_est_vide();

void lister_fichiers();

void lancer_indexation();

void toString(int entier,char chaine[]);

void toInt(char chaine[],int *entier);

int equals(char string1[],char string2[],int taille);

int fichier_deja_indexe(char titre_fichier[]);

void generer_identifiant(int n,char CHEMIN2[],descripteur *d);

descripteur generer_descripteur(char CHEMIN2[],int *taille_max,int n);

void lancer_indexation();
//descripteur generer_descripteur(char chemin[],int Histogramme[]);

#endif