#include<stdio.h>

struct ele{
	int v;
	struct ele *next;
};
struct ele *p = NULL;

int push(int v){
	struct ele *buf;
	buf = malloc(sizeof(struct ele));
	(*buf).v = v; //p->x
	(*buf).next = p; //p->next
        p = buf;
}

void wypisz(){
	struct ele *buf;
	buf = p;
	while(buf != NULL){
		printf("%d\n", buf->v);
		buf = buf->next;
	}
}
void usun(){
	struct ele *buf;
	if(p != NULL){
		buf = p;
		p = p->next;
		free(buf);
	}
}

int main(){
	push(1);
	push(2);
	push(4);
	push(8);
	push(16);
	wypisz();
	usun(); 
	usun(); 
	wypisz();
}
