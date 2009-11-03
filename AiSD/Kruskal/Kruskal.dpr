program Kruskal;

{$APPTYPE CONSOLE}

Type
  PKrawendz = ^TKrawendz;
  TKrawendz = record
    kWaga, kOd, kDo: Integer;
  end;

  PWierzcholek = ^TWierzcholek;
  TWierzcholek = record
    Etykieta: Integer;
    Nastepny: PWierzcholek;
  end;

  TWierzcholki = array of PWierzcholek;
  TKrawendzie = array of PKrawendz;

var Plik: Text;

procedure QucikSort(var Krawendz: TKrawendzie; Left, Right: Integer);
var
  i, j: Integer;
  Buf, Pivot: PKrawendz;
begin

  Buf := nil;

  if Left < Right then
    begin
      Pivot := Krawendz[(Random(Right - Left) + Left + 1)];

      i := Left - 1;
      j := Right + 1;

      while i < j do
        begin
          repeat Inc(i) until Pivot^.kWaga <= Krawendz[i]^.kWaga;
          repeat Dec(j) until Pivot^.kWaga >= Krawendz[j]^.kWaga;

          Buf := Krawendz[i]; Krawendz[i] := Krawendz[j]; Krawendz[j] := Buf;
        end;
      Krawendz[j] := Krawendz[i]; Krawendz[i] := Buf;

      QucikSort(Krawendz, Left, i - 1);
      QucikSort(Krawendz, i, Right);
    end;

end;

procedure Wczytaj(var Korzen, Lisc{, Drzewo}: TWierzcholki;
                  var Krawendz: TKrawendzie; n, m: Integer);
var
  i, vWaga, vOd, vDo: Integer;
begin

  SetLength(Korzen, n);
  SetLength(Lisc, n);
  {SetLength(Drzewo, n);}

  for i := 0 to n - 1 do
    begin
      {New(Drzewo[i]);
      Drzewo[i]^.Etykieta := i;
      Drzewo[i]^.Nastepny := nil;}
      New(Korzen[i]);
      Korzen[i]^.Etykieta := i;
      Korzen[i]^.Nastepny := nil;
      Lisc[i] := Korzen[i];
      //Korzen[i] := Drzewo[i];
    end;

  SetLength(Krawendz, m);
  for i := 0 to m - 1 do
    begin
      Readln(Plik, vOd, vDo, vWaga);
      New(Krawendz[i]);
      Krawendz[i]^.kWaga := vWaga;
      Krawendz[i]^.kOd := vOd;
      Krawendz[i]^.kDo := vDo;
    end;

end;

procedure Kraskal(var Korzen, Lisc, Drzewo: TWierzcholki;
                  var Krawendz: TKrawendzie; m: Integer);
var
  i: Integer;
  Buf: PWierzcholek;
begin

  for i := 0 to m - 1 do
    begin
      if Korzen[Krawendz[i]^.kOd] <> Korzen[Krawendz[i]^.kDo] then
        begin
          Lisc[Korzen[Krawendz[i].kOd]^.Etykieta]^.Nastepny := Korzen[Krawendz[i].kDo];
          Lisc[Korzen[Krawendz[i].kOd]^.Etykieta] := Lisc[Korzen[Krawendz[i].kDo]^.Etykieta];
          Writeln(Krawendz[i]^.kOd, ' -- ', Krawendz[i]^.kDo, ' : ', Krawendz[i]^.kWaga);
          Buf := Korzen[Krawendz[i].kDo];
          while Buf <> nil do
            begin
              Korzen[Buf^.Etykieta] := Korzen[Krawendz[i].kOd];
              Buf := Buf^.Nastepny;
            end;
        end;
    end;
    
end;

procedure WypiszKrawendz(var Krawendz: TKrawendzie);
var
  i, n: Integer;
begin

  n := Length(Krawendz) - 1;
  for i := 0 to n do
    Writeln(Krawendz[i]^.kOd, ' -- ', Krawendz[i]^.kDo, ' : ', Krawendz[i]^.kWaga);

end;

procedure WypiszDrzewo(var Korzen: TWierzcholki);
var
  i, n: Integer;
  Buf: PWierzcholek;
begin

  n := Length(Korzen) - 1;
  for i := 0 to n do
    begin
      if Korzen[i]^.Etykieta = i then
        begin
          Buf := Korzen[i];
          while Buf^.Nastepny <> nil do
            begin
              Write(Buf^.Etykieta, ' --> ');
              Buf := Buf^.Nastepny
            end;
          Writeln(Buf^.Etykieta);
        end;
    end;

end;

var
  n, m: Integer;
  Krawendz: TKrawendzie;
  Korzen, Lisc, Drzewo: TWierzcholki;
begin
  AssignFile(Plik, 'dane.in');
  Reset(Plik);
  Readln(Plik, n, m);
  Wczytaj(Korzen, Lisc,{ Drzewo,} Krawendz, n, m);
  QucikSort(Krawendz, 0, m - 1);
  //WypiszKrawendz(Krawendz);
    Writeln;
  Kraskal(Korzen, Lisc, Drzewo, Krawendz, m);
  WypiszDrzewo(Korzen);
  Closefile(Plik);
  Readln;
end.
