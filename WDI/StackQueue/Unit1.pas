unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

Type
  PRec = ^TRec;
  TRec = record
    Value: Integer;
    Next: PRec;
  end;

type
  TForm1 = class(TForm)
    Memo1: TMemo;
    Button1: TButton;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

Procedure StackPush(V: Integer);
Function StackPop: Integer;

Procedure QueueAdd(V: Integer);
Function QueueRead:Integer;

var
  Form1: TForm1;
  Wsk: PRec;
  WskAdd, WskRead: PRec;

implementation

{$R *.dfm}

Procedure StackPush(V: Integer);
var
  Nowy: PRec;
begin

  New(Nowy);
  Nowy^.Value := V;
  Nowy^.Next := Wsk;
  Wsk := Nowy;

end;

Function StackPop: Integer;
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

Procedure QueueAdd(V: Integer);
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

Function QueueRead:Integer;
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

procedure TForm1.FormCreate(Sender: TObject);
begin

  Wsk := nil;
  New(WskAdd);
  WskRead := nil;
  
end;

procedure TForm1.Button1Click(Sender: TObject);
begin

  StackPush(2);
  StackPush(4);
  StackPush(6);
  StackPush(8);
  Memo1.Lines.Add(IntToStr(StackPop));
  Memo1.Lines.Add(IntToStr(StackPop));
  Memo1.Lines.Add(IntToStr(StackPop));
  Memo1.Lines.Add(IntToStr(StackPop));

  QueueAdd(2);
  QueueAdd(4);
  QueueAdd(6);
  QueueAdd(8);
  Memo1.Lines.Add(IntToStr(QueueRead));
  Memo1.Lines.Add(IntToStr(QueueRead));
  Memo1.Lines.Add(IntToStr(QueueRead));
  Memo1.Lines.Add(IntToStr(QueueRead));

end;

end.
