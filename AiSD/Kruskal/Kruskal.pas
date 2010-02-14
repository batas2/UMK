program Kruskal_1;
{Bartosz Fr¹ckowiak, Algorytm Kruskala
 Zdecydowalem sie reprezentowac zbiory rozlaczane za pomoca list.}
{
 Autor: Bartosz Fr¹ckowiak
 http://www.batas2.boo.pl/
}

Type
  PKrawendz = ^TKrawendz;  //Rekord odpowiadajacy krawendzi
  TKrawendz = record
    kWaga, kOd, kDo: Integer;
  end;

  PWierzcholek = ^TWierzcholek;
  TWierzcholek = record //Rekord odpowiadaj¹cy jedenemu elementowi na liscie reprezentuj¹cej zbior
    Dlugosc: Integer;
    Etykieta: Integer;
    Nastepny: PWierzcholek;
  end;

  TWierzcholki = array of PWierzcholek;  //Tablica wskaznikow na rekordu elementow listy (zbioru)
  TKrawendzie = array of PKrawendz;  //Tablica wskaznikow na rekordy krawendzi

{
 Procedura sortowania szybkiego krawendzi w porzadku nierosnacym,
 sortuje tablice wskaznikow na rekordy poniewaz sortowanie tablicy rekordow
 byloby bardziej czasochlonne
 Krawendz -> Tablica Krawendzi, Lewy, Prawy -> Lewy i prawy zakres sortowanej tablice
}
procedure QucikSort(var Krawendz: TKrawendzie; Lewy, Prawy: Integer);
var
  i, j: Integer;
  Buf, Pivot: PKrawendz;
begin

  Buf := nil;

  if Lewy < Prawy then
    begin
      Pivot := Krawendz[(Random(Prawy - Lewy) + Lewy + 1)];

      i := Lewy - 1;
      j := Prawy + 1;

      while i < j do
        begin
          repeat Inc(i) until Pivot^.kWaga <= Krawendz[i]^.kWaga;
          repeat Dec(j) until Pivot^.kWaga >= Krawendz[j]^.kWaga;

          Buf := Krawendz[i]; Krawendz[i] := Krawendz[j]; Krawendz[j] := Buf;
        end;
      Krawendz[j] := Krawendz[i]; Krawendz[i] := Buf;

      QucikSort(Krawendz, Lewy, i - 1);
      QucikSort(Krawendz, i, Prawy);
    end;

end;

{
 Procedura Wczytujaca dane, oraz tworzaca zbiory zawierajace po 1 elemencie (makeset)
 Korzen -> tablica wskaznikow wskazujacuch na poczatki list (Pusta)
 Lisc -> tablica wskaznikow wskazujacych na konce list (Pusta)
 Krawendz -> tablica krawendzi (Pusta)
 n -> Ilosc wierzcholkow w grafie
 m -> ilosc krawendzi w grafie
}
procedure Wczytaj(var Korzen, Lisc: TWierzcholki;
                  var Krawendz: TKrawendzie; n, m: Integer);
var
  i, vWaga, vOd, vDo: Integer;
begin

  SetLength(Korzen, n);
  SetLength(Lisc, n);

  for i := 0 to n - 1 do {Petla tworzaca nowe 1 elementowe zbiory (makeset)}
    begin
      New(Korzen[i]);
      Korzen[i]^.Etykieta := i;
      Korzen[i]^.Nastepny := nil;
      Korzen[i]^.Dlugosc := 1;
      Lisc[i] := Korzen[i];
    end;

  SetLength(Krawendz, m);
  for i := 0 to m - 1 do
    begin
      Readln(vOd, vDo, vWaga);
      New(Krawendz[i]);
      Krawendz[i]^.kWaga := vWaga;
      Krawendz[i]^.kOd := vOd;
      Krawendz[i]^.kDo := vDo;
    end;

end;

{
 Procedura wykonujaca algorytm Kruskala
 Korzen -> tablica wskaznikow na poczatki list (reprezentantow zbiorow)
 Lisc -> tablica wskaznikow na konce list (na poczatku konce list wskaznuja na reprezentantow poniewaz zbiory sa 1 elementowe)
 Krawendz -> tablica krawendzi
 m -> liczba krawendzi
}
procedure Kraskal(var Korzen, Lisc: TWierzcholki;
                  var Krawendz: TKrawendzie; m: Integer);
var
  i, a, b: Integer;
  Buf: PWierzcholek;
begin

  for i := 0 to m - 1 do
    begin
      if Korzen[Krawendz[i]^.kOd] <> Korzen[Krawendz[i]^.kDo] then
      {Sprawdzamy czy wierzcholek rowny poczatkowni krawendzi lezy w tym samym zbiorze co
       wierzcholek odpowiadajacy koncowi krawendzi, za pomoca reprezentantow zbiorow (find_set)}
        begin
          //Poczatek operacji scalajacych listy (union)

            if Korzen[Krawendz[i]^.kOd]^.Dlugosc > Korzen[Krawendz[i]^.kDo]^.Dlugosc then
            //Sprawdzamy ktora lista jest krotsza aby dodac krotsza do dluzszej
              begin
                a := Krawendz[i]^.kOd; b := Krawendz[i]^.kDo;
              end else
              begin
                a := Krawendz[i]^.kDo; b := Krawendz[i]^.kOd;
              end;

          Lisc[Korzen[a]^.Etykieta]^.Nastepny := Korzen[b];
          //Koncowi dluzszej listy przypisujey poczatek krotszej
          Lisc[Korzen[a]^.Etykieta] := Lisc[Korzen[b]^.Etykieta];
          //Koniec dluzszej listy staje sie konce krotszej
          Inc(Korzen[a]^.Dlugosc, Korzen[b]^.Dlugosc);
          //Zwiekszam zmienna odpowiadajaca za dlugosc listy

          Writeln(Krawendz[i]^.kOd, ' -- ', Krawendz[i]^.kDo, ' : ', Krawendz[i]^.kWaga);

          //Kazdemu elementowi z list krotszej zmieniamy reprezentanta na reprezentanta listy dluzszej
          Buf := Korzen[b];
          while Buf <> nil do
            begin
              Korzen[Buf^.Etykieta] := Korzen[a];
              Buf := Buf^.Nastepny;
            end;
          //Koniec operacji scalajacych listy
        end;
    end;

end;

var
  n, m: Integer;
  Krawendz: TKrawendzie;
  Korzen, Lisc: TWierzcholki;
begin
  Readln(n, m);
  Wczytaj(Korzen, Lisc, Krawendz, n, m);
  QucikSort(Krawendz, 0, m - 1);
  Kraskal(Korzen, Lisc, Krawendz, m);
end.