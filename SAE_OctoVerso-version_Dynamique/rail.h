//
// Created by fitig on 03/12/2024.
//

#ifndef RAIL_H
#define RAIL_H

#include <stdbool.h>

#include "joueur.h"
#include "chevalet.h"

enum { MAX_CASES = 8, MAX = 10 };


typedef struct {
    char cases[MAX_CASES]; // Les cases du rail
    int debut;               // Indice de la première case occupée
    int fin;                 // Indice de la dernière case occupée
    int taille;// Nombre de cases actuellement occupées
} Rail;


/**
 * @brief initialise un rail
 * @param [out] rail initialisé
 */
void initRail(Rail* rail);

/**
 * @brief sert à afficher un rail
 * @param rail , rail à afficher
 */
void afficherRail(const Rail* rail);


/**
 * @brief Compare deux mots pour vérifier s'ils sont identiques.
 *
 * Cette fonction effectue une comparaison caractère par caractère des deux mots fournis.
 * Elle est insensible à la casse et ne prend en compte que les lettres alphabétiques,
 * en ignorant les espaces ou les caractères spéciaux.
 *
 * @param[in] mot1 Le premier mot à comparer.
 * @param[in] mot2 Le second mot à comparer.
 * @return 1 si les deux mots sont identiques, 0 sinon.
 */
int comparerMots(const char* mot1, const char* mot2);

/**
* @brief gére les ajouts de lettres et modifie le rail si il est plein
* @param[out] rail, rail modifié avec les nouvelles lettres
* @param[in] joueur, le joueur qui ajoutes les lettres
* @param[out] adversaire, le joueur qui va récuperer les lettres enlever du rail
* @param[in] lettres, les lettres à ajoutées
* @param[in] cote, cote au quel on ajoute les lettres
* @return si les lettres on été ajoutées
*/
int ajouterLettresAuRail(Rail* rail, Joueur* joueur, Joueur* adversaire, const char* lettres, int cote);

/**
* @brief ajoute des lettres au rail à l'envers
* @param[out] le rail avec les lettres ajoutées
* @param[in] le joueur qui joue le mot
* @param[in] le joueur adverse qui va ramasser les lettres qui vont dépasser du rail
* @param[in] les lettres/mot que le joueur pose
* @param[in] le cote au quel le joueur pose
* @return si le mot est posé
*/
int ajouterlettresALenvers(Rail* rail, Joueur* joueur, Joueur* adversaire, const char* lettres, int cote);

/**
* @brief retire une lettre du rail
* @param[out] rail, rail avec la lettre retirée
* @param[in] cote , cote au quel on retire la lettre
* @return la lettre rejetée
*/
char retirerLettreDuRail(Rail* rail, int cote);

/**
* @brief ajoute une lettre au rail
* @param[out] rail, rail avec la lettre ajoutée
* @param[in] lettre, celle qui va etre ajoutée
* @param[in] cote, cote au quel on va ajouter la lettre
* @param[in] index, index ou on retrouve la lettre à ajouter
* @param[in] longeur du mot
* @return si la lettre a été ajoutée
*/
int ajouterLettreAuRail(Rail* rail, const char* lettres, int cote, int index, int longueur);



/**
* @brief sert à ajouter un premier mot sur le rail
* @param[out] rail avec le mot ajouté
* @param[in] joueur qui a joute le mot et a qui on enlève les lettres de la main
* @param[in] lettres qu'on ajoutes sur le rail
* @param[in] cote au quel on ajoute
* @return si le mot est ajouté
*/
int addFirstWord(Rail* rail, Joueur* joueur, const char* lettres, int cote);

/**
 * @brief fonction qui vérifie si le mot donné est présent dans le dictionnaire
 * @param [in] cheminFichier
 * @param [in] mot_a_verifier
 * @return si le mot est bien présent dans le fichier
 */
int verifierMotDansFichier(const char* cheminFichier, const char* mot_a_verifier);

/**
* @brief ajoute un mot dans la liste des mots déjà utilisés
* @param[out] tableau des mots deja utilisés
* @param[in] taille du mot
* @param[in] capacite du tableau
* @param[in] mot à ajouter
* @return si le mot est ajouté
*/
int addInUsed(char*** tableau, int* taille, int* capacite, const char* mot);


/**
* @brief affiche les mots utilisés
* @param[in] tableau des mots deja utilisés
* @param[in] taille du tableau
*/
void showUsed(char** tableau, int taille);

/**
* @brief désalloue le tableau des mots deja utilisés
* @param[in] tableau des mots deja utilisés
* @param[in] taille du tableau
*/
void freeUsed(char** tableau, int taille);


/**
 * @brief Échange une lettre de la main d'un joueur contre une lettre tirée au hasard dans la pioche.
 * @param[in, out] joueur Le joueur qui effectue l'échange.
 * @param[in, out] pioche La pioche utilisée pour l'échange.
 * @param[in] lettre La lettre de la main du joueur à échanger.
 * @return 1 si l'échange a été effectué avec succès, 0 en cas d'erreur.
 */

int echangerLettre(Joueur* joueur, Chevalet* pioche, char lettre);

/**
 * @brief Vérifie si un mot est présent dans la main du joueur.
 *
 * Cette fonction vérifie si le joueur possède toutes les lettres nécessaires pour former un mot donné.
 *
 * @param[in] joueur Le joueur dont la main est vérifiée.
 * @param[in] lettres Les lettres du mot à vérifier.
 * @return 1 si le joueur possède toutes les lettres nécessaires, 0 sinon.
 */
int verifierCompatibiliteRail(const Rail* rail, const char* lettresRail, int longueurRail, char cote);



/**
 * @brief Ajoute un mot sur le rail en vérifiant sa validité et en retirant les lettres de la main du joueur.
 *
 * Cette fonction permet d'ajouter un mot sur le rail en vérifiant sa validité dans un dictionnaire
 * et en retirant les lettres correspondantes de la main du joueur. Elle gère également les cas
 * où le rail est plein et où des lettres doivent être retirées du rail pour ajouter de nouvelles lettres.
 *
 * @param[out] rail Le rail sur lequel ajouter le mot.
 * @param[in] joueur Le joueur qui ajoute le mot.
 * @param[in] joueur2 Le joueur adverse.
 * @param[in] saisie Le mot à ajouter sur le rail.
 * @param[in] cheminDictionnaire Le chemin du fichier contenant le dictionnaire.
 * @param[in, out] motsJoues Tableau des mots déjà joués.
 * @param[in, out] tailleMotsJoues Nombre de mots déjà joués.
 * @return Le mot ajouté sur le rail si l'opération a réussi, NULL sinon.
 */
char* ajouterMotSurRail(Rail* rail, Joueur* joueur, Joueur* joueur2, const char* saisie, const char* cheminDictionnaire, char** motsJoues, int* tailleMotsJoues);


/**
 * @brief Vérifie si un mot de 8 lettres est formé sur le rail et s'il est valide.
 *
 * Cette fonction vérifie si le rail contient exactement 8 lettres et si le mot formé à partir
 * de ces lettres est valide en le comparant avec un dictionnaire.
 *
 * @param[in] rail Le rail contenant les lettres.
 * @return 1 si le mot est valide et formé de 8 lettres, sinon 0.
 */
int octo(Rail* rail);

/**
 * @brief Permet au joueur de retirer une lettre de sa main après qu'un mot de 8 lettres a été formé sur le rail.
 *
 * Cette fonction permet au joueur de choisir une lettre spécifique parmi celles de sa main pour
 * la retirer après avoir formé un mot de 8 lettres sur le rail. Elle vérifie si la lettre choisie
 * est présente dans la main du joueur et la retire si elle est valide.
 *
 * @param[in, out] joueur Le joueur qui retire une lettre de sa main.
 */
void retirerLettresiOcto(Joueur* joueur);

/**
 * @brief Copie le rail source afin de le coller dans le rail de destination .
 *
 * @param[in] source, le rail qui va être copié
 * @param[out] destination, le rail qui va recevoir la copie
 */
void copierRail(Rail* source, Rail* destination);


#endif //RAIL_H