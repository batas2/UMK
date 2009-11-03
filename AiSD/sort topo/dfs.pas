program Project2;

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
  //TF = array of Integer;

var
  //t: Integer;
  Tab: TTab;
  ColorTab: TColorTab;
  //F: TF;
  Lista: PRec;

procedure Dodaj(var Wsk: PRec; x: Integer);
var
  B: Prec;
begin

  New(B);
  B^.v := x;

  if Wsk = nil then
    begin
      B^.w := nil;
      Wsk := B;
    end
  else
    begin
      B^.W := Wsk;
      Wsk := B;
  end;

end;

procedure wczytaj(var Tab: TTab);
var
  a, b: Integer;
begin

  ReadLn(a, b);
  Dodaj(Tab[a], b);
//Dodaj(Tab[b], a);

end;

function Czytaj(var Wsk: Prec): Integer;
begin

  Czytaj := Wsk^.v;
  Wsk := Wsk^.W;

end;

procedure Wypisz(var Tab: TTab; x: Integer);
var
  b: Integer;
  Buf: PRec;
begin

  Buf := tab[x];
  Write(x, ' -> ');

  while Tab[x] <> nil do
    begin
      b := Czytaj(Tab[x]);
      Write(b, ', ');
    end;

  Tab[x] := Buf;
  WriteLn;

end;

procedure DFS_VISIT(U: Integer);
var
  B: Integer;
  Buf: PRec;
begin

  ColorTab[U] := cSzary;
  Buf := Tab[U];
  //Inc(t);
  Write(U, ' - ');

  while Tab[U] <> nil do
    begin
      B := Czytaj(Tab[U]);
      if ColorTab[B] = cBialy then
        DFS_VISIT(B);
    end;

  //Inc(t); F[U] := t;
  Dodaj(Lista, U);
  ColorTab[U] := cCzarny;

  Tab[U] := Buf;

end;

procedure DFS(n: Integer);
var
  i: Integer;
begin

  for i := 1 to n do
    if ColorTab[i] = cBialy then
      DFS_VISIT(i);

end;

var
  n, m, i: Integer;
begin

ReadLn(n, m);

//t := 0;

SetLength(Tab, n + 1);
SetLength(ColorTab, n + 1);
//SetLength(F, n + 1);

for i := 1 to n do
  begin
    //F[i] := 0;
    Tab[i] := nil;
    ColorTab[i] := cBialy;
  end;

for i := 1 to m do
  Wczytaj(Tab);

  Writeln('Lista sasiedztwa: ');
    for i := 1 to n do
      Wypisz(Tab, i);
  Writeln;

  Write('DFS: ');
    DFS(n);
  Writeln;

  Write('Sort: ');
    while Lista <> nil do
      Write(Czytaj(Lista), ' - ');
  Writeln;

  ReadLn;

end.

