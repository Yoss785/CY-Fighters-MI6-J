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
#define L 90
#define H 6
#define MAX_BARRE 14
