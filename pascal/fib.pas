program fib;

var
  a,b,c : integer;
  
begin
  a := 0;
  b := 1;
  repeat
    c := b + a;
    writeln (c);
    a := b;
    b := c;
  until c > 10000;
end.

