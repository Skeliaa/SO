#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct charM {
    char** mp;
    int dimension;
};

struct tableroN{
    int bUP;
    int bLeft;
    int bRight;
    int bDown;
};

struct centros{
    char nime[12];
    int coord_x;
    int coord_y;
};

struct jugador{
    int id;
    int num;
    char nombre;
    char carta;
    int coord_x;
    int coord_y;
    int tmp;
};

char* getLine(FILE* fp);

struct charM* crearMatriz(const char* nombreArchivo);

void hacer_inicio(char inicio[][90], struct centros* todos);

char** revolverMazoT();

struct tableroN salidasT(char* archiv);

void juntarTablas(char inicio[][90],char* tablaCentral, char*tabla_a_unir, struct centros* allcenter, char dir, char** tableros);


void verificarTablas(char inicio[][90],char* archivo,char** tableros, char dir, struct centros* allcenter);