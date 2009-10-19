program zad16;

procedure Slowo(x: Integer);
const
  Tab : array[1..3] of char = ('1', '2', '3');
var
  i: Integer;
begin

  for i := 1 to x do
    Write(Tab[i]);

end;

procedure Tworz(n: Integer);
var
  i: Integer;
begin

  for i := 1 to n div 3 do
    Slowo(3);

  Slowo(n mod 3);

end;

var
  n: Integer;
begin

  Readln(n);
  Tworz(n);
  Writeln;

end.
