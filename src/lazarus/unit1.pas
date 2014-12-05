unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ExtCtrls,
  StdCtrls, types,LCLType, Spin;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Label1: TLabel;
    OpenDialog1: TOpenDialog;
    PaintBox1: TPaintBox;
    RadioGroup1: TRadioGroup;
    SaveDialog1: TSaveDialog;
    SpinEdit1: TSpinEdit;
    Timer1: TTimer;
    ToggleBox1: TToggleBox;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure PaintBox1Click(Sender: TObject);
    procedure PaintBox1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    PROCEDURE malen;
    procedure RadioGroup1Click(Sender: TObject);
    PROCEDURE read_frame;
    procedure SpinEdit1Change(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure ToggleBox1Change(Sender: TObject);
    PROCEDURE write_frame;
    PROCEDURE clear_frame;
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form1: TForm1;
  frame:array[0..8,0..8,0..8] of boolean;
  frames:TStringList;
  akkframe:integer;
implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.PaintBox1Click(Sender: TObject);
var i,j,k :integer;
begin

end;

procedure TForm1.FormCreate(Sender: TObject);
begin
   frames := TStringList.Create;
  frames.Add('0000000000000000000000000000000000000000000000000000000000000000');

  akkframe:=1;
  clear_frame;
  write_frame;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
    akkframe := 1;
    read_frame;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  akkframe := akkframe - 1;
  if akkframe < 1 then
    akkframe := 1;
  read_frame;
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
   akkframe := akkframe + 1;
  if akkframe > frames.Count then
  begin
    frames.Add('');
    clear_frame;
    write_frame;
  end;

  read_frame;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
    akkframe := frames.Count;
    read_frame;
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
  if OpenDialog1.Execute then
  begin
    if Application.MessageBox('Wirklich öffnen? ungespeichertes wird gelöscht',
      'Öffnen?', MB_ICONQUESTION + MB_YESNO) = idYes then
    begin
      akkframe := 1;
      frames.Clear;
      frames.LoadFromFile(OpenDialog1.FileName);
      Application.MessageBox('Geladen', 'Geladen', MB_ICONINFORMATION);
      read_frame;
    end;
  end;
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
   if SaveDialog1.Execute then
  begin
    frames.SaveToFile(SaveDialog1.FileName);
    Application.MessageBox('Gespeichert', 'Gespeichert', MB_ICONINFORMATION);
  end;
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
   if frames.Count=1 then begin


   clear_frame;
   write_frame;
   end else begin
  frames.Delete(akkframe-1);
  end;
  akkframe:=1;
  read_frame;

end;

procedure TForm1.PaintBox1MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var x8,y8,z8:integer;
begin

   x8 := trunc((x-trunc(x/122)*122)/15) ;
   y8 := trunc(y/15) ;
   z8 := trunc(x/122);
   case RadioGroup1.ItemIndex of
   //0: frame[,,] := not frame[trunc((x-trunc(x/122)*122)/15),y8,trunc(x/122)];
   0: frame[x8,y8,z8] := not frame[x8,y8,z8];
   1: frame[x8,z8,y8] := not frame[x8,z8,y8];
   2: frame[z8,y8,x8] := not frame[z8,y8,x8];
   end;
   //ShowMessage(IntToStr(x8)+', '+IntToStr(y8));
   malen;
   write_frame;
end;

PROCEDURE TForm1.malen;
var i,j,k,iaus,jaus,kaus,x,y:integer;
begin
      Label1.Caption := IntToStr(akkframe) + '/' + IntToStr(frames.Count);
     for i :=0 to 7 do
     begin
        for j :=0 to 7 do
        begin
           for k := 0 to 7 do
           begin
                case RadioGroup1.ItemIndex of
                0:begin
                   iaus:= i;
                   jaus:= j;
                   kaus:= k;
                end;
                1: begin
                   iaus:= i;
                   jaus:= k;
                   kaus:= j;
                   end;
                2:begin
                   iaus:= k;
                   jaus:= j;
                   kaus:= i;
                   end;

                end;
                {
                if frame[i,j,k] then
                PaintBox1.Canvas.Brush.Color:=clLime
                else
                PaintBox1.Canvas.Brush.Color:=clDefault;
                x := (i*15)+(k*122);
                y := j*15;
                PaintBox1.Canvas.Rectangle(x,y,x+15,y+15);  }
                if frame[i,j,k] then
                PaintBox1.Canvas.Brush.Color:=clLime
                else
                PaintBox1.Canvas.Brush.Color:=clDefault;
                x := (iaus*15)+(kaus*122);
                y := jaus*15;
                PaintBox1.Canvas.Rectangle(x,y,x+15,y+15);
           end;
        end;
     end;
end;

procedure TForm1.RadioGroup1Click(Sender: TObject);
begin
  malen;
end;

PROCEDURE TForm1.read_frame;
var iframe:integer;
  i,j,k:integer;
  framepch:PChar;
  ledchar:Char;
begin
  iframe := 0;
  framepch:= PChar(frames[akkframe-1]);
   for k:= 0 to 7 do
   begin
      for j := 0 to 7 do
      begin
         for i := 0 to 7 do
         begin
           ledchar:=framepch[iframe];
           if ledchar = '0' then begin
             frame[i,j,k] := false;
             end
             else begin
               frame[i,j,k] := true;
               end;

           iframe:=iframe + 1;
         end;
      end;

   end;
   malen;
end;

procedure TForm1.SpinEdit1Change(Sender: TObject);
begin
   Timer1.Interval := SpinEdit1.Value;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
  akkframe := akkframe + 1;
  if akkframe > frames.Count then
    akkframe := 1;
  read_frame;
end;

procedure TForm1.ToggleBox1Change(Sender: TObject);
begin
   timer1.Enabled := ToggleBox1.Checked;
end;

PROCEDURE TForm1.write_frame;
var iframe:integer;
  i,j,k:integer;
  framestr:String;
  ledchar:Char;
begin
   framestr:='';
   for k:= 0 to 7 do
   begin
      for j := 0 to 7 do
      begin
         for i := 0 to 7 do
         begin
           if frame[i,j,k] then
           begin
             framestr:=framestr+'1';
           end else begin
             framestr:=framestr+'0';
           end;
         end;
      end;

   end;
   frames[akkframe-1]:=framestr;
end;

PROCEDURE TForm1.clear_frame;
    var i,j,k:integer;
begin
   for k:= 0 to 7 do
   begin
      for j := 0 to 7 do
      begin
         for i := 0 to 7 do
         begin
          frame[i,j,k] := false;
          end;
         end;
      end;
end;

end.

