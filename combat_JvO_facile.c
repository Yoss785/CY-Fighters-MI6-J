#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "affichage.h"
#include "combat.h"
#include "code.h"
#include "check.h"
#include "techniques.h"


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
                while (getchar() != '\n');// Vide le buffer jusqu'à un saut de ligne

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
                    while (getchar() != '\n');// Vide le buffer jusqu'à un saut de ligne
                    
                    tour_bot(&equipe2[i], equipe1);
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

void tour_bot(Combattant* bot, Combattant* equipe_adverse) {
    if (bot->est_KO) return;

    // === Buffs / débuffs progressifs ===
    if(bot->buff_attaque > 0) bot->buff_attaque--;
    if(bot->buff_defense > 0) bot->buff_defense--;
    if(bot->debuff_agilite > 0) bot->debuff_agilite--;

    // === Choix d'une cible aléatoire vivante ===
    int indices_valides[TAILLE_EQUIPE];
    int nb_cibles = 0;

    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        if (!equipe_adverse[i].est_KO) {
            indices_valides[nb_cibles++] = i;
        }
    }

    if (nb_cibles == 0) return; // plus personne à attaquer

    int index_cible = indices_valides[rand() % nb_cibles];
    attaque(bot, &equipe_adverse[index_cible]);

    // === Effets de brûlure ===
    if(bot->brulure > 0) {
        bot->pv -= 10;
        bot->brulure--;
        printf("%s souffre de brûlure et perd 10 PV !\n", bot->nom);
        if(bot->pv <= 0) {
            bot->pv = 0;
            bot->est_KO = 1;
            printf("%s succombe à sa brûlure...\n", bot->nom);
        }
    }
}




void tour(Combattant* perso, Combattant* equipe) {
    if (perso->est_KO == 1) return;
    int choix = -1;
    
    while (choix != 1 && choix != 2) {
        printf("%s - Quelle action voulez-vous effectuer ?\n", perso->nom);
        printf("1 = Attaquer\n2 = Capacité spéciale (%s%s)\n",
               perso->techniques[0].nom,
               perso->techniques[0].cooldown_actuel > 0 ? " - en rechargement" : "");
        choix = getInt(1,2);
        if (choix != 1 && choix != 2) {
            printf("Mauvais choix, recommencez.\n");
        }
    }

    if (choix == 1) {
        attaque(perso, equipe);
    } else {
        attaque_speciale(perso, equipe);
    }
    if (perso->equipe == NULL) {
        printf("Erreur: impossible de déterminer l'équipe du personnage\n");
    } else {
        Combattant* equipe1 = perso->equipe;
        Combattant* equipe2 = equipe;
        if (perso->equipe == equipe) {
            equipe1 = equipe;
            equipe2 = perso->equipe;
        }
        afficher_plateau(equipe1, equipe2);
    }
}
