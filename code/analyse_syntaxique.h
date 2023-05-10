//
// Created by niels on 23/01/23.
//

#ifndef INF404_ANALYSE_SYNTAXIQUE_H
#define INF404_ANALYSE_SYNTAXIQUE_H

#endif // INF404_ANALYSE_SYNTAXIQUE_H

#include "type_ast.h"
#include "ast_construction.h"
typedef enum
{
    E_INIT,
    E_ENTIER,
    E_SYM
} Etat_Automate;

void analyser(char *fichier, Ast *arbre);

void pgm(Ast *A);

int calcul(int ent1, char operation, int ent2);

void rec_eag(Ast *A);

void rec_suite_seq_terme(Ast *Ad, Ast *A);

void rec_seq_terme(Ast *A);

void rec_terme(Ast *A);

void rec_seq_facteur(Ast *A);

void rec_suite_seq_facteur(Ast *Ag, Ast *A);

void rec_facteur(Ast *A);

void rec_seq_inst(Ast *A);

void rec_suite_seq_inst(Ast *A1, Ast *A);

void rec_inst(Ast *A);

void rec_condition(Ast *A);

void rec_suite_seq_condition(Ast *A1, Ast *A);

void rec_seq_condition(Ast *A);

void BoolIf(TypeOperateur *Op);

void operationIf(TypeOperateur *Op);

void op1(TypeOperateur *Op);

void op2(TypeOperateur *Op);



char rec_op();
/*
-- e.i : indifferent
-- e.f : une Expression Arithmetique a ete lue dans fichier
-- si elle ne contient pas d’erreur de syntaxe un message est affiche
-- sinon le pgm termine sur un message d’erreur
 */