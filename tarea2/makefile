.PHONY: clean exe all 

all: main exe clean


yo: Tarea2_SO exe clean

Tarea2_SO: Tarea2_SO.c
	@gcc -Wall -g -o Tarea2_SO.o Tarea2_SO.c Tarea2_SO.h


main: main.c
	@gcc -Wall -g -o main.o main.c Tarea2_SO.h Tarea2_SO.c

exe:
	@./*.o

clean:
	@rm -rf *.o
