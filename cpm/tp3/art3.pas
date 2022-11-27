program art1;

var
  c,i,j : integer;
  ch : char;

begin
  write('seed... press any key.');
  
  randomize;
  repeat
    c := random(60)+10;
  until keypressed;
  read(ch);
  
  write(chr(27),'[2J');  (* clear screen *)
  write(chr(27),'[H');   (* cursor home  *)
  
  j := 1;
  repeat
    c:= random(6)+41;
    write(chr(27),'[',c,'m');
    for i := 1 to 78 do write(' ');
    write(chr(27),'[0m');
    write(chr(27),'[H');
    write(chr(27),'[L');
    j := j + 1;
  until j > 10000;
  writeln(chr(27),'[0m');

end.
