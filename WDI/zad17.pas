program zad17;

type
  PLista = ^TLista;
  TLista = record
    V: Integer;
    Next: PLista;
    Prev: PLista;
  end;

var
  Wsk: PLista;

procedure Cofnij;
begin

  while Wsk^.Prev <> nil do
    Wsk := Wsk^.Prev;

end;

function Przesun(p: Integer):Integer;
var
  i: Integer;
begin

  i := 1;
  while (i < p) and (Wsk^.Next <> nil) do
    begin
      Wsk := Wsk^.Next;
      Inc(i);
    end;
  Przesun := i;

end;

function Czytaj(p: Integer): Integer;
begin

  Cofnij;
  Przesun(p);
  Czytaj := Wsk^.V;

end;

procedure Dodaj(v, p: Integer);
var
  Nowy: PLista;
  i: Integer;
begin

  if Wsk = nil then
    begin
      New(Nowy);
      Nowy^.Prev := nil;
      Nowy^.Next := nil;
      Nowy^.V := v;
    end
  else
    begin

      Cofnij;
      i := Przesun(p);

      New(Nowy);
      Nowy^.V := v;

      if (Wsk^.Next = nil) and (i <> p) then
        begin
          Nowy^.Next := nil;
          Nowy^.Prev := Wsk;
          Wsk^.Next := Nowy;
        end
      else
        begin
          Nowy^.Next := Wsk;
          Nowy^.Prev := Wsk^.Prev;
          Wsk^.Prev := Nowy;
          Wsk := Wsk^.Prev;
          Wsk := Wsk^.Prev;
          if Wsk <> nil then
            Wsk^.Next := Nowy;
        end;

    end;

  Wsk := Nowy;

end;

function Szukaj(v: Integer): Integer;
var
  i: Integer;
begin

  Cofnij;
  i := 1;

  while (Wsk^.V <> v) and (Wsk^.Next <> nil)  do
    begin
      Wsk := Wsk^.Next;
      Inc(i);
    end;

  if Wsk^.Next = nil then
    Szukaj := -1
  else
    Szukaj := i;

end;

procedure Usun(p: Integer);
var
  Buf: PLista;
begin

  Cofnij;
  Przesun(p);

  Buf := Wsk;

  Wsk := Buf^.Prev;
  Wsk^.Next := Buf^.Next;
  Wsk := Buf^.Next;
  Wsk^.Prev := Buf^.Prev;

  Dispose(Buf);

end;

procedure Wypisz();
begin

  Cofnij;
  while Wsk^.Next <> nil do
    begin
      Write(Wsk^.v, #9);
      Wsk := Wsk^.Next;
    end;
  Write(Wsk^.v, #9);
  Writeln;

end;

var
  i: Integer;
  Pos: Integer;
begin

  Randomize;
  for i := 1 to 20 do
    Dodaj(Random(20) + 1, i);
  Wypisz;

  Writeln('Usuniemy elementy nr: 2, 5, 15');
  Usun(2);
  Usun(5);
  Usun(15);
  Wypisz;
  Writeln;

  Writeln('Dodamy elemnt 3 na pozycji 9');
  Dodaj(3, 8);
  Wypisz;
  Writeln;

  Writeln('Dodamy elemnt 16 na koncu listy');
  Dodaj(16, 99);
  Writeln('Dodamy elemnt 24 na poczatku listy');
  Dodaj(24, 1);
  Wypisz;
  Writeln;

  Writeln('Element 3 jest na pozycji: ', Szukaj(3));
  Pos := Szukaj(18);
  if Pos < 0 then
    Writeln('Element 18 nie zostal odnaleziony')
  else
    Writeln('Element 18 jest na pozycji: ', Pos);

  Writeln('Element 3 ma wartos: ', Czytaj(3));
  Writeln('Element 8 ma wartos: ', Czytaj(8));
  Writeln('Element 10 ma wartos: ', Czytaj(10));

end.