#include <sys/types.h>
#include <sys/wait.h>
#include "headerso.h"
//

void enviar(char* msg, int fd[2]){
    int len = strlen(msg)+1;
    write(fd[1],msg,len);
}
void recibir(char* dest, int fd[2]){
    read(fd[0],dest,25);
}
void generarPipes(int array[8][2]){
    for(int i = 0;i<8;i++){
        pipe(array[i]);
    }
}
void generarCartas(int roles[4]){

}
void asignarRoles(){

}

void moverse(){

}

void mover(int movimiento,int distancia, char inicio[][90], struct jugador player){
    //0 para arriba, 1 para la derecha, 2 para la izquierda, 3 para abajo/
    int dirH = 0;
    int dirV = 0;
    switch(movimiento){
        case 0:
            dirV = 1;
        case 1:
            dirH = 1;
        case 2:
            dirV =-1;
        case 3:
            dirH =-1;
    }
        inicio[player.coord_x][player.coord_y] = player.tmp;
        player.tmp = inicio[player.coord_x+distancia*dirH][player.coord_y+distancia*dirV];
        inicio[player.coord_x+distancia*dirH][player.coord_y+distancia*dirV] = player.num;
}
void accionar(){

}
void procesar(struct jugador player,char* cosa, char inicio[][90]){
    // m: movimiento , d: distancia, f: fin del juego (de 1 a 9)
    // encode de acción: mdc,a,f
    if(cosa[0]=='a'){
        
    }
    else{
        mover(cosa[0],cosa[1],inicio,player);
    }
}
void buscarP(struct jugador player, char inicio[][90]){
    for(int i = 0;i<90;i++){
        for(int j=0;j<90;i++){
            if(inicio [i][j]==player.num+48){
                player.coord_x = i;
                player.coord_y = j;
                printf("player %d en (%d,%d)\n",player.num,i,j);
                break;
            }
        }
    }
}

int main(){
    char inicio[90][90];
    struct centros todos[9];
    hacer_inicio(inicio, todos);

    for(int rai = 0; rai<9; rai++){
        if (rai == 0){
            strcpy(todos[0].nime, "Inicio.txt");
            todos[0].coord_x = 47;
            todos[0].coord_y = 47; 
        }
        else{
            strcpy(todos[rai].nime, "cambiar");
            todos[rai].coord_x = -1;
            todos[rai].coord_y = -1; 
        }
    }    


    char** tableros = revolverMazoT();
    //verificarTablas(inicio, "Inicio.txt", tableros, 'u', todos);
    //verificarTablas(inicio, todos[1].nime, tableros, 'u', todos);



    const int lenM = 12;
    struct jugador jugador;
    int rondas = 3;
    int pipes[8][2];
    int mazoCartas[4];
    char orden[lenM];
    char input[lenM]; 
    char ret[lenM];
    generarPipes(pipes);
    generarCartas(mazoCartas);
    int id= 0;
    int p=0;
    int pid;
    char accion[lenM];
    char* msgturno = calloc(lenM,lenM*sizeof(char));
    printf("proceso god: %d\n",getpid());

    
    printf("pipes creadas!\n");

    for(int i = 0;i<4;i++){
        if ((pid=fork())==0){
        
        jugador.id = pid;
        id = i+1;
        jugador.num = id;
        jugador.tmp = 0;
        //buscarP(jugador,inicio);
        break;}
    }
    printf("Hola, me presento, soy: J%d (%d)\nhijo de:%d\n\n",jugador.num,getpid(),getppid());
    //if(id == 0){jugador;}



    if(id == 0){ //logica principal del juego (en proceso padre)
        mover(0,1,inicio,jugador);
        printf("padre diciendo wa\n");
        for(int ronda=1;ronda<=rondas;ronda++){
            printf("\nINICIO DE LA RONDA: %d\n",ronda);
            //write(pipes[0][1],"nueva ronda",lenM);
            
            for(int turno=1;turno<=4;turno++){
                strcat(msgturno,"turno j");
                msgturno[7]=turno;
                msgturno[8]='\0';
                write(pipes[0][1],msgturno,lenM);
                printf("Es el turno del J%d\n",turno);
                read(pipes[3+turno][0],accion,lenM);
            }
        }
        write(pipes[0][1],"fin",lenM); //informar sobre ganador?
    }
    else{
        if(id==1){
            read(pipes[0][0],input,lenM);
            printf("MENSAJE INTERCEPTADO: %s\n",input);
            int k = 0;
            while(strcmp(input,"fin")&&strlen(input)!=0){
                if(1){
                    int j = input[7];
                    printf("Indique la acción a realizar para el J%d: \n",j);
                    scanf("%s",input);printf("\n");
                    //hacer algo con el input
                    //generar ret
                    // encode de acción: (m+a+f)d
                    // m: movimiento , d: distancia, f: fin del juego (de 1 a 9) 
                    //strcpy(ret,input);
                    //printf("echo: %s\n",input);
                    //write(pipes[id][1],ret,lenM);
                    if(j == 1){
                        procesar(jugador,input,inicio);
                        write(pipes[4][1],"ok",lenM);
                    }else{
                        write(pipes[j-1][1],input,lenM);
                        //printf("pipe mandada a J%d: %s\n",j,input);
                    }
                }
                else if(!strcmp(input,"fin")){

                }
                printf("miau %s\n",input);
                //for(int j = 0;j<strlen(input);j++){printf("%c\n",input[j]);}
                read(pipes[0][0],input,lenM);
                k++;
            }
            printf("-------sas\n");
        }
        else{
            read(pipes[id-1][0],input,lenM);
            //printf("MENSAJE INTERCEPTADO: %s\n",input);
            while(strstr(input,"fin")==NULL){
                printf("proceso del J%d esperando pipe\n",id);
                printf("recibido en J%d: %s\n",id,input);
                if(strcat(input,"moverse")){
                    procesar(jugador,input,inicio);
                }

                write(pipes[id+3][1],"ok",lenM);
                read(pipes[id-1][0],input,lenM);
            }
            int winner = input[3];
            printf("J%d felicita al J%d por ganar!!",id,winner);
            exit(0);
        }
    }


    free(msgturno);
}
