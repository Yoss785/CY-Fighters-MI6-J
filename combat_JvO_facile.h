#define COMBAT_JVO_FACILE_H

#include "code.h"

void initialiser_premier_joueur(Combattant* equipe1, Combattant* equipe2);
void phase(Combattant* equipe1, Combattant* equipe2);
void tour_bot(Combattant* bot, Combattant* equipe_adverse);
void tour(Combattant* perso, Combattant* equipe);

#endif
