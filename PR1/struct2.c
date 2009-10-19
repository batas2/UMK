#include<stdio.h>

struct punkt{
	double x;
	double y;
};

struct punkt dodaj(struct punkt s, struct punkt t){
	struct punkt w;
	w.x = s.x + t.x;
	w.y = s.y + t.y;
	return w;
}

int main(){
	struct punkt p={1, -1};
	struct punkt q={2, 3};
	struct punkt r;
	r = dodaj(p, q);
	printf("%lf, %lf\n", r.x, r.y);
	printf("%lf, %lf\n", dodaj(p, q).x, dodaj(p, q).y);
}
