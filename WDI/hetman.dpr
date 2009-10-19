program osiemhetmanow(output);
{$APPTYPE CONSOLE}
{szuka rozwiazania problemu osmiu hetmanow}

var
  a: array[1..8] of boolean; {a[i] brak hetmana w i - tym wierszu}
  b: array[2..16] of boolean; {b[i] brak hetmana na i - tej przekatnej NE - SW}
  c: array[ - 7..7] of boolean;{c[i] brak hetmana na i - tej przekatnej NW - SE}
  x: array[1..8] of integer; {x[i] pozycja hetmana w i - tej kolumnie}

procedure wykresl(col, row: Integer; v: Boolean);
begin

  a[row] := v;
  b[col + row] := v;
  c[col - row] := v;

end;

procedure hetman(col: Integer; var q: Boolean);
var
  row: Integer;
begin {probuj}

  row := 0;
  repeat
    row := row  +  1;
    q :=  false; {zapoczatkuj ustawianie hetmana o numerze col}

    if (a[row] and b[col + row] and c[col - row]) then {jesli pozycja bezpieczna}
      begin {ustaw hetmana:}
        x[col] := row;
        wykresl(col, row, false);
        {"wykresl" wiersz, przekatna NE - SW i NW - SE}

        if col < 8 then
          begin
            hetman(col + 1, q); {rekurencja!  -  ustaw nastepnego hetmana}
            if not q then {proba nieudana}
              wykresl(col, row, true); {usun hetmana}
          end
        else
          q := true {czyli i=8 tj. ustawiono wszystkie hetmany}
      end
  until q {proba udana} or (row = 8)
  {lub nie ma wiecej bezpiecznych pozycji w col - tej kolumnie}
end {probuj};

var
  i: integer;
  q: boolean;
begin

  {Inicjuj szachownice: brak hetmanow na szachownicy}
  for i := 1 to 8 do a[i] := true;
  for i := 2 to 16 do b[i] := true;
  for i :=  - 7 to 7 do c[i] := true;
  hetman(1, q);

{wyswietl rozwiazanie}
  if q then
    for i := 1 to 8 do
      write(x[i]:4);
  writeln;
  readln

end.