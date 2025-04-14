
#include "code.h"

/*#define L 90
#define H 6
#define MAX_BARRE 14*/

/*typedef struct{
    char* nom;
    char* description;
    int cooldown:
    int duree;
    int degats;
    float agl_m; //multiplicateur d'agilité (pour Kizaru), implémenter si besoin pour l'atk ou la def pour d'autres personnages
    int cible; // 0 = soi-même, 1 = ennemi
]TS;// Technique spécial
*/

// Structure pour stocker un personnage
/*typedef struct {
    char *nom;
    char *effet;
    int cible;
    int PV;
    int PVmax;
    int ATQ;
    int DEF;
    int AGL;
    int VIT;
    int position;  // position horizontale du perso
    TS technique;
} Personnage;*/

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
    for (int j = 0; j < L; j++) {
        int affiché = 0;

        // On parcourt chaque perso
        for (int p = 0; p < nb_persos; p++) {
            int pos = persos[p].position;

            // Ligne des noms
            if (ligne == 2 && j == pos) {
                printf("%s %d", persos[p].nom, persos[p].cible);
                j += strlen(persos[p].nom) + 1;
                affiché = 1;
            }
            // Ligne des effets
            else if (ligne == 3 && j == pos) {
                printf("{%s}", persos[p].effet);
                j += strlen(persos[p].effet) + 1;
                affiché = 1;
            }
            // Barre de PV
            else if (ligne == 4 && j == pos) {
                printf("[");
                dessiner_barre(persos[p].PV, MAX_BARRE, '#');
                printf("]");
                j += MAX_BARRE + 1;
                affiché = 1;
            }
            // Barre de tour
            else if (ligne == 5 && j == pos) {
                printf("[");
                dessiner_barre(persos[p].tour, MAX_BARRE, '>');
                printf("]");
                j += MAX_BARRE + 1;
                affiché = 1;
            }
        }

        if (!affiché)
            printf(" ");
    }
    printf("|\n");
}

// Fonction principale d'affichage du plateau
void afficher_plateau(Personnage persos[], int nb_persos) {
    // Haut du cadre
    printf(" ");
    for (int i = 0; i < L; i++) printf("_");
    printf("\n");

    // Lignes du plateau
    for (int i = 1; i <= H; i++) {
        afficher_ligne(i, persos, nb_persos);
    }

    // Bas du cadre
    printf(" ");
    for (int i = 0; i < L; i++) printf("_");
    printf("\n");
}

/* Main
int main() {
    Personnage persos[3] = {
        {"AKAINU", "a", 1, 10, 14, 10, 10, 10, 10, 5,{"Grande eruption", "L'adversaire perd 4% de PV  pendant 2 tours + 15PV ", 3, 2, 15, 1, 1}},
        {"AOKIJI",  "a", 2, 14, 14, 10, 10, 10 7, 38,{"Mur de glace", "L'avdersaire perd 10 PV et ne peut pas attaqué au prochain tour", 4, 1, 10, 1, 1},
        {"KIZARU", "k", 3, 4, 14, 10, 10, 10, 12, 68, {"Illumination", "L'agilité de l'ennemi est multipliée par 0.6 et subit 10 dégâts", 3, 2, 10, 0.6, 1}" }
    };

    afficher_plateau(persos, 3);
    return 0;
}
*/
