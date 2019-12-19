#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/indexation.h"
#include "../include/audio.h"

#include <dirent.h>
/*#ifndef WIN32
    #include <sys/types.h>
#endif*/

DESC * initDesc () {         // Crée une cellule descripteur vide
    DESC * d = malloc(sizeof(DESC));
    d->strDesc = NULL;
    d->suivant = NULL;
    return d;
}

DESC * creerDesc (char * str) {       // Crée une cellule descripteur à partir d'une chaîne de caractères
    DESC * d = initDesc();
    d->strDesc = str;
    return d;
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

char * extensionFichier (char * nom) {
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


void indexation (PILEDESC * p) {        // Crée la liste de tous les decripteurs et la met dans la piledesc
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
        char adrDoc[50];
        sprintf(adrDoc, "base_de_documents/%s", nomDoc);    // Adresse complète du fichier
        //printf("Son adresse : %s \n", adrDoc);
        char * ext = extensionFichier(nomDoc);      // On récupère le type du fichier i
        //printf("Son type : %s \n", ext);
        
        if (strcmp(ext, "xml")==0) {        // Cas d'un fichier texte
            printf("C'est du texte.\n");
            /*DescripteurTexte dt = creerDescripteurTexte(adrDoc);
            char * desc = convertionDescripteurTexteString(dt);
            DESC * strDesc = creerDesc(desc);
            ajouterDescPile(p, strDesc);*/
        }
        if (strcmp(ext, "wav")==0 || strcmp(ext, "bin")==0) {       // Cas d'un fichier audio
            printf("C'est du son.\n");
            /*DescripteurSon ds = creerDescripteurSon(adrDoc);
            char * desc = convertionDescripteurSonString(ds);
            DESC * strDesc = creerDesc(desc);
            ajouterDescPile(p, strDesc);*/
        }
        if (strcmp(ext, "jpg")==0 || strcmp(ext, "bmp")==0) {       // Cas d'une image
            printf("C'est une image.\n");
            /*DescripteurImage di = creerDescripteurImage(adrDoc);
            char * desc = convertionDescripteurImageString(di);
            DESC * strDesc = creerDesc(desc);
            ajouterDescPile(p, strDesc);*/
        }
    }

    closedir(repDocs);
}


int main (int argc, char * argv[]) {
    PILEDESC * p = creerPileDescVide();
    DESC * d = creerDesc("Prout");
    ajouterDescPile(p, d);
    indexation(p);
}
