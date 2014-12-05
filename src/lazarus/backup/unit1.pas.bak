unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ExtCtrls, types;

type

  { TForm1 }

  TForm1 = class(TForm)
    PaintBox1: TPaintBox;
    RadioGroup1: TRadioGroup;
    procedure PaintBox1Click(Sender: TObject);
    procedure PaintBox1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    PROCEDURE malen;
    procedure RadioGroup1Click(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form1: TForm1;
  frame:array[0..8,0..8,0..8] of boolean;
implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.PaintBox1Click(Sender: TObject);
var i,j,k :integer;
begin

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
end;

PROCEDURE TForm1.malen;
var i,j,k,iaus,jaus,kaus,x,y:integer;
begin
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

end.

