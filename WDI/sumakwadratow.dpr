program sumakwadratow;

{$APPTYPE CONSOLE}

uses
  SysUtils, Math;

function spr(n: Integer; var a,b: Integer):Boolean;
var
  i: Integer;
  buf: Extended;
begin

  spr := False;
  buf := 0.1;
  i := 1;
  
  while (i <= Floor(Sqrt(n))) and (Frac(buf) <> 0) do
    begin
      buf := sqrt(n - sqr(i));
      Inc(i);
    end;

  if Frac(buf) = 0 then
    begin
      a := i;
      b := Round(buf);
      spr := True;
    end;

end;

var
  a, b, n: Integer;
  w: Boolean;
begin
  Readln(n);
  w := spr(n, a, b);
  if w then
    Writeln(a, '^2 + ', b, '^2 = ', n, ' => TAK')
  else
    Writeln('NIE');
  Readln;
end.
 