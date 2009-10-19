program Huffman;
{BARTOSZ FRACKOWIAK}
{
//Przykladowy program zamieniajacy tekst "ALA MA KOTA I KOCIAKI" na ciag
//binarny odpowiadajcy wynikowi algorytmu Huffmana
program Huffman_Koduj;

var
  Tab: array[char] of string;
  F: File of Byte;
  i, j, n: Integer;
  b, buf: Byte;
  s: String;
begin
  Assign(F, 'huffman');
  Rewrite(F);

  //Tablica kodow liter po zastosowaniu algorytmu Huffmana do tekstu "ALA MA KOTA I KOCIAKI"
  Tab['L'] := '11110';
  Tab['M'] := '11111';
  Tab['T'] := '11100';
  Tab['C'] := '11101';
  Tab['O'] := '010';
  Tab['K'] := '011';
  Tab['I'] := '110';
  Tab[#32] := '00';
  Tab['A'] := '10';

  s := Tab['A'] + Tab['L'] + Tab['A'] + Tab[#32] + Tab['M'] + Tab['A'] + Tab[#32] +
       Tab['K'] + Tab['O'] + Tab['T'] + Tab['A'] + Tab[#32] + Tab['I'] + Tab[#32] +
       Tab['K'] + Tab['O'] + Tab['C'] + Tab['I'] + Tab['A'] + Tab['K'] + Tab['I'];


  n := Length(s) div 8;
  for i := 0 to n - 1 do
    begin

      //Petla odczytuje po koleji porcje bitow o dlugosci 8,
      //pod zmienna buf podstawiamy jedynke przesunieta binarnie o
      //siedem pozycji w lewo co daje nam wartosc 128.
      //Nastepnie jesli w zakodowanym ciagu znakow na pozycji
      //i * 8 + j wystepuje 1, to dzieki operacji logicznej or w zmiennej b
      //zapalamy bit na 8 pozycji oraz zmienna buf przesuwamy binarnie
      //o jedna pozycje w prawo co daje 64, postepujemy tak 8 razy.
      //Dzieki temu zmienna b typu Byte w reprezentacji binarnej jest
      //identyczna jak odczytana porcja 8 bitow z zakodowanego ciagu.
      //W przypadku gdy zakodowany binarny ciag nie jest dlugosci
      //bedacej wielokrotnoscia 8, zmienna B typu byte jest uzupelniana
      //zerami na koncu.

      b := 0;
      buf := 1 shl 7;

      for j := 1 to 8 do
        begin
          if s[ i * 8 + j] = '1' then
            b := b or buf;
          buf := buf shr 1;
        end;

      Write(F, b);
    end;
  Close(f);

end.

}

type
  PWezel = ^TWezel;
  TWezel = record
    V: Char;
    Prawy, Lewy: PWezel;
  end;

{
  procedure dodajaca wezel do drzewa jako syn
  wezla P
  P - Wskaznik na wezel do ktorego ma zostatac dodany syn
  V - Klucz syna; # -> jesli syn jest wezelem w drzewie
      jedna z liter kodowanego tekstu jesli syn jest lisciem
      w drzewie
  K - True -> Syn bedzie prawym synem wezla P
      False -> Syn bedzie lewym synem wezla P
}
procedure Dodaj(var P: PWezel; V: Char; K: Boolean);
var
  Buf: PWezel;
begin

  New(Buf);
  Buf^.V := V;
  Buf^.Prawy := nil;
  Buf^.Lewy := nil;

  if K then
    P^.Prawy := Buf
  else
    P^.Lewy := Buf;

end;

{
  Procedura generujaca na sztywno drzewo, generowane
  przez algorytm Huffmana na zdaniu
  "ALA MA KOTA I KOCIAKI"
  Tablica czestosci wystepowania liter
  A Spacja I K O L M T C
  5   4    3 3 2 1 1 1 1
}
procedure Drzewo(var P: PWezel);
begin

  New(P);
  P^.V := '#';
  P^.Prawy := nil;
  P^.Lewy := nil;

  Dodaj(P, '#', True);
  Dodaj(P^.Prawy, '#', True);
  Dodaj(P^.Prawy, 'A', False);
  Dodaj(P^.Prawy^.Prawy, '#', True);
  Dodaj(P^.Prawy^.Prawy, 'I', False);
  Dodaj(P^.Prawy^.Prawy^.Prawy, '#', True);
  Dodaj(P^.Prawy^.Prawy^.Prawy, '#', False);
  Dodaj(P^.Prawy^.Prawy^.Prawy^.Prawy, 'M', True);
  Dodaj(P^.Prawy^.Prawy^.Prawy^.Prawy, 'L', False);
  Dodaj(P^.Prawy^.Prawy^.Prawy^.Lewy, 'C', True);
  Dodaj(P^.Prawy^.Prawy^.Prawy^.Lewy, 'T', False);

  Dodaj(P, '#', False);
  Dodaj(P^.Lewy, '#', True);
  Dodaj(P^.Lewy, #32, False);
  Dodaj(P^.Lewy^.Prawy, 'K', True);
  Dodaj(P^.Lewy^.Prawy, 'O', False);

end;

{
  Funkcja przechodzi do syna wezla P
  oraz zwraca klucz syna wezla P
  P - wskaznik na wezel w drzewie
  B - wartosc okreslajaca, w ktora strone
      nalezy sie przemiescic w drzewie,
      True -> Prawo; False -> Lewo
}
function Idz(var P: PWezel; B: Boolean): Char;
begin

  if B then
    P := P.Prawy
  else
    P := P.Lewy;

  Idz := P.V

end;


{
  Procedura przechodzaca drzewo metoda inorder
  oraz wypisujaca kody liter po zastosowanu algorytmu
  Huffmana
  P -> Wskaznik na korzen drzewa
  S -> Zmienna pomocznicza, potrzebna do poprawnego
       okreslenia kodu litery poprzez rekurenje,
       zmienna powinna byc pusta podcza pierwszego
       wywolania funkcji
}
{
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
}

{
  Procedura dekodujaca plik typowany, pojedyncza struktura
  tego pliku jest zmienna typu Byte, zapisywana przez kompilator
  na 8 bitach, czyli z czytuje porcje po 8 bitow z pliku z
  zakodowanym ciagiem.

  W przypadku gdy dlugosc (liczona w bitach) zakodowanego ciagu
  binarnego nie jest wielokrotnosci 8, ciag ten powinien byc
  uzupelniony samymi zerami aby jego dlugosc byla wielokrotnoscia 8

  W jezyku pascal zmienne ktore zajmuja najmniej miejsca w pamieci
  sa to zmienna Byte i Char, one domyslnie maja dlugosci 8 bitow

  Dla przykladu:
  przykladowy zakodowany binarny ciag o dlugosci roznej niz wielokrotnosc 8

  10101010 | 1010
  jesli 8 bitow bedziemy zapamietywac w zmiennej A typu Byte
  zmienna powinna przyjmowac wartosci

  1)
  A = 10101010(2) = 170(10), ta wartosc powinna byc w pliku

  2)
  A = 10100000(2) = 160(10), ta wartosc powinna byc w pliku

  Poniewaz w pascalu najmniejsze type maja po 8 bitow, nie jest
  mozliwym zapisanie do pliku ciagu bitow reprezentujacych zakodowany
  ciag binarny o dlugosci nie bedacej wielokrotnosci 8 (liczonej w bitach)

  Nalezy tylko zwrocic uwaga aby jak w przypadku drugim ciag
  1010 zapisac do pliku jako 10100000 a nie 00001010.

  P -> Wskaznik na korzen drzewa
 }
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

      {Pod zmienna buf podstawiamy jedynke przesunieta binarnie o
       siedem pozycji w lewo co daje nam wartosc 128}

      for i := 1 to 8 do
        begin

          {Jesli wynik operacji logicznej and na zmiennej
           B (zczytana porcja bitow z pliku) oraz Buf bedzie
           wiekszy od zera, znaczy to ze na i-tej pozycji w ciagu
           zczytanych bitow znajduje sie 1, jesli rowny zero znaczy to ze
           na i-tej pozycji w tym ciagu jest 0. Nastepnie przesuwam zmienna
           buf operatorem binarnym przesuniecia w prawo o jedna pozycje.}

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

end.