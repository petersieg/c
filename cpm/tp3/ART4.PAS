program art1;

var
  c,i,j : integer;
  ch : char;

begin
  write('seed... press any key.');
  
  randomize;
  repeat
    c := random(60);
  until keypressed;
  read(ch);
  
  write(chr(27),'[2J');  (* Clear Screen     *)
  write(chr(27),'[H');   (* Cursor Home      *)
  write(chr(27),'[32m'); (* Char color green *)
  
  j := 1;
  repeat
    for i := 1 to 78 do 
    begin
      c := random(2); 
      if (c = 0) then 
      begin
        write(' '); (* more spaces *)
      end
      else
      begin
        c := random(20)+32; 
        if (c > 43) then c:= 32; (* more spaces *)
        write(chr(c));
      end;
    end;
    writeln;
    j := j + 1;
    delay(30000);
    write(chr(27),'[H'); (* 1 line up *)
    write(chr(27),'[L'); (* 1 line up *)
  until j > 100;
  
writeln(chr(27),'[0m');
  
end.
