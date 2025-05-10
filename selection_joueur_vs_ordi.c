#include <time.h>
#include <stdlib.h>
#include "selection.c"


void selection_joueur_vs_ordi(Combattant* joueur, Combattant* ordinateur, FILE* fichier) {
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        int j;

        // === JOUEUR HUMAIN ===
        do {
            rewind(fichier);
            printf("\nJoueur - Sélection du combattant %d\n", i + 1);
            construction_perso(&joueur[i], fichier);

            for (j = 0; j < i; j++) {
                if (strcmp(joueur[i].nom, joueur[j].nom) == 0) {
                    printf("Ce personnage est déjà dans votre équipe. Recommencez.\n");
                    break;
                }
            }
        } while (j < i);
        joueur[i].position = i * 25;

        // === ORDINATEUR ===
        do {
            rewind(fichier);
            construction_perso_auto(&ordinateur[i], fichier);

            // Vérifie dans son équipe
            for (j = 0; j < i; j++) {
                if (strcmp(ordinateur[i].nom, ordinateur[j].nom) == 0) {
                    break;
                }
            }

            // Vérifie contre l'équipe du joueur
            for (int k = 0; k < TAILLE_EQUIPE; k++) {
                if (strcmp(ordinateur[i].nom, joueur[k].nom) == 0) {
                    j = 0; // forcer une nouvelle tentative
                    break;
                }
            }
        } while (j < i);
        ordinateur[i].position = i * 25;

        // === AFFICHAGE STATS DU CHOIX DE L'ORDI ===
        printf("\nL'ordinateur a sélectionné : %s\n", ordinateur[i].nom);
        afficher_stats(ordinateur[i]);
    }
}



void construction_perso_auto(Combattant* perso, FILE* fichier) {
    char buffer[200];
    int choix;
    int numero = 1;

    
    // srand(time(NULL));  ← À faire dans le main

    // Choisir un numéro aléatoire entre 1 et NBPERSO
    choix = (rand() % NBPERSO) + 1;

    rewind(fichier);

    // Avancer dans le fichier jusqu'au bon combattant
    while (numero < choix && fgets(buffer, sizeof(buffer), fichier)) {
        if (strcmp(buffer, "-\n") == 0) {
            numero++;
        }
    }

    fgets(perso->nom, MAX_NOM, fichier);
    perso->nom[strcspn(perso->nom, "\n")] = '\0';

    fscanf(fichier, "%d\n", &perso->pv_max);
    perso->pv = perso->pv_max;
    fscanf(fichier, "%d\n", &perso->attaque);
    fscanf(fichier, "%d\n", &perso->defense);
    fscanf(fichier, "%d\n", &perso->agilite);
    fscanf(fichier, "%d\n", &perso->vitesse);

    fgets(perso->techniques[0].nom, MAX_NOM, fichier);
    perso->techniques[0].nom[strcspn(perso->techniques[0].nom, "\n")] = '\0';

    fgets(perso->techniques[0].description, MAX_DESC, fichier);
    perso->techniques[0].description[strcspn(perso->techniques[0].description, "\n")] = '\0';

    fscanf(fichier, "%d\n", &perso->techniques[0].tours_rechargement);
    fscanf(fichier, "%d\n", &perso->techniques[0].cooldown_actuel);

    // Initialisation par défaut
    perso->techniques[0].propriete_affectee[0] = '\0'; 
    perso->techniques[0].operation[0] = '\0';
    perso->est_actif = 0;
    perso->nb_techniques = 1;
    perso->action = 0;
    perso->est_KO = 0;
    perso->position = -1;
    perso->brulure = 0;
    perso->debuff_agilite = 0;
    perso->buff_defense = 0;
    perso->buff_attaque = 0;
}
