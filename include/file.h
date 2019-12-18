/**
 * @file file.h
 * @author Clément Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 28/11/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define __FILE_DYNAMIQUE__

#ifndef __ELEMENT__
    #include "../include/element.h"
#endif

/**
 * @brief Pointeur sur la structure file
 * 
 */
typedef struct file * File;

/**
 * @brief Initialise la File
 * 
 * @param f 
 */
void initFile(File * f);

/**
 * @brief Affiche la File
 * 
 * @param f 
 */
void afficheFile(File f);

/**
 * @brief Retourne true si la File est vide
 * 
 * @param f 
 * @return int 
 */
int fileIsEmpty(File f);

/**
 * @brief Enfile elt dans la File
 * 
 * @param f 
 * @param elt 
 */
void enFile(File * f, ELEMENT elt);

/**
 * @brief Defile la File
 * 
 * @param f 
 */
void deFile(File * f);

/**
 * @brief Demande le nombre d'element a remplir dans la Pile p
 * @brief   et demande à l'utilisateur de la remplir
 * 
 * @return File 
 */
File saisirFile(void);

/**
 * @brief Renvoit la somme des elements de la file
 * 
 * @param f 
 * @return int 
 */
int sommeFile(File f);