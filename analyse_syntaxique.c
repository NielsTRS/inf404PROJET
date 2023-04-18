
// Created by niels on 23/01/23.
//

#include "stdlib.h"
#include <stdio.h>
#include "string.h"

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "ast_parcours.h"

void analyser(char *fichier, Ast *arbre)
{
    demarrer(fichier);
    pgm(arbre);
    if (lexeme_courant().nature == FIN_SEQUENCE)
    {
        printf("\nSyntaxte correcte \n");
    }
    else
    {
        printf("Erreur syntaxique 1 \n");
        exit(0);
    }
}

void pgm(Ast *A)
{
    rec_seq_inst(A);
}

void rec_eag(Ast *A)
{
    rec_seq_terme(A);
}

void rec_seq_terme(Ast *A)
{
    Ast A1;
    rec_terme(&A1);
    rec_suite_seq_terme(&A1, A);
}

void rec_suite_seq_terme(Ast *Ag, Ast *A)
{
    Ast Ad, A1;
    TypeOperateur op;
    switch (lexeme_courant().nature)
    {
    case PLUS:
    case MOINS:
        op1(&op);
        rec_terme(&Ad);
        A1 = creer_operation(op, *Ag, Ad);
        rec_suite_seq_terme(&A1, A);
        break;
    default:
        *A = *Ag;
        break;
    }
}

void rec_terme(Ast *A)
{
    rec_seq_facteur(A);
}

void rec_seq_facteur(Ast *A)
{
    Ast A1;
    rec_facteur(&A1);
    rec_suite_seq_facteur(&A1, A);
}

void rec_suite_seq_facteur(Ast *Ag, Ast *A)
{
    Ast Ad, A1;
    TypeOperateur op;
    switch (lexeme_courant().nature)
    {
    case MUL:
    case DIV:
        op2(&op);
        rec_facteur(&Ad);
        A1 = creer_operation(op, *Ag, Ad);
        rec_suite_seq_facteur(&A1, A);
        break;
    default:
        *A = *Ag;
        break;
    }
}

void rec_facteur(Ast *A)
{
    switch (lexeme_courant().nature)
    {
    case ENTIER:
        *A = creer_valeur(lexeme_courant().valeur);
        avancer();
        break;
    case PARO:
        avancer();
        rec_eag(A);
        if (lexeme_courant().nature == PARF)
        {
            avancer();
        }
        else
        {
            printf("Erreur syntaxique 2 \n");
            exit(0);
        }
        break;
    case IDF:
        *A = creer_idf(lexeme_courant().chaine);
        avancer();
        break;
    default:
        printf("Erreur syntaxique 3 \n");
        exit(0);
    }
}

void rec_seq_inst(Ast *A)
{
    Ast A1;
    rec_inst(&A1);
    rec_suite_seq_inst(&A1, A);
}

void rec_suite_seq_inst(Ast *A1, Ast *A)
{
    Ast A2;
    switch (lexeme_courant().nature)
    {
    case SEPAFF:
        avancer();
        if (lexeme_courant().nature == FIN_SEQUENCE || lexeme_courant().nature == ELSE || lexeme_courant().nature == FI || lexeme_courant().nature == DONE)
        {
            *A = *A1;
            break;
        }
        rec_seq_inst(&A2);
        *A = creer_seqinst(A1, &A2);
        break;
    default:
        *A = *A1;
        break;
    }
}

void rec_inst(Ast *A)
{
    Ast Ag, Ad;
    Ast Acond, Athen, Aelse, Abody;
    switch (lexeme_courant().nature)
    {
    case IDF:
        Ag = creer_idf(lexeme_courant().chaine);
        avancer();
        if (lexeme_courant().nature == AFF)
        {
            avancer();
        }
        else
        {
            printf("Erreur syntaxique 4 \n");
            exit(0);
        }
        rec_eag(&Ad);
        *A = creer_aff(Ag, Ad);
        break;
    case IF:
        avancer();
        rec_condition(&Acond);
        if (lexeme_courant().nature == THEN)
        {
            avancer();
        }
        else
        {
            printf("Erreur syntaxique 5 \n");
            exit(0);
        }
        rec_seq_inst(&Athen);
        if (lexeme_courant().nature == ELSE)
        {
            avancer();
        }
        else
        {
            printf("Erreur syntaxique 6 \n");
            exit(0);
        }
        rec_seq_inst(&Aelse);
        *A = creer_if(Acond, Athen, Aelse);
        if (lexeme_courant().nature == FI)
        {
            avancer();
        }
        else
        {
            printf("Erreur syntaxique 7 \n");
            exit(0);
        }
        break;
    case LIRE:
        avancer();
        if (lexeme_courant().nature == PARO)
        {
            avancer();
        }
        else
        {
            printf("Erreur syntaxique 8 \n");
            exit(0);
        }
        if (lexeme_courant().nature == IDF)
        {
            Ag = creer_idf(lexeme_courant().chaine);
            avancer();
        }
        else
        {
            printf("Erreur syntaxique 9 \n");
            exit(0);
        }
        *A = creer_lire(Ag);
        if (lexeme_courant().nature == PARF)
        {
            avancer();
        }
        else
        {
            printf("Erreur syntaxique 10 \n");
            exit(0);
        }
        break;
    case ECRIRE:
        avancer();
        if (lexeme_courant().nature == PARO)
        {
            avancer();
        }
        else
        {
            printf("Erreur syntaxique 11 \n");
            exit(0);
        }
        rec_eag(&Ag);
        *A = creer_ecrire(Ag);
        if (lexeme_courant().nature == PARF)
        {
            avancer();
        }
        else
        {
            printf("Erreur syntaxique 12 \n");
            exit(0);
        }
        break;
    case WHILE:
        avancer();
        rec_condition(&Acond);
        if (lexeme_courant().nature == DO)
        {
            avancer();
        }
        else
        {
            printf("Erreur syntaxique 13 \n");
            exit(0);
        }
        rec_seq_inst(&Abody);
        if(lexeme_courant().nature == DONE)
            avancer();
        else
            printf("Erreur syntaxique 14 \n");
        *A = creer_while(Acond, Abody);
        break;
    default:
        printf("Nature : %d \n", lexeme_courant().nature);
        printf("Chaine : %s \n", lexeme_courant().chaine);
        printf("Erreur syntaxique 15 \n");
        exit(0);
    }
}

void rec_condition(Ast *A){
    Ast A1;
    rec_seq_condition(&A1);
    rec_suite_seq_condition(&A1, A);
}

void rec_suite_seq_condition(Ast *A1, Ast *A){
    Ast A2;
    TypeOperateur op;
    switch (lexeme_courant().nature)
    {
    case OPBOOL:
        BoolIf(&op);
        avancer();
        rec_seq_condition(&A2);
        *A = creer_bool(op, A1, &A2);
        break;
    default:
        *A = *A1;
        break;
    }
}

void rec_seq_condition(Ast *A){
    Ast Ag, Ad;
    TypeOperateur op;
    rec_eag(&Ag);
    if(lexeme_courant().nature == OPCOMP){
        operationIf(&op);
        avancer();
    }else{
        printf("Erreur syntaxique 16 \n");
        exit(0);
    }
    rec_eag(&Ad);
    *A = creer_operation(op, Ag, Ad);
}

void BoolIf(TypeOperateur *Op){
    printf("Chaine : %s", lexeme_courant().chaine);
    if(strcmp(lexeme_courant().chaine, "&&") == 0){
        *Op = N_ET;
    }else if(strcmp(lexeme_courant().chaine, "||") == 0){
        *Op = N_OU;
    }else{
        printf("Erreur syntaxique 17 \n");
        exit(0);
    }
}

void operationIf(TypeOperateur *Op){
    if(strcmp(lexeme_courant().chaine, "<") == 0){
        *Op = N_INF;
    }else if(strcmp(lexeme_courant().chaine, ">") == 0){
        *Op = N_SUP;
    }else if(strcmp(lexeme_courant().chaine, "<=") == 0){
        *Op = N_INFEGAL;
    }else if(strcmp(lexeme_courant().chaine, ">=") == 0){
        *Op = N_SUPEGAL;
    }else if(strcmp(lexeme_courant().chaine, "==") == 0){
        *Op = N_EGAL;
    }else if(strcmp(lexeme_courant().chaine, "!=") == 0){
        *Op = N_DIFF;
    }else{
        printf("Erreur syntaxique 18 \n");
        exit(0);
    }
}

void op1(TypeOperateur *Op)
{
    switch (lexeme_courant().nature)
    {
    case PLUS:
        *Op = N_PLUS;
        avancer();
        break;
    case MOINS:
        *Op = N_MOINS;
        avancer();
        break;
    default:
        printf("Erreur syntaxique 19 \n");
        break;
    }
}

void op2(TypeOperateur *Op)
{
    switch (lexeme_courant().nature)
    {
    case MUL:
        *Op = N_MUL;
        avancer();
        break;
    case DIV:
        *Op = N_DIV;
        avancer();
        break;
    default:
        break;
        printf("Erreur syntaxique 20 \n");
    }
}

char rec_op()
{
    switch (lexeme_courant().nature)
    {
    case PLUS:
        avancer();
        return '+';
    case MOINS:
        avancer();
        return '-';
    case MUL:
        avancer();
        return '*';
    case DIV:
        avancer();
        return '/';
    default:
        printf("Erreur syntaxique 21\n");
        exit(0);
    }
}

int calcul(int ent1, char operation, int ent2)
{
    switch (operation)
    {
    case '+':
        return ent1 + ent2;
    case '-':
        return ent1 - ent2;
    case '/':
        return ent1 / ent2;
    case '*':
        return ent1 * ent2;
    default:
        printf("operation inconnue");
        exit(0);
    }
}