(* ANSI ESC Simple Demo Effect - (C) P. Sieg 2022 CC-BY-NC-SA *)
program art1;

var
  c1,c2,x,y,i,j : integer;
  c : char;

begin
  write('seed... press any key.');

  randomize;
  repeat
    x := random(60)+10;
  until keypressed;
  repeat
    read(c);
  until not keypressed;

  repeat
  y := random(15)+5;
  c1:= random(6)+41;
  c2:= random(6)+41;

  write(chr(27),'[2J');  (* clear screen *)
  write(chr(27),'[H');   (* cursor home  *)

  for j := 1 to y do
  begin
    write(chr(27),'[',c1,'m');
    for i := 1 to x do write(' ');

    write(chr(27),'[',c2,'m');
    for i := x+1 to 78 do write(' ');

    writeln(chr(27),'[0m');
  end;

  x := random(60)+10;
  c1:= random(6)+41;
  c2:= random(6)+41;

  for j := y+1 to 24 do
  begin
    write(chr(27),'[',c1,'m');
    for i := 1 to x do write(' ');

    write(chr(27),'[',c2,'m');
    for i := x+1 to 78 do write(' ');

    writeln(chr(27),'[0m');
  end;
  delay(30000);
  delay(30000);
  delay(30000);
  delay(30000);
  delay(30000);
  delay(30000);
  until keypressed;
end.
