#include<stdio.h>
#include<math.h>

struct punkt{
	double x;
	double y;
};

//struct punkt{ struct punkt p;}; NIE MOZNA TAK

struct prostokat{
	struct punkt p1;
	struct punkt p2;
};

double odleglosc(struct punkt s, struct punkt t){
	struct punkt w;
	return sqrt( pow(t.x - s.x, 2) + pow(t.y - s.y, 2));
}

int spr(struct prostokat p, struct punkt r){
	if( (r.x <= p.p2.x) && (r.x >= p.p1.x) && (r.y <= p.p1.y) && (r.y >= p.p2.y) ){
		return 1;
	}else{
		return 0;
	}
}
   
int main(){
	struct punkt p={1, -1};
	struct punkt q={2, 3};
	struct prostokat r;
	r.p1.x = 1; r.p1.y = 1;
	r.p2.x = 4; r.p2.y = 4;
	//r.p1.x = 18;
	//r.p2.y = 31;
	printf("%lf\n", odleglosc(p, q));
	printf("%d\n", spr(r, q));
}
