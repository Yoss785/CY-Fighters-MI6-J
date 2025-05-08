#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "code.h"

void effacer_ecran();
void afficher_indicateur_tour(int action, int max_action);
void afficher_effets_speciaux(Combattant *combattant);
void afficher_equipe(Combattant equipe[], Combattant equipe_adverse[], int taille, int numero_equipe, int est_active);
void afficher_techniques_speciales(Combattant *combattant,int numero_equipe);
void afficher_plateau(Combattant equipe1[], Combattant equipe2[]);
int determiner_equipe_active(Combattant equipe1[], Combattant equipe2[]);
Combattant* trouver_personnage_actif(Combattant equipe[], int taille_equipe);

#endif
