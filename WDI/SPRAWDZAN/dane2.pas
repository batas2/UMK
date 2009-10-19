program dane;
var 
	f: file of integer;
	i:integer;
	a:integer;

begin
	assign(f,'dane2.in');
	reset(f);
	while not eof(f) do	
		begin
			read(f,a);
			writeln(a);
		end;
	close(f);
end.



