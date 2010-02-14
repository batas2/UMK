program Huffman;

{$APPTYPE CONSOLE}
{
 Autor: Bartosz Fr¹ckowiak
 http://www.batas2.boo.pl/
}

uses
  Sysutils;

type
  PWezel = ^TWezel;
  TWezel = record
    V: Char;
    W: Byte;
    Prawy, Lewy: PWezel;
  end;

procedure Dodaj(var P: PWezel; V: Char; W: Byte; K: Boolean);
var
  Buf: PWezel;
begin

  New(Buf);
  Buf^.V := V;
  Buf^.W := W;
  Buf^.Prawy := nil;
  Buf^.Lewy := nil;

  if K then
    P^.Prawy := Buf
  else
    P^.Lewy := Buf;

end;

procedure Drzewo(var P: PWezel);
begin

  New(P);
  P^.V := '#';
  P^.W := 21;
  P^.Prawy := nil;
  P^.Lewy := nil;

  Dodaj(P, '#', 13, True);
  Dodaj(P^.Prawy, '#', 7, True);
  Dodaj(P^.Prawy, 'A', 5, False);
  Dodaj(P^.Prawy^.Prawy, '#', 4, True);
  Dodaj(P^.Prawy^.Prawy, 'I', 3, False);
  Dodaj(P^.Prawy^.Prawy^.Prawy, '#', 2, True);
  Dodaj(P^.Prawy^.Prawy^.Prawy, '#', 2, False);
  Dodaj(P^.Prawy^.Prawy^.Prawy^.Prawy, 'M', 1, True);
  Dodaj(P^.Prawy^.Prawy^.Prawy^.Prawy, 'L', 1, False);
  Dodaj(P^.Prawy^.Prawy^.Prawy^.Lewy, 'C', 1, True);
  Dodaj(P^.Prawy^.Prawy^.Prawy^.Lewy, 'T', 1, False);

  Dodaj(P, '#', 9, False);
  Dodaj(P^.Lewy, '#', 5, True);
  Dodaj(P^.Lewy, #32, 4, False);
  Dodaj(P^.Lewy^.Prawy, 'K', 3, True);
  Dodaj(P^.Lewy^.Prawy, 'O', 2, False);

end;

function Idz(var P: PWezel; B: Boolean): Char;
begin

  if B then
    P := P.Prawy
  else
    P := P.Lewy;

  Idz := P.V

end;

procedure InOrder(var P: PWezel; S: String);
begin

  if P <> nil then
    begin
      InOrder(P^.Lewy, S + '0');
      if P^.V <> '#' then
        Writeln(S, ' --> ', P^.V);
      InOrder(P^.Prawy, s + '1');
    end;

end;

function Dekoduj(var P: PWezel): String;
var
  F: File of Byte;
  B, Buf, i: Byte;
  W: PWezel;
  C: Char;
  Wynik: String;
begin

  Wynik := '';
  Assign(F, 'huffman');
  Reset(F);
  W := P;

  while not EOF(F) do
    begin
      Read(F, B);
      Buf := 1 shl 7;

      for i := 1 to 8 do
        begin

          C := Idz(W, (B and Buf) > 0);
          Buf := Buf shr 1;

          if C <> '#' then
            begin
              Wynik := Wynik + C;
              W := P;
            end;

        end;
    end;
    
  Dekoduj := Wynik;
  Close(F);

end;

var
  P: PWezel;
begin

  Drzewo(P);
  //InOrder(P, '');
  Writeln(Dekoduj(P));
  Readln;
  
end.