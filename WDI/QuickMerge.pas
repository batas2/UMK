procedure QucikSort(var Tab: TTab; Left, Right: Integer);
var
  i, j, Buf: Integer;
  Pivot: Integer;
begin

  Buf := 0;

  if Left < Right then
    begin
      Pivot := Tab[(random(Right - Left) + Left + 1)];

      i := Left - 1;
      j := Right + 1;

      while i < j do
        begin
          repeat Inc(i) until Pivot <= Tab[i];
          repeat Dec(j) until Pivot >= Tab[j];

          Buf := Tab[i]; Tab[i] := Tab[j]; Tab[j] := Buf;
        end;
      Tab[j] := Tab[i]; Tab[i] := Buf;

      QucikSort(Tab, Left, i - 1);
      QucikSort(Tab, i, Right);
    end;

end;

procedure Merge(var Tab: TTab; l, q, p: Integer);
var
  i,  j,  k,  n1,  n2: Integer;
  LL, PP: TTab;
begin

  n1 := q - l + 1;
  n2 := p - q;

  for i := 1 to n1 do LL[i] := a[l - 1 + i];
  for j := 1 to n2 do PP[j] := a[q + j];

  LL[n1 + 1] := 1000; {wartownik}
  PP[n2 + 1] := 1000; {wartownik}

  i := 1; j := 1;
  for k := l to p do
    if (LL[i] < PP[j]) then
      begin
        a[k] := LL[i];
        Inc(i);
      end
    else
      begin
        a[k] := PP[j];
        Inc(j);
      end ;

end;{merge}

procedure MergeSort(var Tab: TTab; l, p: Integer);  {sortuj zakres  [l, p]}
var
  q: Integer;
begin
  if l < p then
    begin
      q :=  (l + p) div 2;
      MergeSort(a, l, q);
      MergeSort(a, q + 1, p);
      Merge(a, l, q, p);
    end
end;