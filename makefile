CC := gcc
CFLAGS := -Wall -c -pedantic -std=c99 -g -O3
LFLAGS := -lm -lSDL2 -g


all: lunar_lander

main.o: main.c config.h naves.h funcionesTP01.c diccionario.c
	$(CC) $(CFLAGS) -lSDL2 main.c

naves.o: naves.c naves.h 
	$(CC) $(CFLAGS) naves.c

funcionesTP01.o: funcionesTP01.c funcionesTP01.h config.h
	$(CC) $(CFLAGS) $(LFLAGS) funcionesTP01.c

diccionario.o: diccionario.c caracteres.c caracteres.h
	$(CC) $(CFLAGS) diccionario.c

lunar_lander: main.o funcionesTP01.o naves.o diccionario.o
	$(CC) $(LFLAGS) $^ -o lunar_lander

clean:
	rm *.o

valgrind: lunar_lander
	valgrind --leak-check=full ./lunar_lander
