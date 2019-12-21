/**
 * @file interact.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
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




void displayMenu(int *isAdmin, enum FSM * state, char * file){
  int nextState = (*state);

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

    case CONNECT:
      connectAdmin(isAdmin);
      (*state)=ADMIN;
      break;
    
    case ADMIN:
      printf("\nMode Admin\n");
      //TODO: Affichage du Menu admin
      //Lancer une indexation manuelle
      //Visualiser un descripteur
      //Changer de Mot de Passe
      //Config
      (*state)=TITLE;
      break;

    case RESEARCH:
      printf("\n=== RECHERCHE ===\n");
      displayMenuResearch(file,state);
      break;

    case R_IMAGE:
      printf("Recherche par IMAGE\n");
      (*state) = TITLE;
      break;

    case R_TEXTE:
      printf("Recherche par TEXTE\n");
      (*state) = TITLE;
      break;

    case R_SON:
      printf("Recherche par SON\n");
      (*state) = TITLE;
      break;

    case R_KEYWORD:
      printf("Recherche par MOT CLES\n");
      (*state) = TITLE;
      break;

    case R_COLOR:
      printf("Recherche par COULEUR DOMINANTE\n");
      (*state) = TITLE;
      break;

    case INFO:
      displayInformations();  
      CLEAR_STDIN
      (*state) = TITLE;
      break;

    default:
      displayError("Twinkie not found.");
      (*state) = TITLE;
      break;
  }
}

void displayMenuResearch(char * file, enum FSM * state){
  char choix[4] = "";
  char ext[8] = "";
  char line[128] = "";
  int i = 0;
  int choixNb = -1;

  FILE * listFile = NULL;
  listFile = fopen("data/index.dat","r");
  rewind(listFile);

  //Si le fichier index.dat existe
  if(listFile!=NULL){
    printf("  #/- Recherche par Couleur Dominante\n");
    printf("  0/- Recherche par mot-clé\n");
    //Lecture du fichier
    while (fgets(line, 128, listFile) != NULL){
      i++;
      printf("  %d/- %s",i,line);
    }
    

    //Lecture du choix
    scanf("%4s",choix);

    //Recuperation du fichier choisi
    choixNb = convertStringChoiceToInt(choix,i);
    if(choixNb > 0){
      rewind(listFile);
      strcpy(line,"");
      for(int k=0; k<choixNb; k++){
        fscanf(listFile,"%s\n",line);
      }

      printf("\n\t >>%s<<\n",line);
      strcpy(ext, strrchr(line,'.'));
      printf("\n\t >>%s<<\n",ext);
      (*state) = ( ( strcmp(ext,".bmp")==0 || strcmp(ext,".jpg")==0 ) ? R_IMAGE : (strcmp(ext,".xml")==0 ? R_TEXTE : (strcmp(ext,".wav")==0 || strcmp(ext,".bin")==0 ) ? R_SON : (*state)));
      strcpy(file,line);
    }else if(choixNb == -1){
        (*state) = R_COLOR;
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

char * getExtensionOfFile(char * file){
  char * ext = (char *)malloc(sizeof(char)*4);
  strcpy(ext,"");
  strcpy(ext, strrchr(file,'.'));
  return ext;
}

void displayInformations(){
  color("37");
  color("1");
  printf("\n=== SEEKFOX TEAM ===\n");
  color("30");
  color("0");
  printf("Gael Camba : CTO\n");
  printf("Oualid El Abdaoui : \n");
  printf("Etienne Combelles : \n");
  printf("Raphael Bizet : Stagiaire\n");
  printf("Clement Truillet : Community Manager\n");
  printf("\n");
  printf("www.seekfox.team - @seekfox\n");
}

void displayError(char * msg){
    color("31");
    printf("\n[ERREUR] %s\n",msg);
    color("0");
}

void connectAdmin(int * isAdmin){
  (*isAdmin) = 1;
  char ch;
  char password[32] = ""; //Chaine du mot de passe
  char passwordGood[32]; //Bon mot de passe
  FILE * fichier = NULL;

  //RECUPERATION MOT DE PASSE ATTENDU
  fichier = fopen("data/admin.dat","r");
  if(fichier!=NULL){
    fscanf(fichier,"%s",passwordGood);
    //printf("MOT DE PASSE ATTENDU : <%s>\n",passwordGood);
    fclose(fichier);
  }else{
    displayError("Fichier de connexion admin indisponible");
  }


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

    //printf("\npassword : <%s>\n",password);
    sprintf(password,"%s",(char*)crypt(password,"456b7016a916a4b178dd72b947c152b7")); //Chiffrement
    //printf("password : <%s>\n",password);

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