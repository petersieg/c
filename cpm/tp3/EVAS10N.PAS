program Evas10n;
{$C-}

{
  EVAS10N.PAS 1.1

  A Turbo Pascal rewrite of Evas10n,
  a BASIC 10-Liner breakout game for the ZX Spectrum.

  Marco's Retrobits
  https://retrobits.altervista.org
  https://retrobits.itch.io

  2020.06.04 Version 1.1:
             * show bales-1
             * constants for ball, bat and brick characters
  2020.06.02 First release
}

const
{
  BallChar: Char = '@';
  BatChars: String[3] = '***';
  BrickChar : Char = '#';
}

  BallChar: Char = ' ';
  BatChars: String[3] = '   ';
  BrickChar : Char = '_';


var
  del, code, bat, batDir, balls, v, w, x, y: Integer;
  bricks: array[3..8] of array[1..32] of Boolean;
  exit, lostBall: Boolean;
  ch: Char;
  param: String[5];

procedure WriteBricks;
  var
    r, c: Integer;
  begin
    LowVideo;
    for r := 3 to 8 do
      for c := 1 to 32 do
        begin
          GotoXY(c,r);
          Write(BrickChar);
        end;
    NormVideo;
  end;

procedure WriteBat;
  begin
    LowVideo;
    GotoXY(bat, 22);
    Write(BatChars);
    NormVideo;
    GotoXY(1, 1);
  end;

procedure DeleteBat;
  begin
    NormVideo;
    GotoXY(bat, 22);
    Write('   ');
    GotoXY(1, 1);
  end;

procedure WriteBall;
  begin
    LowVideo;
    GotoXY(x, y);
    Write(BallChar);
    NormVideo;
    GotoXY(1, 1);
  end;

procedure DeleteBall;
  begin
    NormVideo;
    GotoXY(x, y);
    Write(' ');
  end;

procedure Help;
  begin
    ClrScr;
    Writeln('EVAS10N.PAS v. 1.1');
    Writeln;
    Writeln('A Turbo Pascal rewrite of Evas10n,');
    Writeln('a BASIC 10-Liner breakout game for the ZX Spectrum.');
    Writeln;
    Writeln('Synopsis:');
    Writeln(' EVAS10N [DELAY]');
    Writeln(' DELAY: game loop iteration delay in milliseconds.');
    Writeln('        Default: 800 (assuming 28MHz CPU)');
    Writeln;
    Writeln('Control keys:');
    Writeln(' q:         quit');
    Writeln(' z:         move bat left');
    Writeln(' x:         move bat right');
    Writeln(' any other: stop bat');
    Writeln;
    Writeln('Marco''s Retrobits');
    Writeln('https://retrobits.altervista.org');
    Writeln('https://retrobits.itch.io');
  end;

procedure Init;
  var
    r, c: Integer;
  begin
    balls := 6;
    bat := 15;
    x := 16;
    y := 21;
    v := 1;
    batDir := 1;
    exit := False;
    ClrScr;
    for r := 3 to 8 do
      for c := 1 to 32 do
        begin
          bricks[r, c] := true;
        end;
    WriteBricks;
    GotoXY(3, 24);
    Write('EVAS10N.PAS by Marco V. 2020');
  end;

begin
  del := 800; { 28 MHz assumed }
  if (ParamCount > 0) then
    begin
      param := ParamStr(1);
      Val(param, del, code);
      if (code <> 0) then
        begin
          Help;
          Halt;
        end;
    end;
  repeat
    Init;
    repeat
      w := -1;
      x := bat + 1;
      y := 21;
      WriteBat;
      GotoXY(1, 24);
      Write(balls-1);
      lostBall := False;
      repeat
        Delay(del);
        DeleteBall;
        x := x + v;
        y := y + w;
        { Continuous bat movement }
        if KeyPressed then
        begin
          Read(Kbd, ch);
          if (ch = 'q') then
            exit := True;
          if (ch = 'x') then
            batDir := 1
          else if (ch = 'z') then
            batDir := -1
          else batDir := 0;
        end;
        DeleteBat;
        if ((batDir = 1) and (bat < 30)) or
           ((batDir = -1) and (bat > 1)) then
          bat := bat + batDir;
        WriteBat;
        { Standard bat movement }
        {
        if KeyPressed then
        begin
          Read(Kbd, ch);
          if (ch = 'q') then
            exit := True
          else if (ch = 'x') and (bat < 30) then
            begin
              DeleteBat;
              bat := bat + 1;
              WriteBat;
            end
          else if (ch = 'z') and (bat > 1) then
            begin
              DeleteBat;
              bat := bat - 1;
              WriteBat;
            end;
        end;
        }
        WriteBall;
        if (y = 22) then
          begin
            balls := balls - 1;
            lostBall := True;
            if (balls = 0) then
              begin
                GotoXY(12, 1);
                Write('Game over');
                GotoXY(1, 24);
                Write(' ');
                Delay(del * 8);
                repeat until keypressed;
              end;
            DeleteBall;
          end
        else
          begin
            if (y >= 3) and (y <= 8) then
              bricks[y, x] := false;
            if (x > 1) and (x < 32) and (y >= 3) and (y <= 8)
            and (bricks[y, x + v]) then
              begin
                bricks[y, x + v] := False;
                GotoXY(x + v, y);
                Write(' ');
                GotoXY(1, 1);
                v := -v;
                w := 1;
              end
            else
              begin
                if (y > 3) and (y <= 9)
                and bricks[y - 1, x] then
                begin
                  bricks[y - 1, x] := False;
                  GotoXY(x, y - 1);
                  Write(' ');
                  GotoXY(1, 1);
                  {Write('Ball '); Write(x);Write(y);}
                  w := 1;
                end;
              end;
            if (y = 21) then
              begin
                if (x >= bat - 1) and (x <= bat + 3) then
                  w := -1;
                if (x = bat - 1) then
                  v := -1
                else if (x = bat + 3) then
                  v := 1;
              end;
            if (y = 0) then
              begin
                GotoXY(14, 1);
                Write('Free!');
                Delay(del * 8);
                repeat until keypressed;
                exit := True;
              end;
            if (x = 1) or (x = 32) then
              v := -v;
          end;
      until exit or lostBall;
    until exit or (balls = 0);
  until exit;
  Help;
end.