#include "14_msg_batas2_head.h"

int main(int argc, char *argv[])
{
	if(argc == 4){
		key_t	k;
		char	*home = getenv("HOME");
		struct msg_in	in;
		struct msg_out	out;
		int pid = getpid();

		k = ftok(home, PROJ);

		int msg_id = msgget(k, 0600);
		if(msg_id == -1){
			perror("Blad-msgget");
			exit(1);
		}
	
		in.msg_type = pid;

		in.a = atof(argv[1]);
		in.b = atof(argv[3]);
		
		in.dzialanie = argv[2][0];

		if(msgsnd(msg_id, &in, SIZE_IN, 0) == -1){
			perror("Blad-msgsnd");
			exit(1);
		}
	
		if(msgrcv(msg_id, &out, SIZE_OUT, pid, 0) == -1){
			perror("Blad-msgrcv");
			exit(1);
		}

		printf("Wynik: %0.2f\n", out.wynik);
	}else{
		printf("./client [a] [dzialanie] [b]\n");
		printf("Dostpene dzialania: + - *\n");
		printf("W przypadku problemu z dzialaniem '*' nalezy '*' poprzedzic znakiem '\\',\nponiewaz powloka interpetuje gwiazdke na swoj sposob.\nnp: ./client 2.3 \\* 8.4\n");
	}
}
