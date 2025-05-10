#ifndef SELECTION_H
#define SELECTION_H

#include <stdio.h>
#include "code.h" 

void afficher_stats(Combattant perso);
void afficher_equipe_selection(Combattant* equipe);
void apercu(FILE* fichier, int choix);
void construction_perso(Combattant* perso, FILE* fichier);
void selection(Combattant* equipe1, Combattant* equipe2, FILE* fichier);

#endif
