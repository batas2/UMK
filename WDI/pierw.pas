program pierw;
const epsilon =0.00001;
var
t,s,x:real;
k:integer; 
begin
write('podaj x:');
read(x);
t:=x;
s:=t;
k:=0;
while abs(t)>epsilon*abs(s) do
begin
k := k+2;
t:=-t*sqrt(x)/(k*(k-1));
s:=s+t;
end;
writeln(s);
end.
