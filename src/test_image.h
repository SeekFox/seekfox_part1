

typedef int * bits;

void remplirMatrice(FILE **f,int lignes,int colonnes,int M[lignes][colonnes]);

int quantifierRGB(int composante_rouge,int composante_vert,int composante_bleue,int n);

int quantifierNB(int ComposanteNoire,int n);

void realiserHistogrammeRGB(int lignes,int colonnes,int Image[lignes][colonnes],int Rouge[lignes][colonnes],int Verte[lignes][colonnes],int Bleue[lignes][colonnes],int n,int Histogramme[],int taille_max);

void realiserHistogrammeNB(int lignes,int colonnes,int Image[lignes][colonnes],int noire[lignes][colonnes],int n,int Histogramme[],int taille_max);

void mise_a_jour_base(int n,int i,int taille_max,int Histogramme[],char titre_fichier[]);