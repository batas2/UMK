program pNWD;

{$APPTYPE CONSOLE}

type
  TRec = record
    a, b, NWD: Integer;
  end;
  TTab = array of TRec;

procedure zamien(var a: TRec; var b: TRec);
var
  buf : TRec;
begin

  buf := a;
  a := b;
  b := buf;

end;

function Najwiekszy(s: Integer; var Tab: TTab): Integer;
var
  i, max: Integer;
begin

  max := Tab[s].NWD;
  Najwiekszy := s;

  for i := s - 1 downto 0 do
    if Tab[i].NWD > max then
	    begin
	      max := Tab[i].NWD;
	      Najwiekszy := i;
	    end;

end;

procedure Sortuj(var Tab: TTab);
var
  i : Integer;
begin

  for i := Length(Tab) - 2 downto 1 do
    Zamien(Tab[i], Tab[Najwiekszy(i, Tab)]);

end;

function NWD(a, b : Integer) :Integer;
begin

  while a<>b do
	  begin
    	if a > b then
        a := a - b
      else
        b := b - a;
	end;

  NWD := a;

end;


procedure Licz(var Tab: TTab);
var
  fIn1, fIn2, fOut: Text;
  i:integer;
begin

  Assign(fIn1, 'dane1.in');
  Assign(fIn2, 'dane2.in');
  Assign(fOut, 'wynik.out');

  Reset(fIn1);
  Reset(fIn2);
  Rewrite(fOut);

  SetLength(Tab, 1);
  i := 0;
  while (not EOF(fIn1)) and (not EOF(fIn2)) do
   	begin
      Readln(fIn1, Tab[i].a);
      Readln(fIn2, Tab[i].b);

      Tab[i].NWD := NWD(Tab[i].a, Tab[i].b);
      SetLength(Tab, Length(Tab) + 1);
      Inc(i);
	end;

  Sortuj(Tab);

  for i := 0 to Length(Tab) - 2 do
    Writeln(fOut, 'NWD(', Tab[i].a, ',', Tab[i].b,') = ', #9, Tab[i].NWD);

  Close(fIn1);
  Close(fIn2);
  Close(fOut);
  
end;

var
  Tab: TTab;
begin

  Licz(Tab);
  
end.

