#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "code.h"

void dessiner_barre(int valeur, int max, char symbole);
void afficher_ligne(int ligne, Combattant persos[], int nb_persos);//ajouter int mode_complet
void afficher_plateau_petit(Combattant persos[], int nb_persos);
void afficher_plateau_grand(Combattant persos[], int nb_persos);
void afficher_plateau(Combattant equipe1[], Combattant equipe2[]);

#endif
