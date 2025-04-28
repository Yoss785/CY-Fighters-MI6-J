// Main
#include <stdio.h>
#include "code.h"
#include "selection.h"
#include "techniques.h"
#include "affichage.h"

int main() {
    Combattant equipe1[TAILLE_EQUIPE], equipe2[TAILLE_EQUIPE];
    FILE* fichier = fopen("personnages.txt", "r");

    if (!fichier) {
        printf("Erreur : fichier introuvable.\n");
        return 1;
    }
    selection(equipe1, equipe2, fichier);        
    afficher_plateau(equipe1, equipe2);
    fclose(fichier);
    /*
    int tour_equipe = 1; // 1 pour équipe 1, 2 pour équipe 2
    int jeu_termine = 0; // Booléen pour savoir quand arrêter la partie

    while (!jeu_termine) {
        // Afficher les plateaux selon l'équipe qui joue
        afficher_plateaux_selon_tour(equipe1, equipe2, tour_equipe);

        printf("\nÉquipe %d joue !\n", tour_equipe);

        plus tard :
        // -> Tour du combattant à la barre de vitesse remplie 
        // -> Faire une action (attaque normale, utiliser une technique, etc.)
        // -> Gérer les cooldowns, les PV, etc.

        printf("Fin du tour. Appuyez sur Entrée pour continuer...");
        getchar(); // Vide le buffer s'il faut
        getchar(); // Attend que l'utilisateur appuie sur Entrée

        // Plus tard: vérifier si une équipe est KO pour mettre jeu_termine = 1
    }

    printf("\nLa partie est terminée !\n");*/
    return 0;
}
