#include "headerso.h"


const int MAX = 1000000;



//char* getline tiene como función retornar un string correspondiente a una linea de un archivo.txt

char* getLine(FILE* fp){
    char temp[MAX];
    int i = 0;
    char c = 'a';
    while(c != '\n' && !feof(fp)){
        c = fgetc(fp);
        if(c == 'B' || c == 'E'|| c == '1'|| c == '2'|| c == '3'|| c == '4'|| c == '/'|| c == '0'){
            temp[i] = c;
            i++;
        }
    }
    size_t u = i;
    char* line = calloc(u,sizeof(char));
    strncpy(line,temp,u);    
    return line;
}


// struct charM* crearMatriz hace una matriz de 5x5 en base a los archivos.txt entregados,
// retorna una matriz de tipo char. 
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



/*hacer_matriz se encarga de inicializar el juego con las posiciones de los jugadores iniciales*/
void hacer_inicio(char inicio[][90], struct centros* todos){
        for (int i = 0; i < 90; i++){
            for (int j = 0; j < 90; j++){
                inicio[i][j] = '-';
            }
    }
        FILE *file;
        file = fopen("Inicio.txt", "r");
        char caracter;
        int fila = 45;
        int j = 45;
        while ((caracter = fgetc(file)) != EOF){
  
            if (caracter == 'B' || caracter == 'E' || caracter == '1' || caracter == '0' || caracter == '/' || caracter == '1' || caracter == '2' || caracter =='3'|| caracter == '4'){
                inicio[fila][j] = caracter;
                fila++;
            }
            else if(caracter == '\n'){
                j++;
                fila = 45;
            }
        }

        /* struct jugador jugadores[4];
        int k = 0;

        for (int i = 0; i <90; i++){
            for(int j = 0; j<90; j++){
                if(inicio[i][j] ==  '1' || inicio[i][j] == '2' || inicio[i][j] == '3' || inicio[i][j] == '4'){
                    jugadores[k].nombre = inicio[i][j];
                    jugadores[k].coord_x = i;
                    jugadores[k].coord_y = j;
                    k++;
                }
             //printf("%c",inicio[j][i]);
            }
        //printf("\n");    
    }  */  
        fclose(file);
}      


/*La función revolverMazoT realiza un arreglo con los nombres de los tableros
  luego de ser revueltos entre si. Finalmente la función retorna este "arreglo revuelto"*/

char** revolverMazoT(){
    int tableros[8];
    srand(time(NULL));
    for (int i = 0; i<8; i++){
        int lugarMazo = rand() % 8 + 1;
        for (int j = 0; j<8; j++){
            if (lugarMazo == tableros[j]){
                i--;
                break;
            }
            else if (j == 7){
                tableros[i] = lugarMazo;
                //printf(" %d", tableros[i]);
            }
        }
    }
    printf("\n");
    int j = 1;
    char** arria = malloc(8*sizeof(char*));
    for (int i = 0; i<8; i++){
        
        if (tableros[i] == j){
            char real = i+1 + '0';
            char cadenaNum[2];
            cadenaNum[0] = real;
            cadenaNum[1] = '\0';
            char* tablero = malloc(20*sizeof(char));
            strcpy(tablero, "tablero");
            char* txt = ".txt";
            strcat(tablero, cadenaNum); 
            strcat(tablero, txt); 
            arria[j-1] = tablero;
            //printf(" %s", arria[j-1]);
            i = -1;
            j++;
        }
    }
    return arria;
}

/*La función salidasT recibe como parámetro el nombre de un tablero
  y retorna la existencia de salidas 'B' dentro del tablero*/
struct tableroN salidasT(char* archiv){
    struct tableroN ubic;;
    ubic.bUP = 0;
    ubic.bRight = 0;
    ubic.bDown = 0;
    ubic.bLeft = 0;
    FILE *file;
    file = fopen(archiv, "r");
    struct charM* matriz = crearMatriz(archiv);

   if ( matriz->mp[0][2]== 'B'){
                ubic.bUP = 1;
    }
    if (matriz->mp[2][0] == 'B'){
                ubic.bLeft = 1;
    }
    if (matriz->mp[2][4] == 'B'){
                ubic.bRight = 1;
    }
    if (matriz->mp[4][2] == 'B'){
                ubic.bDown = 1;
    }
    fclose(file);
    return ubic;
}

/*La función juntar tablas recibe como parámetro la matriz general, el tablero dende está parado el jugador X,
  el tablero que se añadirá a la matriz general, una matriz que tiene como datos las coordenadas
  de los centros de los tableros ya descubiertos, la direccion en la cual se */

void juntarTablas(char inicio[][90],char* tablaCentral, char*tabla_a_unir, struct centros* allcenter, char dir, char** tableros){
    char caracter;
    int m = 0;
    int n = 0;
    for(int i = 0; i<9; i++){

        if (strncmp(allcenter[i].nime, tablaCentral, 10) == 0){
            m = allcenter[i].coord_x;
            n = allcenter[i].coord_y;
        }
    }

    char porsilas[12];
    strncpy(porsilas,tabla_a_unir,12);
    FILE* tmp = fopen(porsilas, "r");

    switch (dir){
        case 'u':
            n = n-5;
            break;
        case 'l':
            m = m-5;
            break;
        case 'r':
            m = m+5;
            break;
        case 'd':
            n = n+5;
            break;
    }
    
 
    for (int kai = 0; kai<9; kai++){
        if (strncmp(allcenter[kai].nime, "cambiar", 7) == 0 ){
            allcenter[kai].coord_x = m;
            allcenter[kai].coord_y = n;
            strncpy(allcenter[kai].nime, tabla_a_unir, 12);
            break;
        }
    }


    m = m-2;
    int temp = m;
    n = n-2;
    char carand;
    int contusados = 0;
    int contTreasure = 0;
    while ((caracter = fgetc(tmp)) != EOF){
        if (caracter == 'E' || caracter == '/' || caracter == '0'){
            int tresure = rand() % 100 + 1;
            int casillarand = rand() % 100 + 1;
            if(casillarand <= 25)
                carand = 'C';
            else if (casillarand > 25 && casillarand <= 50)
                carand = 'P';
            else if (casillarand > 50 && casillarand <= 75)
                carand = '%';
            else{
                carand = '#';
            }
            casillarand = rand() % 100 + 1;
            if (casillarand <= 25)
                caracter = carand;  
            if (tresure <= 20 && contTreasure == 0){
                printf("%d0000\n", tresure);
                caracter = 'T';
                contTreasure++;
            }
            for (int i = 0; i<8; i++){
                if(strcmp(tableros[i], "usado") == 0)
                    contusados++;
            }
            if (contusados == 7){
                int ponerlos = rand() % 100 + 1;
                if (ponerlos <= 95)
                    caracter = 'T'; 
            }
            else{
                contusados = 0;
            }
           inicio[m][n] = caracter;
            m++;
        }
        else if(caracter == 'B'|| caracter == '1' || caracter == '2' || caracter == '3' || caracter == '4'){
            inicio[m][n]  = caracter;
            m++;
        }

        else if(caracter == '\n'){
            n++;
            m = temp ;
        }
    }
    for (int i = 0; i <90; i++){
        for(int j = 0; j<90; j++){
    
            printf("%c", inicio[j][i]); 
            }

        printf("\n");    
    }    
    fclose(tmp);
}

/*verificarTablas revisa el arreglo de tableros para ver si entán ya mostrados por pantalla o aún no,
  en el caso que no esten ocupados, revisa las salidas 'B' de estos para ver si son compatibles con el tablero actual
  recibe los mismos parámetros que juntarTablas*/
void verificarTablas(char inicio[][90],char* archivo,char** tableros, char dir, struct centros* allcenter){
    struct tableroN tablaSec;
    struct tableroN tablaTri;
    char quiza[12];
    switch(dir){
        case 'u':
           for(int i = 0; i<8; i++){
               
                    if(strcmp(tableros[i], "usado") != 0){
                    strncpy(quiza, archivo, 12);
                    tablaSec = salidasT(quiza);
                    if(tablaSec.bUP == 1 ){
                        tablaTri = salidasT(tableros[i]);
                        if (tablaTri.bDown == 1){
                            juntarTablas(inicio, archivo, tableros[i], allcenter, dir, tableros);
                            strcpy(tableros[i], "usado");
                            break;
                        }  
                    }
                }    
            }
            break;
           
        case 'l':
            for(int i = 0; i<8; i++){
                    if(strcmp(tableros[i], "usado") != 0){
                    strncpy(quiza, archivo, 12);
                    tablaSec = salidasT(quiza);
                    printf("%d", tablaSec.bLeft);
                    if(tablaSec.bLeft == 1 ){
                        tablaTri = salidasT(tableros[i]);
                        if (tablaTri.bRight == 1){
                            juntarTablas(inicio, archivo, tableros[i], allcenter, dir, tableros);
                            strcpy(tableros[i], "usado");
                            break;
                        }  
                    }
                }    
            }
            break;
        case 'r':    
            for(int i = 0; i<8; i++){
                    if(strcmp(tableros[i], "usado") != 0){
                    strncpy(quiza, archivo, 12);
                    tablaSec = salidasT(quiza);
                    printf("%d", tablaSec.bLeft);
                    if(tablaSec.bRight == 1 ){
                        tablaTri = salidasT(tableros[i]);
                        if (tablaTri.bLeft == 1){
                            juntarTablas(inicio, archivo, tableros[i], allcenter, dir, tableros);
                            strcpy(tableros[i], "usado");
                            break;
                        }  
                    }
                }    
            }
            break;
        case 'd':    
            for(int i = 0; i<8; i++){
                printf("%d", i);
                    if(strcmp(tableros[i], "usado") != 0){
                    strncpy(quiza, archivo, 12);
                    tablaSec = salidasT(quiza);
                    printf("%d", tablaSec.bLeft);
                    if(tablaSec.bDown == 1 ){
                        tablaTri = salidasT(tableros[i]);
                        if (tablaTri.bUP == 1){
                            juntarTablas(inicio, archivo, tableros[i], allcenter, dir, tableros);
                            strcpy(tableros[i], "usado");
                            break;
                        }  
                    }
                }    
            }
            break;    
    }
}
