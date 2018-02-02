
trash = scan.o parse.cc parse.o scan.cc position.hh parse.hh stack.hh \
        location.hh

all: flex bison
	g++ src/scan.o src/parse.o -o tg

flex:
	flex -o src/scan.cc src/scan.ll 	
	g++ -c src/scan.cc -o src/scan.o

bison:
	bison -o src/parse.cc src/parse.yy --defines=src/parse.hh
	g++ -c src/parse.cc -o src/parse.o

clean:
	$(RM) tg $(addprefix src/, $(trash))
