Unit WdIUnit;

Interface

type
  PRec = ^TRec;
  TRec = packed record
    Next, Prev: PRec;
    case Integer of
      0: (I: Int64);
      1: (F: Extended);
      2: (S: ShortString);
    end;

  TTab = array of TRec;
  TType = Integer;

const
  tInt = 0;
  tFloat = 1;
  tString = 2;
  cNotExists : TRec = (Next: nil; Prev: nil; I: -1; F: -1; S: '');

{
Tab -> SetLength(x);
Stack -> Wsk := nil;
Queue -> WskRead := nil; New(WskAdd);
BST -> Wsk := nil;
}

procedure Swap(var A, B: TRec; T: TType);
procedure Losuj(var Tab: TTab; T: TType; Range: Integer; Start: Integer);
procedure Pokaz(var Tab: TTab; T: TType; L: Integer);
procedure QuickSort(var Tab: TTab; T: TType; S, E: Integer); //S -> Start; E -> End;
function Szukaj(var Tab: TTab; V: TRec; T: TType):Integer;

function Min(var Tab: TTab; T: TType): TRec;
function Max(var Tab: TTab; T: TType): TRec;
function NWD(A, B: Integer): Integer;

function Palindrom(S: String): Boolean;
function Odwroc(X: String): String;
function Prefix(S: String; L: Integer): String;
function Surfix(S: String; L: Integer): String;

function X2Str(Rec: TRec; T: TType; L: Integer): TRec;
function Str2X(Rec: TRec; T: TType): TRec;

procedure StackPush(var Wsk: PRec; V: TRec);
function StackPop(var Wsk: PRec): TRec;

procedure QueueAdd(var WskAdd, WskRead: PRec; V: TRec);
function QueueRead(var WskRead: PRec): TRec;

procedure BSTAdd(var Wsk: PRec; V: TRec; T: TType);

procedure BSTInOrder(const Wsk: PRec; T: TType);
procedure BSTPreOrder(const Wsk: PRec; T: TType);
procedure BSTPostOrder(const Wsk: PRec; T: TType);

procedure BSTSearch(var Wsk, Found: PRec; V: TRec; T: TType);
procedure BSTFree(var Wsk: PRec);

implementation

procedure Swap(var A, B: TRec; T: TType);
var
  Tmp: TRec;
begin

  case T of
    tInt:
      begin
        Tmp.I := A.I;
        A.I := B.I;
        B.I := Tmp.I;
      end;
    tFloat:
      begin
        Tmp.F := A.F;
        A.F := B.F;
        B.F := Tmp.F;
      end;
    tString:
      begin
        Tmp.S := A.S;
        A.S := B.S;
        B.S := Tmp.S;
      end;
  end;

end;

procedure Losuj(var Tab: TTab; T: TType; Range: Integer; Start: Integer);
var
  i: Integer;
begin

  Randomize;

  for i := 0 to Length(Tab) - 1 do
    begin
      case T of
        tInt: Tab[i].I := Random(Range) + Start;
        tFloat: Tab[i].F := Random * (Range - Start) + Start;
      end;
    end;

end;

procedure Pokaz(var Tab: TTab; T: TType; L: Integer);
var
  i: Integer;
begin

  for i := 0 to Length(Tab) - 1 do
    case T of
      tInt: Writeln(Tab[i].I);
      tFloat: Writeln(Tab[i].F:0:L);
      tString: Writeln(Tab[i].S);
    end;

end;

procedure QuickSort(var Tab: TTab; T: TType; S, E: Integer); //S -> Start; E -> End;
var
  i, j: Integer;
  X: TRec;
begin

  i := S;
  j := E;
  X := Tab[ (S + E) div 2];

  repeat

    case T of
      tInt:
        begin
          while Tab[i].I < X.I do Inc(i);
          while Tab[j].I > X.I do Dec(j);
        end;
      tFloat:
        begin
          while Tab[i].F < X.F do Inc(i);
          while Tab[j].F > X.F do Dec(j);
        end;
      tString:
        begin
          while Tab[i].S < X.S do Inc(i);
          while Tab[j].S > X.S do Dec(j);
        end;
    end;

    if i <= j then
      begin
        Swap(Tab[i], Tab[j], T);
        Inc(i);
        Dec(j);
      end;

  until i > j;

  if S < j then
    QuickSort(Tab, T, S, j);
  if i < E then
    QuickSort(Tab, T, i, E);

end;

function Szukaj(var Tab: TTab; V: TRec; T: TType):Integer;
var
  S, E, M, W: Integer;
begin

  S := -1;
  E := Length(Tab) - 1;
  W := -1;

  while E > S + 1 do
    begin
      M := (S + E) div 2;
      case T of
        tInt:
          begin
            if Tab[M].I <> V.I then
              begin
                if Tab[M].I < V.I then
                  S := M
                else
                  E := M;
              end
            else
              begin
                W := M;
                break;
              end;
          end;
        tFloat:
          begin
            if Tab[M].F <> V.F then
              begin
                if Tab[M].F < V.F then
                  S := M
                else
                  E := M;
              end
            else
              begin
                W := M;
                break;
              end;
          end;
      end;
    end;

  Szukaj := W;

end;

function Min(var Tab: TTab; T: TType): TRec;
var
  Wynik: TRec;
  i: Integer;
begin

  case T of
    tInt: Wynik.I := High(Int64);
    tFloat: Wynik.F := High(Int64);
  end;

  for i := 0 to Length(Tab) - 1 do
    case T of
      tInt:
        if Tab[i].I < Wynik.I then
          Wynik.I := Tab[i].I;
      tFloat:
        if Tab[i].F < Wynik.F then
          Wynik.F := Tab[i].F;
    end;

  Min := Wynik;

end;

function Max(var Tab: TTab; T: TType): TRec;
var
  Wynik: TRec;
  i: Integer;
begin

  case T of
    tInt: Wynik.I := Low(Int64);
    tFloat: Wynik.F := Low(Int64);
  end;

  for i := 0 to Length(Tab) - 1 do
    case T of
      tInt:
        if Tab[i].I > Wynik.I then
          Wynik.I := Tab[i].I;
      tFloat:
        if Tab[i].F > Wynik.F then
          Wynik.F := Tab[i].F;
    end;

  Max := Wynik;

end;

function NWD(A, B: Integer): Integer;
begin

  while A <> B do
    if A > B then A := A - B
    else B := B - A;

  NWD := A;

end;

function Palindrom(S: String): Boolean;
var
  i: Integer;
  Wynik: Boolean;
begin

  Wynik := true;
  for i := 1 to Length(S) div 2 do
    if s[i] <> S[Length(S) - i + 1] then
      Wynik := false;

  Palindrom := Wynik;

end;

function Odwroc(X: String): String;
var
  i: Integer;
  c: Char;
begin

  for i := 1 to Length(X) div 2 do
    begin
     c := X[i];
     X[i] := X[Length(X) - i + 1];
     X[Length(X) - i + 1] := c;
   end;

  Odwroc := X;

end;

function Prefix(S: String; L: Integer): String;
begin

  Prefix := Copy(S, 1, L);

end;

function Surfix(S: String; L: Integer): String;
begin

  Surfix := Copy(S, Length(S) - L + 1, L);

end;

function X2Str(Rec: TRec; T: TType; L: Integer): TRec;
var
  Wynik: TRec;
begin

  case T of
    tInt: Str(Rec.I, Wynik.S);
    tFloat: Str(Rec.F:0:L, Wynik.S);
  end;

  X2Str := Wynik;

end;

function Str2X(Rec: TRec; T: TType): TRec;
var
  Wynik: TRec;
  Code: Integer;
begin

  case T of
    tInt: Val(Rec.S, Wynik.I, Code);
    tFloat: Val(Rec.S, Wynik.F, Code);
  end;

  if Code = 0 then
    Str2X := Wynik;

end;

procedure StackPush(var Wsk: PRec; V: TRec);
var
  Nowy: PRec;
begin

  New(Nowy);
  Nowy^ := V;
  Nowy^.Next := Wsk;
  Wsk := Nowy;

end;

function StackPop(var Wsk: PRec): TRec;
var
  Buf: PRec;

begin

  if Wsk <> nil then
    begin
      StackPop := Wsk^;
      Buf := Wsk;
      Wsk := Wsk^.Next;
      Dispose(Buf);
    end
  else
    StackPop := cNotExists;

end;

procedure QueueAdd(var WskAdd, WskRead: PRec; V: TRec);
var
  Nowy: PRec;
begin

  New(Nowy);
  Nowy^ := V;
  WskAdd^.Next := Nowy;
  WskAdd := Nowy;

  if WskRead = nil then
    WskRead := WskAdd;

end;

function QueueRead(var WskRead: PRec): TRec;
var
  Buf: PRec;
begin

  if WskRead <> nil then
    begin
      QueueRead := WskRead^;
      Buf := WskRead;
      WskRead := WskRead^.Next;
      Dispose(Buf);
    end
  else
    QueueRead := cNotExists;

end;

procedure BSTAdd(var Wsk: PRec; V: TRec; T: TType);
begin

  if Wsk = nil then
    begin
      New(Wsk);
      Wsk^ := V;
      Wsk^.Prev := nil;
      Wsk^.Next := nil;
    end
  else
    begin
      case T of
        tInt:
          if V.I > Wsk^.I then
            BSTAdd(Wsk^.Next, V, T)
          else
            BSTAdd(Wsk^.Prev, V, T);
        tFloat:
          if V.F > Wsk^.F then
            BSTAdd(Wsk^.Next, V, T)
          else
            BSTAdd(Wsk^.Prev, V, T);
      end;
    end;

end;

procedure BSTInOrder(const Wsk: PRec; T: TType);
begin

  if Wsk <> nil then
    begin
      BSTInOrder(Wsk^.Prev, T);
      case T of
        tInt: Write(Wsk^.I, ' ');
        tFloat: Write(Wsk^.F, ' ');
      end;
      BSTInOrder(Wsk^.Next, T);
    end;

end;

procedure BSTPreOrder(const Wsk: PRec; T: TType);
begin

  if Wsk <> nil then
    begin
      case T of
        tInt: Write(Wsk^.I, ' ');
        tFloat: Write(Wsk^.F, ' ');
      end;
      BSTPreOrder(Wsk^.Prev, T);
      BSTPreOrder(Wsk^.Next, T);
    end;

end;

procedure BSTPostOrder(const Wsk: PRec; T: TType);
begin

  if Wsk <> nil then
    begin
      BSTPostOrder(Wsk^.Prev, T);
      BSTPostOrder(Wsk^.Next, T);
      case T of
        tInt: Write(Wsk^.I, ' ');
        tFloat: Write(Wsk^.F, ' ');
      end;
    end;

end;

procedure BSTSearch(var Wsk, Found: PRec; V: TRec; T: TType);
begin

	if Wsk <> nil then
  	begin
      case T of
        tInt:
          begin
        		if Wsk^.I <> V.I then
          		begin
			          if V.I < Wsk^.I then
            			BSTSearch(Wsk^.Prev, Found, V, T)
          			else
			            BSTSearch(Wsk^.Next, Found, V, T);
          		end
		        else
              Found := Wsk;
          end;
        tFloat:
          begin
        		if Wsk^.F <> V.F then
          		begin
			          if V.F < Wsk^.F then
            			BSTSearch(Wsk^.Prev, Found, V, T)
          			else
			            BSTSearch(Wsk^.Next, Found, V, T);
          		end
		        else
              Found := Wsk;
          end;
      end;
    end
	else
		Found := nil;

end;

procedure BSTFree(var Wsk: PRec);
begin

  if Wsk <> nil then
  	begin
	  	BSTFree(Wsk^.Prev);
		  BSTFree(Wsk^.Next);
		  Dispose(Wsk);
		  Wsk := nil;
  	end;

end;

end.