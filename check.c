#include <stdio.h>
#include <stdlib.h>
#include "check.h"

void flush(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

#include <stdio.h>

int getInt() {
    int val = 0;
    char c;
    int Valide = 1;

    while (1) {
        Valide = 1;  // On suppose au départ que l'entrée est valide
        printf("Entrez un entier : ");
        
        // Lire chaque caractère jusqu'à ce qu'on atteigne '\n' ou EOF
        while ((c = getchar()) != '\n' && c != EOF) {
            // Vérifier si le caractère est un chiffre
            if (c < '0' || c > '9') {
                Valide = 0;  // Entrée invalide si le caractère n'est pas un chiffre
                break;
            }

            // Construire la valeur entière
            val = val * 10 + (c - '0');
        }

        if (Valide) {
            return val;  // Si l'entrée est valide, retourner la valeur
        } else {
            // Si entrée invalide, afficher un message d'erreur et vider le tampon
            printf("Entrée invalide. Veuillez entrer un entier valide.\n");
            // Vider le tampon pour nettoyer l'entrée
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}
