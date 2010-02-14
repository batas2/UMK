#include "head.h"

int local_work(const int port, struct t_call **call)
{
	struct t_bind *req;
	struct sockaddr_in addr_in;
	int fd = -1;

	if ((fd = t_open(DEV_XTI, O_RDWR, NULL)) == -1)
		error("serwer->t_open", fd);

	if ((req = (struct t_bind *) t_alloc(fd, T_BIND_STR, T_ADDR)) == NULL)
		error("serwer->t_alloc-bind", fd);

	req->qlen = 5;
	req->addr.len = sizeof(addr_in);
	req->addr.buf = (char *) & addr_in;

	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.s_addr = INADDR_ANY;
	addr_in.sin_port = htons(port);

	if (t_bind(fd, req, req) < 0)
		error("serwer->t_bind", fd);

	if ((*call = (struct t_call *) t_alloc(fd, T_CALL_STR, T_ALL)) == NULL)
		error("serwer->t_alloc-bind", fd);

	(*call)->addr.len = sizeof(addr_in);
	(*call)->udata.maxlen = 0;

	return fd;
}

int accept_client(int fd, struct t_call *call)
{
	int sd;

	if ((sd = t_open(DEV_XTI, O_RDWR, NULL)) < 0)
		error("serwer->accept_client->t_open", fd, sd);

	if (t_bind(sd, NULL, NULL) < 0)
		error("serwer->accept_client->t_bind", fd, sd);

	if (t_accept(fd, sd, call) < 0) {
		if (t_errno == TLOOK) {
			if (t_rcvdis(fd, NULL) < 0)
				error("serwer->accept_client->t_rcvdis", fd, sd);

			if (t_close(sd) < 0)
				error("serwer->accept_client->t_close", fd, sd);

			return -1;
		}
		error("t_accept failed", fd, sd);
	}
	return(sd);
}

void serwer_work(int sd)
{

	sprintf(line, "%d", (int)time(NULL));
	if(t_snd(sd, line, SIZE_BUF, 0) < 0)
		error("serwer->serwer_work->t_snd", sd);

}
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main(int argc, char *argv[])
{

	int fd = -1, sd = -1;
	int port = -1;
	struct t_call *call;

	if(argc != 2){
		printf("Sposob uruchomienia: %s <port>\n", argv[0]);
		exit(1);
	}else{
		port = atoi(argv[1]);
	}

	fd = local_work(port, &call);

	while (1) {
		if (t_listen(fd, call) < 0)
			error("serwer->t_listen", fd);

		if ((sd = accept_client(fd, call)) != -1)
			serwer_work(sd);
	}
	if (t_close(fd) < 0)
		error("serwer->t_close", fd, sd);
	if (t_close(sd) < 0)
		error("serwer->serwer_wrok->t_close", fd, sd);
}
