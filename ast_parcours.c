
#include <stdio.h>
#include "type_ast.h"

void aff_operateur(TypeOperateur op)
{
	switch (op)
	{
	case N_PLUS:
		printf("+");
		break;
	case N_MOINS:
		printf("-");
		break;
	case N_MUL:
		printf("*");
		break;
	case N_DIV:
		printf("/");
		break;
	}
}

void afficherArbre(Ast expr)
{
	switch (expr->nature)
	{
	case OPERATION:
		printf("(");
		afficherArbre(expr->gauche);
		aff_operateur(expr->operateur);
		afficherArbre(expr->droite);
		printf(")");
		break;
	case VALEUR:
		printf("%d", expr->valeur);
		break;
	}
}

int evaluation(Ast expr)
{
	switch (expr->nature)
	{
	case OPERATION:
		switch (expr->operateur)
		{
		case N_PLUS:
			return evaluation(expr->gauche) + evaluation(expr->droite);
		case N_MOINS:
			return evaluation(expr->gauche) - evaluation(expr->droite);
		case N_MUL:
			return evaluation(expr->gauche) * evaluation(expr->droite);
		case N_DIV:
			return evaluation(expr->gauche) / evaluation(expr->droite);
		}
	case VALEUR:
		return expr->valeur;
	}
}
