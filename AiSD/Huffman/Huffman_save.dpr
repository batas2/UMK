program Huffman_save;
{
 Autor: Bartosz Fr¹ckowiak
 http://www.batas2.boo.pl/
}

{$APPTYPE CONSOLE}

var
  Tab: array[char] of string;
  F: File of Byte;
  i, j, n: Integer;
  b, buf: Byte;
  s: String;
begin
  Assign(F, 'huffman');
  Rewrite(F);

  Tab['L'] := '11110';
  Tab['M'] := '11111';
  Tab['T'] := '11100';
  Tab['C'] := '11101';
  Tab['O'] := '010';
  Tab['K'] := '011';
  Tab['I'] := '110';
  Tab[#32] := '00';
  Tab['A'] := '10';

  s := Tab['A'] + Tab['L'] + Tab['A'] + Tab[#32] + Tab['M'] + Tab['A'] + Tab[#32] +
       Tab['K'] + Tab['O'] + Tab['T'] + Tab['A'] + Tab[#32] + Tab['I'] + Tab[#32] +
       Tab['K'] + Tab['O'] + Tab['C'] + Tab['I'] + Tab['A'] + Tab['K'] + Tab['I'];


  n := Length(s) div 8;
  for i := 0 to n - 1 do
    begin

      b := 0;
      buf := 1 shl 7;
      
      for j := 1 to 8 do
        begin
          if s[ i * 8 + j] = '1' then
            b := b or buf;
          buf := buf shr 1;
        end;
        
      Write(F, b);
    end;
  Close(f);

end.
