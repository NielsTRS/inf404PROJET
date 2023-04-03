
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
	N_IF,
	N_BOOL,
} TypeAst;
typedef enum
{
	N_PLUS,
	N_MUL,
	N_MOINS,
	N_DIV,
	N_SUP, 			// >
	N_SUPEGAL,		// >=
	N_INF,			// <
	N_INFEGAL,		// <=
	N_DIFF, 		// !=
	N_EGAL, 		// ==
	N_OU,			// ||
	N_ET,			// &&
} TypeOperateur;

typedef struct noeud
{
	TypeAst nature;
	TypeOperateur operateur;
	char chaine[100];
	struct noeud *gauche, *droite, *milieu;
	int valeur;
} NoeudAst;

typedef NoeudAst *Ast;

#endif
