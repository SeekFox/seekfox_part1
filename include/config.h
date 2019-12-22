/**
 * @file config.h
 * @author Clément Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 22/12/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define __CONFIG__

typedef struct config_s * Config;

//Getter
/**
 * @brief Get the Password Admin object
 * 
 * @param c 
 * @return char* 
 */
char * getPasswordAdmin(Config c);

/**
 * @brief Get the Audio N object
 * 
 * @param c 
 * @return int 
 */
int getAudioN(Config c);

/**
 * @brief Get the Audio M object
 * 
 * @param c 
 * @return int 
 */
int getAudioM(Config c);

//Setter
/**
 * @brief Set the Password Admin object
 * 
 * @param c 
 * @param pwd 
 */
void setPasswordAdmin(Config *c, char * pwd);

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
 * @brief Recupere les infos du fichier config 
 * 
 * @return Config 
 */
Config loadConfig();

/**
 * @brief Affiche les parametres de configuration
 * 
 * @param c 
 */
void displayConfig(Config c);