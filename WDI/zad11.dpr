program zad11;

{$APPTYPE CONSOLE}

uses
  SysUtils;

function wiesniak(a: Integer; b: Real): Real;
type
  TRec = record
    a: Integer;
    b: Real;
  end;
var
  Tab: array of TRec;
  i: Integer;
  wynik: Real;
begin

  SetLength(Tab, 1);
  while a >= 1 do
    begin
      Tab[Length(Tab) - 1].b := b;
      Tab[Length(Tab) - 1].a := a;
      a := a div 2;
      b := b * 2;
      SetLength(Tab, Length(Tab) + 1);
    end;

  wynik := 0;
  for i := 0 to Length(Tab) - 1 do
    if Tab[i].a mod 2 = 1 then
      wynik := wynik + Tab[i].b;

  wiesniak := wynik;
    
end;

procedure Licz;
var
  fIn, fOut: Text;
  a: Integer;
  b: Real;
begin

  Assign(fIn, 'in.txt');
  Assign(fOut, 'out.txt');

  Reset(fIn);
  Rewrite(fOut);

  while not EOF(fIn) do
    begin
      Read(fIn, a);
      Read(fIn, b);
      Readln(fIn);
      Writeln(fOut, wiesniak(a, b):0:2);
    end;

  Close(fIn);
  Close(fOut);

end;

begin

  Licz;

end.
