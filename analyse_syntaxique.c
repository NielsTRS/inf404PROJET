
// Created by niels on 23/01/23.
//

#include "stdlib.h"
#include <stdio.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"

void analyser(char *fichier, int *resultat) {
    Etat_Automate etat = E_INIT;

    // demarrage
    demarrer(fichier);
    Lexeme lexemeCourant;

    char operation;
    while (!fin_de_sequence()) {
        lexemeCourant = lexeme_courant();
        switch (etat) {
            case E_INIT:
                switch (lexemeCourant.nature) {
                    case ENTIER:
                        etat = E_ENTIER;
                        *resultat += lexemeCourant.valeur;
                        avancer();
                        break;
                    default:
                        printf("Erreur syntaxique \n");
                        exit(0);
                }
                break;
            case E_ENTIER:
                switch (lexemeCourant.nature) {
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
                        printf("Erreur syntaxique \n");
                        exit(0);
                }
                operation = lexemeCourant.chaine[0];
                break;
            case E_SYM:
                switch (lexemeCourant.nature) {
                    case ENTIER:
                        etat = E_ENTIER;
                        *resultat = calcul(*resultat, operation, lexemeCourant.valeur);
                        avancer();
                        break;
                    default:
                        printf("Erreur syntaxique \n");
                        exit(0);
                }
                break;

        }

    }
    switch (etat) {
        case E_ENTIER:
            printf("Syntaxe correcte \n");
            break;
        default:
            printf("Erreur syntaxique \n");
            break;

    }


}

int calcul(int ent1, char operation, int ent2) {
    switch (operation) {
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