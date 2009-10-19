program zad16;

{$APPTYPE CONSOLE}

var
  Max: Int64;
    
function SprKwadrat(S: String): Boolean;
var
  sL, L, i: Integer;
  Sa, Sb: String;
  Wynik: Boolean;
begin

  Wynik := True;
  L := Length(S);

  if L > 2 then
    begin

      sL := L div 2;
      i := 2;

      while (i <= sL) and (Wynik) do
        begin
          Sa := Copy(S, L - i + 1, i);
          Sb := Copy(S, L - (i * 2) + 1, i);
          if Sa = Sb then
            Wynik := False;
          Inc(i);
        end;
     end
  else
    if S[1] = S[2] then
      Wynik := False;

  SprKwadrat := Wynik;

end;

function Kwadrat(S: String): String;
var
  L: Integer;
begin

  L := Length(S);
  if L > Max then
    begin
      Max := L;
      Writeln(Max);
    end;

  case S[L] of
    'A':
      begin
        if SprKwadrat(S + 'B') Then
          Kwadrat(S + 'B');
        if SprKwadrat(S + 'C') Then
          Kwadrat(S + 'C');
      end;
    'B':
      begin
        if SprKwadrat(S + 'A') Then
          Kwadrat(S + 'A');
        if SprKwadrat(S + 'C') Then
          Kwadrat(S + 'C');
      end;
    'C':
      begin
        if SprKwadrat(S + 'A') Then
          Kwadrat(S + 'A');
        if SprKwadrat(S + 'B') Then
          Kwadrat(S + 'B');
      end;
  end;

end;

begin

  Kwadrat('A');
  
end.
