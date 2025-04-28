#include "code.h"
void afficher_equipe(Combattant* equipe) {
	for(int i=0; i<TAILLE_EQUIPE; i++) {
		afficher_stats(*(equipe+i));
	}
}// on affiche les stats de chaque Combattant
void selection(Combattant* equipe1,Combattant* equipe2,FILE* fichier) {
	for(int i=0; i<TAILLE_EQUIPE; i++) {
		rewind(fichier);
		printf("au tour du joueur1 de selectionner un Combattant\n");
		construction_perso((equipe1+i),fichier);
		// printf("%s",equipe1->nom);
		rewind(fichier);
		printf("au tour du joueur2 de selectionner un Combattant\n");
		construction_perso((equipe2+i),fichier);
	}
	//on part du principe que les deux equipes ont meme nb de persos
}   //chaque joueur choisi un Combattant qui sera ensuite construit par la fonction construction_perso
void afficher_stats(Combattant perso) {
	printf("Nom du combattant : %s\n",perso.nom);
	printf("PVmax : %d\n",perso.PVmax);
	printf("Attaque : %d\n",perso.attaque);
	printf("defense : %d\n",perso.defense);
	printf("Agilite : %d\n",perso.agilite);
	printf("vitesse : %d\n",perso.vitesse);
}// on print chaque stat
void apercu(FILE* fichier,int choix) {
	char* poubelle=malloc(40);
	char* nom=malloc(20);
	int stat;
	for(int i=0; i<choix-1; i++) {
		fgets(poubelle,40,fichier);
// 	printf("%s",poubelle);
	}//on "jette" les Combattants qui se trouvent avant le perso selectionne
	free(poubelle);
	fscanf(fichier,"%s\n",nom);
	printf("Nom du combattant : %s\n",nom);
	free(nom);
	fscanf(fichier,"%d",&stat);
	printf("PVmax : %d\n",stat);
	fscanf(fichier,"%d",&stat);
	printf("Attaque : %d \n",stat);
	fscanf(fichier,"%d",&stat);
	printf("Defense : %d \n",stat);
	fscanf(fichier,"%d",&stat);
	printf("Agilite : %d \n",stat);
	fscanf(fichier,"%d",&stat);
	printf("vitesse : %d \n",stat);

}//on affiche les stats sans les stocker car le Combattant ne sera pas forcement valide 
void construction_perso(Combattant* perso,FILE* fichier) {
	int choix=-1;
	int validation=-1;
	char* poubelle=malloc(40);
	perso->nom=malloc(20);//Je ne sais pas quand le free
	if(perso->nom==NULL) {
		printf("erreur malloc");
		exit(9);
	}
	while(validation!=1||choix<1||choix>NBPERSO) {
		printf("Entrez le numero du Combattant que vous voulez\n");
		scanf("%d",&choix);
		if(choix<1||choix>NBPERSO) {
			printf("ce Combattant n'existe pas, veuillez en choisir un autre\n");
		}
		else {
			apercu(fichier,choix);
			printf("validez-vous votre choix? 1=oui 0=non\n");
			scanf("%d",&validation);
			if(validation!=1) {
				printf("On recommence la selection de ce personnnage\n");
			}
		}
		rewind(fichier);
	}

	for(int i=0; i<choix-1; i++) {
		fgets(poubelle,40,fichier);
// 	printf("%s",poubelle);
	}//on "jette" les Combattants qui se trouvent avant le perso selectionne
	free(poubelle);

	fscanf(fichier,"%s",perso->nom);
// 	printf("%s \n",nom);
	//(perso->nom)=nom;
//	printf("%s",perso->nom);
	//free(nom);
	fscanf(fichier,"%d",&(perso->PVmax));
// 	printf("%d \n",perso->PVmax);
	fscanf(fichier,"%d",&(perso->attaque));
// 	printf("%d \n",perso->attaque);
	fscanf(fichier,"%d",&(perso->defense));
// 	printf("%d \n",perso->defense);
	fscanf(fichier,"%d",&(perso->agilite));
// 	printf("%d \n",perso->agilite);
	fscanf(fichier,"%d",&(perso->vitesse));
// 	printf("%d \n",perso->vitesse);
	//on remplie chaque statistiques fixes du Combattant

}
/* 
Yanis: (pour pas écraser le travail d'Hugo et en attendant votre avis et vos questions)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#include "selection.h"

void afficher_stats(Combattant perso) {
    printf("Nom : %s\n", perso.nom);
    printf("PV max : %d\n", perso.pv_max);
    printf("Attaque : %d\n", perso.attaque);
    printf("Défense : %d\n", perso.defense);
    printf("Agilité : %d\n", perso.agilite);
    printf("Vitesse : %d\n", perso.vitesse);
    printf("Nom de la technique : %s\n", perso.techniques[0].nom);
    printf("Description : %s\n", perso.techniques[0].description);
    printf("Tours de rechargement : %d\n", perso.techniques[0].tours_rechargement);
    printf("cooldown_actuel : %d\n", perso.techniques[0].cooldown_actuel);
}

void afficher_equipe(Combattant* equipe) {
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        printf("\n--- Combattant %d ---\n", i + 1);
        afficher_stats(equipe[i]);
    }
}

void apercu(FILE* fichier, int choix) {
    char buffer[200];
    char nom[MAX_NOM];
    int stat;

    // On saute les personnages précédents
    for (int i = 0; i < choix - 1; i++) {
        for (int j = 0; j < 10; j++) { // 10 lignes par perso maintenant
            fgets(buffer, sizeof(buffer), fichier);
        }
    }

    fgets(nom, sizeof(nom), fichier);
    nom[strcspn(nom, "\n")] = '\0'; 
    printf("Nom : %s\n", nom);

    fscanf(fichier, "%d\n", &stat);
    printf("PV max : %d\n", stat);
    fscanf(fichier, "%d\n", &stat);
    printf("Attaque : %d\n", stat);
    fscanf(fichier, "%d\n", &stat);
    printf("Défense : %d\n", stat);
    fscanf(fichier, "%d\n", &stat);
    printf("Agilité : %d\n", stat);
    fscanf(fichier, "%d\n", &stat);
    printf("Vitesse : %d\n", stat);
    
    printf("\n ==== Technique ====\n");
    
    fgets(buffer, sizeof(buffer), fichier); // Nom technique
    buffer[strcspn(buffer, "\n")] = '\0';
    printf("Technique spéciale : %s\n", buffer);

    fgets(buffer, sizeof(buffer), fichier); // Description
    buffer[strcspn(buffer, "\n")] = '\0';
    printf("Description : %s\n", buffer);

    fscanf(fichier, "%d\n", &stat);
    printf("Tours de rechargement : %d\n", stat);

    fscanf(fichier, "%d\n", &stat);
    /*printf("Cooldown actuel : %d\n", stat); On ne l'affiche pas dans l'aperçu*/
}

void construction_perso(Combattant* perso, FILE* fichier) {
    int choix = -1;
    int validation = -1;

    while (validation != 1 || choix < 1 || choix > NBPERSO) {
        printf("Entrez le numéro du combattant à sélectionner (1 à %d) : ", NBPERSO);
        scanf("%d", &choix);

        if (choix < 1 || choix > NBPERSO) {
            printf("Ce combattant n'existe pas. Réessayez.\n");
        } else {
            rewind(fichier);
            apercu(fichier, choix);
            printf("\nValidez-vous ce choix ? (1 = oui, 0 = non) :\n ");
            scanf("%d", &validation);
            if (validation != 1) {
                printf("Recommençons la sélection.\n");
            }
        }
    }

    rewind(fichier);

    // Avancer dans le fichier jusqu'au combattant choisi
    char buffer[200];
    for (int i = 0; i < choix - 1; i++) {
        for (int j = 0; j < 10; j++) { // 10 lignes par personnage
            fgets(buffer, sizeof(buffer), fichier);
        }
    }

    fgets(perso->nom, MAX_NOM, fichier);
    perso->nom[strcspn(perso->nom, "\n")] = '\0';

    fscanf(fichier, "%d\n", &perso->pv_max);
    perso->pv = perso->pv_max;
    fscanf(fichier, "%d\n", &perso->attaque);
    fscanf(fichier, "%d\n", &perso->defense);
    fscanf(fichier, "%d\n", &perso->agilite);
    fscanf(fichier, "%d\n", &perso->vitesse);

    // Lire la technique spéciale
    fgets(perso->techniques[0].nom, MAX_NOM, fichier);
    perso->techniques[0].nom[strcspn(perso->techniques[0].nom, "\n")] = '\0';

    fgets(perso->techniques[0].description, MAX_DESC, fichier);
    perso->techniques[0].description[strcspn(perso->techniques[0].description, "\n")] = '\0';

    fscanf(fichier, "%d\n", &perso->techniques[0].tours_rechargement);
    fscanf(fichier, "%d\n", &perso->techniques[0].cooldown_actuel);

    perso->nb_techniques = 1;
    perso->prochain_tour = 0;
    perso->est_KO = 0;
    perso->position = -1;
}

void selection(Combattant* equipe1, Combattant* equipe2, FILE* fichier) {
    for (int i = 0; i < TAILLE_EQUIPE; i++) {
        rewind(fichier);
        printf("\nJoueur 1 - Sélection du combattant %d\n", i + 1);
        construction_perso(&equipe1[i], fichier);
        equipe1[i].position = i * 25;
        
        rewind(fichier);
        printf("\nJoueur 2 - Sélection du combattant %d\n", i + 1);
        construction_perso(&equipe2[i], fichier);
        equipe1[i].position = i * 25;
    }
}
*/
