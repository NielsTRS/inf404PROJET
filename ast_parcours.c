
#include <stdio.h>
#include <stdlib.h>
#include "ast_parcours.h"
#include "type_ast.h"
#include "string.h"
#include "table.h"

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
	case N_SUP:
		printf(" > ");
		break;
	case N_INF:
		printf(" < ");
		break;
	case N_SUPEGAL:
		printf(" >= ");
		break;
	case N_INFEGAL:
		printf(" <= ");
		break;
	case N_DIFF:
		printf(" != ");
		break;
	case N_EGAL:
		printf(" == ");
		break;
	case N_OU:
		printf(" || ");
		break;
	case N_ET:
		printf(" && ");
		break;
	}
}

void afficherArbre(Ast expr)
{
	switch (expr->nature)
	{
	case N_IF:
		printf("IF(");
		if (expr->gauche != NULL)
		{
			afficherArbre(expr->gauche);
		}
		else
		{
			printf("souci if gauche");
		}
		printf(",");
		if (expr->milieu != NULL)
		{
			afficherArbre(expr->milieu);
		}
		else
		{
			printf("souci if milieu");
		}
		printf(",");
		if (expr->droite != NULL)
		{
			afficherArbre(expr->droite);
		}
		else
		{
			printf("souci if droite");
		}
		printf(")");
		break;
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
	case N_SEPINST:
		printf("NSEPINST(");
		if (expr->gauche != NULL)
		{
			afficherArbre(expr->gauche);
		}
		else
		{
			printf("souci nsepinst gauche");
		}
		printf(",");
		if (expr->droite != NULL)
		{
			afficherArbre(expr->droite);
		}
		else
		{
			printf("souci nsepinst droite");
		}
		printf(")");
		break;
	case N_AFF:
		printf("NAFF(");
		if (expr->gauche != NULL)
		{
			afficherArbre(expr->gauche);
		}
		else
		{
			printf("souci naff gauche");
		}
		printf(",");
		if (expr->droite != NULL)
		{
			afficherArbre(expr->droite);
		}
		else
		{
			printf("souci naff droite");
		}
		printf(")");
		break;
	case N_IDF:
		printf("IDF(%s)", expr->chaine);
		break;
	case N_LIRE:
		printf("NLIRE(");
		if (expr->gauche != NULL)
		{
			afficherArbre(expr->gauche);
		}
		else
		{
			printf("souci nlire");
		}
		printf(")");
		break;
	case N_ECRIRE:
		printf("NECRIRE(");
		if (expr->gauche != NULL)
		{
			afficherArbre(expr->gauche);
		}
		else
		{
			printf("souci necrire");
		}
		printf(")");
		break;
	case N_BOOL:
		printf("BOOL(");
		if (expr->gauche != NULL)
		{
			afficherArbre(expr->gauche);
		}
		else
		{
			printf("souci bool");
		}
		aff_operateur(expr->operateur);
		if (expr->droite != NULL)
		{
			afficherArbre(expr->droite);
		}
		else
		{
			printf("souci bool");
		}
		printf(")");
		break;
	default:
		printf("Error 1");
		break;
	}
}

int evaluation(Ast expr)
{
	int v;
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
		case N_SUP:
			return evaluation(expr->gauche) > evaluation(expr->droite);
		case N_INF:
			return evaluation(expr->gauche) < evaluation(expr->droite);
		case N_SUPEGAL:
			return evaluation(expr->gauche) >= evaluation(expr->droite);
		case N_INFEGAL:
			return evaluation(expr->gauche) <= evaluation(expr->droite);
		case N_DIFF:
			return evaluation(expr->gauche) != evaluation(expr->droite);
		case N_EGAL:
			return evaluation(expr->gauche) == evaluation(expr->droite);
		default:
			printf("Error 2");
			exit(0);
		}
	case VALEUR:
		return expr->valeur;
	case N_IDF:
		estPresentTS(expr->chaine, &v);
		return v;

	case N_BOOL:
		switch (expr->operateur)
		{
		case N_ET:
			return evaluation(expr->gauche) && evaluation(expr->droite);
		case N_OU:
			return evaluation(expr->gauche) || evaluation(expr->droite);
		default:
			printf("Error 2");
			exit(0);
		}
	default:
		printf("Error 3");
		exit(0);
	}
}

void interpreter(Ast A)
{
	switch (A->nature)
	{
	case N_SEPINST:
		interpreter(A->gauche);
		interpreter(A->droite);
		break;
	case N_AFF:
		interpreter_aff(A);
		break;
	case N_LIRE:
		interpreter_lire(A);
		break;
	case N_ECRIRE:
		interpreter_ecrire(A);
		break;
	case N_IF:
		if (evaluation(A->gauche))
		{
			interpreter(A->milieu);
		}
		else
		{
			interpreter(A->droite);
		}
		break;
	default:
		printf("Error 4");
		exit(0);
	}
}

void interpreter_aff(Ast A)
{
	char idf[256];
	int v;
	strcpy(idf, A->gauche->chaine);
	v = evaluation(A->droite);
	insererTS(idf, v);
}

void interpreter_lire(Ast A)
{
	int v;
	printf("Entrez une valeur pour %s  : ", A->gauche->chaine);
	scanf("%d", &v);
	insererTS(A->gauche->chaine, v);
}

void interpreter_ecrire(Ast A)
{
	int v;
	v = evaluation(A->gauche);
	printf("%d\n ", v);
}
