program Huffman;

{$APPTYPE CONSOLE}

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

function Dekoduj(var P: PWezel; S: String): String;
var
  W: String;
  i, n: Integer;
  B: PWezel;
begin

  W := '';
  i := 1;
  n := Length(S);

  while i <= n do
    begin

      B := P;
      while B^.V = '#' do
        begin
          if S[i] = '1' then
            B := B^.Prawy
          else
            B := B^.Lewy;
          Inc(i);
        end;

      W := W + B^.V;

    end;

  Dekoduj := W;

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

function Dec2Bin(V: Byte): String;
var
  W, S: String;
  B: Char;
  n, i: Integer;
begin

  W := '';
  while V <> 0 do
    begin
      W := W + IntToStr(V mod 2);
      V := V div 2;
    end;

  n := Length(W);
  for i := 1 to n div 2 do
    begin
      B := W[i];
      W[i] := W[n - i + 1];
      W[n - i + 1] := B;
    end;

  for i := 1 to 8 - Length(W) do
    S := S + '0';

  Dec2Bin := S + W;

end;

function Wczytaj: String;
var
  F: File of Byte;
  B: Byte;
  W: String;
begin

  W := '';
  Assign(F, 'huffman');
  Reset(F);

  while not EOF(F) do
    begin
      Read(F, B);
      W := W + Dec2Bin(B);
    end;

  Close(F);
  Wczytaj := W;

end;

var
  S: String;
  P: PWezel;
begin

  Drzewo(P);
  S := Wczytaj;
  //InOrder(P, S);
  Writeln(Dekoduj(P, S));
  ReadLn;

end.