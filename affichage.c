
#include "code.h"

/*#define L 90
#define H 6
#define MAX_BARRE 14*/

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
        {"LUFFY", "o", 1, 10, 10, 5},
        {"ZORO",  "z", 2, 14, 7, 38},
        {"SANJI", "s", 3, 4, 12, 68}
    };

    afficher_plateau(persos, 3);
    return 0;
}
*/
