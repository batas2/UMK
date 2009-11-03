program BST;

{$APPTYPE CONSOLE}

uses Math;

type
  PRec = ^TRec;
  TRec = packed record
    Nast, Poprz: PRec;
    W: Integer;
  end;

  TTab = array of Integer;

{- - - - - - - - - - - - POCZATEK PROCEDUR DOTYCZACYCH BST - - - - - - - - - - - -}

{
  Procedura dodajaca element do drzewa bst
  Wsk -> Wskaznik na wezel od ktorego zaczynamy procedure
  V -> wartosc ktora chcemy dodac
}
procedure BSTAdd(var Wsk: PRec; V: Integer);
begin

  if Wsk = nil then //Jesli wskaznik jest nil, tzn ze doszlismy do liscia drzewa lub drzewo bylo puste
    begin
      New(Wsk);
      Wsk^.W := V;
      Wsk^.Poprz := nil;
      Wsk^.Nast := nil;
    end
  else
    begin
      if V > Wsk^.W then
      {W zaleznosci czy dana wartosc jest wieksza od klucza aktualnie
       przegladanego wezla, przechodzimy do prawego syna, jesli nie przechodzimy
       do lewego syna, powtarzamy ta czynnosc az dojdziemy do liscia}
        BSTAdd(Wsk^.Nast, V)
      else
        BSTAdd(Wsk^.Poprz, V);
    end;

end;

{
  Procedura wypisujaca wartosci wezlow, w kolejnosc Lewy syn, Klucz, Prawy syn
  Wsk -> Wskaznik na wezel od ktorego zaczynamy procedure
}
procedure BSTInOrder(Wsk: PRec);
begin

  if Wsk <> nil then
    begin
      BSTInOrder(Wsk^.Poprz);
      Write(Wsk^.W, ' ');
      BSTInOrder(Wsk^.Nast);
    end;

end;

{
  Procedura wypisujaca wartosci wezlow, w kolejnosc Klucz, Lewy syn, Prawy syn
  Wsk -> Wskaznik na wezel od ktorego zaczynamy procedure
}
procedure BSTPreOrder(Wsk: PRec);
begin

  if Wsk <> nil then
    begin
      Write(Wsk^.W, ' ');
      BSTPreOrder(Wsk^.Poprz);
      BSTPreOrder(Wsk^.Nast);
    end;

end;

{
  Procedura wypisujaca wartosci wezlow, w kolejnosc Lewy syn, Prawy syn, Klucz
  Wsk -> Wskaznik na wezel od ktorego zaczynamy procedure
}
procedure BSTPostOrder(Wsk: PRec);
begin

  if Wsk <> nil then
    begin
      BSTPostOrder(Wsk^.Poprz);
      BSTPostOrder(Wsk^.Nast);
      Write(Wsk^.W, ' ');
    end;

end;

{
  Procedura wyszukujaca wezel o danym kluczu, oraz jego rodzica
  Wsk -> Wskaznik na wezel od ktorego zaczynamy procedure
  Found -> Procedura zmieni ten wskaznik na wskaznik wezla o kluczu V
  Ojciec -> Procedura zmieni ten wskaznik na wskiaznik ojca wezla o klucz V
}
procedure BSTSearch(var Wsk, Found, Ojciec: PRec; V: Integer);
begin

  if Wsk <> nil then
    begin
      if Wsk^.W <> V then //Jesli klucz wezla jest rozny od danej wartosci...
        begin
          if V < Wsk^.W then
          {... jesli klucz wezla jest mniejszy od danej wartosci przechodzimy do
           lewego poddrzewa tego wezla, w przeciwnym wypadku do prawgo}
            BSTSearch(Wsk^.Poprz, Found, Ojciec, V)
          else
            BSTSearch(Wsk^.Nast, Found, Ojciec, V);
        end
      else
        Found := Wsk;

      {Dzieki powrotowi z rekurencji ustalimy ojca znalezionego wezla}
      if ((Wsk^.Poprz) <> nil) and ((Wsk^.Poprz)^.W = V) then
        Ojciec := Wsk;

      if ((Wsk^.Nast) <> nil) and ((Wsk^.Nast)^.W = V) then
        Ojciec := Wsk;

    end;

end;

{
  Funkcja zwracajaca wskaznik na wezel o najmniejszej wartosci w poddrzewie wezla
  na ktory wskazuje wskaznik Wsk
  Wsk -> Wskaznik na wezel od ktorego zaczynamy procedure
}
function BSTMin(Wsk: PRec): PRec;
begin

  while Wsk^.Poprz <> nil do
    Wsk := Wsk^.Poprz;

  BSTMin := Wsk;

end;

{
  Funkcja zwracajaca wskaznik na wezel o najwiekszej wartosci w poddrzewie wezla
  na ktory wskazuje wskaznik Wsk
  Wsk -> Wskaznik na wezel od ktorego zaczynamy procedure
}
function BSTMax(Wsk: PRec): PRec;
begin

  while Wsk^.Nast <> nil do
    Wsk := Wsk^.Nast;

  BSTMax := Wsk;

end;

{
  Procedure usuwajaca wezel (na ktory wskazuje Found) z drzewa
  Found -> Wskaznik na wezel ktory mamy usunac
  Ojciec -> Wskaznik na ojca wezla ktory mamy usunac
}
procedure BSTDelete(var Ojciec, Found: PRec);
var
  k: Byte;
  E, OjciecE: PRec;
begin

  if (Found^.Nast = nil) and (Found^.Poprz = nil) then
  {jesli wezel ktory mamy usunac nie ma zadnych potomkow, poprostu go usuwamy
   a w odpowiedni wskaznik ojsca przypisujemy nil}
    begin
      if Ojciec^.Nast = Found then
        Ojciec^.Nast := nil
      else
        Ojciec^.Poprz := nil;
      Dispose(Found);
    end
  else
    if (Found^.Nast <> nil) and (Found^.Poprz <> nil) then
    {jesli wezel ktory mamy usunac ma dwuch potomkow, wybieramy losowo
     czy zamiast wezla do usunieca, wstawimy wezel o najmniejszym kluczu
     z prawego poddrzewa usuwanego wezla, czy wezel o najwiekszym kluczu z lewego
     poddrzewa usuwanego klucza, wybieramy losowo aby drzewo sie nierozrastalo}
      begin
        k := Random(2);
        
        if k = 0 then
          E := BSTMin(Found^.Nast)
        else
          E := BSTMax(Found^.Poprz);

        BSTSearch(Found, E, OjciecE, E^.W);
        {szukamy ojca wezla o najmniejszym lub najwiekszym kluczu z poddrzewa
         wezla found}
        Found^.W := E^.W; //zamieniamy wartosc uwuwanego wezla z wezlem najmniejszym/najwiekszym

        BSTDelete(OjciecE, E); //usuwamy wezel
      end
    else //przechodzimy tutaj jesli usuwany wezel ma jednego przodka
      begin
        if Found^.Nast <> nil then
          Ojciec^.Nast := Found^.Nast
        else
          Ojciec^.Poprz := Found^.Poprz;
        Dispose(Found);
      end;

end;

{
  Procedura usuwajaca cale drzewo
  Wsk -> Wskaznik na wezel od ktorego zaczynamy procedure
}
procedure BSTFree(var Wsk: PRec);
begin

  if Wsk <> nil then
    begin
      BSTFree(Wsk^.Poprz);
      BSTFree(Wsk^.Nast);
      Dispose(Wsk);
      Wsk := nil;
    end;

end;

{- - - - - - - - - - - - KONIEC PROCEDUR DOTYCZACYCH BST - - - - - - - - - - - -}

{- - - - - - - - - - - - POCZATEK PROCEDUR POMOCZNICZYCH - - - - - - - - - - - -}

{
  Procedura zamienijaca wartosci dwuch danych
  A, B -> dane do zamiany
}
procedure Swap(var A, B: Integer);
var
  Tmp: Integer;
begin

  Tmp := A;
  A := B;
  B := Tmp;

end;

{
  Procedura wypelniajaca tablice losowymi wartosciami z przedzialu [Start; Range - 1]
  Tab -> Tablica
  Range, Start -> Ograniczenia przedzialu losowania liczb
}
procedure Losuj(var Tab: TTab; Range: Integer; Start: Integer);
var
  i: Integer;
begin

  Randomize;

  for i := 0 to Length(Tab) - 1 do
    Tab[i] := Random(Range) + Start;

end;

{
  Procedura wypisujaca tablice na standardowe wyjscie
  Tab -> Tablica
}
procedure Pokaz(var Tab: TTab);
var
  i: Integer;
begin

  for i := 0 to Length(Tab) - 1 do
    Write(Tab[i], ' ');

end;

{
  Procedura sortujaca tablice niemalejaco
  Tab -> Tablica
}
procedure QuickSort(var Tab: TTab; S, E: Integer); //S -> Start; E -> End;
var
  i, j: Integer;
  X: Integer;
begin

  i := S;
  j := E;
  X := Tab[ (S + E) div 2];

  repeat

    while Tab[i] < X do Inc(i);
    while Tab[j] > X do Dec(j);

    if i <= j then
      begin
        Swap(Tab[i], Tab[j]);
        Inc(i); Dec(j);
      end;

  until i > j;

  if S < j then
    QuickSort(Tab, S, j);
  if i < E then
    QuickSort(Tab, i, E);

end;

{ Porcedura tworzaca zrownowazone drzewo BST
  Wsk -> Wskaznik na korzen drzewa
  Tab -> Talibca wartosci
  S -> Poczatek tablicy
  E -> Koniec tablicy
}
procedure DodajDoBST(var Wsk: PRec; var Tab: TTab; S, E: Integer);
var
  P: Integer;
begin

  if S < E then
    begin
      P := Floor( (S + E) / 2 );
      BSTAdd(Wsk, Tab[P]);
      DodajDoBST(Wsk, Tab, S, P);
      DodajDoBST(Wsk, Tab, P + 1, E);
    end;

end;

var
  Tab: TTab;
  n, V: Integer;
  Wsk, Found, Ojciec: PRec;
begin

  Write('Podaj liczbe elementow n: ');
  Readln(n);

  SetLength(Tab, n);
  Losuj(Tab, n, 1);
  Ojciec := nil; Found := nil; Wsk := nil;

  Writeln; Writeln('Wylosowana tablica: ');
  Pokaz(Tab);

  QuickSort(Tab, 0, n - 1);

  Writeln; Writeln; Writeln('Posortowana tablica: ');
  Pokaz(Tab);

  DodajDoBST(Wsk, Tab, 0, n);
  Writeln; Writeln; Writeln('InOrder: ');
  BSTInOrder(Wsk);

{  Writeln; Writeln; Writeln('PreOrder: ');
  BSTPreOrder(Wsk);
}
{
  Writeln; Writeln; Writeln('PostOrder: ');
  BSTPostOrder(Wsk);
}
  Writeln; Writeln; Write('Podaj liczbe do usuniecia: ');
  Readln(V);

  BSTSearch(Wsk, Found, Ojciec, V);
  If Found = nil then
    begin Writeln; Writeln('Liczba ', V, ' nie zostala znaleziona.'); end
  else
    begin
      if Ojciec <> nil then
        BSTDelete(Ojciec, Found)
      else
        BSTDelete(Wsk, Found);

      Writeln; Writeln('InOrder: ');
      BSTInOrder(Wsk);

{      Writeln; Writeln('PreOrder: ');
      BSTPreOrder(Wsk);
}
{
      Writeln; Writeln('PostOrder: ');
      BSTPostOrder(Wsk);
}
    end;


  BSTFree(Wsk);
  Readln;

end.