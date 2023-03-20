
// Created by niels on 23/01/23.
//

#include "stdlib.h"
#include <stdio.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "ast_parcours.h"

void analyser(char *fichier, Ast *arbre)
{
    demarrer(fichier);
    rec_seq_aff(arbre);
    if (lexeme_courant().nature == FIN_SEQUENCE)
    {
        printf("Syntaxte correcte \n");
    }
    else
    {
        printf("Erreur syntaxique 1 \n");
        exit(0);
    }
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
        avancer();
        break;
    default:
        printf("Erreur syntaxique 3 \n");
        exit(0);
    }
}

void rec_seq_aff(){
    switch (lexeme_courant().nature)
    {
        case IDF:
            rec_aff();
            rec_seq_aff();
            break;
        default:
            break;
    }
}

void rec_aff(){
    Ast A;
    if(lexeme_courant().nature == IDF){
        avancer();
    }else{
        printf("Erreur syntaxique \n");
        exit(0);
    }
    if(lexeme_courant().nature == AFF){
        avancer();
    }else{
        printf("Erreur syntaxique \n");
        exit(0);
    }
    rec_eag(&A);
    if(lexeme_courant().nature == SEPAFF){
        avancer();
    }else{
        printf("Erreur syntaxique \n");
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
        printf("Erreur syntaxique 6 \n");
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
        printf("Erreur syntaxique 7 \n");
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
        printf("Erreur syntaxique 8\n");
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