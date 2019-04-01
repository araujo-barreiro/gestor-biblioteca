#****************************************
#Proyecto Biblioteca.
#Diego Araujo y Guillermo Barreiro. 2017.
#****************************************

CC = gcc -Wall -g

all: biblioteca

base_datos.o: base_datos.c
	$(CC) base_datos.c -c

pantalla.o: pantalla.c
	$(CC) pantalla.c -c

biblioteca: biblioteca.c pantalla.o base_datos.o
	$(CC) biblioteca.c pantalla.o base_datos.o -o biblioteca

clean:
	rm -f biblioteca *.o *~
