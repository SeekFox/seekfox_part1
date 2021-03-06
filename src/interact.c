/**
 * @file interact.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief Fonctions gerant l'interface entre le programme et l'utilisateur
 * @version 0.1
 * @date 21/11/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>


#ifndef __INTERACT__
    #include <../include/interact.h>
#endif

#ifndef __CONFIG__
    #include <../include/config.h>
#endif

#ifndef __INDEXATION__
  #include <../include/indexation.h>
#endif

#ifndef RECHERCHE_H
  #include "../include/recherche.h"
#endif

/**
 * @brief Affichage du menu
 * 
 * @param isAdmin 
 * @param state 
 * @param file 
 */
void displayMenu(int *isAdmin, enum FSM * state, char * file){
  int nextState = (*state);

  //Machine à état
  switch (*state){
    case TITLE:

      printf("\n1\\- Recherche");
      printf("\n2\\- Administration");
      printf("\n3\\- Informations");
      printf("\n4\\- Quitter Seekfox\n");
    
      scanf("%d",&nextState);
      CLEAR_STDIN
      (*state) = (nextState==1 ? RESEARCH : (nextState==2 ? CONNECT : (nextState==3 ? INFO : (nextState==4 ? END : TITLE))));
      break;

    //Connexion au mode admin
    case CONNECT:
      connectAdmin(isAdmin);
      (*state)=ADMIN;
      break;
    
    //affichage du menu admin
    case ADMIN:
      if(*isAdmin==1) displayMenuAdmin(isAdmin);
      (*state)=TITLE;
      (*isAdmin)=0;
      break;

    //Affichage du menu de recherche
    case RESEARCH:
      printTitle("RECHERCHE");
      displayMenuResearch(file,state);
      break;

    //Recherche image du fichier file
    case R_IMAGE:
      printTitle("Recherche par IMAGE");
      rechercheParFichierImage(file);

      (*state) = END;
      break;

    //Recherche texte du fichier file
    case R_TEXTE:
      printTitle("Recherche par TEXTE");
      afficherResultats(rechercheParFichierTexte(file),R_TEXTE);
      (*state) = END;
      break;

    //Recherche audio du fichier file
    case R_SON:
      printTitle("Recherche par SON");
      printf("%s\n",file);
      afficherResultats(rechercheParFichierSon(file),R_SON);
      (*state) = END;
      break;

    //Recherche par mot clef
    case R_KEYWORD:
      printTitle("Recherche par MOT CLES");
      char * mot = (char*)malloc(sizeof(char)*32);
      //on recupere le mot a rechercher
      printf("Entrez le mot-cle a rechercher : ");
      scanf("%31s",mot);
      afficherResultats(rechercheParMotCle(mot),R_KEYWORD);

      (*state) = END;
      break;

    //Recherche par couleur dominante (non effectuée)
    case R_COLOR:
      //printTitle("Recherche par COULEUR DOMINANTE\n");
      //TODO : Recherche par COULEUR DOMINANTE
      (*state) = END;
      break;

    //affichage des informations du projet
    case INFO:
      displayInformations();  
      CLEAR_STDIN
      (*state) = TITLE;
      break;

    //Etat en cas d'erreur
    default:
      displayError("Twinkie not found.");
      (*state) = TITLE;
      break;
  }
}

/**
 * @brief Affichage du menu de recherche
 * 
 * @param file 
 * @param state 
 */
void displayMenuResearch(char * file, enum FSM * state){
  char choix[4] = "";
  char ext[8] = "";
  char line[128] = "";
  int i = 0;
  int choixNb = -1;

  FILE * listFile = NULL;
  listFile = fopen("data/index.dat","r");
  if(listFile==NULL) return;
  rewind(listFile);

  //Si le fichier index.dat existe
  if(listFile!=NULL){
    //printf("  #/- Recherche par Couleur Dominante\n");
    printf(" -1/- Retour\n");
    printf("  0/- Recherche par mot-clef\n");
    //Lecture du fichier
    while (fgets(line, 128, listFile) != NULL){
      i++;
      printf("  %d/- %s",i,line);
    }
    

    //Lecture du choix
    scanf("%4s",choix);

    //Recuperation du fichier choisi
    choixNb = convertStringChoiceToInt(choix,i);

    //si on choisit un fichier 
    if(choixNb > 0){
      rewind(listFile);
      strcpy(line,"");
      for(int k=0; k<choixNb; k++){
        fscanf(listFile,"%s\n",line);
      }

      printf("Choix du fichier \"%s\"\n\n",line);
      strcpy(ext, strrchr(line,'.'));

      //mise à jour de l'état
      (*state) = ( ( strcmp(ext,".bmp")==0 || strcmp(ext,".jpg")==0 ) ? R_IMAGE : (strcmp(ext,".xml")==0 ? R_TEXTE : (strcmp(ext,".wav")==0 || strcmp(ext,".bin")==0 ) ? R_SON : (*state)));
      strcpy(file,line);

    //Retour
    }else if(choixNb == -1){
        (*state) = TITLE;
    //Recherche par mot clef
    }else if(choixNb == 0){
      (*state) = R_KEYWORD;
    }else{
      (*state) = RESEARCH;
    }

    //Fermeture du fichier
    fclose(listFile);
    
    CLEAR_STDIN
  }else{
    displayError("Ouverture du ficher index.dat impossible.");
  }
}

/**
 * @brief Affichage du menu admin
 * 
 * @param isAdmin 
 */
void displayMenuAdmin(int *isAdmin){
  printTitle("ADMINISTRATION");
  int choix = -1;
  char fichier[64];

  while ((*isAdmin==1)){
    printf("1\\- Lancer l'indexation\n");
    printf("2\\- Visualiser un descripteur\n");
    printf("3\\- Options\n");
    printf("4\\- Retour\n");

    scanf("%d",&choix);
    CLEAR_STDIN
    printf("\n");

    switch (choix){
      case 1:
        displayMenuAdminIndexation();
        break;

      //visualisation du descripteur
      case 2:
        system("echo Vous etes dans le repertoire ${PWD##*/}");
        printf("\nEntrez le chemin vers le fichier du descripteur\n\t>");
        color("36");
        scanf("%64s",fichier);
        color("37");
        CLEAR_STDIN
        displayDescripteur(fichier);
        break;

      //Options
      case 3: 
        displayMenuAdminConfig();
        break;

      //On quitte le menu admin
      case 4:
        (*isAdmin)=0;
        break;
      
      default:
        break;
    }
  }
}

/**
 * @brief Affichage du menu admin -> config
 * 
 */
void displayMenuAdminConfig(){
  int choix = -1;

  while(choix!=8){
    displayConfig();
    printf("1\\- Changer le mot de passe\n");
    printf("2\\- Modifier la taille minimun d'un mot\n");
    printf("3\\- Modifier la valeur limite de mots\n");
    printf("4\\- Modifier le seuil limite de taille de mot\n");
    printf("5\\- Modifier le nombre de bits de quantification\n");
    printf("6\\- Modifier le nombre de fenetres d'analyse\n");
    printf("7\\- Modifier le nombre d'intervalles\n");
    printf("8\\- Retour\n");

    scanf("%d",&choix);
    CLEAR_STDIN

    switch (choix){
      case 1:
        changePassword();
        break;
      
      case 2:
        changeTailleMin();
        break;

      case 3:
        changeVal();
        break;

      case 4:
        changeSeuil();
        break;

      case 5:
        changeNbBits();
        break;

      case 6:
        changeAudioN();
        break;
      
      case 7:
        changeAudioM();
        break;

      
      default:
        printf("\n");
        break;
    }
  }
}

/**
 * @brief Affichage du menu admin -> indexation
 * 
 */
void displayMenuAdminIndexation(){
  int choix = -1;
  char fichier[64];

  printf("1\\- Indexation d'un fichier\n");
  printf("2\\- Indexation totale\n");
  printf("3\\- Afficher les fichiers indexes\n");
  printf("4\\- Retour\n");

  scanf("%d",&choix);
  CLEAR_STDIN
  printf("\n");

  switch (choix){
    case 1:
      printf("Chargement...\n");
      system("echo Vous etes dans le repertoire ${PWD##*/}");
      printf("\nEntrez le chemin vers le fichier a indexer\n\t>");
      color("36");
      scanf("%64s",fichier);
      color("37");
      CLEAR_STDIN
      //printf("\t>> >%s<\n",fichier);
      //On lance l'indexation
      indexationUnique(fichier);

      printf("\n");
      break;

    case 2:
      printf("Indexation des fichiers en cours...");
      indexationTotale();
      color("32");
      printf("\nL'indexation totale a ete effectuee !\n");
      color("37");
      break;

    case 3:
      displayFichierIndexes();
      printf("\n");
      return;
      break;

    case 4:
      break;

    default:
      break;
  }
}

/**
 * @brief Conversion d'un string en int selon son contenu
 * 
 * @param str 
 * @param max 
 * @return int 
 */
int convertStringChoiceToInt(char * str, int max){
  int val;

  if(strcmp(str,"#")==0){
    val = -1;
  }else if(strcmp(str,"0")==0){
    val = 0;
  }else{
    val = atoi(str);
    val = (val==0 || val > max ? -2 : val);
  }

  return val;
}

/**
 * @brief Get the Extension Of File object
 * 
 * @param file 
 * @return const char* 
 */
const char * getExtensionOfFile(const char * file){
  if (strlen(file) == 0 || strcmp(file, "NA") == 0) return "";

  return strrchr(file,'.');
}

/**
 * @brief Get the Name Of File object
 * 
 * @param file 
 * @return char* 
 */
char * getNameOfFile(char * file){
  char * s = NULL;
  s = (char *)malloc(( strlen(file)+1) * sizeof(char));
  strcpy(s,"");

  if( strchr(file,'.') != NULL){
    for(int i=0; (i<(strlen(file)-strlen(strrchr(file,'.'))));i++){
      sprintf(s,"%s%c",s,file[i]);
    }
  }else{
    strcpy(s,file);
  }
  s[strcspn(s,"\r\n")] = 0; //Suppression du \n

  return s;
}

void displayInformations(){
  printTitle("SEEKFOX TEAM");
  printf(" %-22.22s  %s\n","Gael Camba","CTO");
  printf(" %-22.22s  %s\n","Oualid El Abdaoui","Employe du mois");
  printf(" %-22.22s  %s\n","Etienne Combelles","Tresorier");
  printf(" %-22.22s  %s\n","Raphael Bizet","Stagiaire");
  printf(" %-22.22s  %s\n","Clement Truillet","Community Manager");
  printf("\n");
  printf("www.seekfox.team - @seekfox\n");
}

void displayError(char * msg){
    color("31");
    printf("\n[ERREUR] %s\n",msg);
    color("0");
}

void printTitle(char * msg){
  color("37");
  color("1");
  printf("\n=== %s ===\n",msg);
  color("30");
  color("0");
}

void printSeekFox(){
  color("32");
  color("1");
  printf("  ____            _     __                    \n");
  printf(" / ___|  ___  ___| | __/ _| _____  __         \n");
  printf(" \\___ \\ / _ \\/ _ \\ |/ / |_ / _ \\ \\/ /   \n");
  printf("  ___) |  __/  __/   <|  _| (_) >  <          \n");
  printf(" |____/ \\___|\\___|_|\\_\\_|  \\___/_/\\_\\\n\n");
  color("37");
  color("0");
}

/**
 * @brief Connexion au mode admin
 * 
 * @param isAdmin 
 */
void connectAdmin(int * isAdmin){
  (*isAdmin) = 1;
  char ch;
  char password[32] = ""; //Chaine du mot de passe
  char passwordGood[32]; //Bon mot de passe

  //RECUPERATION MOT DE PASSE ATTENDU
  strcpy(passwordGood,getPasswordAdmin());

  printf("Veuillez entrer le mot de passe administrateur : \n");
  for(int i=0; (i<3 && strcmp(password,passwordGood));i++){
    for (;;){ //Recuperation du mot de passe 
      ch = getch();
      if(ch == '\n' || strlen(password)>31){ //Verifier que le mot de passe ne soit pas trop long OU que l'user ne presse pas le bouton entrer
        break;
      }else{
        printf("*"); //Masquage du mot de passe
        sprintf(password,"%s%c",password,ch); //Ajout du nouveau caractere dans password
      }
    }
    printf("\n");

    //Chiffrement
    sprintf(password,"%s",(char*)crypt(password,"456b7016a916a4b178dd72b947c152b7")); //Chiffrement
    //printf("\t\t <%s>\n",password);

    //Si le mot de passe n'est pas valide
    if(strcmp(password,passwordGood)!=0){
      memset(password,0,sizeof(password)); //Vider la zone 
      displayError("mot de passe invalide");
    }
  }

  if(strcmp(password,passwordGood)!=0){
    *isAdmin=0;
  }
  printf("\n");
}








/**-------------------------------------------------------------------------------**/

/**
 * @brief Lecture d'un caractere sur le terminal sans l'afficher
 * 
 * 
 */
int getch(){
    struct termios oldtc, newtc;
    int ch;

    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
    ch=getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);

    return ch;
}