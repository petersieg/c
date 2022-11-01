program DBlick(input, output);

(* This program, DBlick, is copyrighted (C) 1984 by D. Griffith and
     Andrew Zaslow.

      DBlick is a BREAKOUT type game where you bounce a ball into a
      multi-layered wall.  The object is to break all the bricks and
      keep the ball in play with the paddle.  The paddle is moved from
      left to right with the "," and "." keys.  You may choose either
      a paddle with or without a manual stop.  You may also choose
      your desired skill level from 1 (slowest) to 9 (fastest).

      The program will go into demo mode after a game has been
      played and you fail to answer the "Play another game y/n?"
      prompt within 5 seconds.

      DBlick is released into the public domain for non-commercial
         purposes, only.  Reproduction for commercial advantage
         without the permission of the author is in violation of
         all applicable laws.

      DBlick is written in Turbo Pascal v2.0 by Borland International.
*)

(****
        code altered by Steve Sanders 12/16/84 to make the new Kaypro
        video routines work.  also added some code for the scores to
        display in inverse/dim, added a BEEP when bricks were hit,
        and changed the logic in the paddle stop/no stop routine, it
        was backwards.  if you said yes it did the opposite.

****)

(****
        code altered by Larry Fogg at Micro Cornucopia 6/85 to allow
        execution on both 83 and 84 model Kaypros.
****)


type padstr=string[6];

const wblick='#';
      bblick='o';
      paddle='===== ';
      spaces='                ';
      quit=^c;
      pause=^[;
      wait=7500;
      bell=^G;

var bx,dx: real;
    dp,by,dy,i,j,px,py: integer;
    defmov,score: integer;
    padmag,iskill,skill,serves: integer;
    wall: array[1..24] of string[51];
    nowall,bhappy,flag,indemo,shwad: boolean;
    c: char;
    dblick: array[1..7,1..5] of string[40];
    Kaypro84 : Boolean;  { if true then 84 Kaypro - if false then 83 Kaypro }
    inverse,           (* New Kaypro video equates *)
    inverseoff,
    half,
    halfoff,
    blink,
    blinkoff,
    curson,
    cursoff: string[3];

function TypeKaypro : Boolean; { tests for 83 vs 84 Kaypro }
var                            { result is used to turn graphics on or off }
  OriginalVal,
  NewVal,
  NewValStored  : Integer;

begin
  OriginalVal := Port[30];    { port 1E is unused in 83 - doesn't exist in 84 }
  NewVal := OriginalVal - 2;
  Port[30] := NewVal;         { store new value in port 1E }
  NewValStored := Port[30];   { read value stored in port 1E }
  if NewVal<>NewValStored     { was value actually stored? }
    then TypeKaypro := true   { 84 model }
    else TypeKaypro := false; { 83 model }
  Port[30] := OriginalVal;    { restore original value }
end;  { TypeKaypro }


procedure refresh;
var i,j,l: integer;
begin
   clrscr;
   if nowall or indemo then for i:=5 to 9 do for j:=19 to 49 do wall[i][j]:=wblick;
   nowall:=false;
   for i:=1 to 24 do
      begin
         gotoxy(1,i);
         if pos(wblick,wall[i])=0 then write(wall[i])
         else
            for j:=1 to length(wall[i]) do
               if (wall[i][j]=wblick)
                  then write(inverse,wblick,inverseoff)
                  else write(wall[i][j]);
      end;
   gotoxy(3,5); write(inverse,' Score: ',score:4,' ');
   gotoxy(3,6); write(half,' Serves: ',serves:3,' ');
   gotoxy(3,7); write(' Skill: ',(10-round(skill/100)):4,' ');
   write(halfoff,inverseoff);
   gotoxy(px,py); write(paddle);
   if indemo then begin
      gotoxy(25,24);
      write(inverse,blink);
      write(' Play again (Y/N)? ');
      write(inverseoff,blinkoff);
   end;
end;

procedure putpad(x: integer;s: padstr); begin
   wall[py]:=copy(wall[py],1,x-1)+s+copy(wall[py],x+6,52);
   gotoxy(px,py); write(s); gotoxy(1,1);
end;

procedure movepaddle; var k: char; begin
   if keypressed or (i=3) or (i=defmov) then begin
      if (i=3) or (i=defmov) then k:=chr(53+dp) else read(kbd,k);
      if (k in [' ', '5']) then dp:=0;
      if (k in ['<', ',', '4', ^H, ^S]) and (px>15) then begin
         px:=px-1; putpad(px,'===== '); dp:=-padmag; end;
      if (k in ['>', '.', '6', ^L, ^D]) and (px<49) then begin
         putpad(px,' ====='); px:=px+1; dp:=padmag; end;
      if k=quit then begin flag:=true; serves:=0; end;
      if k=pause then while (not keypressed) do;
      end;
end;

procedure youlosebub; var c: char; begin
   flag:=true;
   gotoxy(1,1);
   write(inverse,blink);
   write(' You lose, bub. ');
   gotoxy(19,20);
   write(' [Press space bar to continue] ');
   write(blinkoff,inverseoff);
   repeat read(kbd,c); until (c=' ') or (c=^C);
   if c=^C then begin serves:=0; flag:=true; end;
end;

procedure moveball; var tx: real; ty,nx: integer; begin
   tx:=bx+dx; nx:=round(tx); ty:=by+dy;
   wall[by][round(bx)]:=' '; gotoxy(round(bx),by); write(' ');
   if not indemo then putpad(px,'===== ');
   if (nx<19) or (nx>49) then begin
       dx:=-dx; tx:=bx+dx; nx:=round(tx); end;
   case wall[ty][nx] of
         '=': begin
                 if indemo then dx:=(random(160)-79.5)/42.0 else dx:=(tx-px-2.0)/2.0;
                 if shwad then dx:=dx+(random(31)-16.0)/64.0;
                 dy:=-dy;
              end;
      wblick: if bhappy then begin
                 dx:=-dx; tx:=bx+dx; nx:=round(tx); bhappy:=false; end
              else
              begin score:=score+10-ty; gotoxy(3,5);
              write(inverse,' Score: ',score:4,' ');
              write(bell,inverseoff);
                    dy:=-dy; bhappy:=true;
                    if (score mod 465)=0 then begin
                        flag:=true; nowall:=true; serves:=serves+2; end;
              end;
   else bhappy:=false
   end;
   if ty<3 then begin
      dy:=-dy;
      skill:=iskill-100;
      end;
   if ty<=py then
      begin
         by:=ty; bx:=tx;
         gotoxy(nx,by);
         write(bblick);
         gotoxy(1,1);
      end
   else youlosebub;
end;

procedure serveball; begin
   by:=10;
   dy:=1;
   bx:=random(28)+21;
   repeat
      dx:=random(3)-1;
   until dx<>0;
end;

procedure demo; var i: integer; begin
   indemo:=true;
   write(cursoff);
   score:=0; serves:=4; iskill:=500;
   flag:=true;
   repeat
      if flag then begin
         skill:=iskill;
         serves:=serves-1;
         refresh;
         serveball;
         flag:=false;
         end;
      moveball; putpad(px,'      '); px:=round(bx-2.0); putpad(px,'===== ');
      for i:=1 to skill do if keypressed then read(kbd,c);
      if c in ['1'..'9'] then iskill:=(ord(c)-48)*100+1; skill:=iskill;
   until c in ['Y','y','N','n'];
   clrscr;
   write(curson);
end;

procedure header;  { prints header for pre 84 machines }
  begin
    gotoxy(21,1); write(' DDDD   BBBB   ll');
    gotoxy(21,2); write(' D   D  B   B   l     i          k');
    gotoxy(21,3); write(' D   D  B   B   l                k');
    gotoxy(21,4); write(' D   D  BBBB    l     i     ccc  k k');
    gotoxy(21,5); write(' D   D  B   B   l     i    c     kk');
    gotoxy(21,6); write(' D   D  B   B   l     i    c     k k');
    gotoxy(21,7); write(' DDDD   BBBB   lll   iii    ccc  k  k');
  end;  { header }

begin  { MAIN }
   dblick[1,1]:='  DDD    BBB   l                     ';
   dblick[2,1]:=' D      B       l     /         k    ';
   dblick[3,1]:=' D   D  B   B   l               k    ';
   dblick[4,1]:=' D   D  BBBB    l    i      cc  k k  ';
   dblick[5,1]:=' D   D  B   B   l     i   c     kk   ';
   dblick[6,1]:='     D      B         i   c       k  ';
   dblick[7,1]:=' DDD    BBB    lll    i    cc   k  k ';
;
   dblick[1,2]:=' D DD   B BB   ll               k    ';
   dblick[2,2]:=' D   D  B   B         -              ';
   dblick[3,2]:=' D      B       l               k  k ';
   dblick[4,2]:=' D   D  BBBB    l    ii    c c  k    ';
   dblick[5,2]:='     D      B   l         c     kk   ';
   dblick[6,2]:=' D   D  B   B   l     i   c     k k  ';
   dblick[7,2]:=' DD D   BB B   l l   iii   c c     k ';
;
   dblick[1,3]:=' DD D   BB B   ll               k    ';
   dblick[2,3]:=' D   D  B   B   l     \         k    ';
   dblick[3,3]:=' D   D  B   B                      k ';
   dblick[4,3]:='         BB     l    ii    cc   k k  ';
   dblick[5,3]:=' D   D  B   B   l     i   c     k    ';
   dblick[6,3]:=' D   D  B   B   l         c     k k  ';
   dblick[7,3]:=' D DD   B BB    l    iii    cc  k  k ';
;
   dblick[1,4]:=' DDD     BB    ll               k    ';
   dblick[2,4]:=' D   D  B   B   l     |         k    ';
   dblick[3,4]:='     D      B   l               k  k ';
   dblick[4,4]:=' D   D  BB B         ii    ccc    k  ';
   dblick[5,4]:=' D      B       l     i   c     kk   ';
   dblick[6,4]:=' D   D  B   B   l     i         k    ';
   dblick[7,4]:='  DDD    BB    lll   i i   ccc  k  k ';
;
   dblick[1,5]:=' DDDD   BBBB    l               k    ';
   dblick[2,5]:='     D      B   l               k    ';
   dblick[3,5]:=' D   D  B   B   l               k  k ';
   dblick[4,5]:=' D   D  B BB    l     i    ccc  k k  ';
   dblick[5,5]:=' D   D  B   B         i          k   ';
   dblick[6,5]:=' D      B       l     i   c     k k  ';
   dblick[7,5]:=' DDDD   BBBB   lll   iii   ccc  k    ';

   clrscr;
   Kaypro84 := TypeKaypro;
   if Kaypro84 then
     begin
       inverse:=^['B0';             (* New Kaypro video equates *)
       inverseoff:=^['C0';
       half:=^['B1';
       halfoff:=^['C1';
       blink:=^['B2';
       blinkoff:=^['C2';
       curson:=^['B4';
       cursoff:=^['C4';
     end
   else
     begin
       inverse:='';                { pre 84 machines }
       inverseoff:='';
       half:='';
       halfoff:='';
       blink:='';
       blinkoff:='';
       curson:='';
       cursoff:='';
     end;
   clrscr;

   repeat
      wall[1]:=spaces+' ================================= ';
      for i:=2 to 21 do wall[i]:=spaces+'||                               || ';
      for i:=22 to 24 do wall[i]:=spaces+'                                   ';
      score:=0;
      serves:=3;
      nowall:=true; indemo:=false;
      write(cursoff);
      gotoxy(21,9); write(inverse);
      write(' by  D. Griffith  and  Andrew Zaslow ');
      write(inverseoff);
      gotoxy(15,13); write('Enter skill level (1-Easy through 9-Impossible): ');
      i:=1;
      if Kaypro84 then
        repeat
           if keypressed then read(kbd,c);
           for j:=1 to 7 do begin
              gotoxy(21,j);
              write(dblick[j,i]);
              end;
           i:=i+1; if i>5 then i:=1;
        until c in ['1'..'9']
        else
          begin                   { if pre 84 }
            header;
            gotoxy(64,13);
            repeat read(kbd,c)
            until c in ['1'..'9']
          end;
      gotoxy(64,13); write(c);
      iskill:=(10-(ord(c)-48))*100; skill:=iskill; defmov:=trunc(skill/2);
      gotoxy(15,15); write('Do you want some randomness in your bounces (Y/N)? ');
      if Kaypro84 then
        repeat
           if keypressed then read(kbd,c);
           for j:=1 to 7 do begin
              gotoxy(21,j);
              write(dblick[j,i]);
              end;
           i:=i+1; if i>5 then i:=1;
        until c in ['y','n','Y','N']
        else
          begin                      { if pre 84 }
            gotoxy(66,15);
            repeat read(kbd,c)
            until c in ['y','n','Y','N']
          end;
      gotoxy(66,15); write(c);
      if c in ['Y','y'] then shwad:=true else shwad:=false;
      c:=' ';
      gotoxy(17,17); write('Do you want a paddle with space-bar stop (Y/N)? ');
      if Kaypro84 then
        repeat
           if keypressed then read(kbd,c);
           for j:=1 to 7 do begin
              gotoxy(21,j);
              write(dblick[j,i]);
              end;
           i:=i+1; if i>5 then i:=1;
        until c in ['y','n','Y','N']
        else
          begin                      { if pre 84 }
            gotoxy(63,17);
            repeat read(kbd,c)
            until c in ['y','n','Y','N']
          end;
      gotoxy(63,17); write(c);
      if c in ['N','n'] then padmag:=0 else padmag:=1;
      write(cursoff);
      repeat
         flag:=false;
         wall[py]:=wall[py-1];
         px:=32; py:=23; dp:=0;
         refresh;
         serveball;
         bhappy:=false;
         repeat
            for i:=1 to skill do movepaddle;
            moveball;
         until flag;
         serves:=serves-1;
         skill:=iskill;
      until serves<1;
      clrscr; gotoxy(18,5); write(curson);
         write(inverse,half);
         write(' Do you want to play again (Y/N)? ');
         write(halfoff,inverseoff);
         i:=0; c:=' ';
         repeat
            if keypressed then read(kbd,c);
            i:=i+1;
         until (c in ['Y', 'y', 'N', 'n']) or (i>wait);
         clrscr;
         if i>wait then demo;
   until (c='N') or (c='n');
   clrscr;
end.
