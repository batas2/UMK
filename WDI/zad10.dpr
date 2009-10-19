program zad10;

{$APPTYPE CONSOLE}

uses
  SysUtils, Math;

function palindrom(s: String):boolean;
var
  i: Integer;
begin

  palindrom := true;
  for i := 1 to Length(s) div 2 do
    if s[i] <> s[Length(s) - i + 1] then
      palindrom := false;

end;

function int2str(x: Integer): String;
var
  S: String;
  I: Integer;
begin

  i := 1;
  while x > 0 do
    begin
      SetLength(s, i);
      s[i] := Char((x mod 10) + 48);
      i := i + 1;
      x := x div 10;
    end;

  int2str := S;
  
end;

function odwroc(x: String): String;
var
  i: Integer;
  c: Char;
begin

  for i := 1 to Length(x) div 2 do
    begin
     c := x[i];
     x[i] := x[Length(x) - i + 1];
     x[Length(x) - i + 1] := c;
   end;

  odwroc := x;

end;

procedure licz(n: Integer);
var
  i: Integer;

begin

  for i := 4 to n do
    if palindrom(odwroc(int2str(i * i))) then
      Writeln(i, ' => ', i*i);

end;

var
  n: Integer;
begin

  Readln(n);
  licz(n);

end.
