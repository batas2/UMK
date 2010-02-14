program listasasiedztwa;
{
 Autor: Bartosz Fr¹ckowiak
 http://www.batas2.boo.pl/
}

type
	PRec = ^TRec;
	TRec = record
		W: PRec;
		v: Integer;
	end;
	TTab = array of PRec;

procedure dodaj(var Wsk: PRec; x: Integer);
var
  B: Prec;
begin

new(B);
B^.v := x;

if Wsk = nil then
	begin
	B^.w := nil;
	wsk := B;
	end
else
	begin
	B^.w := Wsk;
	Wsk := B;
        end;

end;

procedure wczytaj(var Tab: TTab);
var
  a, b: Integer;
begin

readln(a, b);
//readln(b);

Dodaj(Tab[a], b);
Dodaj(Tab[b], a);

end;

function czytaj(var Wsk: Prec): Integer;
var
  B: PRec;
begin

 B := wsk;
 wsk := wsk^.w;
 czytaj := B^.v;
 dispose(B);

end;

procedure wypisz(var Tab: TTab; x: Integer);
var
  b: Integer;
begin

  write(x, ' -> ');
  while Tab[x] <> nil do
	begin
	b := czytaj(Tab[x]);
	Write(b, ', ');
	end;
writeln;
end;

var
  n, m, i: Integer;
  Tab: TTab;
begin

readln(n, m);
//readln(m);

setlength(Tab, n + 1);

for i := 1 to n do
	Tab[i] := nil;

for i := 1 to m do
	wczytaj(Tab);

for i := 1 to n do
	wypisz(Tab, i);

readln;
end.
