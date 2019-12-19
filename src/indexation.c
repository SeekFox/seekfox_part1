#include <stdio.h>
#include <stdlib.h>
#include "../include/indexation.h"
#include "../include/audio.h"

#include <dirent.h>
#ifndef WIN32
    #include <sys/types.h>
#endif

DESC * initDesc () {         // Crée une cellule descripteur vide
    DESC * d = malloc(sizeof(DESC));
    d->strDesc = NULL;
    d->suivant = NULL;
    return d;
}

void creerDesc (char * str) {       // Crée une cellule descripteur à partir d'une chaîne de caractères
    DESC * d = initDesc();
    d->strDesc = str;
}

PILEDESC * creerPileDescVide () {       // Crée une pile de descripteur vide
    PILEDESC * p = malloc(sizeof(PILEDESC));
    p->premier = NULL;
    p->dernier = NULL;
    p->nbDesc = 0;
    return p;
}

void ajouterDescPile (PILEDESC * p, DESC * d) {
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




void indexationAudio () {
    FILE * descAudio = NULL;
    descAudio = fopen ("../data/descripteurs/descripteursAudio.txt", "r+");     // Ouverture du fichier qui contiendra les descripteurs
    DIR * repAudio = NULL;
    rep = opendir(../base_de_documents/audio/);     // Ouverture du dossier audio de la base de documents
    
    if (descAudio==NULL || repAudio==NULL) {        // Cas d'erreur : il n'y a pas de fichier de descripteurs
        printf("Erreur : indexation des fichiers audio impossible, vérifiez la présence du fichier de descripteurs et du dossier contenant les fichiers audio.\n");
        return;
    }
    if (repAudio==NULL) {       // Cas d'erreur : il n'y a pas de base de documents audios
        perror("Erreur dans l'ouverture de la base de documents (base_de_documents/audio) ");
        return;
    }

    struct dirent * fichierLu = NULL;
    while ((fichierLu=readdir(rep))!=NULL) {

    }

    fclose(descAudio);
    closedir(repAudio);
}