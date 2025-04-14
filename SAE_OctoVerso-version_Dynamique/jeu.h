//
// Created by fitig on 03/12/2024.
//

#ifndef JEU_H
#define JEU_H

#include "chevalet.h"
#include "joueur.h"
#include "rail.h"

/**
 * @brief ça lance la partie
 */
void jeu();

/**
*	@brief vérifie si la partie est fini
*	@param[in] joueur, le joueur à vérifier
*	@return si la partie est fini
*/
int estFini(Joueur* joueur);

#endif //JEU_H
