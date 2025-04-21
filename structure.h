#define MAX_NOM 50
#define MAX_DESC 200
#define MAX_TECH 2


// Technique spéciale d’un combattant
typedef struct {
    char nom[MAX_NOM];
    int degat;                         // valeur de l’effet
    char propriete_affectee[MAX_NOM];  // ex: "attaque", "pv", "vitesse"
    char operation[10];                // "+", "-", "*", etc.
    char description[MAX_DESC];
    int tours_rechargement;           // cooldown
    int cooldown_actuel;              // pour savoir quand elle sera dispo
} TechniqueSpeciale;

//L'idee c'est de juste creer une fonction qui à partir des information de la technique permette directement d'appliquer cette dernière au lieu de créer une fonction pour chaque technique 

// Combattant (personnage)
typedef struct {
    char nom[MAX_NOM];

    int pv;             // points de vie actuel
    int pv_max;         // points de vie maximum
    int attaque;
    int defense;
    int agilite;
    int vitesse;

    TechniqueSpeciale techniques[MAX_TECHNIQUES];  // techniques spéciales
    int nb_techniques;


    int prochain_tour; // utilisé pour déterminer quand il joue
    int est_KO;        // 0 = actif, 1 = KO
} Combattant;
