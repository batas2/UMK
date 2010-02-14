#include "head.h"

void klient_work(int sd)
{
	time_t t;
	struct tm *timeinfo;
	int flags;

	if (t_rcv(sd, line, sizeof(line), &flags) < 0) {
		if (t_errno == TLOOK) {
			if (t_look(sd) == T_DISCONNECT) {
				if (t_rcvdis(sd, NULL) < 0)
					error("Klient->trcvdis:", sd);

				exit(0);
			}
		}
		error("klient->klient_work->t_rcv", sd);
	}

	t = atoi(line);
	timeinfo = localtime(&t);
	strftime(line, SIZE_BUF, "%Y-%m-%d %H:%M:%S", timeinfo);

	printf("Czas serwera: %s\n", line);
}
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main(int argc, char *argv[])
{
	int sd = -1;
	struct sockaddr_in addr_in;
	struct t_call *call;

	char *host;
	int port = 2608;

	if (argc != 3) {
		printf("Sposob uruchomienia: %s <host> <port>\n", argv[0]);
	}else{
		host = argv[1];
		port = atoi(argv[2]);
	}

	if ((sd = t_open(DEV_XTI, O_RDWR, NULL)) < 0)
		error("Klient->t_open:", sd);

	if (t_bind(sd, NULL, NULL) < 0)
		error("Klient->t_bind:", sd);

	if ((call = (struct t_call *) t_alloc(sd, T_CALL, T_ADDR)) == NULL)
		error("Klient->t_alloc:", sd);

	inet_pton(AF_INET, host, &addr_in.sin_addr);
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(port);

	call->udata.len = 0;
	call->addr.len = sizeof(addr_in);
	call->addr.buf = (char *) & addr_in;

	if (t_connect(sd, call, NULL) < 0)
		error("Klient->t_connect:", sd);

	klient_work(sd);

	if (t_close(sd) < 0)
		error("Klient->t_close:", sd);

}
