#include <stdio.h>
#include <string.h>
#include "techniques.h"

void appliquer_technique(Combattant* utilisateur, Combattant* cible, TechniqueSpeciale* technique) {
    if (technique->cooldown_actuel > 0) {
        printf("La technique %s est en rechargement (%d tours restants).\n",
               technique->nom, technique->cooldown_actuel);
        return;
    }

    printf("%s utilise %s sur %s !\n", utilisateur->nom, technique->nom, cible->nom);
    printf("Effet : %s\n", technique->description);

    if (strcmp(technique->propriete_affectee, "pv") == 0) {
        if (strcmp(technique->operation, "-") == 0) {
            cible->pv -= technique->degat;
            if (cible->pv < 0) cible->pv = 0;
        } else if (strcmp(technique->operation, "+") == 0) {
            cible->pv += technique->degat;
            if (cible->pv > cible->pv_max) cible->pv = cible->pv_max;
        }
    }

    technique->cooldown_actuel = technique->tours_rechargement;
}
