/**
 * @file config.h
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 22/12/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define __CONFIG__

typedef struct config_s * Config;
extern Config config;

//Getter
/**
 * @brief Get the Password Admin object
 * 
 * @return char* 
 */
char * getPasswordAdmin();

/**
 * @brief Get the Taille Min object
 * 
 * @return int 
 */
int getTailleMin();

/**
 * @brief Get the Val object
 * 
 * @return int 
 */
int getVal();

/**
 * @brief Get the Seuil object
 * 
 * @return int 
 */
int getSeuil();

/**
 * @brief Get the Nb Bits object
 * 
 * @return int 
 */
int getNbBits();

/**
 * @brief Get the Audio N object
 * 
 * @return int 
 */
int getAudioN();

/**
 * @brief Get the Audio M object
 * 
 * @return int 
 */
int getAudioM();

/**
 * @brief Get the Logiciel Texte object
 * 
 * @return char* 
 */
char * getLogicielTexte();

/**
 * @brief Get the Logiciel Image object
 * 
 * @return char* 
 */
char * getLogicielImage();

/**
 * @brief Get the Logiciel Audio object
 * 
 * @return char* 
 */
char * getLogicielAudio();

//Setter
/**
 * @brief Set the Password Admin object
 * 
 * @param c 
 * @param pwd 
 */
void setPasswordAdmin(Config *c, char * pwd);

/**
 * @brief Set the Taille Min object
 * 
 * @param c 
 * @param tailleMin 
 */
void setTailleMin(Config *c, int tailleMin);

/**
 * @brief Set the Val object
 * 
 * @param c 
 * @param val 
 */
void setVal(Config *c, int val);

/**
 * @brief Set the Seuil object
 * 
 * @param c 
 * @param seuil 
 */
void setSeuil(Config *c, int seuil);

/**
 * @brief Set the Nb Bits object
 * 
 * @param c 
 * @param nbBits 
 */
void setNbBits(Config *c, int nbBits);

/**
 * @brief Set the Audio N object
 * 
 * @param c 
 * @param n 
 */
void setAudioN(Config *c, int n);

/**
 * @brief Set the Audio M object
 * 
 * @param c 
 * @param m 
 */
void setAudioM(Config *c, int m);

/**
 * @brief Set the Logiciel Texte object
 * 
 * @param c 
 * @param str 
 */
void setLogicielTexte(Config *c, char * str);

/**
 * @brief Set the Logiciel Image object
 * 
 * @param c 
 * @param str 
 */
void setLogicielImage(Config *c, char * str);

/**
 * @brief Set the Logiciel Audio object
 * 
 * @param c 
 * @param str 
 */
void setLogicielAudio(Config *c, char * str);


/**
 * @brief Recupere les infos du fichier config 
 * 
 * @return Config 
 */
Config loadConfig();

/**
 * @brief Affiche les parametres de configuration
 * 
 */
void displayConfig();

/**
 * @brief Changer le mot de passe
 * 
 */
void changePassword();

/**
 * @brief Changer la Taille Min
 * 
 */
void changeTailleMin();

/**
 * @brief Changer la valeur limite de mots
 * 
 */
void changeVal();

/**
 * @brief Changer le seuil limite de taille de mot
 * 
 */
void changeSeuil();

/**
 * @brief Change le parametre NbBits
 * 
 */
void changeNbBits();

/**
 * @brief Changer le parametre Audio N
 * 
 */
void changeAudioN();

/**
 * @brief Changer le parametre Audio M
 * 
 */
void changeAudioM();

/**
 * @brief Met � jour le fichier user.config
 * 
 */
void majConfigFile();