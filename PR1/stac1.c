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
	while(buf->next != NULL){
		printf("%d --> ", buf->v);
		buf = buf->next;
	}
	printf("%d\n", buf->v);
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
	int wybor = 1; int v = 0;
	while(wybor){
		printf("1 - dodaj\n2 - usun\n3 - wypisz\n");
		scanf("%d", &wybor);
		switch(wybor){
			case 1: 
				printf("podaj arg: ");
				scanf("%d", &v);
				push(v);
			break;
			case 2:
				usun();
			break;
			case 3:
				wypisz();
			break;
			default:
				wybor = 0;
		}
	}
}
