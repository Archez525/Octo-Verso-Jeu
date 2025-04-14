//
// Created by fitig on 03/12/2024.
//
#pragma warning disable 4103
#define _CRT_SECURE_NO_WARNINGS
#define strdup _strdup

#include "chevalet.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



Chevalet* initPioche(int capacite) {
    Chevalet* pioche = (Chevalet*)malloc(sizeof(Chevalet)); // Allouer la structure
    if (pioche == NULL) {
        return;
    }

    pioche->lettres = (char*)malloc(capacite * sizeof(char)); // Allouer le tableau de lettres
    if (pioche->lettres == NULL) {
        free(pioche); // Libérer la structure en cas d'échec
        return;
    }

    pioche->taille = 0;       // Commence vide
    pioche->capacite = capacite; // Stocker la capacité

    return pioche;
}

void detruirePioche(Chevalet* pioche) {
    if (pioche) {
        free(pioche->lettres);// Libére la mémoire allouée pour le tableau de lettres
        free(pioche);         // Libére la mémoire allouée pour la structure Chevalet

    }
}

void ajouterCarte(Chevalet* pioche, char lettre) {
    if (pioche->taille < pioche->capacite) {
        // Ajouter la lettre à l'indice correspondant à la taille actuelle de la pioche
        pioche->lettres[pioche->taille++] = lettre; // Ajouter la lettre et incrémenter la taille
    }
}


void creerPioche(Chevalet* pioche) {
    int repetitions[] = { 9, 1, 2, 3, 14, 1, 1, 1, 7, 1, 5, 3, 6, 5, 2, 1, 6, 7, 6, 5, 2 };
    char lettres[] = "ABCDEFGHIJLMNOPQRSTUV"; // Lettres correspondant aux répétitions

    // Calculer le nombre total de lettres à ajouter
    int totalCartes = 0;
    for (int i = 0; i < LETTRE; ++i) {
        totalCartes += repetitions[i]; // Additionner toutes les répétitions
    }
    // Vérifier que la pioche a suffisamment de capacité pour accueillir toutes les lettres
    if (totalCartes > pioche->capacite) {
        return; // Arrêter si la capacité est insuffisante
    }

    // Ajouter les lettres à la pioche en fonction des répétitions
    for (int i = 0; i < LETTRE; ++i) {         // Parcourir chaque lettre
        for (int j = 0; j < repetitions[i]; ++j) { // Ajouter la lettre 'repetitions[i]' fois
            ajouterCarte(pioche, lettres[i]); // Ajouter la lettre à la pioche
        }
    }
}


void melangerPioche(Chevalet* pioche) {
    if (pioche == NULL || pioche->lettres == NULL || pioche->taille <= 1) {
        return;
    }
    // Algorithme de mélange Fisher-Yates du cours
    for (int i = pioche->taille - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        char temp = pioche->lettres[i];
        pioche->lettres[i] = pioche->lettres[j];
        pioche->lettres[j] = temp;
    }
}

void distribuerCartes(Chevalet* pioche, Joueur joueurs[NB_JOUEURS]) {
    // Vérifier si la pioche contient suffisamment de cartes
    if (CARTES_PAR_JOUEUR * NB_JOUEURS > pioche->taille) {
        return; // Arrêter si la pioche ne contient pas assez de cartes
    }

    // Parcourir chaque joueur
    for (int i = 0; i < NB_JOUEURS; ++i) {
        joueurs[i].taille = 0; // Initialiser la taille de la main du joueur
        for (int j = 0; j < CARTES_PAR_JOUEUR; ++j) {
            // Donner une carte de la pioche au joueur
            joueurs[i].main[j] = pioche->lettres[--pioche->taille];
            joueurs[i].taille++; // Incrémenter la taille de la main du joueur
        }
    }
}

void afficherPioche(const Chevalet* pioche) {
    for (int i = 0; i < pioche->taille; ++i) {
        printf("%c ", pioche->lettres[i]);
    }
    printf("\n");
}

void distribuerCartesPredefinies(const char* lettresJoueurs[], Joueur joueurs[], int nbJoueurs) {
    for (int i = 0; i < nbJoueurs; ++i) {
        const char* lettres = lettresJoueurs[i];
        int longueur = strlen(lettres);

        if (longueur > CARTES_PAR_JOUEUR) {
            return;
        }

        joueurs[i].taille = 0;
        for (int j = 0; j < longueur; ++j) {
            joueurs[i].main[j] = lettres[j];
            joueurs[i].taille++;
        }
    }
}