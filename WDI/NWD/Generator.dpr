program gen;

{$APPTYPE CONSOLE}

const
  n = 100;
var
  F: array[1..2] of Text;
  i, j : integer;
begin

  Assign(F[1], 'dane1.in');
  Assign(F[2], 'dane2.in');

  Rewrite(F[1]);
  Rewrite(F[2]);

  Randomize;

  for j := 1 to 2 do
    for i := 1 to random(n) + 1 do
      Writeln(F[j], random(n) + 1);

  Close(F[1]);
  Close(F[2]);
  
end.
