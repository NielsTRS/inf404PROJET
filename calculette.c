//
// Created by niels on 23/01/23.
//

#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"

int main(int argc, char *argv[]) {
    int resultat = 0;
    if (argc == 2) {
        analyser(argv[1], &resultat);
        printf("Resultat : %d \n", resultat);
    } else {
        printf("Il faut 1 argument");
        exit(0);
    }
    return 0;
}