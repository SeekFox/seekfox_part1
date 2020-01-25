#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/texte.h"
#include "../include/config.h"

typedef struct listeMots{
    char * mot;
    int nbOccurence;
    struct listeMots * next;
}listeMots_s;

typedef struct descripteurTexte{
    char * name;
    int nbMots;
    ListeMots liste;
}descripteurTexte_s;

DescripteurTexte initDescripteurTexte(){
    DescripteurTexte dt = (DescripteurTexte)malloc(sizeof(DescripteurTexte));
    dt->name = (char*)malloc(sizeof(char));
    strcpy(dt->name,"");
    dt->liste=initListeMots();
    dt->nbMots=0;

    return dt;
}

ListeMots initListeMots(){
    return NULL;
}

ListeMots ajoutMot(ListeMots liste, char * mot){
    int motAjoute = 0;
    ListeMots lm = liste;
    //Parcours de la liste à la recherche du mot
    while(lm!=NULL){
        if(strcmp(lm->mot,mot)==0){
            lm->nbOccurence++;
            motAjoute=1;
            break;
        }else{
            lm=lm->next;
        }
    }

    lm = liste;

    if(!motAjoute){
        //printf("Nouvel element \"%s\"\n",mot);
        lm=(ListeMots)malloc(sizeof(struct listeMots));
        lm->mot=(char*)malloc(sizeof(char)*strlen(mot));
        strcpy(lm->mot,mot);
        lm->nbOccurence=1;
        lm->next=liste;
    }

    return lm;
}

void afficheDescripteur(DescripteurTexte descripteur){
    printf("==AFFICHAGE Descripteur==\n");
    printf("Fichier         : %s\n",descripteur->name);
    printf("Nombre de mots  : %d mots\n",descripteur->nbMots);
    afficheListeMot(descripteur->liste);
}

void afficheListeMot(ListeMots liste){
    ListeMots lm = liste;
    printf("LISTEMOTS\n");
    while(lm!=NULL){
        printf("\t%-30s %d\n",lm->mot,lm->nbOccurence);
        
        lm=lm->next;
    }
    free(lm);
}

int getNbMotsDescripteurTexte(DescripteurTexte descripteur){
    if(descripteur==NULL) return 0;
    if(descripteur->liste==NULL) return 0;

    int nbMots = 0;
    ListeMots lm = descripteur->liste;

    while(lm!=NULL){
        nbMots+=lm->nbOccurence;
        lm=lm->next;
    }
    free(lm);
    return nbMots;
}

char * getNameDescripteurTexte(DescripteurTexte descripteur){
    return descripteur->name;
}

DescripteurTexte lireFichierTexte(char * file){
    DescripteurTexte descripteur = initDescripteurTexte();
    descripteur->name = (char*)malloc(sizeof(char)*strlen(file));
    strcpy(descripteur->name,file);
    
    ListeMots liste = initListeMots();
    FILE * fichier = NULL;
    char * str = (char*)malloc(sizeof(char)*TAILLEMAXMOT);
    char c;


    fichier = fopen(file, "r");

    if(fichier!=NULL){
        do{
            c = fgetc(fichier);
            //Fin de fichier
            if(c==EOF) break; 

            //Caractere non voulus
            if(c==','||c==':'||c=='!'||c=='\''||c=='?'||c=='.'||c==';') continue; 

            //Ajout d'un mot
            if(c==' '){
                if(strlen(str)>=getTailleMin()){
                    //printf("%s\n",str);
                    liste=ajoutMot(liste,str);
                } 
                
                //printf("%s\n",str);
                strcpy(str,"");
            }else if(c=='<'){
                while(c!='>') c=fgetc(fichier);
            }else{   //Supression des balises
                sprintf(str,"%s%c",str,c);  
            } 
        }while(c!=EOF);

        fclose(fichier);
    
    }else{
        printf("Le fichier \"%s\" n'exite pas\n",file);
        return NULL;
    }

    descripteur->liste = epurerListe(liste);
    descripteur->nbMots=getNbMotsDescripteurTexte(descripteur);
    return descripteur;
    
}

char * descripteurTexteToString(DescripteurTexte descripteur){
    char * str = (char*)malloc(sizeof(char)*strlen(descripteur->name) + sizeof(int) + 4);
    strcpy(str,"");
    sprintf(str,"[%s;%d]",descripteur->name,descripteur->nbMots);

    ListeMots lm = descripteur->liste;
    while(lm!=NULL){
        if((lm->nbOccurence)>=getSeuil()){
            str = (char*) realloc(str,sizeof(char)*strlen(str)+  (sizeof(char)*strlen(lm->mot) + sizeof(int) + 4));
            sprintf(str,"%s{%s;%d}",str,lm->mot,lm->nbOccurence);
        }
        
        lm=lm->next;
    }

    str = (char*) realloc(str,sizeof(char)*strlen(str));
    sprintf(str,"%s!",str);
    free(lm);
    return str;
}

ListeMots ajoutMotEtNbOccur(ListeMots liste, char * mot, int nbOccur){
    int motAjoute = 0;
    ListeMots lm = liste;
    //Parcours de la liste à la recherche du mot
    while(lm!=NULL){
        lm=lm->next;
    }

    lm = liste;

    if(!motAjoute){
        //printf("Nouvel element \"%s\"\n",mot);
        lm=(ListeMots)malloc(sizeof(struct listeMots));
        lm->mot=(char*)malloc(sizeof(char)*strlen(mot));
        strcpy(lm->mot,mot);
        lm->nbOccurence=nbOccur;
        lm->next=liste;
    }

    return lm;
}

DescripteurTexte StringTodescripteurText(char * str){
    DescripteurTexte descripteur = initDescripteurTexte();
    ListeMots liste = initListeMots();

    char * chaine = (char*)malloc(sizeof(char)*TAILLEMAXMOT);
    strcpy(chaine,"");
    char c;

    char * mot; 
    int nbOccur;

    int i=0;

    while(str[i]!='!'&&str[i]!=EOF){
        c=str[i];
        
        if(c==EOF) break;

        //en tête du descripteur
        if(c=='['){
           do{
                i++;
                c=str[i];
                sprintf(chaine,"%s%c",chaine,c);
                if(c==';'){
                    strncpy(descripteur->name,chaine,strlen(chaine)-1);
                    strcpy(chaine,"");
                }
                if(c==']'){
                    descripteur->nbMots=atoi(chaine);
                    strcpy(chaine,"");
                }
                
                
            }while(c!=']');
        }

        //Contenu du descripteur
        if(c=='{'){
            //Récuperation d'un mot
            do{
                i++;
                c=str[i];
                sprintf(chaine,"%s%c",chaine,c);
                //Mot
                if(str[i+1]==';'){
                    mot=(char*)malloc(sizeof(char)*strlen(chaine));
                    strcpy(mot,chaine);
                    strcpy(chaine,"");
                    i++;
                }
                //Nombre d'occurence
                if(c=='}'){
                    nbOccur=atoi(chaine);
                    strcpy(chaine,"");
                    //Ajout du mot à la liste
                    liste=ajoutMotEtNbOccur(liste,mot,nbOccur);
                }    
            }while(c!='}');
        }
        i++;
    }

    descripteur->liste=liste;
    free(liste);
    return descripteur;
}

float comparerDescripteurTexte(DescripteurTexte desc1, DescripteurTexte desc2){
    int nbMotsEnCommun=0;
    ListeMots l1 = desc1->liste;
    ListeMots l2 = desc2->liste;

    if(desc1->nbMots==0||desc2->nbMots==0) return 0; 

    while(l1!=NULL){
        while(l2!=NULL){
            //printf("\t%s / %s\n",l1->mot, l2->mot);
            if(strcmp(l1->mot, l2->mot)==0){
                nbMotsEnCommun+=l1->nbOccurence+l2->nbOccurence;
            }
            l2=l2->next;
        }
        l2 = desc2->liste;
        l1=l1->next;
    }

    free(l1);
    free(l2);
    return ((float)nbMotsEnCommun)/((float)(desc1->nbMots + desc2->nbMots))*100;
}

ListeMots epurerListe(ListeMots l){
    ListeMots lm = initListeMots();

    while(l!=NULL){
        if((l->nbOccurence)>=getSeuil()){
            lm = ajoutMotEtNbOccur(lm,l->mot,l->nbOccurence);
        }
        
        l=l->next;
    }
    free(l);
    return lm;
}