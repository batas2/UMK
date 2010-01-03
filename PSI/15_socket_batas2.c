/*
 *	Mateusz Dziadko
 *	matidz@gmail.com
 *	rok akademicki: 2009/2010
 *	Uniwersytet Mikolaja Kopernika
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/in.h>
#include <netdb.h>


#define WIELKOSC_BUFORA 128

int main(int argc, char **argv)
{
	unsigned int port;
	char host_nazwa[100];
	char bufor[WIELKOSC_BUFORA+1]; 
	
	struct hostent *host;
	struct sockaddr_in adres;
	int dlugosc;
	int sokecik;
	int i;
	

	if(argc!=3)
	{
		printf("zle parametry");
		exit(-1);
	}
	else
	{
		port= atoi(argv[2]);
		strncpy(host_nazwa,argv[1],99);
	}
	host = gethostbyname(host_nazwa);
	sokecik = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 	
	adres.sin_family = AF_INET;
        adres.sin_port = ntohs(port);
	adres.sin_addr = *(struct in_addr *) host->h_addr;
	
	dlugosc = sizeof(adres);

        if((connect(sokecik, (struct sockaddr *) &adres, dlugosc)) == -1) {
                perror("blad connect()");
        return 1;
        }

	write(sokecik, "GET /\r\n", strlen("GET /\r\n"));
	
	i=1;
	while(i>0)
	{  	bufor[0]='\0';	
		i=recv(sokecik, bufor, WIELKOSC_BUFORA, 0);
		if(i>0)
		{
			bufor[i]='\0';
			printf("%s", bufor);
		}
	}
	
	printf("\n\n\n\n\n\n\n");
	close(sokecik);

}
