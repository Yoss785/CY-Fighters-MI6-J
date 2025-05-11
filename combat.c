#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "affichage.h"
#include "combat.h"
#include "code.h"
#include "check.h"
#include "techniques.h"
#include <unistd.h>
//phase du combat
void phase(Combattant* equipe1, Combattant* equipe2) {
    if (!equipe1 || !equipe2) {
        fprintf(stderr, "Erreur: une des équipes est NULL dans phase().\n");
        return;
    }

    // Remplir les barres d'action
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        if (!equipe1[i].est_KO) {
            equipe1[i].action += equipe1[i].vitesse;
        }
        if (!equipe2[i].est_KO) {
            equipe2[i].action += equipe2[i].vitesse;
        }
    }

    // Vérifier immédiatement si une équipe est KO
    if (!equipe_vivante(equipe1) || !equipe_vivante(equipe2)) {
        return;
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
                printf("\n(Appuyez sur Entrée pour continuer...)\n");
                while (getchar() != '\n'); // Vide le buffer
                afficher_plateau(equipe1, equipe2);
                tour(&equipe1[i], equipe2);
                equipe1[i].action = 0;
                equipe1[i].est_actif = 0;
                action_done = 1;
                break;
            }
        }

        // Vérifier après action si une équipe est KO
        if (!equipe_vivante(equipe1) || !equipe_vivante(equipe2)) {
            return;
        }

        // Tour équipe 2
        if (!action_done) {
            for (int i = 0; i < TAILLE_EQUIPE; i++) {
                if (!equipe2[i].est_KO && equipe2[i].action >= 100) {
                    equipe2[i].est_actif = 1;
                    printf("\n(Appuyez sur Entrée pour continuer...)\n");
                    while (getchar() != '\n');
                    afficher_plateau(equipe1, equipe2);
                    tour(&equipe2[i], equipe1);
                    equipe2[i].action = 0;
                    equipe2[i].est_actif = 0;
                    action_done = 1;
                    break;
                }
            }
        }

        // Vérifier après action si une équipe est KO
        if (!equipe_vivante(equipe1) || !equipe_vivante(equipe2)) {
            return;
        }

        // Si aucune action possible, sortir de la boucle
        if (!action_done) {
            return;
        }
    }
}
//Tour du combat
void tour(Combattant* perso, Combattant* equipe) {
    
    if (!perso || !equipe) {
        fprintf(stderr, "Erreur: paramètre NULL dans tour().\n");
        return;
    }
    
    if (perso->nb_techniques <= 0 || !perso->techniques) {
        fprintf(stderr, "Erreur: aucune technique définie pour %s\n", perso->nom);
        return;
    }

    if (perso->est_KO == 1) return;
    
    int choix = -1;
    //choix d'attaque
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
    TechniqueSpeciale* tech=perso->techniques;
    if (tech->cooldown_actuel > 0) {
        printf("La technique %s est encore en rechargement (%d tours restants).\n",
               tech->nom, tech->cooldown_actuel);
               printf("passage en mode attaque normale\n");
        choix=1;
    }

    if (choix == 1) {
         int choix = -1, validation = 0;
    //choix de cible du combattant
    while (choix < 1 || choix > TAILLE_EQUIPE || validation != 1) {
        printf("Entrez la position du personnage à attaquer : ");
        choix = getInt(1,TAILLE_EQUIPE);
        validation = cible_valide(&equipe[choix - 1]);
    }
        attaque(perso,&equipe[choix - 1]);
        if (!equipe_vivante(equipe)) {
            return; // on quitte tour()
        }
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
        //réduction du cooldown 
        for (int i = 0; i < perso->nb_techniques; i++) {
            if (perso->techniques[i].cooldown_actuel > 0) {
            perso->techniques[i].cooldown_actuel--;
            }
        }
        //Buff et débuff
         if(perso->brulure>0){
             printf("\n");
             printf("%s souffre de sa brulure\n",perso->nom);
        perso->pv-=10;
        if(perso->pv<0){
            printf("%s succombe a sa brulure\n",perso->nom);
            perso->est_KO=1;
        }
        printf("il reste %d tours de brulure a %s\n",perso->brulure,perso->nom);
        perso->brulure-=1;
    }
    if(perso->buff_attaque>0){
        perso->buff_attaque-=1;
        printf("\n");
        printf("il reste %d tours de buff d attaque a %s\n",perso->buff_attaque,perso->nom);
    }
    if(perso->buff_defense>0){
        perso->buff_defense-=1;
        printf("\n");
        printf("il reste %d tours de buff de defense a %s\n",perso->buff_defense,perso->nom);
    }
    if(perso->debuff_agilite>0){
        perso->debuff_agilite-=1;
        printf("\n");
        printf("il reste %d tours de debuff d agilite a %s\n",perso->debuff_agilite,perso->nom);
    }    
        //Met en pause l'écran
        sleep(5);
         
        afficher_plateau(equipe1, equipe2);
    }
}
//Attaque basique du combattant
void attaque(Combattant* perso, Combattant* cible) {
    if (!perso || !cible) {
    fprintf(stderr, "Erreur: paramètre NULL dans attaque().\n");
    return;
    }

    printf("%s attaque %s\n", perso->nom, cible->nom);

    int degats = perso->attaque - cible->defense;
    if (degats < 0) degats = 0;
    int rate=rand()%100;
    if(cible->debuff_agilite>0){
        rate*=1.5;
    }
    if(rate<cible->agilite){
        printf("%s esquive l attaque\n",cible->nom);
    }
else{
    int crit = rand() % 100;
    if (crit < perso->agilite) {
        printf("Coup critique ! %s touche un point vital !\n", perso->nom);
        degats = (int)(degats * 1.5);
    }

    printf("%s reçoit %d dégâts.\n", cible->nom, degats);
    cible->pv -= degats;
    if (cible->pv <= 0) {
        cible->pv = 0;
        cible->est_KO = 1;
        printf("%s succombe...\n", cible->nom);
    }
    }
}
//Vérifier si la cible n'est pas K.O.
int cible_valide(Combattant* perso) {
    if (!perso) {
        fprintf(stderr, "Erreur: cible_valide appelée avec un pointeur NULL.\n");
        return 0;
    }

    if (perso->est_KO == 1) {
        printf("Cet ennemi est déjà KO.\n");
        return 0;
    }
    return 1;
}
//Vérifier si une équipe est morte
int equipe_vivante(Combattant* equipe) {
    if (!equipe) {
        fprintf(stderr, "Erreur: equipe_vivante appelée avec un pointeur NULL.\n");
        return 0;
    }

    int morts = 0;
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        if (equipe[i].est_KO == 1) {
            morts++;
        }
    }
    return (morts < TAILLE_EQUIPE);
}
