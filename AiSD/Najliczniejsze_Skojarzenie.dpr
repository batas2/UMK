program Wioletaa;

{$APPTYPE CONSOLE}
{
 Autor: Bartosz Fr¹ckowiak
 http://www.batas2.boo.pl/
}

const
  cBialy = 0;
  cSzary = 1;
  cCzarny = 2;
  Rozmiar = 100;

Type
  PRec = ^TRec;
  TRec = record
    Wartosc: Integer;
    Nastepny: PRec;
  end;

type
  TTab = array[1..Rozmiar] of Byte;
  TMacierz = array[1..Rozmiar] of array[1..Rozmiar] of Integer;
  TListaSas = array[1..Rozmiar] of PRec;

  var Plik: Text;

{ - - - - - - - - - - - - KOLEJKA START - - - - - - - - - - - - }
procedure KolejkaDodaj(var WskDod, WskCzyt: PRec; V: Integer);
var
  Nowy: PRec;
begin

  New(Nowy);
  Nowy^.Wartosc := V;
  Nowy^.Nastepny := nil;

  if WskDod <> nil then
    begin
      WskDod^.Nastepny := Nowy;
      WskDod := Nowy;
    end
  else
    WskDod := Nowy;

  if WskCzyt = nil then
    WskCzyt := WskDod;

end;

function KolejkaCzytaj(var WskDod, WskCzyt: PRec):Integer;
var
  Buf: PRec;
begin

  if WskCzyt <> nil then
    begin
      KolejkaCzytaj := WskCzyt^.Wartosc;

      Buf := WskCzyt;
      WskCzyt := WskCzyt^.Nastepny;
      Dispose(Buf);

      if WskCzyt = nil then
        WskDod := nil;
    end
  else
    KolejkaCzytaj := -1;

end;

procedure KolejkaCzysc(var WskDod, WskCzyt: PRec);
var
  Buf: PRec;
begin

  while WskCzyt <> nil do
    begin
      Buf := WskCzyt;
      WskCzyt := WskCzyt^.Nastepny;
      Dispose(buf);
    end;
    
  WskCzyt := nil;
  WskDod := nil;

end;

function KolejkaPusta(var WskCzyt: PRec) : Boolean;
begin

  if WskCzyt = nil then
    KolejkaPusta := true
  else
    KolejkaPusta := false;

end;

{ - - - - - - - - - - - - KOLEJKA STOP - - - - - - - - - - - - }

{ - - - - - - - - - - - - LISTA SASIEDZTWA START - - - - - - - - - - - - }

procedure DodajListaSas(var ListaSas: TListaSas; a, b: Integer);
var
  Buf: PRec;
begin

  New(Buf);
  Buf^.Wartosc := b;

  if ListaSas[a] = nil then
    begin
      Buf^.Nastepny := nil;
      ListaSas[a] := Buf;
    end
  else
    begin
      Buf^.Nastepny := ListaSas[a];
      ListaSas[a] := Buf;
  end;

end;

function CzytajListaSas(var Wsk: Prec): Integer;
begin

  CzytajListaSas := Wsk^.Wartosc;
  Wsk := Wsk^.Nastepny;

end;

procedure WypiszListaSas(var ListaSas: TListaSas; x: Integer);
var
  b: Integer;
  Buf: PRec;
begin

  Buf := ListaSas[x];
  Write(x, ' -> ');

  while ListaSas[x] <> nil do
    begin
      b := CzytajListaSas(ListaSas[x]);
      Write(b, ', ');
    end;

  ListaSas[x] := Buf;
  WriteLn;

end;
{ - - - - - - - - - - - - LISTA SASIEDZTWA STOP - - - - - - - - - - - - }

{ - - - - - - - - - - - - ALGORYTMY START - - - - - - - - - - - - }

function BFS(start, stop, n: Integer; Wypisz: Boolean; var Wynik: TTab;
             var C: TMacierz): Boolean;
var
  i, u: Integer;
  WskDod, WskCzyt: PRec;
  Koniec: Boolean;
  TabKolor: TTab;
begin

  WskDod := nil; WskCzyt := nil;
  Koniec := False;

  for i := 1 to n do
    begin
      Wynik[i] := 0;
      TabKolor[i] := cBialy;
    end;

  TabKolor[start] := cSzary;
  KolejkaDodaj(WskDod, WskCzyt, start);

  if Wypisz then
    begin
      Writeln;
      Write(start);
    end;

  while (not KolejkaPusta(WskCzyt)) and (not Koniec) do
    begin
      u := KolejkaCzytaj(WskDod, WskCzyt);

      if u = stop then
        Koniec := True;

      for i := 1 to n do
        if (C[u][i] > 0) and (TabKolor[i] <> cCzarny) and (not Koniec) then
          begin
            Wynik[i] := u;
      	    KolejkaDodaj(WskDod, WskCzyt, i);

            if Wypisz then
          	  Write(' -- ', i);
      	end;
        
    	TabKolor[u] := cCzarny;
    end;

  if Wypisz then
    Writeln;

  BFS := Koniec;

end;


Procedure MaxPrzeplyw(var C, F: TMacierz; var WynikBFS: TTab;
		                  start, stop: Integer);
var
  Min, a, b: Integer;
begin

  {Znajdujemy minimalny wartosc potencjalnego przeplywu na sciezce}
  b := stop;
  a := WynikBFS[b];
  Min := C[a][b];

  while a <> start do
    begin
      if Min > C[a][b] then
        Min := C[a][b];
      b := a;
      a := WynikBFS[a];
    end;

  {sedno algorytmy, zwiekszamy potencjalny przeplyw i zmniejszamy warosc na grafie}
  b := stop;
  a := WynikBFS[b];

  while a <> start do
    begin
      F[a][b] := F[a][b] + Min;
      C[a][b] := C[a][b] - Min;
      b := a;
      a := WynikBFS[a];
    end;

  F[Start][b] := F[Start][b] + Min;
  C[Start][b] := C[Start][b] - Min;

end;

Procedure NajliczSkojarz(var C, F: TMacierz; n, d: Integer);
var
  BufM: TMacierz;
  i, j: Integer;
begin

  {Czyszczenie}
  for i := 1 to n + 2 do
    for j := 1 to n + 2 do
      BufM[i][j] := 0;

  for i := 1 to n do
    for j := 1 to n do
        F[i][j] := 0;

  {Laczymy lewe wierzcholki z 1}
  for i := 2 to d + 1 do
    BufM[1][i] := 1;

  {laczymy prawe z ostanim}
  for i := d + 2 to n + 1 do
    BufM[i][n + 2] := 1;

  {przepisujmey krawendzie}
  for i := 1 to n do
    for j := 1 to n do
      if C[i][j] <> 0 then
        BufM[i + 1][j + 1] := 1;

  C := BufM;

end;

{ - - - - - - - - - - - - ALGORYTMY STOP - - - - - - - - - - - - }

procedure WczytajKrawendz(var ListaSas: TListaSas; var C: TMacierz);
var
  a, b, w: Integer;
begin

  ReadLn(plik, a, b, w);

  C[a][b] := w;
  DodajListaSas(ListaSas, a, b); {lista sas}

end;

procedure WypiszWynik(var F: TMacierz; Stop, n: Integer; MaxPrzep: Boolean);
var
  i: Integer;
  Wynik: Integer;
begin

  Wynik := 0;

  for i := 1 to n do
    Wynik := Wynik + F[i][Stop];

  if MaxPrzep then
    Writeln('Maksymalny Przeplyw: ', Wynik)
  else
    Writeln('Skojarzenie o licznosci: ', Wynik);

end;

{ - - - - - - - - - - - - GLOWNY PROGRAM START - - - - - - - - - - - - }

var
  i, n, m, start, stop, d: Integer;
  ListaSas: TListaSas;
  C, F: TMacierz;
  WynikBFS: TTab;
begin

  AssignFile(Plik, 'dane.in');
  Reset(Plik);

  Readln(Plik, n, m);

  for i := 1 to m do
    WczytajKrawendz(ListaSas, C);

  {Lista sas}
  Writeln('Lista Sasiedztwa:');
  for i := 1 to n do
  	WypiszListaSas(ListaSas, i);
  {Lista sas}

  Writeln('BFS:');

  Write('Prosze podac wierzcholek startowy oraz koncowy: ');
  Readln(plik, start, stop);

  while BFS(start, stop, n, true, WynikBFS, C) do
    MaxPrzeplyw(C, F, WynikBFS, start, stop);

  WypiszWynik(F, Stop, n, True);

  Write('Prosze podac liczbe wedlug ktorej zbior wierzcholkow zostanie podzielony: ');
  Readln(plik, d);

  NajliczSkojarz(C, F, n, d);

  while BFS(1, n + 2, n + 2, true, WynikBFS, C) do
    MaxPrzeplyw(C, F, WynikBFS, 1, n + 2);
    
  WypiszWynik(F, n + 2, n + 2, False);

  Closefile(Plik);
  Readln;

end.
