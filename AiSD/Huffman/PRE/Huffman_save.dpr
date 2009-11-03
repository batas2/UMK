program Huffman_save;

{$APPTYPE CONSOLE}
  
function Str2Bin(V: Char): Byte;
begin

  if V = '1' then
    Str2Bin := 1
  else
    Str2Bin := 0;

end;

function Bin2Dec(V: String): Byte;
var
  i, w: Byte;
begin

  w := Str2Bin(V[1]);
  for i := 2 to 8 do
    w := w * 2 + Str2Bin(V[i]);

  Bin2Dec := w;

end;

var
  Tab: array[char] of string;
  F: File of Byte;
  i, j, n: Integer;
  b: Byte;
  s, buf: String;
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

  for i := 1 to 8 - (Length(s) mod 8) do
    s := s + '0';

  n := Length(s) div 8;
  for i := 1 to n do
    begin
      buf := '';
      for j := 1 to 8 do
        buf := buf + s[ (i - 1) * 8 + j];
      b := Bin2Dec(buf);
      write(f, b);
    end;
  close(f);

end.
