all: treasurefinder.exe

treasurefinder.exe: TreasureFinder.o Tablero.o
	 gcc -o treasurefinder.exe TreasureFinder.o Tablero.o

TreasureFinder.o: TreasureFinder.c
	 gcc -c -v TreasureFinder.c

Tablero.o: Tablero.h Tablero.c Bomba.h Bomba.c Tierra.h
	 gcc -c -v Tablero.c Bomba.c

run:
	 ./treasurefinder.exe

clean:
	 rm Tablero.o Bomba.o TreasureFinder.o treasurefinder.exe

valgrind:
	valgrind --leak-check=full ./treasurefinder.exe