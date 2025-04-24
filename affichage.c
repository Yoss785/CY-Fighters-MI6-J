#include <stdio.h>
#include <string.h>
#include "affichage.h"

/*#define L 90
#define H 15
#define h 6
#define MAX_BARRE 14*/


// Fonction pour dessiner une barre (PV ou tour)
void dessiner_barre(int valeur, int max, char symbole) {
    for (int i = 0; i < max; i++) {
        if (i < valeur)
            printf("%c", symbole);
        else
            printf(" ");
    }
}

// Fonction pour afficher une ligne du plateau
void afficher_ligne(int ligne, Personnage persos[], int nb_persos) {
    printf("|");
    int j = 0;
    while (j < L) {
        int affiche = 0;

        for (int p = 0; p < nb_persos; p++) {
            int pos = persos[p].position;
            if (j == pos) {
                if (ligne == 2) {
                    int nb_caracteres = printf("%s", persos[p].nom);
                    j += nb_caracteres;
                    affiche = 1;
                    break;
                } else if (ligne == 4) {
                    printf("[");
                    dessiner_barre(persos[p].pv * MAX_BARRE / persos[p].pv_max, MAX_BARRE, '#');
                    printf("]");
                    j += MAX_BARRE + 2;
                    affiche = 1;
                    break;
                } else if (ligne == 5) {
                    printf("[");
                    dessiner_barre(persos[p].vitesse * MAX_BARRE / 20, MAX_BARRE, '>');
                    printf("]");
                    j += MAX_BARRE + 2;
                    affiche = 1;
                    break;
                }
            }
        }
        //Lignes de la description de la technique du personnage 
        if (ligne >= 7 && ligne <= 13 && j == 0 && nb_persos > 0) {
            TechniqueSpeciale tech = persos[0].techniques[0];
            int nb_caracteres = 0;

            switch (ligne) {
                case 9:
                    nb_caracteres = printf("Technique: %s", tech.nom);
                    break;
                case 10:
                    nb_caracteres = printf("Description: %s", tech.description);
                    break;
                case 11:
                    nb_caracteres = printf("Valeur: %d", tech.degat);
                    break;
                case 12:
                    nb_caracteres = printf("Cooldown: %d", tech.tours_rechargement);
                    break;
                case 13:
                    nb_caracteres = printf("Dispo dans: %d", tech.cooldown_actuel);
                    break;
            }

            // Compléter avec des espaces
            while (j + nb_caracteres < L) {
                printf(" ");
                nb_caracteres++;
            }

            j = L;
            affiche = 1;
        }

        if (!affiche) {
            printf(" ");
            j++;
        }
    }

    printf("|\n");
}

// Fonctions d'affichage du plateau (petit et grand)
void afficher_plateau_petit(Personnage persos[], int nb_persos) {
    printf(" ");
    for (int i = 0; i < L; i++) printf("_");
    printf("\n");

    for (int i = 1; i <= h; i++) {
        afficher_ligne(i, persos, nb_persos);
    }

    printf(" ");
    for (int i = 0; i < L; i++) printf("_");
    printf("\n");
}

void afficher_plateau_grand(Personnage persos[], int nb_persos) {
    printf(" ");
    for (int i = 0; i < L; i++) printf("_");
    printf("\n");

    for (int i = 1; i <= H; i++) {
        afficher_ligne(i, persos, nb_persos);
    }

    printf(" ");
    for (int i = 0; i < L; i++) printf("_");
    printf("\n");
}


