/*
Instituto Politectnico Nacional 
Escuela Superior de Computo
Aplicaciones para la comunicacion en red
Porras Najera Miguel Angel

-cliente.c
Es un socket orientado a la comunicacion utilizando el protcolo tcp para lograr la conexion
este puede enviar un mensaje y recibe uno
IP, PUERTOS FIJOS, MENSAJE FIJO (*practica 1)
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
    int sock = 0, valread;                                                                                                            
    struct sockaddr_in serv_addr; //renombramos la estructura sockaddr_in -> serv_addr                                            
    char *mensaje = "Hello from client";                                                                                           
    char buffer[1024] = {0};                                                                                                      
                                                                                                                                      
                                                                                                                                      
    //Creando descriptor del socket                                                                                                   
    printf("\nIniciando Socket");                                                                                                     
    if( (sock = socket(AF_INET, SOCK_STREAM,0)) < 0){                                                                                                                                                                     
        printf("\n socket faild conection");                                                                                          
        return -1;                                                                                                                    
    }                                                                                                                                 
                                                                                                                                      
    serv_addr.sin_family = AF_INET;                                                                                                   
    serv_addr.sin_port = htons(PORT);                                                                                                 
                                                                                                                                      
                                                                                                                                      
    //Convertimos la IPv4 o IPv6 de texto a binario para ser procesada                                                                
    if(inet_pton(AF_INET,"10.0.0.1",&serv_addr.sin_addr) <= 0){                                                                        
        printf("\nInvalid address/ Address not supported \n");                                                                        
                return -1;                                                                                                            
    }                                                                                                                                 
                                                                                                                                      
    printf("\nConfigurando Socket");                                                                                                  
    //Una vez creado el socket tratamos de lograr la conexion
    int i = 0;                                                                         
    if( i = connect(sock, (struct sockaddr *)&serv_addr,sizeof(serv_addr) ) < 0){                                                         
        printf("\nConnection failed");   
        printf("\n %d",i);                                                                                            
        return -1;                                                                                                                    
    }                                                                                                                                 
                                                                                                                                      
    printf("\nIniciando Conexion");                                                                                                   
    //proceso de comunicacion                                                                                                                                                                                                                                              
    send(sock , mensaje , strlen(mensaje) , 0 );                                                                                      
    printf("-message sent-\n");                                                                                                                                                                                                                                        
    valread = read( sock , buffer, 1024);                                                                                                                                                                                                                        
    printf("%s\n",buffer );                                                                                                                                                                                                                                     
    //cerramos el sockets para las conexion futura asi como envios futuros (argumento 2 SHUT_RDWR)                                                                                                                                                 
    if(shutdown(sock,2) < 0){                                                                                                                                                                                                                                         
        printf("shutdown failed");                                                                                                                                                                                                                                
        return -1;                                                                                                                                                                                                                                                     
    }                                                                                                                                 

    printf("\n");                                                                                                                                                                                                                                                 
    return 0;                                                                                                                     
} 