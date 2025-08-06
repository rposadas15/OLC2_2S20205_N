# Comando para FLEX

flex -l lexer.l

# Comando para BISON

bison -dv parser.y

# Comando para generar .exe

gcc -o compilador main.c parser.tab.c lex.yy.c
