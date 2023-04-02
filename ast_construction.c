#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

#include "type_ast.h"

Ast creer_operation(TypeOperateur opr , Ast opde_gauche , Ast opde_droit) 
{
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = OPERATION;
      expr->operateur = opr;
      if (opde_gauche == NULL || opde_droit == NULL) {
         printf("ERREUR_EXPRESSION\n") ;
	 exit(1) ;
      } else {
         expr->gauche = opde_gauche;
         expr->droite = opde_droit;
      } ;
      return expr ;
}

Ast creer_valeur(int val) { 
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = VALEUR;
      expr->valeur = val;
      return expr ;
}

Ast creer_seqinst(Ast *A1, Ast *A2){
      Ast expr;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = N_SEPINST;
      expr->gauche = *A1;
      expr->droite = *A2;
      return expr;
}

Ast creer_idf(char *idf){
      Ast expr;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = N_IDF;
      strcpy(expr->chaine, idf);
      return expr;
}

Ast creer_lire(Ast A1){
      Ast expr;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = N_LIRE;
      expr->gauche = A1;
      return expr;
}

Ast creer_ecrire(Ast A1){
      Ast expr;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = N_ECRIRE;
      expr->gauche = A1;
      return expr;
}

Ast creer_aff(Ast A1, Ast A2){
      Ast expr;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = N_AFF;
      expr->gauche = A1;
      expr->droite = A2;
      return expr;
}