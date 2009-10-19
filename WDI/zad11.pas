program zad11;


function wiesniak(a: Int64; b: Extended): Extended;
type
  TRec = record
    a: Int64;
    b: Extended;
  end;
var
  Tab: array of TRec;
  i: Integer;
  wynik: Extended;
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
  a: Int64;
  b: Extended;
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
      Writeln(fOut, wiesniak(a, b):0:4);
    end;

  Close(fIn);
  Close(fOut);

end;

begin

  Licz;

end.
