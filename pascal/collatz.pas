(* collatz sequence 
   see: https://en.wikipedia.org/wiki/Collatz_conjecture
   (C) 2024 P.Sieg - CC-BY-SA
*)
program collatz;

var
  x,n,c,h : longint;
  
begin
  writeln ('Enter number:');
  readln(x);
  c := 0;
  h := 0;
  repeat
    if ((x mod 2) = 0) then x := x div 2
    else x := x * 3 + 1;
    c := c + 1;
    if (x > h) then h := x;
    writeln('x=',x,' c=',c,' h=',h)
  until (x < 2);
end.

