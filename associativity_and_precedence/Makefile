calcit: lex.yy.c simple_arithmetic.tab.c
	g++ -std=c++17 lex.yy.c simple_arithmetic.tab.c -o calcit

lex.yy.c: simple_arithmetic.l
	flex simple_arithmetic.l

simple_arithmetic.tab.c: simple_arithmetic.y
	bison -vd simple_arithmetic.y

.PHONY: clean

clean:
	rm -f lex.yy.c simple_arithmetic.tab.c simple_arithmetic.tab.h calcit
