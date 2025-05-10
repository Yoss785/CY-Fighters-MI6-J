#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "code.h"
#include "selection.h"
#include "combat.h"
#include "affichage.h"
#include "check.h"
#include "techniques.h"
#include "JvO_facile.h"
#include "selection_vs_ordi.h"


int main() {
    srand(time(NULL));
    Combattant equipe1[TAILLE_EQUIPE], equipe2[TAILLE_EQUIPE];
    FILE* fichier = fopen("personnages.txt", "r");

    if (!fichier) {
        printf("Erreur : fichier introuvable.\n");
        return 1;
    }

    printf("Choisissez le mode de jeu :\n");
    printf("1 - Joueur vs Joueur\n");
    printf("2 - Joueur vs Ordinateur\n");
    int choix_mode = getInt(1, 2);

    if (choix_mode == 1) {
        selection(equipe1, equipe2, fichier); // sélection manuelle des 2 équipes

        for (int i = 0; i < TAILLE_EQUIPE; i++) {
            equipe1[i].position = i + 1;
            equipe2[i].position = i + 1;
            equipe1[i].equipe = equipe1;
            equipe2[i].equipe = equipe2;
        }

        while (equipe_vivante(equipe1) && equipe_vivante(equipe2)) {
            phase(equipe1, equipe2);

            if (!equipe_vivante(equipe1)) {
                printf("L'équipe 2 a gagné !\n");
                break;
            }
            if (!equipe_vivante(equipe2)) {
                printf("L'équipe 1 a gagné !\n");
                break;
            }
        }
    }   else{
        selection_joueur_vs_ordi(equipe1, equipe2, fichier); // équipe2 générée automatiquement

        for (int i = 0; i < TAILLE_EQUIPE; i++) {
            equipe1[i].position = i + 1;
            equipe2[i].position = i + 1;
            equipe1[i].equipe = equipe1;
            equipe2[i].equipe = equipe2;
        }

        while (equipe_vivante(equipe1) && equipe_vivante(equipe2)) {
            phase_bot(equipe1, equipe2);  // ici, bot joue à la place de l'équipe 2

            if (!equipe_vivante(equipe1)) {
                printf("L'ordinateur a gagné !\n");
                break;
            }
            if (!equipe_vivante(equipe2)) {
                printf("Le joueur a gagné !\n");
                break;
            }
        }
    }

    fclose(fichier);
    return 0;
}
