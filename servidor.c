/*
Instituto Politectnico Nacional 
Escuela Superior de Computo

Aplicaciones para la comunicacion en red
Porras Najera Miguel Angel

-servidor.C
Es un socket orientado a la comunicacion utilizando el protcolo tcp para lograr la conexion
este recibe un mensaje y posteriormente eniva una respuesta

IP Y PUERTOS FIJOS (*practica 1)
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 6044

//Servidor TCP, puerto fijo
int main(int argc, char const *argv[]){
    
    //declaracion de variables para configuracion del socket
    int server_fd, new_socket, valread;
    struct sockaddr_in address; //renombramos la estructura sockaddr_in -> address para uso dentro del programa
    int opt = 1; 
    int addr_len = sizeof(address); //variable para almacenar la longitud de la direccion
    char buffer[1024] = {0}; // almacenamiento libre para recepcion de mensajes
    char *mensaje = "Hello from server";//mensaje ha enviar
    printf("\nIniciando Socket");
    //Creando descriptor del socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed to create socket");
        exit(EXIT_FAILURE); 
    }

    /*
    setsocktopt - permite definir el nivel al que operara el socket
    SOL_SOCKET - uso de IPv4 y IPv6
    SO_REUSEADDR -permite al socket usar una direccion que ya este en uso
    SO_REUSEPORT - permite usar un puerto que ya este en uso
    */
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))){
		perror("socket failed in level configuration");
		exit(EXIT_FAILURE);
	}
    printf("\nConfigurando Socket");
    address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

    //Forzamos al puerto ha estar dentro del puerto especificado y la ip local del computador
    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
    printf("\nEn espera de Mensaje");
    //Inicio de proceso de espera de una conexion
    if (listen(server_fd, 3) < 0){
		perror("listen faild");
		exit(EXIT_FAILURE);
	}
    printf("\nIniciando Conexion");

    //Acepta el la primer conexion que se encuentre en la cola de pendientes
    //regresa un socket de aceptacion para responder el mensaje
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addr_len))<0){
		perror("accept faild");
		exit(EXIT_FAILURE);
	}
    printf("\nConexion exitosa");
    valread = read( new_socket , buffer, 1024); //se lee el mensaje del socket cliente
	printf("%s\n",buffer );
	send(new_socket , mensaje , strlen(mensaje) , 0 );
	printf("-message sent-\n");
	printf("%d\n",sizeof(long int));
    printf("-shutdown socket-\n");

    //cerramos el sockets para las conexion futura asi como envios futuros (argumento 2 SHUT_RDWR)
    if(shutdown(server_fd,2) < 0){
        perror("shutdown failed");
        exit(EXIT_FAILURE);
    }
    printf("\n");
	return 0;


}