#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> 


#ifndef INET6_ADDRSTRLEN
# define INET6_ADDRSTRLEN 46
#endif /* INET6_ADDRSTRLEN */

#define SIZE_BUF 	256
#define SIZE_P		10
#define MAX_PLAYERS	10

char MSG_WAIT[] = "MSG|Prosze czekac na zgloszenie sie drugiego gracza.|\n";
char MSG_START[] = "MSG|Gracze podlaczeni. Start gry.|\n";
char MSG_STOP[] = "MSG|Koniec gry.|\n";
char MSG_EMPTY[] = "MSG|Pudlo! Pozycja [%d, %d]|\n";
char MSG_HIT[] = "MSG|Trafiony! Pozycja [%d, %d]|\n";
char MSG_HITTED[] = "MSG|Juz strzelales w pole [%d, %d]|\n";

#define IEXIT	1 + 48
#define ISET	2 + 48
#define IEMPTY	3 + 48
#define	IHIT	4 + 48
#define ITURN	5 + 48

char CMD_EXIT[] = "CMD|1|";
char CMD_SET[] = "CMD|2|%d|%d|";
char CMD_EMPTY[] = "CMD|3|%d|%d|";
char CMD_HIT[] = "CMD|4|%d|%d|";
char CMD_TURN[] = "CMD|5|";

void move(char *str, int n)
{
	memmove(str, str + n, (strlen(str) - n) * sizeof(char));
	str[strlen(str) - n] = '\0';
	return;
}

void split(char *str, char **result)
{
	char *pos = NULL;
	int pos_i = 0, i = 0;
	
	while( (pos = strstr(str, "|")) != NULL ){
	
		pos_i = pos - str; 
		strncpy(result[i], str, sizeof(char) * (pos_i));
		result[i++][pos_i] = '\0';
		move(str, pos_i + 1);
	}

	result[i] = str;
	result[i][strlen(result[i]) - 1] = '\0';
	result[i + 1] = NULL; 
	return;
}
