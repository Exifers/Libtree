
all:
	bison -o src/parse.cc src/parse.yy --defines=src/parse.hh
	flex -o src/scan.cc src/scan.ll 
	g++ -c src/parse.cc -o src/parse.o
	g++ -c src/scan.cc -o src/scan.o
	g++ src/scan.o src/parse.o -o tg

lex:
	flex -o src/scan.cc src/scan.ll 	
	g++ src/scan.cc -o tg
