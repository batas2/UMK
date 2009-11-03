unit WdIUnit;

Type
  PRec = ^TRec;
  TRec = record
    Value: Integer;
    Next: PRec;
  end;

procedure StackPush(V: Integer);
function StackPop: Integer;

procedure QueueAdd(V: Integer);
function QueueRead:Integer;

var
  Wsk: PRec;
  WskAdd, WskRead: PRec;

implementation

procedure StackPush(V: Integer);
var
  Nowy: PRec;
begin

  New(Nowy);
  Nowy^.Value := V;
  Nowy^.Next := Wsk;
  Wsk := Nowy;

end;

function StackPop: Integer;
var
  Buf: PRec;
begin

  if Wsk <> nil then
    begin
      StackPop := Wsk^.Value;
      Buf := Wsk;
      Wsk := Wsk^.Next;
      Dispose(Buf);
    end
  else
    StackPop := -1;

end;

procedure QueueAdd(V: Integer);
var
  Nowy: PRec;
begin

  New(Nowy);
  Nowy^.Value := V;
  WskAdd^.Next := Nowy;
  WskAdd := Nowy;

  if WskRead = nil then
    WskRead := WskAdd;

end;

function QueueRead:Integer;
var
  Buf: PRec;
begin

  if WskRead <> nil then
    begin
      QueueRead := WskRead^.Value;
      Buf := WskRead;
      WskRead := WskRead^.Next;
      Dispose(Buf);
    end
  else
    QueueRead := -1;

end;

initialization

  Wsk := nil;

  New(WskAdd);
  WskRead := nil;

end.
