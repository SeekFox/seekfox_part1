#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/recherche.h"
#include "../include/audio.h"

/*==================================================================================================================================*/
/* FONCTIONS DE MANIPULATION DES STRUCTURES */

FICHIER * initCelluleFichier () {           // Initialise une cellule vide
    FICHIER * f = malloc(sizeof(FICHIER));
    f->adresse = NULL;
    f->similarite = 0;
    f->precedent = NULL;
    f->suivant = NULL;
    return f;
}

FICHIER * creerCelluleFichier (char * nom, float sim) {         // Crée une cellule à partir de l'adresse d'un fichier et d'un taux de similarité
    FICHIER * f = initCelluleFichier();
    f->adresse = malloc(strlen(nom)*sizeof(char));
    f->adresse = nom;
    f->similarite = sim;
    f->precedent = initCelluleFichier();
    f->precedent = NULL;
    f->suivant = initCelluleFichier();
    f->suivant = NULL;
    return f;
}

RECHERCHE * creerRechercheVide () {         // Crée une pile "recherche" vide
    RECHERCHE * r = malloc(sizeof(RECHERCHE));
    r->premier = initCelluleFichier();
    r->premier = NULL;
    r->dernier = initCelluleFichier();
    r->dernier = NULL;
    r->nbFichiers = 0;
    return r;
}

void ajouterFichierRecherche (RECHERCHE * r, FICHIER * f) {     // Ajoute un fichier dans la pile recherche en le triant par rapport à son taux de similarité
    if(r->nbFichiers==0) {
        r->premier = f;
        r->dernier = f;
        r->nbFichiers++;
    } else {
        FICHIER * courant = r->premier;
        while (courant->similarite>=f->similarite && courant->suivant!=NULL) courant = courant->suivant;
        if  (r->premier==courant && r->premier->similarite<f->similarite) {     // Cas où la similarité est supérieure à toutes celles déjà rentrées
            r->premier->precedent = f;
            f->suivant = r->premier;
            r->premier = f;
            r->nbFichiers++;
        } else if (courant->similarite>=f->similarite) {      // Cas où la similarité est inférieure à toutes celles déjà rentrées
            courant->suivant = f;
            f->precedent = courant;
            r->dernier = f;
            r->nbFichiers++;
        } else {    // Autres cas
            courant->precedent->suivant = f;
            f->precedent = courant->precedent;
            f->suivant = courant;
            courant->precedent = f;
            r->nbFichiers++;
        }
    }
}

/*==================================================================================================================================*/

int main (int argc, char * argv[]) {

    RECHERCHE * r = creerRechercheVide();
    FICHIER * f1 = creerCelluleFichier("Auguste", 50);
    FICHIER * f2 = creerCelluleFichier("Dioclétien", 30);
    FICHIER * f3 = creerCelluleFichier("Trajan", 70);
    FICHIER * f4 = creerCelluleFichier("Gallien", 8);
    FICHIER * f5 = creerCelluleFichier("Constantin", 30);

    ajouterFichierRecherche(r, f4);
    ajouterFichierRecherche(r, f1);
    ajouterFichierRecherche(r, f2);
    ajouterFichierRecherche(r, f3);
    ajouterFichierRecherche(r, f5);

    FICHIER * courant = r->premier;
    int i=1;
    while(courant!=NULL) {
        printf("%d - %s -> %f\n", i, courant->adresse, courant->similarite);
        courant = courant->suivant;
        i++;
    }

    return 0;
}