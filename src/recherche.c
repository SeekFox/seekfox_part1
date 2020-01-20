/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/recherche.h"
#include "../include/indexation.h"
#include "../include/audio.h"

//==================================================================================================================================
// FONCTIONS DE MANIPULATION DES STRUCTURES 

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

//==================================================================================================================================


//==================================================================================================================================
// FONCTIONS DE RECHERCHE 

RECHERCHE * rechercheParFichierTexte (char * adresse) {

    // Etape 1 : on crée un descripteur du fichier requête après avoir vérifié son existence 
    FILE * requete = NULL;
    requete = fopen(adresse, "r");
    DESCRIPTEUR * descRequete = NULL;
    if (requete==NULL) {
        // WIP : affichage de l'erreur 
        printf("ERREUR - Le fichier à rechercher n'existe pas ou n'a pas pu être ouvert.");
        return NULL;
    } else {
        // WIP : création du descripteur 
        descRequete = creerDescripteurTexte(requete);
        fclose(requete);
    }

    // Etape 2 : on compare ce descripteur à tous les descripteurs textes indexés 
    FILE * fichiersIndexes = NULL;
    FILE * descripteurs = NULL;
    fopen("data/descripteurs/fichiersIndexes.txt", "r");
    fopen("data/descripteurs/descripteurs.txt", "r");

    if (fichiersIndexes==NULL || descripteurs==NULL) {      // Vérification de l'ouverture des fichiers
        // WIP : affichage de l'erreur 
        printf("ERREUR - Problème d'accès à la base des descripteurs.");
        return NULL;
    }

    char * fichCourant = malloc(200*sizeof(char));      // Stockage de l'adresse du fichier courant
    char * descCourant = malloc(2000*sizeof(char));     // Stockage du descripteur associé
    
    RECHERCHE * resultats = creerRechercheVide();     // File qui contiendra les résultats de la recherche
    float seuil = recupSeuilRecherche();        // WIP : récupérer le seuil de similarité à partir duquel on considère un fichier suffisamment similaire pour être affiché
    
    while(fgets(fichCourant, 200, fichiersIndexes)!=NULL) {     // On passe chaque ligne du fichier listant les fichiers indexés en revue
        fgets(descCourant, 2000, descripteurs);     // Pour chacune de ces lignes (donc pour chacun de ces fichiers), on récupère le descripteur associé
        
        if(extensionFichier(fichCourant)=="xml") {      // Cas où le descripteur récupéré est celui d'un fichier texte (on ne traite que ces cas)
            DESCRIPTEUR * desc = convertirStringDescTexte(descCourant);     // On convertit le descripteur (jusque là au format string) en structure descripteur
            float sim = comparaisonDescTexte(desc, descRequete);        // On calcule la similarité entre le fichier recherché et le fichier courant
            if(sim>=seuil) {        // Cas où le descripteur récupéré a une similarité suffisante avec la recherche
                FICHIER * fcomp = creerCelluleFichier(fichCourant, sim);
                ajouterFichierRecherche(resultats, fcomp);      // On ajoute à la liste triée des fichiers compatibles avec la recherche
            }
        }
    }

    fclose(fichiersIndexes);
    fclose(descripteurs);

    return resultats;
}

RECHERCHE * rechercheParFichierImage (char * adresse) {

    // Etape 1 : on crée un descripteur du fichier requête après avoir vérifié son existence 
    FILE * requete = NULL;
    requete = fopen(adresse, "r");
    DESCRIPTEUR * descRequete = NULL;
    if (requete==NULL) {
        // WIP : affichage de l'erreur 
        printf("ERREUR - Le fichier à rechercher n'existe pas ou n'a pas pu être ouvert.");
        return NULL;
    } else {
        // WIP : création du descripteur 
        descRequete = creerDescripteurImage(requete);
        fclose(requete);
    }

    // Etape 2 : on compare ce descripteur à tous les descripteurs images indexés 
    FILE * fichiersIndexes = NULL;
    FILE * descripteurs = NULL;
    fopen("data/descripteurs/fichiersIndexes.txt", "r");
    fopen("data/descripteurs/descripteurs.txt", "r");

    if (fichiersIndexes==NULL || descripteurs==NULL) {      // Vérification de l'ouverture des fichiers
        // WIP : affichage de l'erreur 
        printf("ERREUR - Problème d'accès à la base des descripteurs.");
        return NULL;
    }

    char * fichCourant = malloc(200*sizeof(char));      // Stockage de l'adresse du fichier courant
    char * descCourant = malloc(2000*sizeof(char));     // Stockage du descripteur associé
    
    RECHERCHE * resultats = creerRechercheVide();     // File qui contiendra les résultats de la recherche
    float seuil = recupSeuilRecherche();        // WIP : récupérer le seuil de similarité à partir duquel on considère un fichier suffisamment similaire pour être affiché
    
    while(fgets(fichCourant, 200, fichiersIndexes)!=NULL) {     // On passe chaque ligne du fichier listant les fichiers indexés en revue
        fgets(descCourant, 2000, descripteurs);     // Pour chacune de ces lignes (donc pour chacun de ces fichiers), on récupère le descripteur associé
        
        if(extensionFichier(fichCourant)=="jpg" || extensionFichier(fichCourant)=="bmp") {      // Cas où le descripteur récupéré est celui d'un fichier image (on ne traite que ces cas)
            DESCRIPTEUR * desc = convertirStringDescImage(descCourant);     // On convertit le descripteur (jusque là au format string) en structure descripteur
            float sim = comparaisonDescImage(desc, descRequete);        // On calcule la similarité entre le fichier recherché et le fichier courant
            if(sim>=seuil) {        // Cas où le descripteur récupéré a une similarité suffisante avec la recherche
                FICHIER * fcomp = creerCelluleFichier(fichCourant, sim);
                ajouterFichierRecherche(resultats, fcomp);      // On ajoute à la liste triée des fichiers compatibles avec la recherche
            }
        }
    }

    fclose(fichiersIndexes);
    fclose(descripteurs);

    return resultats;
}

RECHERCHE * rechercheParFichierSon (char * adresse) {
    // IMPORTANT : pour les fichiers audio, les résultats de la recherche sont triés par nombre de fenêtres de corpus contenant le jingle et non par similitude 

    // Etape 1 : on crée un descripteur du fichier requête après avoir vérifié son existence 
    FILE * requete = NULL;
    requete = fopen(adresse, "r");
    DescripteurAudio * descRequete = NULL;
    if (requete==NULL) {
        // Affichage de l'erreur (A ADAPTER) 
        printf("ERREUR - Le fichier à rechercher n'existe pas ou n'a pas pu être ouvert.");
        return NULL;
    } else {
        // Création du descripteur audio 
        int tailleFenetre = getAudioN();        // Taille d'une fenêtre, pour le descripteur
        int nbIntervalles = getAudioM();        // Nombre d'intervalles, pour le descripteur
        int numExt;
        if (extensionFichier(adresse)=="wav") numExt=1;     // Numéro correspondant au type du fichier, pour le descripteur
        else if (extensionFichier(adresse)=="bin") numExt=2;
        else numExt=0;
        *descRequete = creerDescripteurAudio(requete, tailleFenetre, nbIntervalles, numExt);
        fclose(requete);
    }

    // Etape 2 : on compare ce descripteur à tous les descripteurs sons indexés 
    FILE * fichiersIndexes = NULL;
    FILE * descripteurs = NULL;
    fopen("data/descripteurs/fichiersIndexes.txt", "r");
    fopen("data/descripteurs/descripteurs.txt", "r");

    if (fichiersIndexes==NULL || descripteurs==NULL) {      // Vérification de l'ouverture des fichiers
        // Affichage de l'erreur (A ADAPTER) 
        printf("ERREUR - Problème d'accès à la base des descripteurs.");
        return NULL;
    }

    char * fichCourant = malloc(200*sizeof(char));      // Stockage de l'adresse du fichier courant
    char * descCourant = malloc(2000*sizeof(char));     // Stockage du descripteur associé
    
    RECHERCHE * resultats = creerRechercheVide();     // File qui contiendra les résultats de la recherche
    
    while(fgets(fichCourant, 200, fichiersIndexes)!=NULL) {     // On passe chaque ligne du fichier listant les fichiers indexés en revue
        fgets(descCourant, 2000, descripteurs);     // Pour chacune de ces lignes (donc pour chacun de ces fichiers), on récupère le descripteur associé
        
        if(extensionFichier(fichCourant)=="wav" || extensionFichier(fichCourant)=="bin") {      // Cas où le descripteur récupéré est celui d'un fichier son (on ne traite que ces cas)
            DescripteurAudio desc = stringToDescripteurAudio(descCourant, strlen(descCourant));     // On convertit le descripteur (jusque là au format string) en structure descripteur
            PILE sim = comparerDescripteursAudio(desc, *descRequete);        // On calcule la similarité entre le fichier recherché et le fichier courant
            if(taillePILE(sim)>=1) {        // Cas où le descripteur récupéré contient au moins une fois le jingle recherché
                FICHIER * fcomp = creerCelluleFichier(fichCourant, taillePile(sim));
                ajouterFichierRecherche(resultats, fcomp);      // On ajoute à la liste triée des fichiers compatibles avec la recherche
            }
        }
    }

    fclose(fichiersIndexes);
    fclose(descripteurs);

    return resultats;
}

//==================================================================================================================================


int main (int argc, char * argv[]) {

    RECHERCHE * r = creerRechercheVide();
    FICHIER * f1 = creerCelluleFichier("Auguste", 50);
    FICHIER * f2 = creerCelluleFichier("Dioclétien", 30);
    FICHIER * f3 = creerCelluleFichier("Trajan", 70);
    FICHIER * f4 = creerCelluleFichier("Gallien", 8);
    FICHIER * f5 = creerCelluleFichier("Constantin", 30);
<<<<<<< HEAD

=======
    FICHIER * f6 = creerCelluleFichier("Septime Sévère", 33);

    ajouterFichierRecherche(r, f6);
>>>>>>> dev
    ajouterFichierRecherche(r, f4);
    ajouterFichierRecherche(r, f1);
    ajouterFichierRecherche(r, f2);
    ajouterFichierRecherche(r, f3);
    ajouterFichierRecherche(r, f5);

    // Code pour afficher les résultats d'une recherche (ajouter de la mise en forme ?) 
    FICHIER * courant = r->premier;
    int i=1;
    while(courant!=NULL) {
        printf("%d - %s -> %f\n", i, courant->adresse, courant->similarite);
        courant = courant->suivant;
        i++;
    }

    return 0;
}*/