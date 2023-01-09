(* Simple Rotomat - (C) P. Sieg 2022 CC-BY-NC-SA *)
program rotomat;

var
  x,total,bed,win2,win3,wl,wm,wr,nr,ac : integer;
  c : char;

begin
  total := 100; (* total sum *)
  bed   := 10;  (* cost for each game round *)
  win2  := 20;  (* win for 2 same values *)
  win3  := 100; (* win for all 3 same values *)
  nr    := 0;   (* number of game rounds *)
  ac    := 0;   (* autorun count *)

  writeln('seed... press any key.');

  randomize;
  repeat
    x := random(100);
  until keypressed;
  repeat
    read(c);
  until not keypressed;
  c := ' ';
  
  writeln('x=exit; a=run 100 times; any key=next round.');
  write('Total start: '); readln(total);
  write('Bed costs  : '); readln(bed);
  write('Win2 amount: '); readln(win2);
  write('Win3 amount: '); readln(win3);
  if (total < bed) then total := bed;
  
  repeat
  
    (* write(chr(27),'[2J');  (* clear screen *)
    (* write(chr(27),'[H');   (* cursor home  *)
    
    total := total - bed;
    nr    := nr + 1;
      
    wl := random(9)+1;     (* walze links *)
    wm := random(9)+1;     (* walze mitte *)
    wr := random(9)+1;     (* walze rechts *)
    
    if ((wl = wm) and (wm = wr)) then total := total + win3
    else if ((wl = wm) or  (wl = wr) or (wm = wr)) then total := total + win2;
    
    writeln(nr,'->',wl,wm,wr,'=',total);
    
    if (c <> 'a') then
    begin
      repeat
        read(c);
      until not keypressed;
    end
    else
    begin
      ac := ac + 1;
      if (ac > 100) then
      begin
        ac := 0;
        c  := ' ';
      end;
    end;
  until ((total < bed) or (total > 10000) or (nr > 10000) or (c = 'x'));
end.
