#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#include "selection.h"
#include "check.h"


void afficher_stats(Combattant perso) {
    printf("Nom : %s\n", perso.nom);
    printf("PV max : %d\n", perso.pv_max);
    printf("Attaque : %d\n", perso.attaque);
    printf("Défense : %d\n", perso.defense);
    printf("Agilité : %d\n", perso.agilite);
    printf("Vitesse : %d\n", perso.vitesse);
    printf("Nom de la technique : %s\n", perso.techniques[0].nom);
    printf("Description : %s\n", perso.techniques[0].description);
    printf("Tours de rechargement : %d\n", perso.techniques[0].tours_rechargement);
    printf("cooldown_actuel : %d\n", perso.techniques[0].cooldown_actuel);
}

void afficher_equipe_selection(Combattant* equipe) {
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        printf("\n--- Combattant %d ---\n", i + 1);
        afficher_stats(equipe[i]);
    }
}

void apercu(FILE* fichier, int choix) {
    char buffer[200];
    char nom[MAX_NOM];
    int numero = 1;
    int stat;
    
     rewind(fichier);

    while (numero < choix && fgets(buffer, sizeof(buffer), fichier)) {
        if (strcmp(buffer, "-\n") == 0) {
            numero++;
        }
    }
    
    fgets(nom, sizeof(nom), fichier);
    nom[strcspn(nom, "\n")] = '\0'; 
    printf("Nom : %s\n", nom);

    fscanf(fichier, "%d\n", &stat);
    printf("PV max : %d\n", stat);
    fscanf(fichier, "%d\n", &stat);
    printf("Attaque : %d\n", stat);
    fscanf(fichier, "%d\n", &stat);
    printf("Défense : %d\n", stat);
    fscanf(fichier, "%d\n", &stat);
    printf("Agilité : %d\n", stat);
    fscanf(fichier, "%d\n", &stat);
    printf("Vitesse : %d\n", stat);
    
    printf("\n ==== Technique ====\n");
    
    fgets(buffer, sizeof(buffer), fichier); // Nom technique
    buffer[strcspn(buffer, "\n")] = '\0';
    printf("Technique spéciale : %s\n", buffer);

    fgets(buffer, sizeof(buffer), fichier); // Description
    buffer[strcspn(buffer, "\n")] = '\0';
    printf("Description : %s\n", buffer);

    fscanf(fichier, "%d\n", &stat);
    printf("Tours de rechargement : %d\n", stat);

    fscanf(fichier, "%d\n", &stat);
    /*printf("Cooldown actuel : %d\n", stat); On ne l'affiche pas dans l'aperçu*/
}

void construction_perso(Combattant* perso, FILE* fichier) {
    int choix = -1;
    int validation = -1;

    while (validation != 1 || choix < 1 || choix > NBPERSO) { //faire un getInt pour voir si la plage de donnée est correcte
        printf("Entrez le numéro du combattant à sélectionner (1 à %d) : ", NBPERSO);
        choix = getInt(1, NBPERSO);

        if (choix < 1 || choix > NBPERSO) {
            printf("Ce combattant n'existe pas. Réessayez.\n");
        } else {
            rewind(fichier);
            apercu(fichier, choix);
            printf("\nValidez-vous ce choix ? (1 = oui, 0 = non) :\n ");
            validation = getInt(0, 1);
            if (validation != 1) {
                printf("Recommençons la sélection.\n");
            }
        }
    }

    rewind(fichier);

    // Avancer dans le fichier jusqu'au combattant choisi
    char buffer[200];
    int numero = 1;
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

    // Lire la technique spéciale
    fgets(perso->techniques[0].nom, MAX_NOM, fichier);
    perso->techniques[0].nom[strcspn(perso->techniques[0].nom, "\n")] = '\0';

    fgets(perso->techniques[0].description, MAX_DESC, fichier);
    perso->techniques[0].description[strcspn(perso->techniques[0].description, "\n")] = '\0';

    fscanf(fichier, "%d\n", &perso->techniques[0].tours_rechargement);
    fscanf(fichier, "%d\n", &perso->techniques[0].cooldown_actuel);
    
    perso->techniques[0].propriete_affectee[0] = '\0'; 
    perso->techniques[0].operation[0] = '\0';
    perso->est_actif = 0;
    perso->nb_techniques = 1;
    perso->action = 0;
    perso->est_KO = 0;
    perso->position = -1;
    perso->brulure = 0;
    perso->debuff_agilite=0;
    perso->buff_defense=0;
    perso->buff_attaque=0;
}
//vérifier les retours de fscanf (et aussi les fonctions) 
void selection(Combattant* equipe1, Combattant* equipe2, FILE* fichier) {
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        rewind(fichier);
        printf("\nJoueur 1 - Sélection du combattant %d\n", i + 1);
        construction_perso(&equipe1[i], fichier);
        equipe1[i].position = i * 25;
        
        rewind(fichier);
        printf("\nJoueur 2 - Sélection du combattant %d\n", i + 1);
        construction_perso(&equipe2[i], fichier);
        equipe2[i].position = i * 25;
    }
}
