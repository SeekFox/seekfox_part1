/**
 * @file element.h
 * @author Clément Truillet (clement.truillet@univ-tlse3.fr)
 * @brief 
 * @version 0.1
 * @date 07/11/2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define __ELEMENT__

/**
 * @brief Structure de ELEMENT
 * 
 */
typedef struct element * ELEMENT;

/**
 * @brief Initialisation de ELEMENT
 * 
 * @return ELEMENT 
 */
ELEMENT init_ELEMENT();

/**
 * @brief Affiche ELEMENT
 * 
 * @param elt 
 */
void affiche_ELEMENT(ELEMENT elt);

/**
 * @brief Saisie de ELEMENT via in
 * 
 * @param elt 
 */
ELEMENT saisir_ELEMENT();

/**
 * @brief Get the Next object
 * 
 * @param e 
 * @return ELEMENT 
 */
ELEMENT getNext(ELEMENT e);

/**
 * @brief Set the Next object
 * 
 * @param e 
 * @param eNext 
 */
void setNext(ELEMENT e, ELEMENT eNext);

/**
 * @brief Affectation de la valeur de ELEMENT
 * 
 * @param elt 
 * @param i 
 * @param c 
 */
void affect_ELEMENT(ELEMENT elt, int i);
//void affect_ELEMENT(ELEMENT elt, int i, char c);

/**
 * @brief Compare 2 ELEMENTS
 *          Renvoie -1 si elt1 < elt2
 *          Renvoie  0 si elt1 == elt2
 *          Renvoie  1 si elt1 > elt2
 * 
 * @param elt1 
 * @param elt2 
 * @return int 
 */
int compare_ELEMENT(ELEMENT elt1, ELEMENT elt2);

/**
 * @brief 
 * 
 * @param e 
 * @return int 
 */
int getI(ELEMENT e);