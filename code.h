#ifndef CODE_H
#define CODE_H

#define MAX_NOM 50
#define MAX_DESC 200
#define MAX_TECHNIQUES 2
#define TAILLE_EQUIPE 1 //Pour faciliter mes tests sinon c'est 3 
#define L 90 
#define H 15
#define h 6
#define MAX_BARRE 14
#define NBPERSO 3

typedef struct {
    char nom[MAX_NOM];
    int degat; 
    char propriete_affectee[MAX_NOM];
    char operation[10]; 
    char description[MAX_DESC];
    int tours_rechargement;
    int cooldown_actuel;
} TechniqueSpeciale; //on n'affiche que le nom, la description ,le tour de rechargement et le cooldown actuel

typedef struct {
    char nom[MAX_NOM];
    int pv;
    int pv_max;
    int attaque;
    int defense;
    int agilite;
    int vitesse;

    TechniqueSpeciale techniques[MAX_TECHNIQUES];
    int nb_techniques;

    int prochain_tour;
    int est_KO;
    int position;
} Combattant;

#endif
