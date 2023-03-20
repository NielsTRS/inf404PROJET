#include <stdio.h>
#include "string.h"
#include "table.h"

void initTS(){
    NbSymb = 0;
}

void afficheTS(){
    for(int i = 0; i< NbSymb; i++){
        printf("Nom : %s, valeur : %i\n", TS[i].nom, TS[i].valeur);
    }
}

int estPresentTS(char *idf, int *v){
    for(int i = 0; i< NbSymb; i++){
        if(strcmp(TS[i].nom, idf) == 0){
            *v = TS[i].valeur;
            return 1;
        }
    }
    return 0;
}

void insererTS(char *idf, int v){
    for(int i = 0; i< NbSymb; i++){
        if(strcmp(TS[i].nom, idf) == 0){
            TS[i].valeur = v;
            return;
        }
    }
    strcpy(TS[NbSymb].nom, idf);
    TS[NbSymb].valeur = v;
    NbSymb++;
}