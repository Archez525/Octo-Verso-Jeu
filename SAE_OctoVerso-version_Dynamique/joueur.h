//
// Created by fitig on 03/12/2024.
//

#ifndef JOUEUR_H
#define JOUEUR_H


enum { MAX_MAIN = 88, MAX_CHAR = 100 };

typedef struct {
    char main[MAX_MAIN]; //la main du joueur
    int taille; //nombre de cartes dans la main
}Joueur;

/**
 * @brief affcihe la main du joueur
 * @param [] joueur
 */
void afficherMain(const Joueur* joueur);

/**
    @brief v�rifie que les lettres jou�s par le joueur son bien pr�sente dans sa main
    @param[in] joueur , le joueur � v�rifier
    @param[in] lettres, les lettres a v�rifier
    @return si les les lettres existent
*/
int verifierLettresDansMain(Joueur* joueur, const char* lettres);

/**
* @brief ajoute une lettre � lamain du joueur
* @param[in] joueur, le joueur chez qui on ajoute la lettre
* @param[in] lettre, la lettre � ajouter
* @return si la lettre � bien �t� ajout�e
*/
int ajouterLettreDansMain(Joueur* joueur, char lettre);

/**
* @brief retire une lettre de la main du joueur et d�cale les autres lettres
* @param[in] joueur, le joueur chez qui on retire la lettre
* @param[in] lettre, la lettre � retirer
*/
void retirerLettreDeMain(Joueur* joueur, char lettre);

/**
* @brief v�rifie si la main du joueur est vide
* @param[in] joueur, le joueur pour qui on v�rifie
* @return si la main est vide
*/
int estVide(const Joueur* joueur);


/**
* @brief compte le nombre de fois qu'une lettre est pr�sente dans un mot
* @param[in] mot, le mot dans lequel on compte
* @param[in] lettre, la lettre � compter
*
* @return le nombre de fois que la lettre est pr�sente
*/
int nbLettreMot(const char* mot, char lettre);


/**
* @brief compte le nombre de fois qu'une lettre est pr�sente dans la main du joueur
* @param[in] joueur, le joueur chez qui on compte
*
* @param[in] lettre, la lettre � compter
*
* @return le nombre de fois que la lettre est pr�sente
*/
int nbLettreMain(const Joueur* joueur, char lettre);

/**
* @brief v�rifie si une lettre est pr�sente dans la main du joueur
* @param[in] joueur, le joueur chez qui on v�rifie
*
* @param[in] lettre, la lettre � v�rifier
*
* @return si la lettre est pr�sente
*/
int verifierlettre(Joueur* joueur, char lettre);


/**
* @brief sauvegarde la main du joueur dans une autre main
* @param[in] joueur, le joueur chez qui on sauvegarde
*
* @param[in] sauvegarde, l'autre main o� on sauvegarde
*/

void sauvegarderMain(const Joueur* joueur, Joueur* sauvegarde);


/**
* @brief compare les lettres pour le tri
* @param[in] a, la premi�re lettre
*
* @param[in] b, la deuxi�me lettre
*
* @return le r�sultat de la comparaison
*/
int comparerLettres(const void* a, const void* b);


/**
* @brief vide le contenu de la main temporaire
* @param[in] mainTemporaire, la main que l'on va vider
*/
void viderMainTemporaire(Joueur* mainTemporaire);

#endif //JOUEUR_H//
