#ifndef COMBAT_H
#define COMBAT_H

#include "code.h"

void phase(Combattant* equipe1, Combattant* equipe2);
void tour(Combattant* perso, Combattant* equipe);
void attaque(Combattant* perso, Combattant* equipe);
int cible_valide(Combattant* perso);
int equipe_vivante(Combattant* equipe);

#endif
