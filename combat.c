#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "affichage.h"
#include "combat.h"
#include "code.h"
#include "check.h"

void initialiser_premier_joueur(Combattant* equipe1, Combattant* equipe2) {
    Combattant* plus_rapide = NULL;

    // Cherche le personnage avec la plus grande vitesse dans les deux équipes
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        if (equipe1[i].est_KO == 0 && (plus_rapide == NULL || equipe1[i].vitesse > plus_rapide->vitesse)) {
            plus_rapide = &equipe1[i];
        }
        if (equipe2[i].est_KO == 0 && (plus_rapide == NULL || equipe2[i].vitesse > plus_rapide->vitesse)) {
            plus_rapide = &equipe2[i];
        }
    }

    // Si un personnage a été trouvé, lui donner une action à 100
    if (plus_rapide != NULL) {
        plus_rapide->action = 100;
    }
}

void phase(Combattant* equipe1, Combattant* equipe2) {
    // Remplir les barres d'action
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        if (!equipe1[i].est_KO) {
            equipe1[i].action += equipe1[i].vitesse;
        }
        if (!equipe2[i].est_KO) {
            equipe2[i].action += equipe2[i].vitesse;
        }
    }

    // Boucle principale pour exécuter les tours
    while (1) {
        int action_done = 0;

        // Réinitialiser les est_actif
        for (int i = 0; i < TAILLE_EQUIPE; i++) {
            equipe1[i].est_actif = 0;
            equipe2[i].est_actif = 0;
        }

        // Tour équipe 1
        for (int i = 0; i < TAILLE_EQUIPE; i++) {
            if (!equipe1[i].est_KO && equipe1[i].action >= 100) {
                equipe1[i].est_actif = 1;
                afficher_plateau(equipe1, equipe2);

                // Pause pour visualiser l'affichage
                printf("\n(Appuyez sur Entrée pour continuer...)\n");
                getchar(); // consomme '\n' résiduel si nécessaire
                getchar();

                tour(&equipe1[i], equipe2);
                equipe1[i].action = 0;
                equipe1[i].est_actif = 0;
                action_done = 1;
                break;
            }
        }

        // Tour équipe 2
        if (!action_done) {
            for (int i = 0; i < TAILLE_EQUIPE; i++) {
                if (!equipe2[i].est_KO && equipe2[i].action >= 100) {
                    equipe2[i].est_actif = 1;
                    afficher_plateau(equipe1, equipe2);

                    printf("\n(Appuyez sur Entrée pour continuer...)\n");
                    getchar();
                    getchar();

                    tour(&equipe2[i], equipe1);
                    equipe2[i].action = 0;
                    equipe2[i].est_actif = 0;
                    action_done = 1;
                    break;
                }
            }
        }

        if (!action_done) break;

        // Réduction des cooldowns
        for (int i = 0; i < TAILLE_EQUIPE; i++) {
            if (!equipe1[i].est_KO) {
                for (int j = 0; j < equipe1[i].nb_techniques; j++) {
                    if (equipe1[i].techniques[j].cooldown_actuel > 0) {
                        equipe1[i].techniques[j].cooldown_actuel--;
                    }
                }
            }
            if (!equipe2[i].est_KO) {
                for (int j = 0; j < equipe2[i].nb_techniques; j++) {
                    if (equipe2[i].techniques[j].cooldown_actuel > 0) {
                        equipe2[i].techniques[j].cooldown_actuel--;
                    }
                }
            }
        }
    }
}

void tour(Combattant* perso, Combattant* equipe) {
    if(perso->buff_attaque>0){
        perso->buff_attaque-=1;
    }
     if(perso->buff_defense>0){
        perso->buff_defense-=1;
    }
     if(perso->debuff_agilite>0){
        perso->debuff_agilite-=1;
    }
	if (perso->est_KO == 1) return;
	int choix = -1;
	while (choix != 1 && choix != 2) {
		printf("%s - Quelle action voulez-vous effectuer ?\n", perso->nom);
		printf("1 = Attaquer\n2 = CapacitC) spC)ciale (%s%s)\n",
		       perso->techniques[0].nom,
		       perso->techniques[0].cooldown_actuel > 0 ? " - en rechargement" : "");
		scanf("%d", &choix);
		if (choix != 1 && choix != 2) {
			printf("Mauvais choix, recommencez.\n");
		}
	}

	if (choix == 1) {
		attaque(perso, equipe);
	} else {
		attaque_speciale(perso, equipe);
	}
	if(perso->brulure>0) {
		perso->pv-=10;
		perso->brulure-=1;
		if(perso->pv<=0){
		    printf("%s succombe a sa brulure",perso->nom);
		    perso->est_KO=1;
		}
	}
}

void attaque(Combattant* perso, Combattant* equipe) {
	int choix = -1, validation = 0;
	while (choix < 1 || choix > TAILLE_EQUIPE || validation != 1) {
		printf("Entrez la position du personnage C  attaquer : ");
		scanf("%d", &choix);
		validation = cible_valide(&equipe[choix - 1]);
	}

	Combattant* cible = &equipe[choix - 1];
	printf("%s attaque %s\n", perso->nom, cible->nom);

	int degats = perso->attaque - cible->defense;
	if(perso->buff_attaque>0) {
		degats*=1.5;
	}
	if(cible->buff_defense>0) {
		degats=degats/1.5;
	}
	if (degats < 0) degats = 0;

	int miss=rand()%100;
	if(cible->debuff_agilite>0){
	    miss*=1.5;
	}
	if(miss<cible->agilite) {
		printf("%s esquive habilement l attaque de %s\n ",cible->nom,perso->nom);
	}
	else {

		int crit = rand() % 100;
		if (crit < perso->agilite) {
			printf("Coup critique ! %s touche un point vital !\n", perso->nom);
			degats = (int)(degats * 1.5);
		}
		printf("%s recoit %d degats\n", cible->nom, degats);
		cible->pv -= degats;
		if (cible->pv <= 0) {
			cible->pv = 0;
			cible->est_KO = 1;
			printf("%s succombe...\n", cible->nom);
		}
	}
}


void attaque_speciale(Combattant* utilisateur, Combattant* equipe_adverse) {
    TechniqueSpeciale* tech = &utilisateur->techniques[0];

    if (tech->cooldown_actuel > 0) {
        printf("La technique %s est encore en rechargement (%d tours restants).\n",
               tech->nom, tech->cooldown_actuel);
        return;
    }

    printf("Choisissez un ennemi pour utiliser la technique spéciale %s :\n", tech->nom);
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        if (!equipe_adverse[i].est_KO) {
            printf("%d. %s (PV: %d)\n", i + 1, equipe_adverse[i].nom, equipe_adverse[i].pv);
        }
    }

    int choix = -1, validation = 0;
    while (choix < 1 || choix > TAILLE_EQUIPE || validation != 1) {
        choix = getInt(1,TAILLE_EQUIPE);
        validation = cible_valide(&equipe_adverse[choix - 1]);
    }

    appliquer_technique(utilisateur, &equipe_adverse[choix - 1], tech);
}

void appliquer_technique(Combattant* utilisateur, Combattant* cible, TechniqueSpeciale* technique) {
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

    if (cible->pv <= 0) {
        cible->est_KO = 1;
        printf("%s succombe sous l'effet de la technique...\n", cible->nom);
    }

    technique->cooldown_actuel = technique->tours_rechargement;
}

int cible_valide(Combattant* perso) {
    if (perso->est_KO == 1) {
        printf("Cet ennemi est déjà KO.\n");
        return 0;
    }
    return 1;
}

int equipe_vivante(Combattant* equipe) {
    int morts = 0;
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        if (equipe[i].est_KO == 1) {
            morts++;
        }
    }
    return (morts < TAILLE_EQUIPE);
}
