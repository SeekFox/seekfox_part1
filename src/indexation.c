/**
 * @file indexation.c
 * @author Etienne Combelles
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/indexation.h"
#include "../include/audio.h"
#include "../include/header_image.h"
#include "../include/descripteur_txt.h"

#ifndef __INTERACT__
    #include "../include/interact.h"
#endif

#ifndef __CONFIG__
    #include "../include/config.h"
#endif

#include "../include/audio.h"


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

int isFileExist(char * adrDoc){
    FILE * fichier = NULL;
    //printf("\t >> >%s<\n",adrDoc);
    fichier = fopen(adrDoc,"r");
    if(fichier==NULL){
        return 0;
    }
    fclose(fichier);
    return 1;
}

int dejaIndexe (char * adrDoc) {        // Dit si le fichier dont l'adresse est passée en paramètre est déjà indexé (0=oui, 1=non)
    FILE * fichiersIndex = NULL;
    //printf("\t >> >%s<\n",adrDoc);
    fichiersIndex = fopen("data/descripteurs/fichiersIndexes.txt", "r");
    if (fichiersIndex==NULL) {
        displayError("Indexation : impossible d'accéder à l'index des fichiers indexés.");
        return -1;
    }

    int pres = 1;
    char * fichCourant = malloc(200*sizeof(char));
   
    while (fgets(fichCourant, 200, fichiersIndex)!=NULL) {
        fichCourant[strcspn(fichCourant,"\r\n")] = 0; //Suppression du \n
        //printf("<%s> && <%s>\n",adrDoc,fichCourant);
        if(strcmp(adrDoc, fichCourant)==0) pres=0;
    }

    fclose(fichiersIndex);
    return pres;
}

int nbLignesFichier (char * adr_fic) {      // Renvoie le nombre de lignes du fichier passé en paramètre
    char * commande = malloc((20+strlen(adr_fic))*sizeof(char));
    sprintf(commande, "wc -l %s > data/descripteurs/temp", adr_fic);     // On fait la commande
    system(commande);       // Exécution de la commande
    FILE * temp = NULL;
    temp = fopen ("data/descripteurs/temp", "r+");       // Ouverture du fichier créé par la commande
    if(temp==NULL) {
        displayError("Problème dans l'exécution du script. \n");
        return 0;
    }
    char * nbLc = malloc(5*sizeof(char));   // char * qui contiendra le nombre de lignes mais au format char
    char courant;
    int i=0;
    do      // On récupère les chiffres jusqu'au premier espace
    {
        courant = fgetc(temp);
        nbLc[i] = courant;
        i++;
    } while (courant!=' ');
    
    int nbLi = atoi(nbLc);      // On convertit au format int
    fclose(temp);
    remove("data/descripteurs/temp");
    return nbLi;
}

void supprLignesIndex (int * lignasuppr) {        // Supprime la ligne n du fichier fichiersIndexes
    /* NOTE : les descripteurs ne sont pas réellement supprimés, pour éviter d'endommager les autres */

    /* Création des fichiers avec les lignes supprimées */
    FILE * tempIndex = NULL;
    tempIndex = fopen("data/descripteurs/tempIndex.txt", "w+");

    /* Ouverture des fichiers contenant les lignes à supprimer */
    FILE * index = NULL;
    index = fopen("data/descripteurs/fichiersIndexes.txt", "r+");

    if (tempIndex==NULL || index==NULL) {
        displayError("Suppression des lignes de l'index impossible.");
        return;
    }

    int lCourante = 0;
    int i = 0;
    char * ligne = malloc(200*sizeof(char));

    while(fgets(ligne, 200, index)!=NULL) {
        if(lignasuppr[i]!=lCourante) {
            fprintf(tempIndex, "%s", ligne);
        } else {
            fprintf(tempIndex, "NA\n");
            i++;
        }
        lCourante++;
    }

    fclose(index);
    fclose(tempIndex);

    remove("data/descripteurs/fichiersIndexes.txt");
    rename("data/descripteurs/tempIndex.txt", "data/descripteurs/fichiersIndexes.txt");

}

char * moveFileInBDB(char * adrDoc){
    char * adrDocOnBDB = (char*)malloc(24*sizeof(char) + strlen(adrDoc));
    if(strncmp("base_de_documents",adrDoc,strlen("base_de_documents") )!=0){
        sprintf(adrDocOnBDB,"base_de_documents/%s", adrDoc);
        rename(adrDoc,adrDocOnBDB);
        return adrDocOnBDB;
    }
    return adrDoc;    
}

void displayFichierIndexes(){
    FILE * fichier = NULL;
    char line[64];
    char * file;

    fichier = fopen("data/descripteurs/fichiersIndexes.txt","r");

    if(fichier == NULL){
        displayError("Le fichier fichiersIndexes.txt n'existe pas.");
        return;
    }else{
        color("36");
        while(fgets(line, 64,fichier)!=NULL){
            file = strtok(line,"/");
            file = strtok(NULL,"/");
            printf("  > %s",file);    
        }
        color("37");
    }    
}

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
        char * adrDoc = malloc((30+strlen(nomDoc))*sizeof(char));
        sprintf(adrDoc, "base_de_documents/%s", nomDoc);    // Adresse complète du fichier
        char * ext = getExtensionOfFile(nomDoc);      // On récupère le type du fichier i
        
        /*if (strcmp(ext, ".xml")==0) {        // Cas d'un fichier texte
            // DescripteurTexte dt = creerDescripteurTexte(adrDoc);
            FILE * f = NULL;
            f = fopen(adrDoc, "r+");
            DESCTXT dt = creerDescripteur_txt(f);
            char * desc = descToString(dt);          
            //char * desc = "Texte";
            DESC * strDesc = creerDesc(desc);
            ajouterDescPile(pileDesc, strDesc);
            DESC * adr = creerDesc(adrDoc);
            ajouterDescPile(adrFichiers, adr);
        }*/
        if (strcmp(ext, ".bin")==0) {                               // Cas d'un fichier audio
        //if (strcmp(ext, ".wav")==0 || strcmp(ext, ".bin")==0) {       
            //printf("C'est du son.\n");

            DescripteurAudio ds = creerDescripteurAudio(fopen(adrDoc,"r"),getAudioN(),getAudioM(),((strcmp(ext, ".wav")==0)?WAV_FILE:BIN_FILE));

            //char * desc = "Audio";
            char * desc = descripteurAudioToString(ds);

            DESC * strDesc = creerDesc(desc);
            ajouterDescPile(pileDesc, strDesc);
            DESC * adr = creerDesc(adrDoc);
            ajouterDescPile(adrFichiers, adr);
        }
        if (strcmp(ext, ".jpg")==0 || strcmp(ext, ".bmp")==0) {       // Cas d'une image
            //printf("C'est une image.\n");
            descripteur di;
            int taille_max=0;
            generer_descripteur(&di, "base_de_documents/", nomDoc, &taille_max, getNbBits());
            char * desc = malloc(1500*sizeof(char));
            descripteur_image_to_string(di, desc, taille_max);
            //descripteur di = creerDescripteurImage(adrDoc);
            //char * desc = convertionDescripteurImageString(di);
            DESC * strDesc = creerDesc(desc);
            ajouterDescPile(pileDesc, strDesc);
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
    
    printf("\nIndexation du fichier en cours...\n");

    if(!isFileExist(adrDoc)){
        displayError("Le fichier n'existe pas.");
        return;
    }

    strcpy(adrDoc,moveFileInBDB(adrDoc));
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
    char * ext = getExtensionOfFile(adrDoc);
    if (strcmp(ext, ".xml")==0) {
        // DescripteurTexte dt = creerDescripteurTexte(adrDoc);
        char * strDt = "Texte";
        fprintf(indexDesc, "%s\n", strDt);
        fprintf(fichiersIndex, "%s\n", adrDoc);
    }
    if (strcmp(ext, ".bin")==0) {
    //if (strcmp(ext, ".wav")==0 || strcmp(ext, ".bin")==0) {
        DescripteurAudio ds = creerDescripteurAudio(fopen(adrDoc,"r"),getAudioN(),getAudioM(),((strcmp(ext, ".wav")==0)?WAV_FILE:BIN_FILE));

        //char * strDs = "Audio";
        char * strDs = descripteurAudioToString(ds);
        fprintf(indexDesc, "%s\n", strDs);
        fprintf(fichiersIndex, "%s\n", adrDoc);
    }
    if (strcmp(ext, ".jpg")==0 || strcmp(ext, ".bmp")==0) {
        // DescripteurImage di = creerDescripteurImage(adrDoc);
        char * strDi = "Image";
        fprintf(indexDesc, "%s\n", strDi);
        fprintf(fichiersIndex, "%s\n", adrDoc);
    }

    fclose(indexDesc);
    fclose(fichiersIndex);

    color("32");
    printf("L'indexation a ete effectuee !\n\n");
    color("37");
}

void suppressionOrphelins () {      // Supprime les fichiers indexés qui n'existent plus
    
    /* Ouverture et vérification de l'ouverture du fichier fichiersIndexes.txt */
    FILE * fichiersIndex = NULL;
    fichiersIndex = fopen("data/descripteurs/fichiersIndexes.txt", "r+");
    if (fichiersIndex==NULL) {
        displayError("Indexation : impossible d'accéder à la liste des fichiers indexés.");
        return;
    }

    /* Tableau qui contiendra les numéros des lignes des descripteurs orphelins */
    int * lignasuppr = malloc(nbLignesFichier("data/descripteurs/fichiersIndexes.txt")*sizeof(int));
    int nbL = 0;
    
    /* Pour chaque ligne du fichier, on tente d'ouvrir le fichier associé, si ce n'est pas possible c'est qu'il n'existe pas */
    FILE * courant = NULL;
    char * fichCourant = malloc(200*sizeof(char));
    int lCourante = 0;
    while (fgets(fichCourant, 200, fichiersIndex)!=NULL) {
        fichCourant[strcspn(fichCourant,"\r\n")] = 0; // Suppression du saut de ligne à la fin de l'adresse

        courant = fopen(fichCourant, "r");
        if (courant==NULL) {
            lignasuppr[nbL] = lCourante;
            nbL++;
        } else {
            fclose(courant);
            courant = NULL;
        }
        lCourante++;
    }
    
    fclose(fichiersIndex);
    supprLignesIndex(lignasuppr);
} 

void indexationAutomatique () {

    FILE * indexDesc = NULL;
    FILE * fichiersIndex = NULL;
    indexDesc = fopen("data/descripteurs/descripteurs.txt", "r+");
    fichiersIndex = fopen("data/descripteurs/fichiersIndexes.txt", "r+");

    //printf("Mise à jour de la base de descripteurs...\n");
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
    //printf("Mise à jour réussie !\n");
}

void displayDescripteur(char * fichier){
    /* Ouverture des fichiers qui contiendront les descripteurs et la liste des fichiers indexés, en supprimant leur contenu précédent */
    //FILE * indexDesc = NULL;
    FILE * fichiersIndex = NULL;
    char chaine[128] ="";

    int compteur = 0;

    //indexDesc = fopen("data/descripteurs/descripteurs.txt", "r");
    fichiersIndex = fopen("data/descripteurs/fichiersIndexes.txt", "r");

    /* Vérification de l'ouverture correcte des fichiers */
    if (fichiersIndex==NULL) {
    //if (indexDesc==NULL || fichiersIndex==NULL) {
        displayError("Indexation : impossible d'accéder aux fichiers de descripteurs.");
        return;
    }
    //On parcours le fichier fichiersIndexes
    if (fichiersIndex != NULL){
        while (fgets(chaine, 64, fichiersIndex) != NULL){ // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
            chaine[strcspn(chaine,"\r\n")] = 0; //Suppression du \n
            if(strcmp(chaine,fichier)==0){
                break;
            }
            compteur++;
        }
        fclose(fichiersIndex);
        
    }
    sprintf(chaine,"sed -n %dp data/descripteurs/descripteurs.txt > data/descripteurs/descripteur.txt; %s data/descripteurs/descripteur.txt",compteur+1,getLogicielTexte());
    system(chaine);
}