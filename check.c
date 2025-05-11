#include <stdio.h>
#include <stdlib.h>
#include "check.h"

int getInt(int min, int max) {
    if (min > max) {
        fprintf(stderr, "Erreur : getInt() appelé avec min > max (%d > %d)\n", min, max);
        return 0;
    }
    char buffer[100];
    int val = 0;
    int valide = 0;

    while (!valide) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erreur de lecture. Réessayez.\n");
            continue;
        }

        val = 0;
        int i = 0;
        while (buffer[i] >= '0' && buffer[i] <= '9') {
            val = val * 10 + (buffer[i] - '0');
            i++;
        }

        // Si i == 0 => aucun chiffre lu, donc saisie invalide
        // Si buffer[i] n’est pas '\n' ou '\0' => il y a des caractères invalides
        if (i == 0 || (buffer[i] != '\n' && buffer[i] != '\0')) {
            printf("Entrée invalide. Veuillez entrer un nombre entre %d et %d.\n", min, max);
            continue;
        }

        if (val >= min && val <= max) {
            valide = 1;
        } else {
            printf("Veuillez entrer un nombre entre %d et %d.\n", min, max);
        }
    }

    return val;
}
