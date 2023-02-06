
// Created by niels on 23/01/23.
//

#include "stdlib.h"
#include <stdio.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"

void analyser(char *fichier, int *resultat)
{
    Etat_Automate etat = E_INIT;

    // demarrage
    demarrer(fichier);
    Lexeme lexemeCourant;

    char operation;
    while (!fin_de_sequence())
    {
        lexemeCourant = lexeme_courant();
        switch (etat)
        {
        case E_INIT:
            switch (lexemeCourant.nature)
            {
            case ENTIER:
            case PARO:
                etat = E_ENTIER;
                *resultat += rec_eaep();
                break;
            default:
                printf("Erreur syntaxique 1  \n");
                exit(0);
            }
            break;
        case E_ENTIER:
            switch (lexemeCourant.nature)
            {
            case PLUS:
                etat = E_SYM;
                avancer();
                break;
            case MOINS:
                etat = E_SYM;
                avancer();
                break;
            case DIV:
                etat = E_SYM;
                avancer();
                break;
            case MUL:
                etat = E_SYM;
                avancer();
                break;
            default:
                printf("Erreur syntaxique 2 \n");
                exit(0);
            }
            operation = lexemeCourant.chaine[0];
            break;
        case E_SYM:
            switch (lexemeCourant.nature)
            {
            case ENTIER:
                etat = E_ENTIER;
                *resultat = calcul(*resultat, operation, lexemeCourant.valeur);
                avancer();
                break;
            case PARO:
                etat = E_ENTIER;
                *resultat = calcul(*resultat, operation, rec_eaep());
                break;
            default:
                printf("Erreur syntaxique 3 \n");
                exit(0);
            }
            break;
        }
    }
    switch (etat)
    {
    case E_ENTIER:
        printf("Syntaxe correcte \n");
        break;
    default:
        printf("Erreur syntaxique 4 \n");
        break;
    }
}

int rec_eaep()
{
    switch (lexeme_courant().nature)
    {
    case ENTIER:
        avancer();
        return lexeme_courant().valeur;
    case PARO:
        avancer();
        int a = rec_eaep();
        char op = rec_op();
        int b = rec_eaep();
        if (lexeme_courant().nature == PARF)
        {
            avancer();
            return calcul(a, op, b);
        }
        else
        {
            printf("Erreur syntaxique \n");
            exit(0);
        }
    default:
        printf("Erreur syntaxique \n");
        exit(0);
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
        printf("Erreur syntaxique \n");
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