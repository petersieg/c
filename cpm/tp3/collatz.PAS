(* Simple collatz - (C) P. Sieg 2023 CC-BY-NC-SA *)
(* collatz mathematical problem - see wikipedia  *)
(* if n is even   then n := n / 2                *)
(* if n is uneven then n := 3 * n + 1            *)
program collatz;

var
  n,r,c : integer;

begin
  repeat
    write('Input integer: ');
    readln(n);
    if (n < 1) then n := 1;
    c := 0;
    
    repeat
      (* determine if n is even or uneven *)
      r := n mod 2;
      (* writeln('n=',n,' r=',r); *)    
      if (r <> 1) then n := n div 2
      else n := 3 * n + 1;
      c := c + 1;
      writeln('c=',c,' n=',n);
    until (n = 1);
  until (n = 1);
end.
