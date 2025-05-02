#include "code.h"





void phase(Combattant* equipe1,Combattant* equipe2){
for(int i=0;i<NBPERSO;i++){
	(equipe1+i)->action+=(equipe1+i)->vitesse;
	if((equipe1+i)->action>=100){
		(equipe1+i)->action-=100;
		tour(equipe1+i,equipe2);
	}
	(equipe2+i)->action+=(equipe2+i)->vitesse;
	if((equipe2+i)->action>=100){
		(equipe2+i)->action-=100;
		tour(equipe2+i,equipe1);
	}
}
}
void tour(Combattant* perso,Combattant* equipe){
	int choix=-1;
	while(choix!=1&&choix!=2){
		printf("Quelle action voulez vous effectuer:\n 1=attaquer\n 2=capacite speciale\n");
		scanf("%d",&choix);
		if(choix!=1&&choix!=2){
			printf("mauvais choix");
		}
	}
	if(choix==1){
		attaque(perso,equipe);
	}
	else{
		//attaque_speciale(perso,equipe);
	}

}
void attaque(Combattant* perso,Combattant* equipe){
    int choix=-1;
    while(choix<1||choix>TAILLE_EQUIPE){
    printf("Entrez la position du perso a attaquer\n");
    scanf("%d",&choix);
    }
    printf("%s attaque %s\n",perso->nom,(equipe+choix-1)->nom);
    int degats=(perso->attaque)-((equipe+choix-1)->defense);
    int crit=rand()%100;
    if(crit<perso->agilite){
        printf("%s touche un point vital\n",perso->nom);
        degats=degats*3;// a changer pour equilibrage
    }// on determine si il y a un coup critique
    printf("%s recoit %d degats\n",(equipe+choix-1)->nom,degats);
    (equipe+choix-1)->PV-=degats;
    if((equipe+choix-1)->PV<=0){
        printf("%s succombe\n",(equipe+choix-1)->nom);
        (equipe+choix-1)->est_KO=0;
    }
}