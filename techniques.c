#include "techniques.h"
#include "code.h"
#include "combat.h"


void attaque_speciale(Combattant* utilisateur, Combattant* equipe_adverse) {
	TechniqueSpeciale* tech = &utilisateur->techniques[0];

	if (tech->cooldown_actuel > 0) {
		printf("La technique %s est encore en rechargement (%d tours restants).\n",
		       tech->nom, tech->cooldown_actuel);
		return;
	}

	printf("Choisissez un ennemi pour utiliser la technique spC)ciale %s :\n", tech->nom);
	for (int i = 0; i < TAILLE_EQUIPE; i++) {
		if (!equipe_adverse[i].est_KO) {
			printf("%d. %s (PV: %d)\n", i + 1, equipe_adverse[i].nom, equipe_adverse[i].pv);
		}
	}

	int choix = -1, validation = 0;
	while (choix < 1 || choix > TAILLE_EQUIPE || validation != 1) {
		scanf("%d", &choix);
		validation = cible_valide(&equipe_adverse[choix - 1]);
	}

	appliquer_technique(utilisateur, &equipe_adverse[choix - 1], tech);
}



void appliquer_technique(Combattant* utilisateur, Combattant* cible, TechniqueSpeciale* technique) {

	if(strcmp(technique->nom,"Mur de glace")==0) {
		mur_de_glace(utilisateur,cible);
	}
	else if(strcmp(technique->nom,"Blaster meteor")==0) {
		blaster_meteor(utilisateur,cible);
	}
	else if(strcmp(technique->nom,"Kamehameha")==0) {
		kamehameha(utilisateur,cible);
	}
	else if(strcmp(technique->nom,"Final flash")==0) {
		final_flash(utilisateur,cible);
	}



	printf("%s utilise %s sur %s !\n", utilisateur->nom, technique->nom, cible->nom);
	printf("Effet : %s\n", technique->description);

	technique->cooldown_actuel = technique->tours_rechargement;
}

void mur_de_glace(Combattant* utilisateur, Combattant* cible) {
	printf("ICE AGE\n");
	cible->pv-=utilisateur->attaque;
	if(cible->pv<=0) {
		printf("%s transforme %s en statue\n",utilisateur->nom,cible->nom);
	}
	cible->action=0;
}

void blaster_meteor(Combattant* utilisateur, Combattant* cible) {
	printf("Chargement du KI\n");
	if(cible->position==1) {
		attaque(utilisateur,cible);
		attaque(utilisateur,cible+1);
	}
	if(cible->position==2) {
		attaque(utilisateur,cible-1);
		attaque(utilisateur,cible);
		attaque(utilisateur,cible+1);
	}
	if(cible->position==3) {
		attaque(utilisateur,cible-1);
		attaque(utilisateur,cible);
	}
}
void kamehameha(Combattant* utilisateur, Combattant* cible) {
	printf("Chargement du KI\n");
	printf("KAMEHAME..........HAAAAAAAAAAA\n");
	attaque(utilisateur,cible);
	utilisateur->attaque*=1.2;
}
void final_flash(Combattant* utilisateur, Combattant* cible) {
	printf("Chargement du KI\n");
	printf("FINAL FLASH\n");
	attaque(utilisateur,cible);
	utilisateur->defense*=1.2;
}