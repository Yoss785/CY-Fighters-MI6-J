#include <stdio.h>
#include <string.h>
#define L 90
#define H 6
#define MAX_BARRE 14
#define NBPERSO 2 //a changer a la fin
#define TAILLE_EQUIPE 3//a changer potentiellement
// Structure pour stocker un personnage
typedef struct {
    char *nom;
    char *effet;
    int cible;
    int PV;
    int PVmax;
    int ATQ;
    int DEF;
    int AGL;
    int VIT;
    int position;  // position horizontale du perso
} Personnage;

void dessiner_barre(int valeur, int max, char symbole);
void afficher_ligne(int ligne, Personnage persos[], int nb_persos);
void afficher_plateau(Personnage persos[], int nb_persos);
