CXX = g++

FLEX = flex
BISON = bison

bin = tc

trash = scantiger.o parsetiger.cc parsetiger.o scantiger.cc position.hh \
parsetiger.hh stack.hh location.hh

testsuite_trash = error.log

all: bison flex
	$(CXX) src/parse/scantiger.o src/parse/parsetiger.o -o $(bin)

flex:
	$(FLEX) -o src/parse/scantiger.cc src/parse/scantiger.ll
	$(CXX) -c src/parse/scantiger.cc -o src/parse/scantiger.o

bison:
	$(BISON) -o src/parse/parsetiger.cc src/parse/parsetiger.yy \
--defines=src/parse/parsetiger.hh
	$(CXX) -c src/parse/parsetiger.cc -o src/parse/parsetiger.o

check:
	./tests/test.sh

clean:
	$(RM) $(bin) $(addprefix src/parse/, $(trash)) $(testsuite_trash)
