program DFS;

{$APPTYPE CONSOLE}
{
 Autor: Bartosz Fr¹ckowiak
 http://www.batas2.boo.pl/
}

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

var
  Tab: TTab;
  ColorTab: TColorTab;

procedure Wczytaj(var Tab: TTab);
var
  a, b: Integer;
  tmp: PRec;
begin

  ReadLn(a, b);

  New(tmp);
  tmp^.v := b;

  if Tab[a] = nil then
    begin
      tmp^.w := nil;
      Tab[a] := tmp;
    end
  else
    begin
      tmp^.W := Tab[a];
      Tab[a] := tmp;
  end;

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

  Write(U, ' - ');

  while Tab[U] <> nil do
    begin
      B := Czytaj(Tab[U]);
      if ColorTab[B] = cBialy then
        DFS_VISIT(B);
    end;

  ColorTab[U] := cCzarny;
  Tab[U] := Buf;

end;

procedure pDFS(n: Integer);
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

SetLength(Tab, n + 1);
SetLength(ColorTab, n + 1);

for i := 1 to n do
  begin
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
    pDFS(n);
  Writeln;

  ReadLn;

end.

