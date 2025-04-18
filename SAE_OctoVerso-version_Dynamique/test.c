#include "test.h"

void testPioche() {
    //Test de la cr�ation de la pioche
    Chevalet* pioche = initPioche(MAX_CARTES);
    creerPioche(pioche);
    melangerPioche(pioche);
    afficherPioche(pioche);
    printf("%d\n", pioche->taille);
    assert(pioche->taille == 88);

    //Test de distribution des chevalets 
    Joueur joueurs[NB_JOUEURS];
    distribuerCartes(pioche, joueurs);
    afficherPioche(pioche);
    printf("%d\n", pioche->taille);
}

void testEstFini() {
    Joueur joueur;
    const char* lettresPredefinies[NB_JOUEURS] = {
        "", // Lettres pour le joueur 1
        "" };  // Lettres pour le joueur 2
    distribuerCartesPredefinies(lettresPredefinies, &joueur, 1);
    afficherMain(&joueur);
    printf("%d", joueur.taille);
    //assert(estFini(&joueur)); // Main vide, devrait retourner vrai (1)

}

void testInitRail() {
    Rail rail;
    initRail(&rail);
    assert(rail.taille == 0); // Rail initialis� vide
}

void testAddFirstWord() {
    Rail rail;
    Joueur joueur;

    initRail(&rail);

    const char* lettresPredefinies[NB_JOUEURS] = {
        "TEST", // Lettres pour le joueur 1
        "" };  // Lettres pour le joueur 2
    char mot[] = "TEST";
    distribuerCartesPredefinies(lettresPredefinies, &joueur, 1);

    assert(addFirstWord(&rail, &joueur, mot, 1)); // Ajout valide
    assert(rail.taille == 4); // Taille du rail apr�s ajout

}

void testAjouterMotSurRail() {
    Rail rail;
    Joueur joueur, joueur2;
    initRail(&rail);

    const char* lettresPredefinies[NB_JOUEURS] = {
       "TEST", // Lettres pour le joueur 1
       "PROUT" };  // Lettres pour le joueur 2
    char mot[] = "TEST";
    distribuerCartesPredefinies(lettresPredefinies, &joueur, 2);

    // Ajoute le mot sur le rail
    char* result = ajouterLettresAuRail(&rail, &joueur, &joueur2, mot, 1);
    assert(result != 0); // Mot ajout� avec succ�s
    assert(rail.taille == 4); // La taille du rail est correcte
    afficherRail(&rail);

}

void testOcto() {
    Rail rail;
    initRail(&rail);
    Joueur joueur, joueur2;
    const char* cheminFichier = "ods4.txt";

    const char* lettresPredefinies[NB_JOUEURS] = {
       "RENDFORT", // Lettres pour le joueur 1
       "PROUT" };  // Lettres pour le joueur 2
    char mot[] = "RENDFORT";
    distribuerCartesPredefinies(lettresPredefinies, &joueur, 1);

    int a = ajouterLettresAuRail(&rail, &joueur, &joueur2, mot, 1);
    assert(a == 1); // Si le rail atteint 8 lettres, octo devrait retourner 1
    //printf("%d\n", a);
    afficherRail(&rail);
}