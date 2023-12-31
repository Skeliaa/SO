#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

const int MAX = 1000;

struct charM {
    char orientacion[20];
    char** mp;
    int dimension;
};
// strReverse da vuelta la palabra si es que es necesario (si la palabra buscada en la sopa es nomaj, la da vuelta a jamon)
char* strReverse(char* src){
    int l = strlen(src);
    char* dest = calloc(l,sizeof(char));
    for(int i = 0;i<l;i++){
        dest[i]=src[l-i-1];
    }
    return dest;
}
// char* getline extrae un string correspondiente a una linea dentro de un archivo txt
char* getLine(FILE* fp){
    char temp[MAX];
    int i = 0;
    char c = 'a';
    while(c != '\n' && !feof(fp)){
        c = fgetc(fp);
        if(c >= 65 && c<= 122){
            temp[i] = c;
            i++;
        }
    }
    if(temp[i-1]<65 || temp[i-1]>122){
        temp[i-1] = 0;
    } 
    size_t u = i;
    char* line = calloc(u,sizeof(char));
    strncpy(line,temp,u);
    for(int j = 0;j<strlen(line+1);j++){
        if (line[j]< 65 || line[j]> 90){
            
        }
    }
    
    return line;
}


// struct charM* crearMatriz hace una matriz de la sopa de letras contenida en un archivo txt
struct charM* crearMatriz(const char* nombreArchivo){
    char* tmp;
    int i= 0;
    FILE *fp = fopen(nombreArchivo,"r");
    struct charM* strArray = malloc(sizeof(struct charM));
    if (fp == NULL){
        printf("No se pudo abrir el archivo :c\n");
        return NULL;
    }
    tmp = getLine(fp);
    strcpy(strArray->orientacion,tmp);
    tmp = getLine(fp);
    const int n = strlen(tmp);
    strArray->mp = calloc(n,sizeof(char*));
    strArray->mp[0] = tmp;
    strArray->dimension = strlen(tmp);
    i++;
    while(!feof(fp)){
        strArray->mp[i] = getLine(fp);
        i++;
    }
    fclose(fp);
    return strArray;
}
// int buscarPalabra se dedica a buscar la palabra dentro de la matriz extraída de un archivo txt
int buscarPalabra(struct charM *matrix, char* clave){
    for(int i = 0;i<matrix->dimension;i++){
        if(strstr(matrix->mp[i],clave) != NULL || strstr(matrix->mp[i],strReverse(clave)) != NULL){
            return 1;
        }
    }
    return 0;
}
//int trasponerMatriz da vuelta la matriz extraída de un archivo txt en caso de que la orientacion de este sea vertical
int trasponerMatriz(struct charM* matrix){
    char tmp;
    int n = matrix->dimension;
    if (n > 200){
        n = 200;
    }
    
    for(int i = 0;i<n;i++){
        for(int j = i; j<n;j++){
            
            tmp = matrix->mp[i][j];
            matrix->mp[i][j] = matrix->mp[j][i];
            matrix->mp[j][i] = tmp;
        }
    }
    return 0;
}
//printMatriz muestra por pantalla la sopa de letras extraída de un archivo txt
void printMatriz(struct charM* matrix){
    printf("%d\n",matrix->dimension);
    for(int i = 0;i<matrix->dimension;i++){
        printf("Linea %d: %s\n",i,matrix->mp[i]);
    }
}

int carpetas(){
    DIR *dir;
    struct dirent* entry;
    char direct[300] = "./archivos/";
    char cambiar[300];

    const char *archiv = "./archivos";

    if (opendir("./CWD") == NULL){
        mkdir("./CWD", 0700);
    }

    dir = opendir(archiv);
    if (dir==NULL){
        printf("no se abrió el archivo");
        exit(2);
    }

     while ((entry = readdir(dir)) != NULL) {
        if((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0) ){
        // Procesar la entrada (nombre del archivo) aquí
        printf("Nombre del archivo: %s\n", entry->d_name);
        strcat(direct, entry->d_name);
        FILE *archivo;
        char linea[13];
        char letraSopa[2];
        int contador_horizontal = 0;
        int contador_vertical = 0;
        archivo = fopen(direct, "r");
        if (fgets(linea, sizeof(linea), archivo) != NULL){
            printf("la linea es: %s", linea);    
        }

        fgets(letraSopa, sizeof(letraSopa), archivo);
        contador_horizontal++;
        while(letraSopa[0] != '\n'){
            fgets(letraSopa, sizeof(letraSopa), archivo);
            contador_horizontal++;
        }
        contador_horizontal = (contador_horizontal-1)/2;
        contador_vertical = contador_horizontal;
        printf("el tamaño del archivo es: %dx%d\n", contador_horizontal, contador_vertical);
        printf("\n");
        printf("%d", strcmp(linea, "horizontal"));
        if (strcmp(linea, "vertical") == 13){
            if (opendir("./CWD/vertical") == NULL){
                mkdir("./CWD/vertical", 0700);
            }
            printf("%d\n", contador_horizontal);
            if (contador_horizontal == 50){
                if (opendir("./CWD/vertical/50x50") == NULL){
                    mkdir("./CWD/vertical/50x50", 0700);
                }
                strcpy(cambiar, "./CWD/vertical/50x50/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);
            }    
            else if(contador_horizontal == 100){
                if (opendir("./CWD/vertical/100x100") == NULL){
                    mkdir("./CWD/vertical/100x100", 0700);
                }
                strcpy(cambiar, "./CWD/vertical/100x100/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);
            }
            else if((contador_horizontal == 200)){
                if (opendir("./CWD/vertical/200x200") == NULL){
                    mkdir("./CWD/vertical/200x200", 0700);
                }
                strcpy(cambiar, "./CWD/vertical/200x200/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);

            }
        }    
        if (strcmp(linea, "horizontal") == 13){
            if (opendir("./CWD/horizontal") == NULL){
                mkdir("./CWD/horizontal", 0700);
            }
            printf("%d\n", contador_horizontal);
            if (contador_horizontal == 50){
                if (opendir("./CWD/horizontal/50x50") == NULL){
                    mkdir("./CWD/horizontal/50x50", 0700);
                }
                strcpy(cambiar, "./CWD/horizontal/50x50/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);
            }    
            else if(contador_horizontal == 100){
                if (opendir("./CWD/horizontal/100x100") == NULL){
                    mkdir("./CWD/horizontal/100x100", 0700);
                }
                strcpy(cambiar, "./CWD/horizontal/100x100/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);
            }
            else if((contador_horizontal == 200)){
                if (opendir("./CWD/horizontal/200x200") == NULL){
                    mkdir("./CWD/horizontal/200x200", 0700);
                }
                strcpy(cambiar, "./CWD/horizontal/200x200/");
                strcat(cambiar, entry->d_name);
                printf("%s", direct);
                rename(direct, cambiar);

            }
        }    
        }

        strcpy(direct, "./archivos/");
        
    }
    return 0;
}


int main(){
    printf("Inicio de la ejecución\n");
    int opcion;
    printf("Que quiere hacer? (1) Ordenar archivos (2) Comprobar sopa de letras\n");
    scanf("%d",&opcion);
    if (opcion == 1){
        carpetas();
    }else if(opcion == 2){
        struct charM *matrix = crearMatriz("gato.txt");
        printf("orientacion: %s\n",matrix->orientacion);
        if(strcmp(matrix->orientacion,"vertical") == 0){
            trasponerMatriz(matrix);
        }
        clock_t start = clock();        
        for (int i = 0; i<100;i++){
            buscarPalabra(matrix,"GATO");
        }
        clock_t end = clock();
        double total = (double)(end - start) / (CLOCKS_PER_SEC*100);
        printf("start: %ld\nend: %ld\ncocks realizados:%f\n",start,end,total);
    }
    printf("Fin de la ejecución.\n");
    return 0;
}