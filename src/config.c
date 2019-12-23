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
 *  passwordAdmin           : Mot de passe administrateur chiffré
 * TEXTE
 *  Valeur limite           : Les x mots les plus presents
 *  Seuil                   : Les mots qui apparaissent plus de x fois
 * AUDIO
 *  audio_n                 : Fenetre d'analyse 
 *  audio_m                 : Nombre d'intervalles de la fenetre d'analyse
 * 
 */
struct config_s{
    char passwordAdmin[32];
    int audio_n;
    int audio_m;
};

//Getter
char * getPasswordAdmin(){
    return (config->passwordAdmin);
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
            line[strlen(line)-1] = '\0'; //Remove '\n' char

            switch (i){
                case 0:
                    setPasswordAdmin(&c,line);
                    break;

                case 1:
                    setAudioN(&c,atoi(line));
                    break;

                case 2:
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
    printf("AUDIO \n");
    printf("\tNombre de fenetres d'analyse         %d\n",getAudioN(config));
    printf("\tNombre d'intervalles                 %d\n",getAudioM(config));
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
        printf("\nVotre mot de passe à bien ete modifie !\n\n");
        color("37");
        //on met à jour le fichier user.config
        majConfigFile();
    }else{
        displayError("Les mots de passe ne sont pas identiques.\n");
    }
}

void majConfigFile(){
    FILE * fichier = NULL;

    fichier = fopen("data/user.config","w+");

    if(fichier!=NULL){
        fprintf(fichier,"%s\n",getPasswordAdmin());
        fprintf(fichier,"%d\n",getAudioN());
        fprintf(fichier,"%d\n",getAudioM());
    }else{
        displayError("Fichier de config inexistant");
        exit(-1);
    }
    fclose(fichier);
}