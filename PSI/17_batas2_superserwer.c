//Bartosz Frackowiak
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <sys/time.h>
#include <unistd.h>
#include <sys/select.h>

#ifndef INET6_ADDRSTRLEN
# define INET6_ADDRSTRLEN 46
#endif /* INET6_ADDRSTRLEN */

#define SIZE_BUF 256

//Zmienna trzymajaca polecenie wczytane z pierwszej lini pliku konfiguracyjnego
char cmd[SIZE_BUF];

//funkcja przydziela do tablicy sd deskryptory gniazd tworzone w funkcji
//getSocket, oraz wypelnia tablice wskaznikow na funkcje odpowiedzialne
//za akcje na poszczegolnych portach
void sockFactory(int *sd,  int *ports, void (*fun[10])(int sock));
//funkcja resetuje oraz tworzy zbior deskryptorow gniazd
int setFactory(int *sd, fd_set *rsds);


void error(char *message, int line);
void loadFile(char *src, char *cmd, int *ports);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//funkcja pobiera domain oraz port, a zwraca wypelniona strukture result
//oraz jej rozmiar size
void getSockAddr(int domain, int port, struct sockaddr *result, socklen_t *size)
{
	struct sockaddr *addr;
	if(domain == AF_INET6){
		struct sockaddr_in6 addr6;
	
		addr6.sin6_family = AF_INET6;
		addr6.sin6_port = htons(port);
		addr6.sin6_addr = in6addr_any;

		addr = (struct sockaddr*)&addr6;
		memcpy(result, addr, sizeof(addr6));
		*size = sizeof(addr6);
		return;
	}else if(domain == AF_INET){
		struct sockaddr_in addr4;

       	        addr4.sin_family = AF_INET;
		addr4.sin_port = htons(port);
		addr4.sin_addr.s_addr = htonl(INADDR_ANY);

		addr = (struct sockaddr*)&addr4;
		memcpy(result, addr, sizeof(addr4));
		*size = sizeof(addr4);
		return;
	}
	return;
}

//funkcja pobiera typ polaczenia, wersje IP oraz port i 
//zwraca deskryptor gniazda
int getSocket(int domain, int type, int port)
{
	struct sockaddr *addr = malloc(sizeof(struct sockaddr));
	socklen_t size;

	int sock = socket(domain, type, 0);
	getSockAddr(domain, port, addr, &size);

	if(bind(sock, addr, size) == -1 ){
		error("bind", __LINE__);
	}

	if(type == SOCK_STREAM){
       	        if(listen(sock, 5) == -1){
               	        error("listen", __LINE__);
		}
	}
	return sock;
}

void action(int sd, void (*fun)(int sock))
{
	int pid = 0;
	if( (pid = fork()) < 0 ){
		error("fork", __LINE__);
	}else{
		if(pid == 0){
			fun(sd);
			exit(0);
		}
	}
}
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main()
{
	int maxsd = -1;

	char src[SIZE_BUF] = "serwer.conf";

	int ports[10]; //tablica portow
	int sd[10]; //tablica deskryptorow gniazd
	void (*fun[5])(int sock); //tablica wskaznikow na funkcje

	loadFile(src, cmd, ports); //wczytujemy konfiguracje serwera
	sockFactory(sd, ports, fun); //tworzymy wszystkie gniazda

	fd_set rsds;
 	int retval;

	while( 1 ){
		//tworzymy zbior gniazd oraz pobieramy najwyzszy deskryptor
		maxsd = setFactory(sd, &rsds);
		//ostatni parametr == NULL, powoduje ze funkcja select czeka tak
		//dlugo az cos sie pojawi do odczytu
		retval = select(maxsd + 1, &rsds, NULL, NULL, NULL);

		if(retval < 0){
			error("retval", __LINE__);
		}
		if(retval > 0){
			int i;
			for(i = 0; i < 10; i++){
				if(FD_ISSET(sd[i], &rsds)){
					action(sd[i], fun[i % 5]);
				}
			}
		}
	}
	return 0;
}

int acceptConnection(int sock)
{
	int sockd = -1;
	socklen_t size;
    
	if((sockd = accept(sock, NULL, NULL)) == -1){
		error("accept", __LINE__);
	}
	return sockd;
}

void tcp_echo(int sock)
{

	char buf[SIZE_BUF];
	sock = acceptConnection(sock);

	while(read(sock, buf, sizeof(buf)) > 0){;
		write(sock, buf, sizeof(buf));
	}

	close(sock);
}

void tcp_time(int sock)
{
	time_t now;
   	struct tm *ts;
   	char buf[80];
 
	now = time(NULL);
 
	ts = localtime(&now);
	strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z\0", ts);

	sock = acceptConnection(sock);
	
	write(sock, buf, sizeof(buf));
	close(sock);
}

void tcp_special(int sock)
{
	sock = acceptConnection(sock);
	
	dup2(sock, fileno(stdout));
	execlp(cmd, cmd, NULL);

	char buf[] = "Nie ma takiego polecenia!\n";
	write(sock, buf, sizeof(buf));
	close(sock);
}

void udp_echo(int sock)
{
	char buf[SIZE_BUF];
	struct sockaddr addr;
	socklen_t socklen;

	if(recvfrom(sock, buf, SIZE_BUF, 0, &addr, &socklen) == -1){
		error("recvfrom", __LINE__);
	}
	sendto(sock, buf, SIZE_BUF, 0, &addr, socklen);
}

void udp_time(int sock)
{
	time_t now;
   	struct tm *ts;
   	char t[80];

	char buf;
	struct sockaddr addr;
 	socklen_t socklen;
	
	now = time(NULL);
	ts = localtime(&now);
	strftime(t, sizeof(t), "%a %Y-%m-%d %H:%M:%S %Z\0", ts);

	if(recvfrom(sock, &buf, sizeof(buf), 0, &addr, &socklen) == -1){
		error("recvfrom", __LINE__);
	}
	sendto(sock, t, sizeof(t), 0, &addr, socklen);
	
}

int setFactory(int *sd, fd_set *rsds)
{
	FD_ZERO(rsds);

	int i = 0, maxsd = -1;
	for(i = 0; i < 10; i++){
		FD_SET(sd[i], rsds);
		if(maxsd < sd[i]){
			maxsd = sd[i];
		}

	}
	return maxsd;
}

void sockFactory(int *sd, int *ports, void (*fun[5])(int sock) )
{

	sd[0] = getSocket(AF_INET, SOCK_STREAM, ports[0]);
	sd[1] = getSocket(AF_INET, SOCK_STREAM, ports[1]);
	sd[2] = getSocket(AF_INET, SOCK_STREAM, ports[2]);
	sd[3] = getSocket(AF_INET, SOCK_DGRAM, ports[3]);
	sd[4] = getSocket(AF_INET, SOCK_DGRAM, ports[4]);
	sd[5] = getSocket(AF_INET6, SOCK_STREAM, ports[5]);
	sd[6] = getSocket(AF_INET6, SOCK_STREAM, ports[6]);
	sd[7] = getSocket(AF_INET6, SOCK_STREAM, ports[7]);
	sd[8] = getSocket(AF_INET6, SOCK_DGRAM, ports[8]);
	sd[9] = getSocket(AF_INET6, SOCK_DGRAM, ports[9]);

	fun[0] = tcp_echo;
	fun[1] = tcp_time;
	fun[2] = tcp_special;
	fun[3] = udp_echo;
	fun[4] = udp_time;

}

void error(char *message, int line)
{
	char buf[SIZE_BUF];
	sprintf(buf, "%d: %s", line, message);
	perror(buf);
	exit(1);
}

void loadFile(char *src, char *cmd, int *ports)
{
	FILE *fd = fopen(src, "r");
	fscanf(fd, "%s", cmd);
	int i = 0;
	for(i = 0; i < 10; i++){
		fscanf(fd, "%d", ports + i);
	}
	fclose(fd);
}
