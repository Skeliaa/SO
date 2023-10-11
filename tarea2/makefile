.PHONY: clean exe all 

all: main exe clean

main: main.c headerso.c headerso.h
	@gcc -Wall -g -o main.o main.c headerso.c 

exe:
	@./*.o

clean:
	@rm -rf *.o