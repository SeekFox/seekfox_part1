#ifndef RECHERCHE_H
#define RECHERCHE_H
#include "pile_dynamiqueAudio.h"
/* Principe : pour un fichier donné en recherche, on parcours tous les descripteurs du même type et on met les adresses de ceux 
qui ont un taux de similitude suffisant dans une pile/file où il sont triés par similarité décroissante */

/* Cellule de la pile contenant l'adresse d'un fichier et son taux de similitude */
typedef struct fichier {            
    char * adresse;                 // Adresse
    float similarite;               // Taux de similarité
    int * tps;                      // Utilisé par le son uniquement, position en secondes des jingles identiques
    struct fichier * precedent;     // Fichier précédent (plus similaire)
    struct fichier * suivant;       // Fichier suivant (moins similaire)
} FICHIER;

/* Pile/file doublement chaînée qui contient les fichiers correspondants à la recherche, triés par ordre de similarité décroissante */
typedef struct recherche {          
    FICHIER * premier;              // Fichier correspondant le mieux à la recherche
    FICHIER * dernier;              // Dernier fichier pouvant être affiché
    int nbFichiers;                 // Nombre de fichiers dans la pile
} RECHERCHE;

/* FONCTIONS DE MANIPULATION DES STRUCTURES */
FICHIER * initCelluleFichier ();                                // Crée une cellule fichier vide
FICHIER * creerCelluleFichierSon (char *,PILE);
FICHIER * creerCelluleFichier (char *,float);                  // Crée une cellule fichier contenant l'adresse d'un fichier et un taux de similarité
RECHERCHE * creerRechercheVide ();                              // Crée une file triée recherche vide
void ajouterFichierRecherche (RECHERCHE *, FICHIER *);          // Ajoute une cellule fichier dans la file en la triant (par ordre décroissant)

void afficherResultats(RECHERCHE *r, int typeRecherche);

/* FONCTIONS DE RECHERCHE PAR FICHIER */
// /!\ IMPORTANT : ces fonctions ont besoin de toutes les fonctions de manipulation/création de descripteur pour pouvoir fonctionner
RECHERCHE * rechercheParFichierTexte (char *);
RECHERCHE * rechercheParFichierImage (char *);
RECHERCHE * rechercheParFichierSon (char *);
// Pour chacune de ces fonctions, renvoie la liste triée des fichiers les plus similaires à celui dont l'adresse est passée en paramètre

#endif