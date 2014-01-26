
.SUFFIXES: .o .c
.c.o:
	$(CC) -c $< $(CFLAGS)
CC = gcc
CFLAGS = -Wall -g -O0 -lm
SRC = comun.c comun.h dispersionAbierta.c dispersionAbierta.h dispersionCerrada.c dispersionCerrada.h main.c 
OBJ = comun.o  dispersionAbierta.o dispersionCerrada.o main.o

all: $(OBJ)
	$(CC) -o main $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ) main

comun.o: comun.c comun.h 
dispersionAbierta.o:dispersionAbierta.c dispersionAbierta.h 
dispersionCerrada.0:dispersionCerrada.c dispersionCerrada.h 
main.o: main.c

