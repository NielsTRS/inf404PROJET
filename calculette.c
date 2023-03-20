//
// Created by niels on 23/01/23.
//

#include <stdio.h>
#include <stdlib.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "ast_parcours.h"

int main(int argc, char *argv[])
{
    Ast arbre;
    if (argc == 2)
    {
        analyser(argv[1], &arbre);
        printf("L'arbre est :");
        afficherArbre(arbre);
        
        printf("\n Le résultat est : %d\n", evaluation(arbre));
    }
    else
    {
        printf("Il faut 1 argument");
        exit(0);
    }
    return 0;
}