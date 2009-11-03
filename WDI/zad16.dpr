program zad16;

{$APPTYPE CONSOLE}

uses
  SysUtils, Math;

var
  Done: Boolean;
  Wynik: String;

function SprKwadrat(S: String): Boolean;
{Funkcja sprawdzajaca czy podane slowo zawiera w sobie podslowo ktore jest kwadratem.}
var
  sL, L, i: Integer;
  Sa, Sb: String;
  Wynik: Boolean;
begin

  Wynik := True;
  L := Length(S);

  if L > 2 then
    begin

      sL := L div 2; {Ogranicznik petli, wartoscia jego jest polowa dlugosc slowa
                      poniewaz zeby slowo bylo kwadratem musi byc postawci vv
                      czyli maksymalna dlugosc v jest rowna polowie dlugosci slowa}
      i := 2;

      while (i <= sL) and (Wynik) do {Petla sprawdza czy wystepuje w slowie podslowo kwadrat
                                      ,sprawdza od tylu lancucha poniewaz dodajemy na koncu
                                      kolejna literke alfabetu, najpierw bierze podslowo dlugosci
                                      2 (zmienna Sa) od konca lancucha odraz podslowo takze dlugosci
                                      2 ale od konca lancucha minus dlugosc zmienne Sa, nastepnie
                                      zwieksza wartosc i (dlugosc lancucha Sa i Sb w kazdym przebiegu petli)
                                      az i osiagnie wartosc sl lub lancuch Sa i Sb beda sobie rowne, tzn
                                      ze wystepuje slowo kwadrat}
        begin
          Sa := Copy(S, L - i + 1, i);
          Sb := Copy(S, L - (i * 2) + 1, i);
          if Sa = Sb then
            Wynik := False;
          Inc(i);
        end;
     end
  else
    if S[1] = S[2] then
      Wynik := False;

  SprKwadrat := Wynik;

end;

function Kwadrat(S: String; L: Integer): String; //S - Slowo; L - Liczba liter do osiagnieca porzadnej dlugosc slowa
{Funkcja wykorzystujaca rekurencje z nawrotami do wyznaczenia slowa od dlugosci n
bez zadnego podslowa kwadratu, diala na zasadzie "Prob i bledow". Na poczatku wywolywana
jest ze slowem dlugosc 1, nastepnie dodaje do slowa na inny znak z alfabetu, oraz sprawdza
czy podane tak slowo nie zawiera podslowa bedacego kwadratem, jesli zawiera rekurencja bedzie
sie cofac tak dlugo az slowo nie bedzie miala podslowa kwadratu, oraz dobierze nastepny znak z
alfabetu rozny od poprzedniego}
begin

  if (L <= 1) and (not Done) then
    begin
      Done := True;
      Wynik := S;
    end;

  If not Done then
  case S[Length(S)] of
  {W zaleznosci od ostatniej litery slowa S, sprawdzamy czy dodanie kolejnej
  innej litery nie powoduje wystapienia podslowa kwadratu w slowie S}
    'A':
      begin
        if SprKwadrat(S + 'B') Then
          Kwadrat(S + 'B', L - 1);
        if SprKwadrat(S + 'C') Then
          Kwadrat(S + 'C', L - 1);
      end;
    'B':
      begin
        if SprKwadrat(S + 'A') Then
          Kwadrat(S + 'A', L - 1);
        if SprKwadrat(S + 'C') Then
          Kwadrat(S + 'C', L - 1);
      end;
    'C':
      begin
        if SprKwadrat(S + 'A') Then
          Kwadrat(S + 'A', L - 1);
        if SprKwadrat(S + 'B') Then
          Kwadrat(S + 'B', L - 1);
      end;
  end;

end;

var
  n: Integer;
begin

  Done := False;
  Readln(n);
  Kwadrat('A', n);
  Writeln(Wynik);
  Readln;

end.
