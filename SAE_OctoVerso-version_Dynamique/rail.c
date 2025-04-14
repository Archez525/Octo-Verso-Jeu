//
// Created by fitig on 03/12/2024.
//
#pragma warning disable 4103
#define _CRT_SECURE_NO_WARNINGS
#define strdup _strdup

#include "rail.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void initRail(Rail* rail) {
    for (int i = 0; i < MAX_CASES; ++i) {
        rail->cases[i] = ' ';
    }
    rail->debut = 0;
    rail->fin = -1; // Aucun élément n'est encore présent
    rail->taille = 0;
}

void afficherRail(const Rail* rail) {
    if (rail->taille == 0) {
        return;
    }

    printf("R : ");
    for (int i = 0; i < rail->taille; i++) {
        int index = (rail->debut + i) % MAX_CASES;
        printf("%c ", rail->cases[index]);
    }
    printf("\n");

    printf("V : ");
    for (int i = 0; i < rail->taille; i++) {
        int index = (rail->fin - i + MAX_CASES) % MAX_CASES;
        printf("%c ", rail->cases[index]);
    }
    printf("\n");
}


int comparerMots(const char* mot1, const char* mot2) {
    int resultat = strcmp(mot1, mot2);

    if (resultat == 0) {
        return -1; // identiques
    }
    else if (resultat < 0) {
        return 1;  // deuxieme  plus grand
    }
    else {
        return 0;  // premier plus grand
    }
}


int ajouterLettresAuRail(Rail* rail, Joueur* joueur, Joueur* adversaire, const char* lettres, int cote) {
    int longueur = strlen(lettres);
    char lettreRejetee;

    for (int i = 0; i < longueur; i++) {
        // Gérer les cas de rail plein
        if (rail->taille == MAX_CASES) {
            lettreRejetee = retirerLettreDuRail(rail, cote);
            if (!ajouterLettreDansMain(adversaire, lettreRejetee)) {
                return 0; // Échec
            }
        }

        // Ajouter la lettre au rail
        if (!ajouterLettreAuRail(rail, lettres, cote, i, longueur)) {
            return 0; // Échec
        }

        // Retirer la lettre de la main du joueur
        retirerLettreDeMain(joueur, lettres[i]);
    }

    return 1; // Succès
}

char retirerLettreDuRail(Rail* rail, int cote) {
    char lettreRejetee;

    if (cote == 1) { // Ajouter à droite
        lettreRejetee = rail->cases[rail->debut];
        rail->debut = (rail->debut + 1) % MAX_CASES;
    }
    else { // Ajouter à gauche
        lettreRejetee = rail->cases[rail->fin];
        rail->fin = (rail->fin - 1 + MAX_CASES) % MAX_CASES;
    }

    rail->taille--;
    return lettreRejetee;
}

int ajouterLettreAuRail(Rail* rail, const char* lettres, int cote, int index, int longueur) {
    if (cote == 1) { // Ajouter à droite
        rail->fin = (rail->fin + 1) % MAX_CASES;
        rail->cases[rail->fin] = lettres[index];
    }
    else { // Ajouter à gauche
        rail->debut = (rail->debut - 1 + MAX_CASES) % MAX_CASES;
        rail->cases[rail->debut] = lettres[longueur - 1 - index];
    }

    rail->taille++;
    return 1; // Succès
}



// Fonction pour vérifier si un mot est présent dans un fichier
int verifierMotDansFichier(const char* cheminFichier, const char* mot_a_verifier) {
    char mot_lu[MAX_CHAR]; // Variable pour lire les mots du fichier
    FILE* fichier = fopen(cheminFichier, "r");

    if (fichier == NULL) {
        return 0; // Retourne 0 si le fichier ne peut pas être ouvert
    }

    // Lecture du fichier mot par mot
    while (fscanf(fichier, "%99s", mot_lu) != EOF) { // Utilisation de fscanf pour lire un mot
        if (strcmp(mot_lu, mot_a_verifier) == 0) { // Comparer le mot lu avec le mot à vérifier.
            // strcmp retourne 0 si les deux chaînes sont identiques.
            fclose(fichier);
            return 1; // Mot trouvé, retourne 1
        }
    }

    fclose(fichier);
    return 0; // Mot non trouvé, retourne 0
}

// Fonction pour ajouter un mot dans un tableau dynamique
int addInUsed(char*** tableau, int* taille, int* capacite, const char* mot) {
    if (*taille >= *capacite) {
        *capacite *= 2;
        char** nouveauTableau = realloc(*tableau, (*capacite) * sizeof(char*));
        if (!nouveauTableau) {
            return 0; // Échec
        }
        *tableau = nouveauTableau;
    }

    (*tableau)[*taille] = strdup(mot);
    if (!(*tableau)[*taille]) {
        return 0; // Échec
    }
    (*taille)++;
    return 1; // Succès
}


// Fonction pour afficher le tableau dynamique
void showUsed(char** tableau, int taille) {
    if (!tableau || taille <= 0) {
        printf("Le tableau dynamique est vide ou invalide.\n");
        return;
    }

    printf("Nombre d'elements dans le tableau dynamique : %d\n", taille);

    printf("Contenu du tableau dynamique :\n");
    for (int i = 0; i < taille; i++) {
        if (tableau[i]) {
            printf("- %s\n", tableau[i]); // Affiche l'élément si non NULL
        }
        else {
            printf("- (pointeur NULL)\n"); // Indique les cases non allouées
        }
    }
}


int isInUsed(const char** tableau, const int taille, const char* mot) {
    for (int i = 0; i < taille; ++i) {
        if (strcmp(tableau[i], mot) == 0) {
            return 1;
        }
    }
    return 0;
}

// Fonction pour libérer la mémoire
void freeUsed(char** tableau, int taille) {
    for (int i = 0; i < taille; i++) {
        free(tableau[i]); // Libérer chaque chaîne
    }
    free(tableau); // Libérer le tableau lui-même
}

//fonction pour ajouter un premier mot (experimentale)
int addFirstWord(Rail* rail, Joueur* joueur, const char* lettres, int cote) {
    int longueur = strlen(lettres);
    char lettreRejetee;

    // Vérifier si le mot est bien présent dans le dictionnaire
    const char* cheminFichier = "ods4.txt";
    if (!verifierMotDansFichier(cheminFichier, lettres)) {
        return 0;
    }

    // Vérifier si le joueur possède toutes les lettres nécessaires
    if (verifierLettresDansMain(joueur, lettres) == 0) {
        return 0; // Échec
    }
    if (longueur < 4 || longueur > 4) {
        return 0;
    }
    else {
        // Ajouter les lettres sur le rail
        for (int i = 0; i < longueur; i++) {

            // Ajouter la lettre au rail
            if (cote == 1) { // Ajouter à droite
                rail->fin = (rail->fin + 1) % MAX_CASES;
                rail->cases[rail->fin] = lettres[i];
            }
            else { // Ajouter à gauche
                rail->debut = (rail->debut - 1 + MAX_CASES) % MAX_CASES;
                rail->cases[rail->debut] = lettres[longueur - 1 - i];
            }
            rail->taille++;

            // Retirer la lettre de la main du joueur
            for (int j = 0; j < joueur->taille; j++) {
                if (joueur->main[j] == lettres[i]) {
                    // Décaler les lettres restantes pour combler le trou
                    for (int k = j; k < joueur->taille - 1; k++) {
                        joueur->main[k] = joueur->main[k + 1];
                    }
                    joueur->taille--;
                    break;
                }
            }
        }
    }

    return 1; // Succès
}



int verifierCompatibiliteRail(const Rail* rail, const char* lettresRail, int longueurRail, char cote) {
    int compatibleGauche = 1; // Assume compatible jusqu'à preuve du contraire
    int compatibleDroite = 1; // Assume compatible jusqu'à preuve du contraire

    // Vérification côté gauche
    for (int i = 0; i < longueurRail; i++) {
        int indexGauche;
        if (cote == 'R' || cote == 'r') {
            // Côté gauche pour rail à l'endroit
            indexGauche = (rail->debut + i) % MAX_CASES;
        }
        else if (cote == 'V' || cote == 'v') {
            // Côté gauche pour rail à l'envers
            indexGauche = (rail->fin - i + MAX_CASES) % MAX_CASES;
        }

        if (lettresRail[i] != '(' && lettresRail[i] != ')' &&
            rail->cases[indexGauche] != lettresRail[i]) {
            compatibleGauche = 0; // Incompatibilité détectée
            break;
        }
    }

    // Vérification côté droit
    for (int i = 0; i < longueurRail; i++) {
        int indexDroite;
        if (cote == 'R' || cote == 'r') {
            // Côté droit pour rail à l'endroit
            indexDroite = (rail->fin - longueurRail + 1 + i + MAX_CASES) % MAX_CASES;
        }
        else if (cote == 'V' || cote == 'v') {
            // Côté droit pour rail à l'envers
            indexDroite = (rail->debut + longueurRail - 1 - i + MAX_CASES) % MAX_CASES;
        }

        if (lettresRail[i] != '(' && lettresRail[i] != ')' &&
            rail->cases[indexDroite] != lettresRail[i]) {
            compatibleDroite = 0; // Incompatibilité détectée
            break;
        }
    }

    // Retourner les résultats de compatibilité
    if (compatibleGauche && compatibleDroite) {
        printf("Compatible avec les deux côtés.\n");
        return 2; // Compatible avec les deux côtés
    }
    if (compatibleGauche) {
        return 0; // Compatible avec le côté gauche
    }
    if (compatibleDroite) {
        return 1; // Compatible avec le côté droit
    }

    return -1; // Aucun côté compatible
}


// Fonction pour ajouter un mot sur le rail en respectant les règles spécifiées
char* ajouterMotSurRail(Rail* rail, Joueur* joueur, Joueur* joueur2, const char* saisie, const char* cheminDictionnaire, char** motsJoues, int* tailleMotsJoues) {
    char cote;           // Côté du rail ('R' ou 'V') 
    char mot[MAX_CHAR];       // Mot complet saisi (y compris les parenthèses)
    char motForme[MAX_CHAR];  // Nouveau mot formé (y compris lettres du rail)
    char lettresRail[MAX]; // Lettres extraites du rail
    int longueurRail = 0;

    // Lire le côté et le mot saisi
    if (sscanf(saisie, "%c %99s", &cote, mot) != 2) {
        return NULL;
    }

    // Validation du côté
    if (cote != 'R' && cote != 'r' && cote != 'V' && cote != 'v') {
        return NULL;
    }

    // Extraire les lettres entre parenthèses
    char* debutParenthese = strchr(mot, '(');
    char* finParenthese = strchr(mot, ')');

    if (!debutParenthese || !finParenthese || debutParenthese > finParenthese) {
        return NULL;
    }

    // Extraire les lettres du rail
    strncpy(lettresRail, debutParenthese + 1, finParenthese - debutParenthese - 1);
    lettresRail[finParenthese - debutParenthese - 1] = '\0';
    longueurRail = strlen(lettresRail);

    // Former le mot final
    strncpy(motForme, mot, debutParenthese - mot); // Partie avant les parenthèses
    motForme[debutParenthese - mot] = '\0';
    strcat(motForme, lettresRail);                 // Ajouter les lettres du rail
    strcat(motForme, finParenthese + 1);           // Partie après les parenthèses

    // Vérifier si le mot final existe dans le dictionnaire
    if (!verifierMotDansFichier(cheminDictionnaire, motForme)) {
        return NULL;
    }

    if (isInUsed((const char**)motsJoues, *tailleMotsJoues, motForme)) {
        return NULL;
    }



    // Vérifier si le joueur possède les lettres nécessaires (hors des parenthèses)
    char motHorsParenthese[MAX_CHAR];
    strncpy(motHorsParenthese, mot, debutParenthese - mot); // Partie avant les parenthèses
    motHorsParenthese[debutParenthese - mot] = '\0';
    strcat(motHorsParenthese, finParenthese + 1);           // Partie après les parenthèses


    if (verifierLettresDansMain(joueur, motHorsParenthese) == 0) {
        return 0; // Échec
    }


    // Regarde si c'est compatible 
    int numcote = verifierCompatibiliteRail(rail, lettresRail, longueurRail, cote);
    if (numcote == -1) {
        return NULL; // Aucun côté compatible
    }

    if ((cote == 'R') || (cote == 'r')) {
        // Ajouter le mot sur le rail
        ajouterLettresAuRail(rail, joueur, joueur2, motHorsParenthese, numcote);
    }
    else {
        ajouterlettresALenvers(rail, joueur, joueur2, motHorsParenthese, numcote);
    }



    // Creation pointeur pour renvoyer le resultat
    char* ptrMotForme = malloc((strlen(motForme) + 1) * sizeof(char));
    strcpy(ptrMotForme, motForme);
    return ptrMotForme; // Succès
}





int echangerLettre(Joueur* joueur, Chevalet* pioche, char lettre) {
    // Vérifier que la lettre est présente dans la main du joueur
    if (!verifierlettre(joueur, lettre)) {
        return 0;
    }

    // Vérifier que la pioche n'est pas vide
    if (pioche->taille <= 0) {
        return 0;
    }

    // Retirer une lettre au hasard de la pioche
    int indexAleatoire = rand() % pioche->taille;
    char lettrePiochee = pioche->lettres[indexAleatoire];

    // Ajouter la lettre de la pioche à la main du joueur
    if (!ajouterLettreDansMain(joueur, lettrePiochee)) {
        return 0;
    }

    // Retirer la lettre échangée de la main du joueur
    retirerLettreDeMain(joueur, lettre);

    // Retirer la lettre piochée de la pioche
    for (int i = indexAleatoire; i < pioche->taille - 1; i++) {
        pioche->lettres[i] = pioche->lettres[i + 1];
    }
    pioche->taille--;

    // Ajouter la lettre échangée à la pioche
    ajouterCarte(pioche, lettre);

    return 1;
}



int ajouterlettresALenvers(Rail* rail, Joueur* joueur, Joueur* adversaire, const char* lettres, int cote) {
    int longueur = strlen(lettres);
    char lettreRejetee;

    if (cote == 0) {
        cote = 1;

        for (int i = longueur - 1; i >= 0; --i) {
            // Gérer les cas de rail plein
            if (rail->taille == MAX_CASES) {
                lettreRejetee = retirerLettreDuRail(rail, cote);
                if (!ajouterLettreDansMain(adversaire, lettreRejetee)) {
                    return 0; // Échec si l'adversaire ne peut pas recevoir la lettre
                }
            }
            if (cote == 1) { // Côté droit
                rail->fin = (rail->fin + 1) % MAX_CASES;
                rail->cases[rail->fin] = lettres[i];
                /*ajouterLettreAuRail(rail, lettres, cote, i, longueur);*/
            }
            else {
                return 0; // Échec si le côté est invalide
            }

            rail->taille++; // Augmenter la taille après insertion

            // Retirer la lettre de la main du joueur
            retirerLettreDeMain(joueur, lettres[i]);
        }
    }

    else if (cote == 1) {
        cote = 0;

        for (int i = 0; i < longueur; ++i) {
            // Gérer les cas de rail plein
            if (rail->taille == MAX_CASES) {
                lettreRejetee = retirerLettreDuRail(rail, cote);
                if (!ajouterLettreDansMain(adversaire, lettreRejetee)) {
                    return 0; // Échec si l'adversaire ne peut pas recevoir la lettre
                }
            }

            // Ajouter la lettre au rail
            if (cote == 0) { // Côté gauche
                rail->debut = (rail->debut - 1 + MAX_CASES) % MAX_CASES;
                rail->cases[rail->debut] = lettres[i];
            }
            else {
                return 0; // Échec si le côté est invalide
            }

            rail->taille++; // Augmenter la taille après insertion

            // Retirer la lettre de la main du joueur
            retirerLettreDeMain(joueur, lettres[i]);
        }
    }


    return 1; // Succès
}



// Fonction qui vérifie si un mot valide de 8 lettres est formé sur le rail
int octo(Rail* rail) {
    // Vérifier si le rail contient exactement 8 lettres
    if (rail->taille != MAX_CASES) {
        return 0;  // Retourne 0 si le rail ne contient pas 8 lettres
    }

    // Construire le mot actuel sur le rail
    char motR[MAX_CASES + 1]; // Espace pour 8 lettres + caractère null
    for (int i = 0; i < MAX_CASES; i++) {
        motR[i] = rail->cases[(rail->debut + i) % MAX_CASES];
    }
    motR[MAX_CASES] = '\0'; // Terminer la chaîne

    char motV[MAX_CASES + 1]; // Espace pour 8 lettres + caractère null
    for (int i = 0; i < MAX_CASES; i++) {
        // Accéder au verso en inversant les indices
        motV[i] = rail->cases[(rail->debut + MAX_CASES - 1 - i) % MAX_CASES];
    }
    motV[MAX_CASES] = '\0'; // Terminer la chaîne

    // Vérifier si le mot est valide dans le dictionnaire
    if (verifierMotDansFichier("ods4.txt", motR)) {
        return 1;  // Retourne 1 si le mot est valide
    }

    else if (verifierMotDansFichier("ods4.txt", motV)) {
        return 1;  // Retourne 1 si le mot est valide
    }
    else {
        return 0;  // Retourne 0 si le mot n'est pas valide
    }
}

// Fonction qui demande au joueur de retirer une lettre de sa main
void retirerLettresiOcto(Joueur* joueur) {
    if (joueur->taille > 0) {
        // Demander au joueur quelle lettre retirer
        char lettreChoisie;

        scanf("%c", &lettreChoisie); // Lire la lettre choisie

        // Vérifier si la lettre est présente dans la main du joueur
        int index = -1;
        for (int i = 0; i < joueur->taille; i++) {
            if (joueur->main[i] == lettreChoisie) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            return; // Lettre non trouvée
        }

        // Retirer la lettre de la main du joueur
        retirerLettreDeMain(joueur, lettreChoisie);

    }
}






void copierRail(Rail* source, Rail* destination) {
    destination->taille = source->taille;
    destination->debut = source->debut;
    for (int i = 0; i < MAX_CASES; i++) {
        destination->cases[i] = source->cases[i];
    }
}


int ajouterMotSiSignalement(Rail* railPrecedent, Joueur* sauvegardeMainAdversaire, const char* motSignale, const char* cheminDictionnaire, char coteSignalement, Joueur* joueurCourant) {


    //if (!octo(railPrecedent)) {
        //printf("Erreur \n");
        //return 0;
    //}

    // Vérifier que le mot signalé existe dans le dictionnaire
    if (!verifierMotDansFichier(cheminDictionnaire, motSignale)) {
        return 0;
    }

    // Vérifier que le mot signalé peut être formé avec le rail précédent et la main de l'adversaire
    if (!verifierCompatibiliteRail(railPrecedent, motSignale, strlen(motSignale), coteSignalement) ||
        !verifierLettresDansMain(sauvegardeMainAdversaire, motSignale)) {
        return 0;
    }


    // Demander au joueur de choisir une lettre à retirer
    retirerLettresiOcto(joueurCourant);

    return 1;
}


