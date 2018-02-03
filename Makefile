CXX = g++

FLEX = flex
BISON = bison

bin = tc

trash = scan.o parse.cc parse.o scan.cc position.hh parse.hh stack.hh \
        location.hh

testsuite_trash = error.log

all: bison flex
	$(CXX) src/scan.o src/parse.o -o $(bin)

flex:
	$(FLEX) -o src/scan.cc src/scan.ll
	$(CXX) -c src/scan.cc -o src/scan.o

bison:
	$(BISON) -o src/parse.cc src/parse.yy --defines=src/parse.hh
	$(CXX) -c src/parse.cc -o src/parse.o

check:
	./tests/test.sh

clean:
	$(RM) $(bin) $(addprefix src/, $(trash)) $(testsuite_trash)
