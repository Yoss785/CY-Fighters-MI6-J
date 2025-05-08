#include <stdio.h>
#include <stdlib.h>
#include "check.h"

void flush(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
int getInt(int min, int max) {
    int val = 0;
    char c;
    int valide = 0;

    while (!valide) {
        c = getchar();  // Lire un caractère
        if (c == '\n') continue;  // Ignorer les retours à la ligne

        // Vérifier si c'est un chiffre
        if (c >= '0' && c <= '9') {
            val = val * 10 + (c - '0');  // Construire l'entier
        } else if (c == '\n') {
            // Vérification si la valeur est dans l'intervalle valide
            if (val >= min && val <= max) {
                valide = 1;  // Saisie valide
            } else {
                printf("Veuillez entrer un nombre entre %d et %d.\n", min, max);
                val = 0;  // Réinitialiser la valeur si elle est invalide
                printf("Essayer encore : ");
            }
        } else {
            printf("Entrée invalide. Essayez de nouveau.\n");
            val = 0;  // Réinitialiser si l'entrée n'est pas un chiffre
        }
    }
    return val;
}
