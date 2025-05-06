#include "code.h"
int equipe_vivante(Combattant* equipe){
    int morts=0;
    for(int i=0;i<TAILLE_EQUIPE;i++){
        if((equipe+i)->est_KO==1){
            morts+=1;
        }
    }
    if(morts==TAILLE_EQUIPE){
        return 0;
    }
    else{
        return 1;
    }
}
void flush(){
    char lettre='a';
    while(lettre=!'\n'){
        scanf("%c",&lettre);
    }
}
