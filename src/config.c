/**
 * @file config.c
 * @author Clément Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 22/12/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
typedef struct config_s{
    char passwordAdmin[32];
    int audio_n;
    int audio_m;
} config;



//Getter
char * getPasswordAdmin(Config c){
    return (c->passwordAdmin);
}

int getAudioN(Config c){
    return (c->audio_n);
}

int getAudioM(Config c){
    return (c->audio_m);
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
    Config c = (Config)malloc(sizeof(config));
    FILE * fichier = NULL;
    char line[64] = "";
    int i = 0;

    fichier = fopen("data/user.config","r");
    if(fichier!=NULL){
        while (fgets(line, 64, fichier) != NULL){
            line[strlen(line)-2] = '\0'; //Remove '\n' char
            printf(">%s<\n",line);

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
        displayError("Fichier de config indisponible");
        exit(-1);
    }

    return c;
}

void displayConfig(Config c){
    printf("\n===CONFIG===\n");
    printf("%s\n",getPasswordAdmin(c));
    printf("%d\n",getAudioN(c));
    printf("%d\n",getAudioM(c));
    printf("\n");
}   