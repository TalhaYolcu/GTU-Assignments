hw:
	yacc -d -Wall gpp_interpreter.y
	lex -o gpp_lexer.c gpp_lexer.l
	cc gpp_lexer.c y.tab.c -ll
	./a.out