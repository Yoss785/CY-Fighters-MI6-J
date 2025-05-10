#ifndef TECHNIQUES_H
#define TECHNIQUES_H

#include "code.h"

void appliquer_technique(Combattant* utilisateur, Combattant* cible, TechniqueSpeciale* technique);
void attaque_speciale(Combattant* utilisateur, Combattant* equipe_adverse);
void blaster_meteor(Combattant* utilisateur, Combattant* cible);
void mur_de_glace(Combattant* utilisateur, Combattant* cible);
void final_flash(Combattant* utilisateur, Combattant* cible);
void kamehameha(Combattant* utilisateur, Combattant* cible);
void crazy_diamond(Combattant* utilisateur, Combattant* cible);
void appliquer_technique_allie(Combattant* utilisateur,Combattant* cible,TechniqueSpeciale* technique);
void illumination_divine(Combattant* utilisateur, Combattant* cible);
void senzu(Combattant* utilisateur, Combattant* cible);
void grande_eruption(Combattant* utilisateur, Combattant* cible);

#endif
