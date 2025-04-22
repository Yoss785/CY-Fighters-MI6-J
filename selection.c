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
