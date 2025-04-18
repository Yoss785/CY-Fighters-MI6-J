
#include "code.h"

/*#define L 90
#define H 15
#define h 6
#define MAX_BARRE 14*/

/*typedef struct{
    char* nom;
    char* description;
    int cooldown:
    int duree;
    int degats;
    float agl_m; //multiplicateur d'agilité (pour Kizaru), implémenter si besoin pour l'atk ou la def pour d'autres personnages
    int cible; // 0 = soi-même, 1 = ennemi
}TS;// Technique spécial
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

/* 
// Fonction pour appliquer une technique spéciale à un ennemi (comme celle de Kizaru)
void appliquer_technique(Personnage *attaquant, Personnage *cible) {
    TS technique = attaquant->technique; 

    if (technique.cible == 1) { // Si la technique cible l'ennemi
        // Si la technique est un multiplicateur d'agilité
        if (technique.agl_m != 1.0) {
            cible->AGL = cible->AGL * technique.agl_m; // Applique le multiplicateur d'agilité
        }
        // Appliquer les dégâts
        cible->PV -= technique.degats; 
    }
}

*/
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
            //Ligne de nom des personnages
            if (j == pos) {
                if (ligne == 2) {
                    int nb_caracteres = printf("%s %d", persos[p].nom, persos[p].cible);
                    j += nb_caracteres;
                    affiche = 1;
                    break;
                    //Ligne des effets
                } else if (ligne == 3) {
                    int nb_caracteres = printf("{%s}", persos[p].effet);
                    j += nb_caracteres;
                    affiche = 1;
                    break;
                    //Ligne de la barre de vie
                } else if (ligne == 4) {
                    printf("[");
                    dessiner_barre(persos[p].PV, MAX_BARRE, '#');
                    printf("]");
                    j += MAX_BARRE + 2;
                    affiche = 1;
                    break;
                    //Ligne de la barre de tour
                } else if (ligne == 5) {
                    printf("[");
                    dessiner_barre(persos[p].VIT, MAX_BARRE, '>');
                    printf("]");
                    j += MAX_BARRE + 2;
                    affiche = 1;
                    break;
                }
            }
        }
        //Lignes de la description de la technique du personnage 
        if (ligne >= 7 && ligne <= 14 && j == 0) {
            TS tech = persos[0].technique;
            int nb_caracteres = 0;

            switch (ligne) {
                case 7:
                    nb_caracteres = printf("Technique du perso 1: %s", tech.nom);
                    break;
                case 8:
                    nb_caracteres = printf("Description: %s", tech.description);
                    break;
                case 9:
                    nb_caracteres = printf("Cooldown: %d", tech.cooldown);
                    break;
                case 10:
                    nb_caracteres = printf("Durée: %d", tech.duree);
                    break;
                case 11:
                    nb_caracteres = printf("Dégâts: %d", tech.degats);
                    break;
                case 12:
                    nb_caracteres = printf("Cible: %s", (tech.cible == 1) ? "Ennemi" : "Soi-même");
                    break;
                case 13:
                    nb_caracteres = printf("Multiplicateur AGL: %.2f", tech.agl_m);
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

/* Main
int main() {
    Personnage persos[3] = {
        {"AKAINU", "a", 1, 10, 14, 10, 10, 10, 10, 5, {"Grande eruption", "L'adversaire perd 4% de PV pendant 2 tours + 15PV", 3, 2, 15, 1.0f, 1}},
        {"AOKIJI",  "a", 2, 14, 14, 10, 10, 10 ,7, 38,{"Mur de glace", "L'adversaire perd 10 PV et ne peut pas attaquer au prochain tour", 4, 1, 10, 1.0f, 1}},
        {"KIZARU", "k", 3, 4, 14, 10, 10, 10, 12, 68,{"Illumination", "L'agilité de l'ennemi est multipliée par 0.6 et subit 10 dégâts", 3, 2, 10, 0.6f, 1}}};

    afficher_plateau_petit(persos, 3);
    afficher_plateau_grand(persos, 3);

    return 0;
}
*/
