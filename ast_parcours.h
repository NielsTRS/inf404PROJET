#ifndef __AST_PARCOURS__
#define __AST_PARCOURS__

#include "type_ast.h"

void afficherArbre(Ast expr);
// affiche l'arbre abstrait de l'expression arithmetique expr

int evaluation(Ast expr) ;
// calcule la valeur de l'expression arithmetique expr
// FONCTION A COMPLETER !

void interpreter(Ast A);

void interpreter_aff(Ast A);

void interpreter_lire(Ast A);

void interpreter_ecrire(Ast A);

#endif

