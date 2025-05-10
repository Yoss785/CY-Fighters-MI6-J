#include "techniques.h"
#include "code.h"
#include "combat.h"
#include "check.h"

void attaque_speciale(Combattant* utilisateur, Combattant* equipe_adverse) {
    TechniqueSpeciale* tech = &utilisateur->techniques[0];

    if (tech->cooldown_actuel > 0) {
        printf("La technique %s est encore en rechargement (%d tours restants).\n",
               tech->nom, tech->cooldown_actuel);
        return;
    }
    int cible;
    if(strcmp(tech->nom,"Crazy Diamond")==0||strcmp(tech->nom,"Senzu")==0){
        cible=2;
    }
    else if((strcmp(tech->nom,"Blaster meteor")==0)){
        cible=3;
    }
    else{
        cible=1;
    }

    if (cible == 1) {
        printf("Choisissez un ennemi pour utiliser la technique spéciale %s :\n", tech->nom);
        for (int i = 0; i < TAILLE_EQUIPE; i++) {
            if (!equipe_adverse[i].est_KO) {
                printf("%d. %s (PV: %d)\n", i + 1, equipe_adverse[i].nom, equipe_adverse[i].pv);
            }
        }

        int choix = -1, validation = 0;
        while (!validation) {
            choix = getInt(1, TAILLE_EQUIPE);
            validation = cible_valide(&equipe_adverse[choix - 1]);
        }

        appliquer_technique(utilisateur, &equipe_adverse[choix - 1], tech);
    }

    else if (cible == 2) {
        Combattant* equipe_allie = utilisateur->equipe;
        printf("Choisissez un allié pour utiliser la technique spéciale %s :\n", tech->nom);
        for (int i = 0; i < TAILLE_EQUIPE; i++) {
            if (!equipe_allie[i].est_KO) {
                printf("%d. %s (PV: %d)\n", i + 1, equipe_allie[i].nom, equipe_allie[i].pv);
            }
        }

        int choix = -1, validation = 0;
        while (!validation) {
            choix = getInt(1, TAILLE_EQUIPE);
            validation = cible_valide(&equipe_allie[choix - 1]);
        }

        appliquer_technique_allie(utilisateur, &equipe_allie[choix - 1], tech);
    }
    else if(cible==3){
         appliquer_technique(utilisateur, &equipe_adverse[1], tech);
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
    else if(strcmp(technique->nom,"Grande eruption")==0) {
		grande_eruption(utilisateur,cible);
	}


//	printf("%s utilise %s sur %s !\n", utilisateur->nom, technique->nom, cible->nom);
//	printf("Effet : %s\n", technique->description);

	technique->cooldown_actuel = technique->tours_rechargement;

}

void appliquer_technique_allie(Combattant* utilisateur,Combattant* cible,TechniqueSpeciale* technique){
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
		cible->est_KO=1;
	}
	cible->action=0;
}

void blaster_meteor(Combattant* utilisateur, Combattant* cible) {
    printf("Chargement du KI...\n");
    printf("BLASTER METEOR !\n");

    Combattant* equipe_adverse = cible->equipe;

    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        if (!equipe_adverse[i].est_KO) {
            printf("%s subit une pluie de KI !\n", equipe_adverse[i].nom);
            equipe_adverse[i].pv -= 20;
            if (equipe_adverse[i].pv <= 0) {
                equipe_adverse[i].est_KO = 1;
                printf("%s est éliminé !\n", equipe_adverse[i].nom);
            }
        }
    }
}
void kamehameha(Combattant* utilisateur, Combattant* cible) {
	printf("Chargement du KI\n");
	printf("KAMEHAME..........HAAAAAAAAAAA\n");
	int degats=utilisateur->attaque-cible->defense;
    degats*=2;
    if(utilisateur->buff_attaque>0) {
		degats*=1.5;
	}
	if(cible->buff_defense>0) {
		degats=degats/1.5;
	}
	if (degats < 0) degats = 0;
	printf("%s inflige %d degats a %s \n",utilisateur->nom,degats,cible->nom);
    cible->pv-=degats;
	utilisateur->buff_attaque=3;
	if(cible->pv<=0) {
		printf("%s a éliminé %s, la menace de la Terre\n",utilisateur->nom,cible->nom);
		cible->est_KO=1;
	}
	cible->action=0;
	
}

void final_flash(Combattant* utilisateur, Combattant* cible) {
	printf("Chargement du KI\n");
	printf("FINAL FLASH\n");
	int degats=utilisateur->attaque-cible->defense;
    degats*=2;
    if(utilisateur->buff_attaque>0) {
		degats*=1.5;
	}
	if(cible->buff_defense>0) {
		degats=degats/1.5;
	}
	if (degats < 0) degats = 0;
	printf("%s inflige %d degats a %s \n",utilisateur->nom,degats,cible->nom);
    cible->pv-=degats;
	utilisateur->buff_defense=3;
	if(cible->pv<=0) {
		printf("%s a éliminé %s et sauve sa Bulma\n",utilisateur->nom,cible->nom);
		cible->est_KO=1;
	}
	cible->action=0;
}
void crazy_diamond(Combattant* utilisateur, Combattant* cible){
    printf("%s pose sa main sur %s\n",utilisateur->nom,cible->nom);
    cible->pv=cible->pv_max;
    printf("%s se sent de nouveau en pleine forme\n",cible->nom);
}
void grande_eruption(Combattant* utilisateur, Combattant* cible){
    printf("Akainu charge son magma\n");
    printf("GRANDE ERRUPTION\n");
    int degats=utilisateur->attaque-cible->defense;
    degats*=2;
    if(utilisateur->buff_attaque>0) {
		degats*=1.5;
	}
	if(cible->buff_defense>0) {
		degats=degats/1.5;
	}
	if (degats < 0) degats = 0;
    cible->pv-=degats;
    printf("%s inflige %d degats a %s\n",utilisateur->nom,degats,cible->nom);
    if(cible->pv<=0) {
		printf("%s transforme %s en tas de cendre\n",utilisateur->nom,cible->nom);
		cible->est_KO=1;
	}
	else{
	    cible->brulure+=3;
	}
}
void illumination_divine(Combattant* utilisateur, Combattant* cible){
    printf("%s place son index et son majeur devant les yeux de %s \n",utilisateur->nom,cible->nom);
    printf("AMATERASU: ILLUMINATION DIVINE\n");
    int degats=utilisateur->attaque-cible->defense;
    degats*=1.5;
    if(utilisateur->buff_attaque>0) {
		degats*=1.5;
	}
	if(cible->buff_defense>0) {
		degats=degats/1.5;
	}
	if (degats < 0) degats = 0;
    cible->pv-=degats;
    printf("%s inflige %d degats a %s\n",utilisateur->nom,degats,cible->nom);
   
    if(cible->pv<=0) {
		printf("%s fait exploser %s \n",utilisateur->nom,cible->nom);
		cible->est_KO=1;
	}
	cible->debuff_agilite+=3;
}
void senzu(Combattant* utilisateur, Combattant* cible){
    printf("%s lance un haricot a %s\n",utilisateur->nom,cible->nom);
    cible->pv+=40;
    if(cible->pv>cible->pv_max){
        cible->pv=cible->pv_max;
    }
    cible->brulure=0;
    printf("%s se sent de nouveau en pleine forme\n",cible->nom);
}
