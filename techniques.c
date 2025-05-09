#include "techniques.h"
#include "code.h"
#include "combat.h"


void attaque_speciale(Combattant* utilisateur, Combattant* equipe_adverse) {
	TechniqueSpeciale* tech = &utilisateur->techniques[0];
    int cible;
    printf("voulez vous utiliser la technique sur un ennemi(tapez 1)ou un allie(tapez 2)\n");
    scanf("%d",&cible);
	if (tech->cooldown_actuel > 0) {
		printf("La technique %s est encore en rechargement (%d tours restants).\n",
		       tech->nom, tech->cooldown_actuel);
		return;
	}
	
    if(cible==1){
	printf("Choisissez un ennemi pour utiliser la technique speciale %s :\n", tech->nom);
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
    
    if(cible==2){
        Combattant* equipe_allie=utilisateur->equipe;
	printf("Choisissez un allie pour utiliser la technique speciale %s :\n", tech->nom);
	for (int i = 0; i < TAILLE_EQUIPE; i++) {
		if (!equipe_allie[i].est_KO) {
			printf("%d. %s (PV: %d)\n", i + 1, equipe_allie[i].nom, equipe_allie[i].pv);
		}
	}

	int choix = -1, validation = 0;
	while (choix < 1 || choix > TAILLE_EQUIPE || validation != 1) {
		scanf("%d", &choix);
		validation = cible_valide(&equipe_allie[choix - 1]);
	}

	appliquer_technique(utilisateur, &equipe_allie[choix - 1], tech);
    }
    
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
	else if(strcmp(technique->nom,"Illumination divine")==0) {
		illumination_divine(utilisateur,cible);
	}



	printf("%s utilise %s sur %s !\n", utilisateur->nom, technique->nom, cible->nom);
	printf("Effet : %s\n", technique->description);

	technique->cooldown_actuel = technique->tours_rechargement;

}

void appliquer_technique_allie(Combattant* utilisateur,Combattant* cible,Combattant* technique){
    if(strcmp(technique->nom,"Crazy Diamond")==0) {
		crazy_diamond(utilisateur,cible);
    }
    else if(strcmp(technique->nom,"Senzu")==0) {
		senzu(utilisateur,cible);
    }
}

void mur_de_glace(Combattant* utilisateur, Combattant* cible) {
	printf("ICE AGE\n");
	cible->pv-=utilisateur->attaque;
	printf("Aokiji inflige %d degats a %s\n",utilisateur->attaque,cible->nom);
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
	utilisateur->buff_attaque+=2;
}
void final_flash(Combattant* utilisateur, Combattant* cible) {
	printf("Chargement du KI\n");
	printf("FINAL FLASH\n");
	attaque(utilisateur,cible);
	utilisateur->buff_defense+=2;
}
void crazy_diamond(Combattant* utilisateur, Combattant* cible){
    printf("Josuke pose sa main sur %s\n",cible->nom);
    cible->pv=cible->pv_max;
    printf("%s se sent de nouveau en pleine forme\n",cible->nom);
}
void grande_eruption(Combattant* utilisateur, Combattant* cible){
    printf("Akainu charge son magma\n");
    printf("GRANDE ERRUPTION\n");
    int degats=utilisateur->attaque-cible->defense;
    degats*=2;
    printf("Akainu inflige %d degats a %s\n",degats,cible->nom);
    if(cible->pv<=0) {
		printf("%s transforme %s en tas de cendre\n",utilisateur->nom,cible->nom);
	}
	else{
	    cible->brulure+=3;
	}
}
void illumination_divine(Combattant* utilisateur, Combattant* cible){
    printf("Kizaru place son index et son majeur devant les yeux de %s \n",cible->nom);
    printf("AMATERASU: ILLUMINATION DIVINE\n");
    int degats=utilisateur->attaque-cible->defense;
    degats*=1.5;
    printf("Kizaru inflige %d degats a %s\n",degats,cible->nom);
    if(cible->pv<=0) {
		printf("%s fait exploser %s \n",utilisateur->nom,cible->nom);
	}
}
void senzu(Combattant* utilisateur, Combattant* cible){
    printf("Krillin lance un haricot a %s",cible->nom);
    cible->pv+=40;
    cible->brulure=0;
    printf("%s se sent de nouveau en pleine forme\n",cible->nom);
}
}
