/**
 * @file config.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
 * @version 0.2
 * @date 23/12/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
#include <math.h>

#ifndef __CONFIG__
    #include <../include/config.h>
#endif

#ifndef __INTERACT__
    #include <../include/interact.h>
#endif

/**
 * @brief Structure de Configuration
 * 
 * GENERAL
 *  passwordAdmin           : Mot de passe administrateur chiffre
 * TEXTE
 *  tailleMin               : La taille minimun pour qu'un mot soit regardé
 *  val                     : Les x mots les plus presents
 *  seuil                   : Les mots qui apparaissent plus de x fois
 * AUDIO
 *  audio_n                 : Fenetre d'analyse 
 *  audio_m                 : Nombre d'intervalles de la fenetre d'analyse
 * 
 */
struct config_s{
    //General
    char passwordAdmin[32];

    //Texte
    int tailleMin;
    int val;
    int seuil;

    //Audio
    int audio_n;
    int audio_m;
};

//Getter
char * getPasswordAdmin(){
    return (config->passwordAdmin);
}

int getTailleMin(){
    return (config->tailleMin);
}

int getVal(){
    return (config->val);
}

int getSeuil(){
    return (config->seuil);
}

int getAudioN(){
    return (config->audio_n);
}

int getAudioM(){
    return (config->audio_m);
}

//Setter
void setPasswordAdmin(Config *c, char * pwd){
    strcpy((*c)->passwordAdmin,pwd);
}

void setTailleMin(Config *c, int tailleMin){
    (*c)->tailleMin=tailleMin;
}

void setVal(Config *c, int val){
    (*c)->val=val;
}

void setSeuil(Config *c, int seuil){
    (*c)->seuil=seuil;
}

void setAudioN(Config *c, int n){
    (*c)->audio_n = n;
}

void setAudioM(Config *c, int m){
    (*c)->audio_m = m;
}

Config loadConfig(){
    Config c = (Config)malloc(sizeof(struct config_s));
    FILE * fichier = NULL;
    char line[64] = "";
    int i = 0;

    fichier = fopen("data/user.config","r");
    if(fichier!=NULL){
        while (fgets(line, 64, fichier) != NULL){
            line[strcspn(line,"\r\n")] = 0; //Suppression du \n
            //printf("\t<<%s>>\n",line);
            switch (i){
                case 0:
                    setPasswordAdmin(&c,line);
                    break;

                case 1:
                    setTailleMin(&c,atoi(line));
                    break;

                case 2:
                    setVal(&c,atoi(line));
                    break;

                case 3:
                    setSeuil(&c,atoi(line));
                    break;

                case 4:
                    setAudioN(&c,atoi(line));
                    break;

                case 5:
                    setAudioM(&c,atoi(line));
                    break;

                
                default:
                    break;
            }
            i++;

        }
        fclose(fichier);
    }else{
        displayError("Fichier de config inexistant");
        exit(-1);
    }

    return c;
}

void displayConfig(){
    printTitle("CONFIGURATIONS");

    printf("TEXTE \n");
    printf("\tTaille minimun d'un mot              ");
    color("1");
    printf("%d\n",getTailleMin(config));
    color("0");
    printf("\tValeur limite de mots                ");
    color("1");
    printf("%d\n",getVal(config));
    color("0");
    printf("\tSeuil limite de taille de mot        ");
    color("1");
    printf("%d\n",getSeuil(config));
    color("0");

    printf("AUDIO \n");
    printf("\tTaille de la fenetre d'analyse       ");
    color("1");
    printf("%d\n",getAudioN(config));
    color("0");
    printf("\tNombre d'intervalles                 ");
    color("1");
    printf("%d\n",getAudioM(config));
    color("0");
    printf("\n");
}   

void changePassword(){
    char pwd[32] = "";
    char confirm_pwd[32] = "";
    char ch;

    printf("Entrez le nouveau mot de passe\n");

    for (;;){ //Recuperation du mot de passe 
      ch = getch();
      if(ch == '\n' || strlen(pwd)>31){ //Verifier que le mot de passe ne soit pas trop long OU que l'user ne presse pas le bouton entrer
        break;
      }else{
        printf("*"); //Masquage du mot de passe
        sprintf(pwd,"%s%c",pwd,ch); //Ajout du nouveau caractere dans password
      }
    }
    printf("\nConfirmez le mot de passe\n");

    for (;;){ //Recuperation du mot de passe 
      ch = getch();
      if(ch == '\n' || strlen(confirm_pwd)>31){ //Verifier que le mot de passe ne soit pas trop long OU que l'user ne presse pas le bouton entrer
        break;
      }else{
        printf("*"); //Masquage du mot de passe
        sprintf(confirm_pwd,"%s%c",confirm_pwd,ch); //Ajout du nouveau caractere dans password
      }
    }
    //les mots de passes sont identiques ?
    if(strcmp(pwd,confirm_pwd)==0){
        strcpy(config->passwordAdmin,(char*)crypt(pwd,"456b7016a916a4b178dd72b947c152b7"));
        color("32");
        printf("\nVotre mot de passe a bien ete modifie !\n\n");
        color("37");
        //on met a jour le fichier user.config
        majConfigFile();
    }else{
        displayError("Les mots de passe ne sont pas identiques.\n");
    }
}

void changeTailleMin(){
    int n;
    printf("Entrez la nouvelle taille minimun d'un mot.\n");
    scanf("%d",&n);
    CLEAR_STDIN

    if(n>=3){    //n superieur ou egale a 3
        config->audio_n=n;
        color("32");
        printf("\nLa taille minimun d'un mot a bien ete modifie !\n\n");
        color("37");
        //on met a jour le fichier user.config
        majConfigFile();
    }else{
        displayError("La taille minimun d'un mot doit etre superieur ou egal a 3\n");
    }
}

void changeVal(){
    int n;
    printf("Entrez la nouvelle valeur limite de mots.\n");
    scanf("%d",&n);
    CLEAR_STDIN

    if(n>0){    //n positif
        config->audio_n=n;
        color("32");
        printf("\nLa tvaleur limite de mots a bien ete modifie !\n\n");
        color("37");
        //on met a jour le fichier user.config
        majConfigFile();
    }else{
        displayError("La valeur limite de mots doit etre positive.\n");
    }
}

void changeSeuil(){
    int n;
    printf("Entrez la nouvelle valeur de seuil de taille de mot.\n");
    scanf("%d",&n);
    CLEAR_STDIN

    if(n>0){    //n positif
        config->audio_n=n;
        color("32");
        printf("\nLe seuil de taille de mot. a bien ete modifie !\n\n");
        color("37");
        //on met a jour le fichier user.config
        majConfigFile();
    }else{
        displayError("Le seuil limite de taille de mot doit etre positif.\n");
    }
}


void changeAudioN(){
    int n;
    printf("Entrez la nouvelle taille de fenetre d'analyse.\n");
    scanf("%d",&n);
    CLEAR_STDIN

    if(ceil(log2((double)n))==floor(log2((double)n)) && n>0){    //n est une puissance de 2
        config->audio_n=n;
        color("32");
        printf("\nLa taille de la fenetre d'analyse a bien ete modifie !\n\n");
        color("37");
        //on met ï¿½ jour le fichier user.config
        majConfigFile();
    }else{
        displayError("La taille de la fenetre d'analyse doit etre une puissance de 2 positive.\n");
    }
}

void changeAudioM(){
    int m;
    printf("Entrez la nouveau nombre d'intervalles.\n");
    scanf("%d",&m);
    CLEAR_STDIN

    if(m%2==0 && m>0){    //m multiple de 2
        config->audio_m=m;
        color("32");
        printf("\nLe nombre d'echantillons a bien ete modifie !\n\n");
        color("37");
        //on met ï¿½ jour le fichier user.config
        majConfigFile();
    }else{
        displayError("Le nombre d'echantillons doit etre un multiple de 2 positif.\n");
    }
}


void majConfigFile(){
    FILE * fichier = NULL;

    fichier = fopen("data/user.config","w+");

    if(fichier!=NULL){
        fprintf(fichier,"%s\n",getPasswordAdmin());
        fprintf(fichier,"%d\n",getTailleMin());
        fprintf(fichier,"%d\n",getVal());
        fprintf(fichier,"%d\n",getSeuil());
        fprintf(fichier,"%d\n",getAudioN());
        fprintf(fichier,"%d\n",getAudioM());
    }else{
        displayError("Fichier de config inexistant");
        exit(-1);
    }
    fclose(fichier);
}
