program pierw;
{$APPTYPE CONSOLE}

const
  Epsilon = 0.0000001;
var
  A, B, S, X: Extended;

begin
  Write('Podaj x:');
  Readln(X);

  A := X;
  B := 1;
  S := 0;

  while B > Epsilon do
    begin
      B := 0.5 * B;
      if Sqr(A) >= 2 then
        begin
          A := 0.5 * Sqr(A);
          S := S + B;
        end
      else
        A := Sqr(A);
    end;

  Writeln(S:0:10);
  Readln;
  
end.
