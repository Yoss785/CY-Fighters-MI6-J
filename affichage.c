#include <stdio.h>
#include <string.h>
#include "affichage.h"

// Fonction pour dessiner une barre (PV, vitesse, etc.)
void dessiner_barre(int valeur, int max, char symbole) {
    for (int i = 0; i < max; i++) {
        if (i < valeur) printf("%c", symbole);
        else printf(" ");
    }
}

// Fonction pour afficher une ligne du plateau
void afficher_ligne(int ligne, Combattant persos[], int nb_persos) { //ajouter int mode_complet
    printf("|");
    int j = 0;

    while (j < L) {
        int affiche = 0;

        for (int p = 0; p < nb_persos; p++) {
            int pos = persos[p].position;
            if (j == pos) {
                if (ligne == 2) {
                    int nb_caracteres = printf("%-20s", persos[p].nom); //%-20s le signe "-" c'est pour aligné à gauche
                    j += nb_caracteres;
                    affiche = 1;
                    break;
                } 
                else if (ligne == 4) {
                    printf("[");
                    dessiner_barre(persos[p].pv * MAX_BARRE / persos[p].pv_max, MAX_BARRE, '#');
                    printf("]");
                    j += MAX_BARRE + 2;
                    affiche = 1;
                    break;
                } 
                else if (ligne == 5) {
                    printf("[");
                    dessiner_barre(persos[p].vitesse * MAX_BARRE / 20, MAX_BARRE, '>');
                    printf("]");
                    j += MAX_BARRE + 2;
                    affiche = 1;
                    break;
                } 
                else if (ligne == 7 /*&& mode_complet*/) {
                    int nb_caracteres = printf("Attaque normale: faible dégât et aucun temps de rechargement ");
                    j += nb_caracteres;
                    affiche = 1;
                    break;
                }
                
                else if (ligne == 9 /*&& mode_complet*/) {
                    int nb_caracteres = printf("Technique:: %-15s", persos[p].techniques[0].nom);
                    j += nb_caracteres;
                    affiche = 1;
                    break;
                }
                else if (ligne == 10 /*&& mode_complet*/) {
                    int nb_caracteres = printf("%-40s", persos[p].techniques[0].description);
                    j += nb_caracteres;
                    affiche = 1;
                    break;
                }
                else if (ligne == 11 /*&& mode_complet*/) {
                    int nb_caracteres = printf("CD: %d |Disponible dans %d tour(s)", 
                        persos[p].techniques[0].tours_rechargement, 
                        persos[p].techniques[0].cooldown_actuel);
                    j += nb_caracteres;
                    affiche = 1;
                    break;
                }
            }
        }

        if (!affiche) {
            printf(" ");
            j++;
        }
    }
    printf("|\n");
}

// Fonction pour afficher le plateau en petit 
void afficher_plateau_petit(Combattant persos[], int nb_persos) {
    printf(" ");
    for (int i = 0; i < L; i++) printf("_");
    printf("\n");

    for (int i = 1; i <= h; i++) {
        afficher_ligne(i, persos, nb_persos); //ajouter "0" pour que mode_complet=0
    }

    printf(" ");
    for (int i = 0; i < L; i++) printf("_");
    printf("\n");
}

// Fonction pour afficher le plateau en grand
void afficher_plateau_grand(Combattant persos[], int nb_persos) {
    printf(" ");
    for (int i = 0; i < L; i++) printf("_");
    printf("\n");

    for (int i = 1; i <= H; i++) {
        afficher_ligne(i, persos, nb_persos); //ajouter"1" pour que mode_complet=1
    }

    printf(" ");
    for (int i = 0; i < L; i++) printf("_");
    printf("\n");
}

 //Fonction pour afficher les deux plateaux (le plateau de l'équipe 2 s'affiche pas car trop d'informations affichées)
void afficher_plateau(Combattant equipe1[], Combattant equipe2[]) {
    printf("\n=== Plateau Équipe 1 ===\n");
    afficher_plateau_grand(equipe1, TAILLE_EQUIPE);

    printf("\n=== Plateau Équipe 2 ===\n");
    afficher_plateau_petit(equipe2, TAILLE_EQUIPE);
}
/* void afficher_plateaux_selon_tour(Combattant equipe1[], Combattant equipe2[], int tour_equipe) {
    if (tour_equipe == 1) {
        printf("\n=== Tour de l'Équipe 1 ===\n");
        afficher_plateau_grand(equipe1, TAILLE_EQUIPE);
        afficher_plateau_petit(equipe2, TAILLE_EQUIPE);
    } else if (tour_equipe == 2) {
        printf("\n=== Tour de l'Équipe 2 ===\n");
        afficher_plateau_grand(equipe2, TAILLE_EQUIPE);
        afficher_plateau_petit(equipe1, TAILLE_EQUIPE);
    } else {
        printf("Erreur : numéro d'équipe invalide (tour_equipe = %d)\n", tour_equipe);
    }
}
*/
