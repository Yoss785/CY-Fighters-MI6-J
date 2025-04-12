// Main
#include "code.h"
int main() {
    Personnage persos[3] = {
        {"LUFFY", "l", 1, 10, 14, 10, 10, 10, 10, 5},
        {"ZORO",  "z", 2, 14, 14, 10, 10, 10 7, 38},
        {"SANJI", "s", 3, 4, 14, 10, 10, 10, 12, 68}
    };
    afficher_plateau(persos, 3);
    return 0;
}
