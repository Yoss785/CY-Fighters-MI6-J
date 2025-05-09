#ifndef CODE_H
#define CODE_H

#ifndef CODE_H
#define CODE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NOM 50
#define MAX_DESC 200
#define MAX_TECHNIQUES 1
#define TAILLE_EQUIPE 1
#define L 90
#define H 15
#define h 6
#define MAX_BARRE 10
#define NBPERSO 8

typedef struct {
    char nom[MAX_NOM];
    int degat;
    char propriete_affectee[MAX_NOM];
    char operation[10]; 
    char description[MAX_DESC];
    int tours_rechargement;
    int cooldown_actuel;
    
} TechniqueSpeciale;

typedef struct Combattant {
    char nom[MAX_NOM];
    int pv;
    int pv_max;
    int attaque;
    int buff_attaque;
    int defense;
    int buff_defense;
    int agilite;
    int debuff_agilite;
    int vitesse;
    int action;
    TechniqueSpeciale techniques[MAX_TECHNIQUES];
    int nb_techniques;
    int est_actif;
    int est_KO;
    int position;
    struct Combattant* equipe; // Ajout du pointeur vers l'équipe
    int brulure;
} Combattant;

#endif
