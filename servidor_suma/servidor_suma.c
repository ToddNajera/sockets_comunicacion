/*
Instituto Politectnico Nacional 
Escuela Superior de Computo

Aplicaciones para la comunicacion en red
Porras Najera Miguel Angel

-servidor_suma.C
Es un socket no bloqueante orientado a la comunicacion utilizando el protcolo tcp para lograr la conexion
este recibe un mensaje el cual consiste de dos numeros enteros y un signo el cual refiere a la operacion que 
se debera realizar con ellos, el resultado se le regresa al cliente

IP Y PUERTOS FIJOS (*practica 4)
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>                                                                                                                 
#define TAM 1024
#define PORT 6044


int main(int argc, char *argv[]){

    //declaracion de variables para configuracion del socket
    int i, s, s_conec, leido, ndesc;
	unsigned int tam_dir;
	struct sockaddr_in dir, dir_cliente;
	char buf[TAM];
	int opcion=1;
	fd_set desc_sockets; 
	fd_set desc_sockets_copia; 

    printf("\nIniciando Socket");
    if ((s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("error creando socket");
		return 1;
	}

    printf("\nConfigurando Socket");
	/* Para reutilizar puerto inmediatamente */
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opcion, sizeof(opcion))<0){
        perror("error en setsockopt");
        return 1;
    }

	dir.sin_addr.s_addr=INADDR_ANY;
	dir.sin_port=htons( PORT );
	dir.sin_family=PF_INET;

    printf("\nConfigurando IP");


	if (bind(s, (struct sockaddr *)&dir, sizeof(dir)) == -1) {
		perror("error en bind");
		close(s);
		return 1;
	}

    printf("\nEsperando Conexion");
    if (listen(s, 5) < 0) {
		perror("error en listen");
		close(s);
		return 1;
	}

    //Variables para mantener los sockets en espera
	FD_ZERO(&desc_sockets); 
	FD_SET(s, &desc_sockets);

	while (1) {

		desc_sockets_copia=desc_sockets; 
		if ((ndesc=select(FD_SETSIZE, &desc_sockets_copia,NULL, NULL, NULL))<0) {
			perror("error en select");
			close(s);
			return 1;
		}
		if (FD_ISSET(s, &desc_sockets_copia)) {
			ndesc--;
			tam_dir=sizeof(dir_cliente);
			if ((s_conec=accept(s, (struct sockaddr *)&dir_cliente,&tam_dir))<0){
				perror("error en accept");
				close(s);
				return 1;
			}
			FD_SET(s_conec, &desc_sockets); 
		}
		for (i=0; ndesc; i++) {
			if (FD_ISSET(i, &desc_sockets_copia)) {
				ndesc--;
				if ((leido=read(i, buf, TAM))>0) {
					char *mensaje = "Conexion exitosa";
					printf("Procesando datos recibidos: %s\n",buf);

					if (write(i, mensaje, leido)<0) {
						perror("error en write");
						close(s);
						return 1;
					}
				}
	
				if (leido<0) {
					perror("error en read");
					close(s);
					return 1;
				}
				if (leido==0) { // cliente cierra conexión
					close(i);
					FD_CLR(i, &desc_sockets); 
				}
			}
		}
	}

	close(s);

	return 0;

}