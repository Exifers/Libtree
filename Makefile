
all:
	flex -o src/scan.cc src/scan.ll 
	g++ src/scan.cc -o tg
