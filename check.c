#include <stdio.h>
#include <stdlib.h>
#include "check.h"

void flush(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getInt(int min, int max) {
    int valeur;
    char buffer[100];

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &valeur) == 1) {
                if (valeur >= min && valeur <= max) {
                    return valeur;
                } else {
                    printf("Erreur : valeur hors des limites.\n");
                }
            } else {
                printf("Erreur : entrée invalide, veuillez entrer un entier.\n");
            }
        } else {
            printf("Erreur de lecture. Réessayez.\n");
            clearerr(stdin);
        }
    }
}
