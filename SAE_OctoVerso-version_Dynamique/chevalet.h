//
// Created by fitig on 03/12/2024.
//

#ifndef CHEVALET_H
#define CHEVALET_H

#include "joueur.h"

enum { MAX_CARTES = 88, LETTRE = 21 }; // LETTRE correspond au nombre de lettres de l'alphabet présent dans le jeu


typedef struct {
    char* lettres;//ça représente la lettre sur le chevalet
    int taille;//nombre de cartes restante
    int capacite;// capacité totale de la pioche
}Chevalet;


enum { NB_JOUEURS = 2, CARTES_PAR_JOUEUR = 12 };

/**
 * @brief sert à initialisé un chevalet
 * @param [in] capacite à la quelle ont l'initialise
 * @return un chevalet initialisé
 */
Chevalet* initPioche(int capacite);

/**
 * @brief sert à désallouer la pioche a la fin de la partie
 * @param [in] pioche à détruire
 */
void detruirePioche(Chevalet* pioche);

/**
 * @brief sert a ajouter une carte dans la pioche (ont pourra l'utiliser si on voudra re mettres des cartes du terrains ou main à la pioche
 * @param [out] pioche avec la carte ajouter
 * @param [in] lettre à ajouter dans la pioche
 */
void ajouterCarte(Chevalet* pioche, char lettre);

/**
 * @brief la pioche du jeu
 * @param [out] la pioche du jeu
 */
void creerPioche(Chevalet* pioche);

/**
 * @brief pour mélanger la pioche
 * @param [out] pioche mélangée
 */
void melangerPioche(Chevalet* pioche);

/**
 * @brief distribue les lettres aux 2 Joueurs
 * @param [in] pioche
 * @param [in] joueurs
 */
void distribuerCartes(Chevalet* pioche, Joueur joueurs[NB_JOUEURS]);

/**
 * @brief affiche la pioche
 * @param [out]
 */
void afficherPioche(const Chevalet* pioche);




/**
 * @brief Distribue des lettres prédéfinies aux joueurs pour simuler des parties spécifiques.
 *
 * Cette fonction remplace la distribution aléatoire des cartes par une distribution
 * basée sur des chaînes de lettres prédéfinies, permettant de recréer des situations
 * spécifiques au début d'une partie.
 *
 * @param[in] lettresJoueurs Tableau contenant les chaînes de lettres prédéfinies pour chaque joueur.
 * @param[in, out] joueurs Tableau des joueurs à qui distribuer les lettres.
 * @param[in] nbJoueurs Nombre de joueurs dans la partie.
 */
void distribuerCartesPredefinies(const char* lettresJoueurs[], Joueur joueurs[], int nbJoueurs);

#endif //CHEVALET_H