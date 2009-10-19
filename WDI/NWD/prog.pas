program prog;

type
  TRec = record
  a,b, nwd:Integer;
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

function najwiekszy(s: Integer; var Tab: TTab): Integer;
var
  i, max: Integer;
begin

  max := Tab[s].nwd;
  najwiekszy := s;

  for i := s - 1 downto 0 do
    if tab[i].nwd > max then
	begin
	  max := tab[i].nwd;
	  najwiekszy := i;
	end;

end;

procedure sortuj(var Tab: TTab);
var
  i : Integer;
begin

  for i := Length(Tab) - 2 downto 1 do
    zamien(Tab[i], Tab[najwiekszy(i, Tab)]);

end;

function nwd(a,b:integer):integer;
begin
while a<>b do
	begin
	if a > b then a:=a-b else b:=b-a;
	end;
  nwd := a;

end;


procedure licz(var Tab:TTab);
var
  in1, in2, out1: Text;
  i:integer;
begin
Assign(in1, 'dane1.in');
assign(in2, 'dane2.in');
assign(out1, 'wynik.out');
reset(in1);
reset(in2);
rewrite(out1);

  SetLength(Tab, 1);
  i := 0;
  while (not EOF(in1)) and (not EOF(in2)) do
 	begin

         Readln(in1, Tab[i].a);
         Readln(in2, Tab[i].b);

	 Tab[i].nwd := nwd(Tab[i].a, Tab[i].b);
         SetLength(Tab, Length(Tab) + 1);
         Inc(i);
	end;

sortuj(tab);

for i := 0 to Length(Tab) - 2 do
   Writeln(out1, 'NWD(', Tab[i].a, ',', Tab[i].b,')=',tab[i].nwd);

close(in1);
close(in2);
close(out1);
end;

var
  Tab: TTab;
begin
licz(tab);
end.

