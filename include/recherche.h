#ifndef RECHERCHE_H
#define RECHERCHE_H

/* Principe : pour un fichier donné en recherche, on parcours tous les descripteurs du même type et on met les adresses de ceux 
qui ont un taux de similitude suffisant dans une pile/file où il sont triés par similitude décroissante */

/* Cellule de la pile contenant l'adresse d'un fichier et son taux de similitude */
typedef struct fichier {            
    char * adresse;                 // Adresse
    float similarite;               // Taux de similitude
    struct fichier * precedent;     // Fichier précédent (plus similaire)
    struct fichier * suivant;       // Fichier suivant (moins similaire)
} FICHIER;

/* Pile/file doublement chaînée qui contient les fichiers correspondants à la recherche */
typedef struct recherche {          
    FICHIER * premier;              // Fichier correspondant le mieux à la recherche
    FICHIER * dernier;              // Dernier fichier pouvant être affiché
    int nbFichiers;                 // Nombre de fichiers dans la pile
} RECHERCHE;

/* FONCTIONS DE MANIPULATION DES STRUCTURES */
FICHIER * initCelluleFichier ();
FICHIER * creerCelluleFichier (char *, float);
RECHERCHE * creerRechercheVide ();
void ajouterFichierRecherche (RECHERCHE *, FICHIER *);

#endif