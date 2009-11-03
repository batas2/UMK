program zad16licz;

{$APPTYPE CONSOLE}

uses
  SysUtils;

const
  Tab: Array[1..12] of String = ('ABA', 'ACA', 'BAB', 'BCB', 'CAC', 'CBC', 'ABC', 'ACB', 'BCA', 'BAC', 'CAB', 'CBA');

var
  Fin, Fout: Text;
  S, Sa: String;
  i: Integer;
begin

  Assign(Fin, 'wynik.txt');
  Assign(Fout, 'Liczby.txt');

  Reset(Fin);
  Rewrite(Fout);

  Readln(Fin, S);

  while Length(S) > 3 do
    begin
      Sa := Copy(S, 1, 3);
      i := 1;
      while Tab[i] <> Sa do
        Inc(i);
      Write(FOut, #9, i);
      Delete(S, 1, 3);
    end;

  Close(FIn);
  Close(FOut);
end.
