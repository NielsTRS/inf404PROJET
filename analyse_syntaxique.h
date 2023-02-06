//
// Created by niels on 23/01/23.
//

#ifndef INF404_ANALYSE_SYNTAXIQUE_H
#define INF404_ANALYSE_SYNTAXIQUE_H

#endif //INF404_ANALYSE_SYNTAXIQUE_H

typedef enum {
    E_INIT, E_ENTIER, E_SYM
} Etat_Automate;

void analyser(char *fichier, int *resultat);

int calcul(int ent1, char operation, int ent2);
/*
-- e.i : indifferent
-- e.f : une Expression Arithmetique a ete lue dans fichier
-- si elle ne contient pas d’erreur de syntaxe un message est affiche
-- sinon le pgm termine sur un message d’erreur
 */