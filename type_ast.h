
#ifndef __TYPE_AST__
#define __TYPE_AST__

typedef enum
{
	OPERATION,
	VALEUR,
	N_SEPINST,
	N_AFF,
	N_LIRE,
	N_ECRIRE,
	N_IDF,
	N_ADD,
	N_MULT,
	N_DIVI,
	N_SUB,
} TypeAst;
typedef enum
{
	N_PLUS,
	N_MUL,
	N_MOINS,
	N_DIV
} TypeOperateur;

typedef struct noeud
{
	TypeAst nature;
	TypeOperateur operateur;
	char chaine[100];
	struct noeud *gauche, *droite;
	int valeur;
} NoeudAst;

typedef NoeudAst *Ast;

#endif
