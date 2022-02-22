/*
Instituto Politectnico Nacional 
Escuela Superior de Computo

Aplicaciones para la comunicacion en red
Porras Najera Miguel Angel

-servidor_i.C
Es un socket iterativo orientado a la comunicacion utilizando el protcolo tcp para lograr la conexion
este recibe un mensaje y posteriormente eniva una respuesta, este proceso se puede repide 10 veces antes de apagar el socket completamente 

IP Y PUERTOS FIJOS (*practica 2)
*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>                                                                                                                                                                                                                                   
#include <string.h>                                                                                                                    
#define PORT 6044


//Socket cliente caracteristicas : TCP, IP Y PUERTO FIJO                                                                                                                                                                                            
int main(int argc, char const *argv[]){   
    //Declaramos las variables para la configuracion del socket                                                                       
    int sock = 0, valread,contador=10;                                                                                                            
    struct sockaddr_in serv_addr; //renombramos la estructura sockaddr_in -> serv_addr                                            
    char *mensaje = "Hello from client";                                                                                           
    char buffer[1024] = {0};
    
     
}