program sito;
var
  tab: array of Boolean;
  n: Integer;
  i, j: Integer;
begin

  Write('Podaj n:');
  ReadLn(n);

  SetLength(Tab, n + 1);
  for i := 2 to n do
    Tab[i] := True; //Pocz¹tkowo wszystkie liczby sa pierwsze

  for i := 2 to Round(Sqrt(n)) + 1 do
    begin
      j := 2;
      while i * j <= n do
        begin
          tab[i * j] := False;
          {Ta liczba napewno nie jest pierwsza poniewaz da sie
           zapisac w postaci x = i * j dla i,j <> 1 AND i,j <> x}
          Inc(j)
        end;
    end;

  for i := 2 to n do
    if Tab[i] then
      writeln(i);

end.