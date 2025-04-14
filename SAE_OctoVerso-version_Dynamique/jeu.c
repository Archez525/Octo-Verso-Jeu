//
// Created by fitig on 03/12/2024.
//
#pragma warning disable 4103
#define _CRT_SECURE_NO_WARNINGS
#define strdup _strdup

#include "jeu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void jeu() {

    // Variables nécessaires
    char saisie[MAX_CHAR];      // Entrée du joueur (mot + côté)
    int joueurActuel = 0;  // Index du joueur courant
    // Initialisation du tableau dynamique pour les mots déjà utilisés
    int capacite = 2;  // Capacité initiale
    int taille = 0;    // Nombre d'éléments dans le tableau
    char** tableau = malloc(capacite * sizeof(char*));
    if (!tableau) {
        return;
    }

    srand(time(NULL)); // Initialisation aléatoire

    const char* cheminFichier = "ods4.txt"; // Chemin du fichier à vérifier

    Joueur sauvegardeMainPrecedente; // Sauvegardes des mains
    Joueur maintemporaire;

    // Initialisation des rails
    Rail rail, railprecedent;
    initRail(&rail);
    initRail(&railprecedent); // Initialisation du rail qui sert de sauvegarde


    // Initialisation de la pioche
    Chevalet* pioche = initPioche(MAX_CARTES);
    creerPioche(pioche);
    melangerPioche(pioche);

    // Initialisation des joueurs
    Joueur joueurs[NB_JOUEURS]; // Assurez-vous que NB_JOUEURS est défini correctement (2 ici)



    const char* lettresPredefinies[NB_JOUEURS] = {
        "DEJMNNNORRSS", // Lettres pour le joueur 1
        "AAAEEEEILMTT" };  // Lettres pour le joueur 2

    printf("Appuyez sur 1 pour utiliser les cartes predefinies ou sur 2 pour une partie normal avec des cartes aleatoires.\n");
    int choix;
    if (scanf("%d", &choix) != 1) {
        printf("Entrée invalide. Le jeu sera arrete.\n");
        free(tableau);
        return;
    }
    while (getchar() != '\n'); 

    // Distribution des cartes selon le choix
    if (choix == 1) {
        distribuerCartesPredefinies(lettresPredefinies, joueurs, NB_JOUEURS);
        printf("Cartes predefinies distribuees.\n");
    }
    else if (choix == 2) {
        distribuerCartes(pioche, joueurs);
        printf("Cartes distribuees de maniere aléatoire.\n");
    }
    else {
        printf("Choix invalide. Le jeu sera arrete.\n");
        free(tableau);
        return;
    }

    // Affichage initial des mains des joueurs
    for (int i = 0; i < NB_JOUEURS; ++i) {
        printf("%d : ", i + 1);
        afficherMain(&joueurs[i]);
    }
    printf("\n");
    // Rail initialement vide
    afficherRail(&rail);

    // Sauvegarde initiale pour éviter un état non initialisé
    sauvegarderMain(&joueurs[0], &sauvegardeMainPrecedente);
    sauvegarderMain(&joueurs[0], &maintemporaire);// Creation d'une main temporaire pour stocké


    // Début de la partie
    int jeuEnCours = 1; // Indicateur pour continuer ou terminer le jeu
    while (jeuEnCours) {
        Joueur* joueur2 = &joueurs[(joueurActuel + 1) % NB_JOUEURS];



        // Vérification si la partie est terminée
        if (estFini(&joueurs[joueurActuel])) {
            break; // Sort de la boucle pour terminer la partie
        }

        printf("%d> ", joueurActuel + 1);


        // Validation et ajout du mot au rail
        if (rail.taille == 0) {
            // Cas où le rail est vide ou à capacité spécifique
            fgets(saisie, sizeof(saisie), stdin);
            saisie[strcspn(saisie, "\n")] = '\0'; // Supprimer le saut de ligne

            if (addFirstWord(&rail, &joueurs[joueurActuel], saisie, 1)) {
                addInUsed(&tableau, &taille, &capacite, saisie);

            }
            else {
                continue; // Rejoue le tour du même joueur
            }
        }

        else if (rail.taille == 4) {
            // Cas où le rail est vide ou à capacité spécifique
            fgets(saisie, sizeof(saisie), stdin);
            saisie[strcspn(saisie, "\n")] = '\0'; // Supprimer le saut de ligne

            if (addFirstWord(&rail, &joueurs[joueurActuel], saisie, 0)) {
                addInUsed(&tableau, &taille, &capacite, saisie);
                // Afficher les mains des joueurs
                printf("\n");
                for (int i = 0; i < NB_JOUEURS; ++i) {
                    printf("%d : ", i + 1);
                    afficherMain(&joueurs[i]);

                }
                // Afficher le rail après l'ajout du mot
                afficherRail(&rail);
                printf("\n");

                if (comparerMots(tableau[0], tableau[1]) == 0) { // compare pour savoir qui va jouer en premier
                    joueurActuel = (joueurActuel + 1) % NB_JOUEURS;

                }
            }
            else {
                continue; // Rejoue le tour du même joueur
            }
        }

        else {
            // Cas où le rail est déjà en cours

            fgets(saisie, sizeof(saisie), stdin);
            saisie[strcspn(saisie, "\n")] = '\0'; // Supprimer le saut de ligne

            // Vérifier si l'entrée correspond à un échange de lettre (format : '- lettre')
            if (saisie[0] == '-' && strlen(saisie) == 3) { // Vérifier la longueur de saisie qui ddoit correpondre à 3
                char lettre = saisie[2]; // Lettre après le tiret

                // Tenter d'échanger la lettre
                if (!echangerLettre(&joueurs[joueurActuel], pioche, lettre)) {
                    continue; // Rejoue le tour
                }
				printf("\n");
                // Afficher les mains des joueurs
                for (int i = 0; i < NB_JOUEURS; ++i) {
                    printf("%d : ", i + 1);
                    afficherMain(&joueurs[i]);

                }
                // Afficher le rail après l'ajout du mot
                afficherRail(&rail);
                printf("\n");
            }
            // Sinon, traiter l'entrée comme un mot
            else if (saisie[0] == 'R' || saisie[0] == 'V') {

                // Sauvegarde de la main du joueur et du rail afin de pouvoir les restaurer en cas de signalement d'octo
                sauvegarderMain(&joueurs[joueurActuel], &sauvegardeMainPrecedente);
                copierRail(&rail, &railprecedent);
                ;
                // Ajouter le mot au rail
                char* mot = ajouterMotSurRail(&rail, &joueurs[joueurActuel], joueur2, saisie, cheminFichier, tableau, &taille); // Ajouter le mot au rail et le stocker dans mot
                printf("\n");
                // Activer la fonction octo si le rail atteint 8 lettres
                if (octo(&rail) == 1) {

                    // Afficher les mains des joueurs
                    for (int i = 0; i < NB_JOUEURS; ++i) {
                        printf("%d : ", i + 1);
                        afficherMain(&joueurs[i]);
                    }
                    afficherRail(&rail); // Afficher le rail après l'ajout du mot
                    printf("\n");
                    printf("-%d> ", joueurActuel + 1);
                    retirerLettresiOcto(&joueurs[joueurActuel]); // Retirer une lettre de la main du joueur
					printf("\n");
                }
                if (mot) {
                    addInUsed(&tableau, &taille, &capacite, mot);
                    // Afficher les mains des joueurs
                    for (int i = 0; i < NB_JOUEURS; ++i) {
                        printf("%d : ", i + 1);
                        afficherMain(&joueurs[i]);

                    }
                    // Afficher le rail après l'ajout du mot
                    afficherRail(&rail);
                    printf("\n");
                }
                else {
                    continue; // Rejoue le tour du même joueur
                }
            }
            // Sinon, traiter l'entrée comme un mot
            else if (saisie[0] == 'r' || saisie[0] == 'v') {

                // Ajouter le mot au rail
                char* mot = ajouterMotSurRail(&railprecedent, &sauvegardeMainPrecedente, &maintemporaire, saisie, cheminFichier, tableau, &taille);
                afficherRail(&railprecedent);
                // Activer la fonction octo si le rail atteint 8 lettres
                if (octo(&railprecedent) == 1) {

                    printf("-%d> ", joueurActuel + 1);
                    retirerLettresiOcto(&joueurs[joueurActuel]); // Retirer une lettre de la main du joueur
                    viderMainTemporaire(&maintemporaire);
                    joueurActuel = (joueurActuel + 1) % NB_JOUEURS; // Passer au joueur suivant afin que le même joueur puisse rejouer aprés.

                }
                if (mot) {
                    addInUsed(&tableau, &taille, &capacite, mot);
                    // Afficher les mains des joueurs
                    for (int i = 0; i < NB_JOUEURS; ++i) {
                        printf("%d : ", i + 1);
                        afficherMain(&joueurs[i]);

                    }
                    // Afficher le rail après l'ajout du mot
                    afficherRail(&rail);
                    printf("\n");
                }
                else {
                    continue; // Rejoue le tour du même joueur
                }

            }
            else {
                continue; // Rejoue le tour
            }
        }






        // Vérification si la partie est terminée
        if (estFini(&joueurs[joueurActuel])) {
            break; // Sort de la boucle pour terminer la partie
        }

        // Passer au joueur suivant
        joueurActuel = (joueurActuel + 1) % NB_JOUEURS;



    }
    // Afficher les mots utilisés
    printf("\n=== Mots utilises pendant la partie ===\n");
    showUsed(tableau, taille);



    // Libérer les ressources allouées
    detruirePioche(pioche);
    freeUsed(&tableau, capacite);

    printf("\nPartie terminée ! Merci d'avoir joué.\n");

}


int estFini(const Joueur* joueur) {
    if (estVide(joueur)) // regarder si la main du joueur est vide
        return 1;
    return 0;
}