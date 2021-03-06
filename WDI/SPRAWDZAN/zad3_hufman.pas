program kody_hufman;

type
	{w�ze� drzewa}
	wwezel=^wezel;
	wezel=record
		czestosc:integer; {dane to cz�sto�� znaku oraz znak}
		znak:char;
		lewe,prawe:wwezel; {dowi�zanie do prawego i lewego poddrzewa}
	end;

	{element listy uporz�dkowanej}
	welement=^element;
	element=record
		dane:wwezel; {dane - wska�nik na w�ze� drzewa (korze�)}
		nastepny:welement; {dowi�zanie do nast�pnego elementu}
	end;



var
       kod:record {kod znaku}
		napis:array [1..255] of char; {kod znaku - ci�g zank�w (0 lub 1)}
		dlugosc:integer; {d�ugo�� kodu}
	end;

procedure wstaw(var poczatek:welement;d:wwezel);
var
tmp, nowy,buf:welement;
begin
tmp := poczatek;
new(nowy);
nowy^.dane := d;
nowy^.nastepny := nil;
if tmp = nil then
  begin
    poczatek := nowy;
  end
else
  if tmp^.nastepny = nil then
    begin
      if poczatek^.dane^.czestosc <= d^.czestosc then
        poczatek^.nastepny := nowy
      else
        begin
          nowy^.nastepny := poczatek;
          poczatek := nowy;
        end;
    end
  else
  begin

        if d^.czestosc > tmp^.dane^.czestosc then
        begin
        while (tmp^.nastepny <> nil) and (d^.czestosc <= tmp^.nastepny^.dane^.czestosc) do
        begin
        writeln(tmp^.dane^.czestosc,' ',Integer(tmp^.nastepny));
        tmp := tmp^.nastepny;

        end;
        buf := tmp;
        tmp^.nastepny := nowy;
        nowy^.nastepny := buf^.nastepny;
        end
        else
        begin
        nowy^.nastepny := tmp;
        poczatek := nowy;
        end;
  end;
end;


{Procedura buduj_lista buduje pocz�tkow� liste drzewa wysoko�ci 0 kt�re w korzeniu maj� znaki i cz�sto�ci wyst�powania}
{Lista ta budowana jest przy pomocy procedury wstaw}
procedure buduj_lista(var poczatek:welement;cz:integer;zn:char);
var
	nowy:wwezel;
begin
	{tworzymy korze� drzewa i umieszczamy w nim dane}
	new(nowy);
	nowy^.czestosc:=cz;
	nowy^.znak:=zn;
	nowy^.lewe:=NIL;
	nowy^.prawe:=NIL;

	{wstawiamy te dane do listy}
	wstaw(poczatek,nowy);
end;

procedure huffman(var poczatek:welement);
{Ta procedur� masz napisa�}
begin
while poczatek^.nastepny <> nil do
begin

end;

end;

{Procedura pomocnicza wupisuje dane pojedy�czego elementu}
procedure wypiszkod;
var
	i:integer;
begin

	for i:=1 to kod.dlugosc do
		write(kod.napis[i]);
end;

{Procedura wypisuje kody wszystkich znak�w na podstawie zbudowanego drzewa}
procedure kody(korzen:wwezel);
begin
	if korzen<>NIL then
		begin
			if korzen^.znak<>' ' then
				begin
					write(korzen^.znak,' ');
					wypiszkod;
					writeln;
				end;
			if korzen^.lewe <> NIL then
				begin
					kod.dlugosc:=kod.dlugosc+1;
					kod.napis[kod.dlugosc]:='0';
					kody(korzen^.lewe);
					kod.dlugosc:=kod.dlugosc-1;
				end;

			if korzen^.prawe <> NIL then
				begin
					kod.dlugosc:=kod.dlugosc+1;
					kod.napis[kod.dlugosc]:='1';
					kody(korzen^.prawe);
					kod.dlugosc:=kod.dlugosc-1;
				end;
		end
end;

{Procedury robi�ce porz�dek po wypisaniu kod�w, niszcz� drzewa i liste}

procedure drwal(var korzen:wwezel);
begin
	if korzen <> NIL then
		begin
			drwal(korzen^.lewe);
			drwal(korzen^.prawe);
			dispose(korzen);
		end;
end;

procedure niszczl(var poczatek:welement);
var
	tmp:welement;
begin
		while poczatek <> NIL do
		begin
			tmp:=poczatek;
			drwal(tmp^.dane);
			poczatek:=poczatek^.nastepny;
			dispose(tmp);
		end;
end;

procedure wypisz(var poczatek:welement);
var
buf:welement;
i:integer;
begin
buf :=poczatek;
for i:= 1 to 5 do
//while buf<>nil do
begin
writeln(buf^.dane^.czestosc);
buf := buf^.nastepny;
end;
end;

var lista:welement; {Faktyczna lista drzew}

BEGIN {poczatek programu}

lista:=NIL; {Na poczatku lista jest pusta}
kod.dlugosc:=0; {Dlugosc kodu jest rowna zero, kod jest pusty}

{Przyk�adowe dane}
buduj_lista(lista,10,'a');
buduj_lista(lista,5,'b');
buduj_lista(lista,10,'g');
buduj_lista(lista,11,'v');
buduj_lista(lista,2,'j');
buduj_lista(lista,5,'m');
buduj_lista(lista,7,'s');
//wypisz(lista);
huffman(lista); {Znajd� kody}
kody(lista^.dane); {Wypisz kody}
niszczl(lista); {Zr�b porz�dek}
readln;
END.


