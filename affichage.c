#include <stdio.h>
#include <string.h>
#include "affichage.h"
#include "code.h"
#include "combat.h"
#include <stdlib.h>

void effacer_ecran() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void afficher_equipe(Combattant equipe[], Combattant equipe_adverse[], int taille, int numero_equipe, int est_active) {
    if (equipe == NULL || equipe_adverse == NULL || taille <= 0) return;

    int hauteur = h;

    printf("_[EQUIPE %d]", numero_equipe);
    for (int i = 0; i < L - 12; i++) printf("_");
    printf("\n");

    for (int i = 0; i < taille; i++) {
        if (equipe[i].est_KO) continue;

        char ligne[L];
        int decalage = 0;

        char nom_formate[64];
        if (equipe[i].est_actif) {
            snprintf(nom_formate, sizeof(nom_formate), "> %-15s <", equipe[i].nom);
        } else {
            snprintf(nom_formate, sizeof(nom_formate), "  %-15s  ", equipe[i].nom);
        }

        decalage += snprintf(ligne + decalage, sizeof(ligne) - decalage, "| %s |%2d| ", nom_formate, equipe[i].position);
        decalage += snprintf(ligne + decalage, sizeof(ligne) - decalage, "%3d/%3d ", equipe[i].pv, equipe[i].pv_max);

        int barre_pleine = (equipe[i].action * MAX_BARRE) / 100;
        ligne[decalage++] = '[';
        for (int j = 0; j < MAX_BARRE; j++) {
            if (j < barre_pleine) {
                ligne[decalage++] = '>';
            } else {
                ligne[decalage++] = ' ';
            }
        }
        ligne[decalage++] = ']';

        while (decalage < L - 2) {
            ligne[decalage++] = ' ';
        }
        ligne[decalage++] = '|';
        ligne[decalage] = '\0';

        printf("%s\n", ligne);
    }

    for (int i = 0; i < hauteur - 2 - taille; i++) {
        printf("|");
        for (int j = 0; j < L - 3; j++) printf(" ");
        printf("|\n");
    }

    printf("|");
    for (int i = 0; i < L - 3; i++) printf("_");
    printf("|\n");
}


void afficher_techniques_speciales(Combattant *combattant, int numero_equipe) {
    if (combattant == NULL) return;

    int hauteur = h;
    char ligne[L];
    int l;

    snprintf(ligne, sizeof(ligne), "| > %s (Equipe %d) <", combattant->nom, numero_equipe);
    l = strlen(ligne);
    while (l < L - 3) ligne[l++] = ' ';
    ligne[l++] = '|';
    ligne[l] = '\0';
    printf("%s\n", ligne);

    snprintf(ligne, sizeof(ligne), "| TECHNIQUE SPECIALE");
    l = strlen(ligne);
    while (l < L - 3) ligne[l++] = ' ';
    ligne[l++] = '|';
    ligne[l] = '\0';
    printf("%s\n", ligne);

    for (int i = 0; i < combattant->nb_techniques; i++) {
        TechniqueSpeciale *technique = &combattant->techniques[i];

        snprintf(ligne, sizeof(ligne), "| [%d] %s", i + 1, technique->nom);
        l = strlen(ligne);
        while (l < L - 3) ligne[l++] = ' ';
        ligne[l++] = '|';
        ligne[l] = '\0';
        printf("%s\n", ligne);

        snprintf(ligne, sizeof(ligne), "|     -> %.75s", technique->description);
        l = strlen(ligne);
        while (l < L - 3) ligne[l++] = ' ';
        ligne[l++] = '|';
        ligne[l] = '\0';
        printf("%s\n", ligne);

        if (technique->cooldown_actuel > 0) {
            snprintf(ligne, sizeof(ligne), "|     -> Recharge: %d/%d tours",
                     technique->cooldown_actuel, technique->tours_rechargement);
            l = strlen(ligne);
            while (l < L - 3) ligne[l++] = ' ';
            ligne[l++] = '|';
            ligne[l] = '\0';
            printf("%s\n", ligne);
        }
    }

    printf("|");
    for (int i = 0; i < L - 4; i++) printf("_");
    printf("|\n");
}


int determiner_equipe_active(Combattant equipe1[], Combattant equipe2[]) {
    if (equipe1 == NULL || equipe2 == NULL) return 1;

    int max_action1 = 0, max_action2 = 0;
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        if (equipe1[i].est_KO == 0 && equipe1[i].action > max_action1)
            max_action1 = equipe1[i].action;
        if (equipe2[i].est_KO == 0 && equipe2[i].action > max_action2)
            max_action2 = equipe2[i].action;
    }
    return (max_action1 >= max_action2) ? 1 : 2;
}

Combattant* trouver_personnage_actif(Combattant equipe[], int taille_equipe) {
    if (equipe == NULL || taille_equipe <= 0) return NULL;

    Combattant* actif = NULL;
    int max_action = -1;
    for (int i = 0; i < taille_equipe; i++) {
        if (equipe[i].est_KO == 0 && equipe[i].est_actif == 1 && equipe[i].action > max_action) {
            max_action = equipe[i].action;
            actif = &equipe[i];
        }
    }
    return actif;
}

void afficher_plateau(Combattant equipe1[], Combattant equipe2[]) {
    if (equipe1 == NULL || equipe2 == NULL) return;

    effacer_ecran();
    int equipe_active = determiner_equipe_active(equipe1, equipe2);
    int numero_equipe_actif = equipe_active;

    if (equipe_active == 1) {
        afficher_equipe(equipe1, equipe2, TAILLE_EQUIPE, 1, 1);
        afficher_equipe(equipe2, equipe1, TAILLE_EQUIPE, 2, 0);
    } else {
        afficher_equipe(equipe1, equipe2, TAILLE_EQUIPE, 1, 0);
        afficher_equipe(equipe2, equipe1, TAILLE_EQUIPE, 2, 1);
    }

    Combattant *combattant_actif = (equipe_active == 1)
        ? trouver_personnage_actif(equipe1, TAILLE_EQUIPE)
        : trouver_personnage_actif(equipe2, TAILLE_EQUIPE);

    if (combattant_actif != NULL && combattant_actif->nb_techniques > 0) {
        afficher_techniques_speciales(combattant_actif, numero_equipe_actif);
    }
}
