#include <stdio.h>
#include <string.h>
#include "affichage.h"
#include "code.h"

// Définition des lignes d'affichage
#define LIGNE_NOM 2
#define LIGNE_PV 4
#define LIGNE_BARRE 5
#define LIGNE_TECH 9
#define LIGNE_DESC 10
#define LIGNE_CD 11

void dessiner_barre(int valeur, int max, char symbole) {
    for (int i = 0; i < max; i++) {
        putchar((i < valeur) ? symbole : ' ');
    }
}

void afficher_ligne(int ligne, Combattant persos[], int nb_persos, int est_grand_plateau) {
    char buffer[L + 1];
    memset(buffer, ' ', L);
    buffer[L] = '\0';

    putchar('|');

    int espacement = est_grand_plateau ? 25 : 20;

    for (int i = 0; i < nb_persos; i++) {
        Combattant* perso = &persos[i];
        if (perso->est_KO) continue;

        int pos_affichage = i * espacement;

        if (pos_affichage < 0 || pos_affichage >= L - 1) continue;

        if (ligne == LIGNE_NOM) {
            snprintf(buffer + pos_affichage, L - pos_affichage,
                     perso->est_actif ? "> %-18s <" : "  %-20s", perso->nom);
        } else if (ligne == LIGNE_PV) {
            snprintf(buffer + pos_affichage, L - pos_affichage,
                     "[%3d/%3d]   ", perso->pv, perso->pv_max);
        } else if (ligne == LIGNE_BARRE) {
            int nb = (perso->action * MAX_BARRE) / 100;
            if (nb > MAX_BARRE) nb = MAX_BARRE;

            char barre[MAX_BARRE + 3];
            barre[0] = '[';
            for (int j = 0; j < MAX_BARRE; j++)
                barre[j + 1] = (j < nb) ? '>' : ' ';
            barre[MAX_BARRE + 1] = ']';
            barre[MAX_BARRE + 2] = '\0';

            snprintf(buffer + pos_affichage, L - pos_affichage, "%s", barre);
        }

        if (perso->est_actif && perso->nb_techniques > 0) {
            if (ligne == LIGNE_TECH) {
                snprintf(buffer + pos_affichage, L - pos_affichage, "Technique: %-20s", perso->techniques[0].nom);
            } else if (ligne == LIGNE_DESC) {
                snprintf(buffer + pos_affichage, L - pos_affichage, "%.*s",
                         (L - pos_affichage > 70) ? 70 : (L - pos_affichage - 1),
                         perso->techniques[0].description);
            } else if (ligne == LIGNE_CD) {
                snprintf(buffer + pos_affichage, L - pos_affichage,
                         "CD: %2d | Dispo dans %2d tour(s)",
                         perso->techniques[0].tours_rechargement,
                         perso->techniques[0].cooldown_actuel);
            }
        }
    }

    printf("%s|\n", buffer);
}

void afficher_plateau_petit(Combattant persos[], int nb_persos) {
    putchar(' ');
    for (int i = 0; i < L; i++) putchar('_');
    putchar('\n');

    for (int l = 1; l <= h; l++)
        afficher_ligne(l, persos, nb_persos, 0);

    putchar(' ');
    for (int i = 0; i < L; i++) putchar('_');
    putchar('\n');
}

void afficher_plateau_grand(Combattant persos[], int nb_persos) {
    putchar(' ');
    for (int i = 0; i < L; i++) putchar('_');
    putchar('\n');

    for (int l = 1; l <= H; l++)
        afficher_ligne(l, persos, nb_persos, 1);

    putchar(' ');
    for (int i = 0; i < L; i++) putchar('_');
    putchar('\n');
}

void afficher_plateau(Combattant equipe1[], Combattant equipe2[]) {
    Combattant* actif = NULL;
    int equipe1_active = 0;

    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        if (equipe1[i].est_actif) {
            actif = &equipe1[i];
            equipe1_active = 1;
            break;
        } else if (equipe2[i].est_actif) {
            actif = &equipe2[i];
            break;
        }
    }

    if (equipe1_active) {
        printf("=== ÉQUIPE 1 (actif) ===\n");
        afficher_plateau_grand(equipe1, TAILLE_EQUIPE);
        printf("=== ÉQUIPE 2 ===\n");
        afficher_plateau_petit(equipe2, TAILLE_EQUIPE);
    } else {
        printf("=== ÉQUIPE 2 (actif) ===\n");
        afficher_plateau_grand(equipe2, TAILLE_EQUIPE);
        printf("=== ÉQUIPE 1 ===\n");
        afficher_plateau_petit(equipe1, TAILLE_EQUIPE);
    }
}
