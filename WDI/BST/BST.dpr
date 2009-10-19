program BST;

{$APPTYPE CONSOLE}

type
  PTree = ^TTree;
  TTree = record
    Value: Integer;
    Left, Right: PTree;
  end;

procedure BSTNew(var Wsk: PTree; V: Integer);
begin

  New(Wsk);
  Wsk^.Value := V;

end;

procedure BSTAddValue(Wsk: PTree; V: Integer);
var
  Done: Boolean;
  Buf: PTree;
begin

  Done := False;
  
  while not Done do
    begin

      if V < Wsk^.Value then
        begin
          if Wsk^.Left = nil then
            begin
              New(Buf);
              Buf^.Value := V;
              Done := True;
              Wsk^.Left := Buf;
            end
          else
            begin
//                  Buf := Wsk;
              Wsk := Wsk^.Left;
            end;
        end
      else
        begin
          if Wsk^.Right = nil then
            begin
              New(Buf);
              Buf^.Value := V;
              Done := True;
              Wsk^.Right := Buf;
            end
          else
            begin
              Wsk := Wsk^.Right;
            end;
        end;
  end;

end;

procedure BSTAdd(var Wsk: PTree; V: Integer);
begin

  if Wsk = nil then
    BSTNew(Wsk, V)
  else
    BSTAddValue(Wsk, V);
    
end;

var
  BSTa: PTree;
begin
  BSTAdd(BSTA, 10);
  BSTAdd(BSTA, 15);
  BSTAdd(BSTA, 5);
  BSTAdd(BSTA, 20);
  BSTAdd(BSTA, 3);
end.
