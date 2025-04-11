// Main
#include "code.h"
int main() {
    Personnage persos[3] = {
        {"LUFFY", "o", 1, 10, 10, 5},
        {"ZORO",  "z", 2, 14, 7, 38},
        {"SANJI", "s", 3, 4, 12, 68}
    };
    printf("hello");
    afficher_plateau(persos, 3);
    return 0;
}
