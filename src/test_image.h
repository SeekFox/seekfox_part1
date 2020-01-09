#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef int * bits;
typedef int ** matrice;

int quantifierRGB(int composante_rouge,int composante_vert,int composante_bleue,int n);
int quantifierNB(int ComposanteNoire,int n);

matrice allouerMemoire(matrice tab,int lignes,int colonnes);
matrice libererMemoire(matrice m,int colonnes);


void remplirMatrice(FILE **f,matrice M,int lignes,int colonnes);
void realiserHistogrammeRGB(matrice Image,matrice Rouge,matrice Verte,matrice Bleue,int lignes,int colonnes,int n,int Histogramme[],int taille_max);
void realiserHistogrammeNB(matrice Image,matrice noire,int lignes,int colonnes,int n,int Histogramme[],int taille_max);