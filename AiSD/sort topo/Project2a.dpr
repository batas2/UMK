program Project2;

{$APPTYPE CONSOLE}

uses
  SysUtils;

const
  cBialy = 0;
  cSzary = 1;
  cCzarny = 2;
  
type
	PRec = ^TRec;
	TRec = record
		W: PRec;
		v: Integer;
	end;
	TTab = array of PRec;
  TColorTab = array of Byte;
  TF = array of Integer;

var
  t: Integer;

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

Dodaj(Tab[a], b);
//Dodaj(Tab[b], a);

end;

function czytaj(var Wsk: Prec): Integer;
begin

 czytaj := wsk^.v;
 wsk := wsk^.w;

end;

procedure wypisz(var Tab: TTab; x: Integer);
var
  B: Integer;
  Buf: PRec;
begin

  buf := tab[x];
  write(x, ' -> ');
  while Tab[x] <> nil do
	begin
	b := czytaj(Tab[x]);
	Write(b, ', ');
	end;
  tab[x] := buf;
writeln;
end;

procedure DFS_VISIT(var Tab: TTab; var ColorTab: TColorTab; var F: TF; U: integer);
var
  B: Integer;
  Buf: PRec;
begin

  ColorTab[U] := cSzary;
  Buf := Tab[U];
  Writeln(U);
  while Tab[U] <> nil do
    begin
      B := Czytaj(Tab[U]); Inc(t);
      if ColorTab[B] = cBialy then
        begin
          DFS_VISIT(Tab, ColorTab, F, B);
        end;
      Inc(t); F[U] := t;
      ColorTab[U] := cCzarny;
    end;
  Tab[U] := Buf;
      
end;

procedure DFS(var Tab: TTab; var ColorTab: TColorTab; var F: TF; n: Integer);
var
  i: Integer;
begin

  for i := 1 to n do
    if ColorTab[i] = cBialy then
      DFS_VISIT(Tab, ColorTab, F, i);
      
end;

var
  n, m, i: Integer;
  Tab: TTab;
  ColorTab: TColorTab;
  F: TF;
begin

ReadLn(n, m);

t := 0;

SetLength(Tab, n + 1);
SetLength(ColorTab, n + 1);
SetLength(F, n + 1);

for i := 1 to n do
  begin
    F[i] := 0;
  	Tab[i] := nil;
    ColorTab[i] := cBialy;
  end;

for i := 1 to m do
	wczytaj(Tab);

DFS(Tab, ColorTab, F, n);

for i := 1 to n do
	wypisz(Tab, i);

ReadLn;

end.

