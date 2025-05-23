//
// Created by fitig on 03/12/2024.
//
#pragma warning disable 4103
#define _CRT_SECURE_NO_WARNINGS
#define strdup _strdup


#include "joueur.h"

#include <stdio.h>
#include <stdlib.h>

// Fonction de comparaison pour qsort
int comparerLettres(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

void afficherMain(const Joueur* joueur) {
    // Trier la main en utilisant qsort
    qsort(joueur->main, joueur->taille, sizeof(char), comparerLettres);

    // Afficher la main tri�e
    for (int i = 0; i < joueur->taille; ++i) {
        printf("%c ", joueur->main[i]);
    }
    printf("\n");
}


int ajouterLettreDansMain(Joueur* joueur, char lettre) {
    if (!joueur) {
        return 0; // �chec
    }

    if (joueur->taille >= MAX_MAIN) {
        return 0; // �chec
    }

    joueur->main[joueur->taille] = lettre; // Ajout de la lettre
    joueur->taille++; // Incr�mentation de la taille
    return 1; // Succ�s
}

void retirerLettreDeMain(Joueur* joueur, char lettre) {
    for (int j = 0; j < joueur->taille; j++) {
        if (joueur->main[j] == lettre) {
            // D�caler les lettres restantes pour combler le trou
            for (int k = j; k < joueur->taille - 1; k++) {
                joueur->main[k] = joueur->main[k + 1];
            }
            joueur->taille--;
            break;
        }
    }
}

int estVide(const Joueur* joueur) {
    if (joueur->taille == 0)
        return 1;
    return 0;
}

int nbLettreMot(const char* mot, char lettre) {
    int longueur = strlen(mot);
    int nbLettre = 0;// Compteur pour le nombre de fois que la lettre est dans la main
    for (int i = 0; i < longueur; i++) {
        if (lettre == mot[i]) {
            ++nbLettre;
        }
    }
    return nbLettre;
}

int nbLettreMain(const Joueur* joueur, char lettre) {
    int nbLettre = 0;// Compteur pour le nombre de fois que la lettre est dans la main
    for (int i = 0; i < joueur->taille; i++) {
        if (lettre == joueur->main[i]) {
            ++nbLettre;
        }
    }
    return nbLettre;
}

int verifierLettresDansMain(Joueur* joueur, const char* lettres) {
    int longueur = strlen(lettres);

    for (int i = 0; i < longueur; ++i) {
        int a = nbLettreMot(lettres, lettres[i]); // Nombre d'occurrences de la lettre dans 'lettres'
        int b = nbLettreMain(joueur, lettres[i]); // Nombre d'occurrences de la lettre dans la main du joueur

        if (b < a) {
            return 0; // Une lettre manquante ou insuffisante => �chec imm�diat
        }
    }

    return 1; // Toutes les lettres sont pr�sentes en quantit� suffisante
}

int verifierlettre(Joueur* joueur, char lettre) {
    for (int i = 0; i < joueur->taille; i++) {
        if (joueur->main[i] == lettre) {
            return 1;
        }
    }
    return 0;
}



void sauvegarderMain(const Joueur* joueur, Joueur* sauvegarde) {
    // Copier le nombre de cartes dans la main
    sauvegarde->taille = joueur->taille;
    // Copier chaque carte de la main
    for (int i = 0; i < joueur->taille; i++) {
        sauvegarde->main[i] = joueur->main[i];
    }
}

void viderMainTemporaire(Joueur* mainTemporaire) {
    while (mainTemporaire->taille > 0) {
        // Supprimer la premi�re lettre de la main temporaire
        retirerLettreDeMain(mainTemporaire, mainTemporaire->main[0]);
    }
    printf("La main temporaire a �t� vid�e.\n");
}

