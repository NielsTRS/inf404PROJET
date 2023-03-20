
all : test_lexeme calculette essai_ast 


ast_construction.o: ast_construction.c type_ast.h
	gcc -g -Wall -c ast_construction.c

ast_parcours.o: ast_parcours.c type_ast.h
	gcc -g -Wall -c ast_parcours.c

essai_ast.o: essai_ast.c  ast_construction.h  ast_parcours.h  type_ast.h
	gcc -g -Wall -c essai_ast.c




calculette.o: calculette.c analyse_syntaxique.h lecture_caracteres.h analyse_lexicale.h
	gcc -g -Wall -c calculette.c

analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_lexicale.c

lecture_caracteres.o: lecture_caracteres.h lecture_caracteres.c
	gcc -g -Wall -c lecture_caracteres.c

test_lexeme.o: analyse_lexicale.h
	gcc -g -Wall -c test_lexeme.c

analyse_syntaxique.o : analyse_syntaxique.c analyse_syntaxique.h analyse_lexicale.h 
	gcc -g -Wall -c analyse_syntaxique.c

essai_ast: ast_construction.o  ast_parcours.o  essai_ast.o  
	gcc -g -Wall -o essai_ast ast_construction.o  ast_parcours.o  essai_ast.o
	
test_lexeme: analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o
	gcc -g -Wall -o test_lexeme analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o

calculette: calculette.o analyse_syntaxique.o  ast_parcours.o ast_construction.o analyse_lexicale.o lecture_caracteres.o
	gcc -g -Wall -o calculette analyse_lexicale.o lecture_caracteres.o analyse_syntaxique.o calculette.o ast_parcours.o ast_construction.o


clean:
	rm *.o essai_ast calculette test_lexeme

