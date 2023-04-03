
#ifndef __AST_CONSTRUCTION__
#define __AST_CONSTRUCTION__

#include "type_ast.h"

Ast creer_operation(TypeOperateur opr , Ast opde_gauche , Ast opde_droit) ;
// renvoie un arbre abstrait de nature OPERATEUR,  d'operateur opr 
// et ayant opde_gauche et opde_droit pour fils gauche et droit

Ast creer_valeur(int val) ; 
// renvoie un arbre abstrait "feuille", de nature OPERATION  
// et de valeur val

Ast creer_seqinst(Ast *A1, Ast *A2);

Ast creer_idf(char *idf);

Ast creer_aff(Ast A1, Ast A2);

Ast creer_lire(Ast A1);

Ast creer_ecrire(Ast A1);

Ast creer_if(Ast A1, Ast A2, Ast A3);

#endif
