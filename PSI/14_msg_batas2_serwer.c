#include "14_msg_batas2_head.h"

int _stop = 0;
int _quiet = 1;

void koniec(int v);
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main(int argc, char *argv[])
{
	key_t	k;
	char	*home = getenv("HOME");
	struct msg_in	in;
	struct msg_out	out;

	k = ftok(home, PROJ);

	signal(SIGUSR1, koniec);

	if(argc == 2 && argv[1][0] == '1'){
		_quiet = 0;
	}

	int msg_id = msgget(k, IPC_CREAT|IPC_EXCL|0600);
	if(msg_id == -1){
		if ( (msg_id = msgget(k, IPC_CREAT|0600)) == -1){
			perror("Blad-msgget");
			exit(1);
		}
	}

	while(!_stop){
		if(msgrcv(msg_id, &in, SIZE_IN, 0, 0) == -1){
			perror("Blad-msgrcv");
			exit(1);
		}

		switch(in.dzialanie){
			case '+': out.wynik = in.a + in.b; break;
			case '-': out.wynik = in.a - in.b; break;
			case '*': out.wynik = in.a * in.b; break;
		}
		out.msg_type = in.msg_type;
		
		if(!_quiet){		
			printf("SERWER: %0.2f %c %0.2f = %0.2f\n", in.a, in.dzialanie, in.b, out.wynik);
		}
		
		if(msgsnd(msg_id, &out, SIZE_OUT, 0) == -1){
			perror("Blad-msgsnd");
			exit(1);
		}
	}

	msgctl(msg_id, IPC_RMID, NULL);
	return 0;
}

void koniec(int v)
{
	_stop = 1;
	if(!_quiet){
		printf("Serwer zakonczyl swoje dzialanie.\n");
	}
}
