#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/indexation.h"
#include "../include/audio.h"

#include <dirent.h>
#ifndef WIN32
    #include <sys/types.h>
#endif

#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif


/*==================================================================================================================================*/
/* FONCTIONS DE MANIPULATION DES STRUCTURES */

DESC * initDesc () {         // Crée une cellule descripteur vide
    DESC * d = malloc(sizeof(DESC));
    d->strDesc = NULL;
    d->suivant = NULL;
    return d;
}

DESC * creerDesc (char * str) {       // Crée une cellule descripteur à partir d'une chaîne de caractères
    DESC * d = initDesc();
    d->strDesc = malloc(strlen(str)*sizeof(char));
    d->strDesc = str;
    d->suivant = initDesc();
    d->suivant = NULL;
    return d;
}

PILEDESC * creerPileDescVide () {       // Crée une pile de descripteur vide
    PILEDESC * p = malloc(sizeof(PILEDESC));
    p->premier = initDesc();
    p->premier = NULL;
    p->dernier = initDesc();
    p->dernier = NULL;
    p->nbDesc = 0;
    return p;
}

void ajouterDescPile (PILEDESC * p, DESC * d) {         // Ajoute un descripteur d à la pile de descripteurs p
    if(p->nbDesc==0) {
        p->premier = d;
        p->dernier = d;
        p->nbDesc++;
    } else {
        p->dernier->suivant = d;
        p->dernier = d;
        p->nbDesc++;
    }
}

/*==================================================================================================================================*/



/*==================================================================================================================================*/
/* FONCTIONS UTILITAIRES DIVERSES */

char * extensionFichier (char * nom) {          // Renvoie l'extension du fichier dont le nom ou l'adresse est passé en paramètre
    int i = 0;
    int pospoint = 0;
    while (nom[i]!='\0') {      // On trouve le dernier point de la chaîne
        if (nom[i]=='.') pospoint = i;
        i++;
    }
    char * ext = malloc(5*sizeof(char));
    int k=0;
    for (int j=pospoint+1; j<=i; j++) {
        ext[k]=nom[j];
        k++;
    }
    return ext;
}

int dejaIndexe (char * adrDoc) {        // Dit si le fichier dont l'adresse est passée en paramètre est déjà indexé (0=oui, 1=non)
    FILE * fichiersIndex = NULL;
    fichiersIndex = fopen("data/descripteurs/fichiersIndexes.txt", "r");
    if (fichiersIndex==NULL) {
        displayError("Indexation : impossible d'accéder à l'index des fichiers indexés.");
        return -1;
    }

    int pres = 1;
    char * fichCourant = malloc(200*sizeof(char));
    char * adrDocMod = malloc((1+strlen(adrDoc))*sizeof(char));     // Pour comparer correctement avec les chaînes de caractère récupérées
    sprintf(adrDocMod,"%s\n", adrDoc);      // On rajoute un saut de ligne à la fin de l'adresse (car il y en a dans le fichier)
    while (fgets(fichCourant, 200, fichiersIndex)!=NULL) {
        if(strcmp(adrDocMod, fichCourant)==0) pres=0;
    }

    fclose(fichiersIndex);
    return pres;
}

void displayError(char * msg){          // Affiche un message d'erreur en rouge (récupéré de Clément)
    color("31");
    printf("[ERREUR] %s\n",msg);
    color("0");
}

/*void supprLigneFichiersIndexes (FILE * fichier, int n) {        // Supprime la ligne n du fichier fichiersIndexes
    FILE * temp = NULL;
    fopen ("data/descripteurs/temp.txt", "w+");

    char * ligne = malloc(200*sizeof(char));

}*/

/*==================================================================================================================================*/



/*==================================================================================================================================*/
/* FONCTIONS D'INDEXATION */

void empilementDesDescripteurs (PILEDESC * pileDesc, PILEDESC * adrFichiers) {        // Crée la liste de tous les decripteurs et la met dans la piledesc, avec l'adresse à laquelle ils renvoient dans adrFichiers
    DIR * repDocs = NULL;
    repDocs = opendir("base_de_documents");       // Ouverture du dossier de la base de documents

    if (repDocs==NULL) {       // Cas d'erreur : il n'y a pas de base de documents
        perror("Erreur dans l'ouverture de la base de documents ");
        return;
    }

    struct dirent * fichierLu = NULL;
    while ((fichierLu=readdir(repDocs))!=NULL) {        // On parcourt tous les fichiers du dossier
        
        char * nomDoc = fichierLu->d_name;      // On récupère le nom du fichier i
        //printf("Fichier trouvé : %s \n", nomDoc);
        char * adrDoc = malloc((30+strlen(nomDoc))*sizeof(char));
        sprintf(adrDoc, "base_de_documents/%s", nomDoc);    // Adresse complète du fichier
        //printf("Son adresse : %s \n", adrDoc);
        char * ext = extensionFichier(nomDoc);      // On récupère le type du fichier i
        //printf("Son type : %s \n", ext);
        
        if (strcmp(ext, "xml")==0) {        // Cas d'un fichier texte
            printf("C'est du texte.\n");
            //DescripteurTexte dt = creerDescripteurTexte(adrDoc);
            char * desc = "pates tomates";
            DESC * strDesc = creerDesc(desc);
            ajouterDescPile(pileDesc, strDesc);
            DESC * adr = creerDesc(adrDoc);
            ajouterDescPile(adrFichiers, adr);
        }
        if (strcmp(ext, "wav")==0 || strcmp(ext, "bin")==0) {       // Cas d'un fichier audio
            printf("C'est du son.\n");
            //DescripteurSon ds = creerDescripteurSon(adrDoc);
            char * desc = "flatulences malpoli";
            DESC * strDesc = creerDesc(desc);
            ajouterDescPile(pileDesc, strDesc);
            DESC * adr = creerDesc(adrDoc);
            ajouterDescPile(adrFichiers, adr);
        }
        if (strcmp(ext, "jpg")==0 || strcmp(ext, "bmp")==0) {       // Cas d'une image
            printf("C'est une image.\n");
            /*DescripteurImage di = creerDescripteurImage(adrDoc);
            char * desc = convertionDescripteurImageString(di);
            DESC * strDesc = creerDesc(desc);
            ajouterDescPile(pileDesc, strDesc);*/
            DESC * adr = creerDesc(adrDoc);
            ajouterDescPile(adrFichiers, adr);
        }
    }

    closedir(repDocs);
}

void indexationTotale () {          // Fait l'indexation totale de la base de documents en supprimant l'indexation précédente

    /* Ouverture des fichiers qui contiendront les descripteurs et la liste des fichiers indexés, en supprimant leur contenu précédent */
    FILE * indexDesc = NULL;
    FILE * fichiersIndex = NULL;
    indexDesc = fopen("data/descripteurs/descripteurs.txt", "w+");
    fichiersIndex = fopen("data/descripteurs/fichiersIndexes.txt", "w+");

    /* Vérification de l'ouverture correcte des fichiers */
    if (indexDesc==NULL || fichiersIndex==NULL) {
        displayError("Indexation : impossible d'accéder aux fichiers de descripteurs.");
        return;
    }

    /* Création de la pile de descripteurs et de la pile d'adresses */
    PILEDESC * pDesc = creerPileDescVide();         // Pile de descripteurs
    PILEDESC * pAdr = creerPileDescVide();          // Pile d'adresses
    empilementDesDescripteurs(pDesc, pAdr);

    /* Impression des descripteurs dans le fichier de descripteurs */
    DESC * courant = pDesc->premier;
    for (int i=0; i<pDesc->nbDesc; i++) {
        fprintf(indexDesc, "%s\n", courant->strDesc);
        courant=courant->suivant;
    }

    /* Impression de la liste des fichiers indexés */
    courant = pAdr->premier;
    for (int i=0; i<pAdr->nbDesc; i++) {
        fprintf(fichiersIndex, "%s\n", courant->strDesc);
        courant=courant->suivant;
    }

    /* Fermeture des fichiers */
    fclose(indexDesc);
    fclose(fichiersIndex);
}

void indexationUnique (char * adrDoc) {         // Indexe un unique document à partir de son adresse donnée en paramètre
    
    /* On vérifie que le fichier n'est pas déjà indexé */
    if(dejaIndexe(adrDoc)==0) {
        displayError("Fichier déjà indexé.");
        return;
    }

    /* Ouverture des fichiers qui contiendront le descripteur et l'adresse du fichier indexé */
    FILE * indexDesc = NULL;
    FILE * fichiersIndex = NULL;
    indexDesc = fopen("data/descripteurs/descripteurs.txt", "r+");
    fichiersIndex = fopen("data/descripteurs/fichiersIndexes.txt", "r+");

    /* Vérification de l'ouverture correcte des fichiers */
    if (indexDesc==NULL || fichiersIndex==NULL) {
        displayError("Indexation : impossible d'accéder aux fichiers de descripteurs.");
        return;
    }

    /* On se positionne à la fin du fichier pour ne pas réécrire des lignes */
    fseek(indexDesc, 0, SEEK_END);
    fseek(fichiersIndex, 0, SEEK_END);

    /* Création du descripteur associé au fichier puis indexation dans les deux fichiers */
    char * ext = extensionFichier(adrDoc);
    if (strcmp(ext, "xml")==0) {
        // DescripteurTexte dt = creerDescripteurTexte(adrDoc);
        char * strDt = "Blabla patatipatata";
        fprintf(indexDesc, "%s\n", strDt);
        fprintf(fichiersIndex, "%s\n", adrDoc);
    }
    if (strcmp(ext, "wav")==0 || strcmp(ext, "bin")==0) {
        // DescripteurSon ds = creerDescripteurSon(adrDoc);
        char * strDs = "Tagada tsointsoin";
        fprintf(indexDesc, "%s\n", strDs);
        fprintf(fichiersIndex, "%s\n", adrDoc);
    }
    if (strcmp(ext, "jpg")==0 || strcmp(ext, "bmp")==0) {
        // DescripteurTexte di = creerDescripteurImage(adrDoc);
        char * strDi = "Image";
        fprintf(indexDesc, "%s\n", strDi);
        fprintf(fichiersIndex, "%s\n", adrDoc);
    }

    fclose(indexDesc);
    fclose(fichiersIndex);
}

void suppressionOrphelins () {      // Supprime les fichiers indexés qui n'existent plus
    
    /* Ouverture et vérification de l'ouverture du fichier fichiersIndexes.txt */
    FILE * fichiersIndex = NULL;
    fichiersIndex = fopen("data/descripteurs/fichiersIndexes.txt", "r+");
    if (fichiersIndex==NULL) {
        displayError("Indexation : impossible d'accéder à la liste des fichiers indexés.");
        return;
    }
    
    /* Pour chaque ligne du fichier, on tente d'ouvrir le fichier associé, si ce n'est pas possible c'est qu'il n'existe pas */
    FILE * courant = NULL;
    char * fichCourant = malloc(200*sizeof(char));
    while (fgets(fichCourant, 200, fichiersIndex)!=NULL) {
        int i=0;
        while(fichCourant[i]!='\n') i++;
        fichCourant[i]='\0';                // Suppression du saut de ligne à la fin de l'adresse
        courant = fopen(fichCourant, "r");
        if (courant==NULL) {
            fprintf(fichiersIndex, "NULL");
        } else {
            fclose(courant);
            courant = NULL;
        }
    }
    
    fclose(fichiersIndex);
} 

void indexationAutomatique () {

    FILE * indexDesc = NULL;
    FILE * fichiersIndex = NULL;
    indexDesc = fopen("data/descripteurs/descripteurs.txt", "r+");
    fichiersIndex = fopen("data/descripteurs/fichiersIndexes.txt", "r+");

    if (indexDesc==NULL || fichiersIndex==NULL) {
        /* Cas où les fichiers n'existent pas : on fait une indexation totale */
        indexationTotale();
    } else if(fgetc(fichiersIndex)==EOF || fgetc(indexDesc)==EOF) {
        /* Cas où les fichiers sont vides : on fait une indexation totale */
        fclose(indexDesc);
        fclose(fichiersIndex);
        indexationTotale();
    } else {
        /* Cas où il y a des fichiers indexés : on supprime les descripteurs orphelins */
        fclose(indexDesc);
        fclose(fichiersIndex);
        suppressionOrphelins();
    }
}

/*==================================================================================================================================*/


int main (int argc, char * argv[]) {
    indexationAutomatique();
}
