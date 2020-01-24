/**
 * @file recherche.c
 * @author Etienne Combelles
 * @brief 
 * @version 0.1
 * @date 24/01/2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/recherche.h"
#include "../include/indexation.h"
#include "../include/audio.h"
#include "../include/config.h"
#include "../include/interact.h"
#include "../include/header_image.h"

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

FICHIER * creerCelluleFichierSon (char * nom, PILE sim) {         // Crée une cellule à partir de l'adresse d'un fichier et d'un taux de similarité
    FICHIER * f = initCelluleFichier();
    f->adresse = malloc(strlen(nom)*sizeof(char));
    strcpy(f->adresse,nom);
    (f->adresse)[0] = ' ';
    f->similarite = taillePILE(sim);
    f->precedent = initCelluleFichier();
    f->tps = malloc(taillePILE(sim)*sizeof(int));
    int tps;
    for(int i=0; i<taillePILE(sim); i++) {
        sim = dePILE(sim, &tps);
        f->tps[i]=tps;
    }
    f->precedent = NULL;
    f->suivant = initCelluleFichier();
    f->suivant = NULL;
    return f;
}

FICHIER * creerCelluleFichier (char * nom, float sim) {         // Crée une cellule à partir de l'adresse d'un fichier et d'un taux de similarité
    FICHIER * f = initCelluleFichier();
    f->adresse = malloc(strlen(nom)*sizeof(char));
    strcpy(f->adresse,nom);
    (f->adresse)[0] = ' ';
    f->similarite = sim;
    f->tps = NULL;
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

void afficherResultats(RECHERCHE *r,int typeRecherche){
    //printf("Affichage des resultats\n");
    if(r->premier!=NULL){
        FICHIER * courant = r->premier;
        int i=1;
    
        if(typeRecherche == R_SON){
            if(courant!=NULL) {
                printf("\t%d -%-20s -> %.0f occurence%s -> ", i, courant->adresse, courant->similarite,(courant->similarite>1?"s":""));
                for(int j = 0; j < courant->similarite; j++){
                    printf("%ds \n", courant->tps[j]);
                }
            }
        } else{
            while(courant!=NULL) {
                printf("\t%d -%-20s -> %.2f", i, courant->adresse, courant->similarite);
                printf("%c\n",'%');
                courant = courant->suivant;
                i++;
            }
        }

        char cmd[128];

        switch (typeRecherche){
            case R_SON:
                r->premier->adresse[0] = '/';
                sprintf(cmd,"%s base_de_documents%s.wav",getLogicielOuvertureFichier(),((r->premier)->adresse));
                break;

            case R_TEXTE:
                sprintf(cmd,"%s base_de_documents%s",getLogicielOuvertureFichier(),((r->premier)->adresse));
                break;
            
            case R_IMAGE:
                sprintf(cmd,"%s base_de_documents%s",getLogicielOuvertureFichier(),((r->premier)->adresse));
                break;

            default:

                break;
        }

        printf("COMMANDE : %s\n",cmd);
    } else {
        printf("Aucun résultat trouvé...\n");
    }
    //msystem(cmd);
}

//==================================================================================================================================
// FONCTIONS DE RECHERCHE 
/*
RECHERCHE * rechercheParFichierTexte (char * adresse) {

    // Etape 1 : on crée un descripteur du fichier requête après avoir vérifié son existence 
    FILE * requete = NULL;
    requete = fopen(adresse, "r");
    DESC descRequete;
    if (requete==NULL) {
        // Affichage de l'erreur 
        displayError("Le fichier à rechercher n'existe pas ou n'a pas pu être ouvert.");
        return NULL;
    } else {
        // Création du descripteur 
        descRequete = creerDescripteur_txt(requete);
        fclose(requete);
    }

    // Etape 2 : on compare ce descripteur à tous les descripteurs textes indexés 
    FILE * fichiersIndexes = NULL;
    FILE * descripteurs = NULL;
    fichiersIndexes = fopen("data/descripteurs/fichiersIndexes.txt", "r");
    descripteurs = fopen("data/descripteurs/descripteurs.txt", "r");

    if (fichiersIndexes==NULL || descripteurs==NULL) {      // Vérification de l'ouverture des fichiers
        // Affichage de l'erreur
        displayError("Problème d'accès à la base des descripteurs.");
        return NULL;
    }

    char * fichCourant = malloc(200*sizeof(char));      // Stockage de l'adresse du fichier courant
    char * descCourant = malloc(20000*sizeof(char));     // Stockage du descripteur associé
    
    RECHERCHE * resultats = creerRechercheVide();     // File qui contiendra les résultats de la recherche
    float seuil = 70;       //recupSeuilRecherche();        // WIP : récupérer le seuil de similarité à partir duquel on considère un fichier suffisamment similaire pour être affiché (j'ai mis 70 par défaut)
    
    while(fgets(fichCourant, 200, fichiersIndexes)!=NULL) {     // On passe chaque ligne du fichier listant les fichiers indexés en revue
        fgets(descCourant, 20000, descripteurs);     // Pour chacune de ces lignes (donc pour chacun de ces fichiers), on récupère le descripteur associé
        
        if(strcmp(getExtensionOfFile(fichCourant), ".xml")==0) {      // Cas où le descripteur récupéré est celui d'un fichier texte (on ne traite que ces cas)
            // Conversion de la chaine de char en FIFO de char (c'est plus fun je suppose)
            FIFO fifodesc;
            Init_File(fifodesc);
            for(int i=0; i<strlen(descCourant); i++) {
                fifodesc = Enfiler(*fifodesc, descCourant[i]);
            }    
            DESC desc = conversionStringDescripteur(fifodesc);     // On convertit le descripteur (jusque là au format string) en structure descripteur
            float sim = comparerDescripteurs(desc, descRequete);        // On calcule la similarité entre le fichier recherché et le fichier courant
            if(sim>=seuil) {        // Cas où le descripteur récupéré a une similarité suffisante avec la recherche
                FICHIER * fcomp = creerCelluleFichier(fichCourant, sim);
                ajouterFichierRecherche(resultats, fcomp);      // On ajoute à la liste triée des fichiers compatibles avec la recherche
            }
        }
    }

    free(descCourant);
    fclose(fichiersIndexes);
    fclose(descripteurs);

    return resultats;
}
*/
RECHERCHE * rechercheParFichierImage (char * fichier) {
    
    /* Etape 1 : on crée un descripteur du fichier requête après avoir vérifié son existence */
    FILE * requete = NULL;
    char adresse[64];
    sprintf(adresse, "requete/%s", fichier);
    requete = fopen(adresse, "r");
    descripteur descRequete;
    if (requete==NULL) {
        /* Affichage de l'erreur */
        displayError("Le fichier à rechercher n'existe pas ou n'a pas pu être ouvert.");
        return NULL;
    } else {
        /* Création du descripteur */
        fclose(requete);                // fclose placé au début car generer_descripteur ne prend pas de FILE* en paramètre
        int taille_max = 0;         // Taille max du descripteur
        generer_descripteur(&descRequete, "requete/", fichier,&taille_max, getNbBits());     // Quantification sur 2 bits
    }
    
    
    /* Etape 2 : on compare ce descripteur à tous les descripteurs images indexés */
    FILE * fichiersIndexes = NULL;
    FILE * descripteurs = NULL;
    fichiersIndexes = fopen("data/descripteurs/fichiersIndexes.txt", "r");
    descripteurs = fopen("data/descripteurs/descripteurs.txt", "r");

    if (fichiersIndexes==NULL || descripteurs==NULL) {      // Vérification de l'ouverture des fichiers
        /* Affichage de l'erreur */
        displayError("ERREUR - Problème d'accès à la base des descripteurs.");
        return NULL;
    }
    

    char * fichCourant = malloc(200*sizeof(char));      // Stockage de l'adresse du fichier courant
    char * descCourant = malloc(20000*sizeof(char));     // Stockage du descripteur associé
    
    RECHERCHE * resultats = creerRechercheVide();     // File qui contiendra les résultats de la recherche
    //float seuil = recupSeuilRecherche();        // WIP : récupérer le seuil de similarité à partir duquel on considère un fichier suffisamment similaire pour être affiché
    
    // Explications de ce qui suit : il n'y a pas de fonction pour comparer 2 descripteurs image, etla fonction recherche a été faite 
    // par Oualid, donc pour m'adapter à cette fonction je transfère tous les descripteurs image indexés dans le fichier ouvert ci-dessous.
    // C'est ce fichier qui est utilisé dans la fonction de oualid comme base de descripteurs.
    // (D'ailleurs, je sais pas à quoi correspond le dernier paramètre, donc j'ai mis 10)
    //      Merci etienne, je suis heureux de l'apprendre
    FILE * descImages = NULL;
    descImages = fopen("data/base_descripteur_image", "w+");
    if(descImages==NULL) {
        displayError("Problème dans la recherche image.");
        return NULL;
    }
    
    while(fgets(fichCourant, 200, fichiersIndexes)!=NULL) {     // On passe chaque ligne du fichier listant les fichiers indexés en revue
        fgets(descCourant, 20000, descripteurs);     // Pour chacune de ces lignes (donc pour chacun de ces fichiers), on récupère le descripteur associé

        if(strcmp(getExtensionOfFile(fichCourant), ".jpg\n")==0 || strcmp(getExtensionOfFile(fichCourant), ".bmp\n")==0) {      // Cas où l'adresse récupérée est celle d'un fichier image (on ne traite que ces cas)
            printf("Fichier courant : %s\n", fichCourant);
            printf("Son descripteur : %s\n", descCourant);
            fprintf(descImages, "%s", descCourant); 
                  
            /*descripteur * desc = toDescripteur(descCourant);     // On convertit son descripteur (jusque là au format string) en structure descripteur
            float sim = comparaisonDescImage(desc, descRequete);        // On calcule la similarité entre le fichier recherché et le fichier courant
            if(sim>=seuil) {        // Cas où le descripteur récupéré a une similarité suffisante avec la recherche
                FICHIER * fcomp = creerCelluleFichier(fichCourant, sim);
                ajouterFichierRecherche(resultats, fcomp);      // On ajoute à la liste triée des fichiers compatibles avec la recherche
            }*/
        }
    }

    fclose(descImages);
    
    printf("Fichier : %s\n");
    rechercher_image("../requete/", fichier, 10);
    printf("Kikou1\n");
    free(descCourant);

    fclose(fichiersIndexes);
    fclose(descripteurs);

    return resultats;
}


RECHERCHE * rechercheParFichierSon (char * fichier) {
    // IMPORTANT : pour les fichiers audio, les résultats de la recherche sont triés par nombre de fenêtres de corpus contenant le jingle et non par similitude 

    // Etape 1 : on crée un descripteur du fichier requête après avoir vérifié son existence 
    FILE * requete = NULL;
    char adresse[64];
    sprintf(adresse, "requete/%s", fichier);

    requete = fopen(adresse, "r");
    DescripteurAudio descRequete;
    if (requete==NULL) {
        /* Affichage de l'erreur */
        displayError("Le fichier à rechercher n'existe pas ou n'a pas pu être ouvert.");
        return NULL;
    } else {

        // Création du descripteur audio 
        int tailleFenetre = getAudioN();        // Taille d'une fenêtre, pour le descripteur
        int nbIntervalles = getAudioM();        // Nombre d'intervalles, pour le descripteur
        int numExt;
        if (strcmp(getExtensionOfFile(fichier),".wav")==0) numExt=1;     // Numéro correspondant au type du fichier, pour le descripteur
        else if (strcmp(getExtensionOfFile(fichier),".bin")==0) numExt=2;
        else numExt=0;
        descRequete = creerDescripteurAudio(requete, tailleFenetre, nbIntervalles, numExt);
        fclose(requete);
    }

    // Etape 2 : on compare ce descripteur à tous les descripteurs sons indexés 
    FILE * fichiersIndexes = NULL;
    FILE * descripteurs = NULL;
    PILE sim = init_PILE();

    fichiersIndexes = fopen("data/descripteurs/fichiersIndexes.txt", "r");
    descripteurs = fopen("data/descripteurs/descripteurs.txt", "r");

    if (fichiersIndexes==NULL || descripteurs==NULL) {      // Vérification de l'ouverture des fichiers
        // Affichage de l'erreur
        displayError("Problème d'accès à la base des descripteurs.");
        return NULL;
    }

    char * fichCourant = malloc(200*sizeof(char));      // Stockage de l'adresse du fichier courant
    char * descCourant = malloc(200000*sizeof(char));     // Stockage du descripteur associé
    
    RECHERCHE * resultats = creerRechercheVide();     // File qui contiendra les résultats de la recherche
    
    while(fgets(fichCourant, 200, fichiersIndexes)!=NULL) {     // On passe chaque ligne du fichier listant les fichiers indexés en revue
        fichCourant[strcspn(fichCourant,"\r\n")] = 0; //Suppression du \n
        
        fgets(descCourant, 200000, descripteurs);     // Pour chacune de ces lignes (donc pour chacun de ces fichiers), on récupère le descripteur associé
        
        if((strcmp(getExtensionOfFile(fichCourant),".wav")==0) || (strcmp(getExtensionOfFile(fichCourant),".bin")==0)) {      // Cas où le descripteur récupéré est celui d'un fichier son (on ne traite que ces cas)
            sprintf(fichCourant,"%s",strrchr(getNameOfFile(fichCourant),'/'));
            DescripteurAudio desc = stringToDescripteurAudio(descCourant);     // On convertit le descripteur (jusque là au format string) en structure descripteur
            sim = comparerDescripteursAudio(descRequete,desc);        // On calcule la similarité entre le fichier recherché et le fichier courant
            //int tps;            // Durée du passage le plus long en commun
            if(taillePILE(sim)>=1) {        // Cas où le descripteur récupéré contient au moins une fois le jingle recherché
                //sim = dePILE(sim, &tps);
                FICHIER * fcomp = creerCelluleFichierSon(fichCourant, sim);
                ajouterFichierRecherche(resultats, fcomp);      // On ajoute à la liste triée des fichiers compatibles avec la recherche
            }
            
        }
    }

    free(descCourant);

    fclose(fichiersIndexes);
    fclose(descripteurs);

    return resultats;
}

//==================================================================================================================================

/*
int main (int argc, char * argv[]) {

    RECHERCHE * r = creerRechercheVide();
    FICHIER * f1 = creerCelluleFichier("Auguste", 50);
    FICHIER * f2 = creerCelluleFichier("Dioclétien", 30);
    FICHIER * f3 = creerCelluleFichier("Trajan", 70);
    FICHIER * f4 = creerCelluleFichier("Gallien", 8);
    FICHIER * f5 = creerCelluleFichier("Constantin", 30);
    FICHIER * f6 = creerCelluleFichier("Septime Sévère", 33);

    ajouterFichierRecherche(r, f6);
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