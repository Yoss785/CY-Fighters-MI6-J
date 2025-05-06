#include "code.h"
int cible_valide(Combattant* perso) {
	if(perso->est_KO==1) {
		printf("cet ennemi est deja mort \n");
		return 0;
	}
	else {
		return 1;
	}
}




void phase(Combattant* equipe1,Combattant* equipe2) {
	for(int i=0; i<NBPERSO; i++) {
		if((equipe1+i)->est_KO==0) {
			(equipe1+i)->action+=(equipe1+i)->vitesse;
			if((equipe1+i)->action>=100) {
				(equipe1+i)->action-=100;
				printf("au tour du joueur 1\n");
				tour(equipe1+i,equipe2);
			}
		}
		else {
			(equipe1+i)->action=0;
		}
		if((equipe2+i)->est_KO==0) {
			(equipe2+i)->action+=(equipe2+i)->vitesse;
			if((equipe2+i)->action>=100) {
				(equipe2+i)->action-=100;
				printf("au tour du joueur 2\n");
				tour(equipe2+i,equipe1);
			}
		}
		else {
			(equipe2+i)->action=0;
		}
	}
	//affichage(equipe1);
	//affichage(equipe2);
}
void tour(Combattant* perso,Combattant* equipe) {
	int choix=-1;
	while(choix!=1&&choix!=2) {
		printf("Quelle action voulez vous effectuer:\n 1=attaquer\n 2=capacite speciale\n");
		scanf("%d",&choix);
		if(choix!=1&&choix!=2) {
			printf("mauvais choix");
		}
	}
	if(choix==1) {
		attaque(perso,equipe);
	}
	else {
		//attaque_speciale(perso,equipe);
	}

}
void attaque(Combattant* perso,Combattant* equipe) {
	int choix=-1;
	int validation=-1;
//	affichage(equipe);
	while(choix<1||choix>TAILLE_EQUIPE||validation!=1) {
	    
		printf("Entrez la position du perso a attaquer\n");
		scanf("%d",&choix);
		validation=cible_valide(equipe+choix-1);

	}
	printf("%s attaque %s\n",perso->nom,(equipe+choix-1)->nom);
	int degats=(perso->attaque)-((equipe+choix-1)->defense);
	int crit=rand()%100;
	if(crit<perso->agilite) {
		printf("%s touche un point vital\n",perso->nom);
		degats=degats*3;// a changer pour equilibrage
	}// on determine si il y a un coup critique
	printf("%s recoit %d degats\n",(equipe+choix-1)->nom,degats);
	(equipe+choix-1)->pv-=degats;
	if((equipe+choix-1)->pv<=0) {
		printf("%s succombe\n",(equipe+choix-1)->nom);
		(equipe+choix-1)->pv=0;
		(equipe+choix-1)->est_KO=1;
	}
}