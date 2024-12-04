program mandel;
var
ca, cb, a, b, t: real;
x, y, i, k: integer;
ch: char;

begin
  for y := -12 to 12 do
  begin
    for x := -39 to 39 do
    begin
      ca := x * 0.0458;
      cb := y * 0.08333;
      a := ca;
      b := cb;
      k := 99;
      for i := 0 to 15 do
      if k = 99 then
      begin
        t := a * a - b * b + ca;
        b := 2.0 * a * b + cb;
        a := t;
        if (a * a + b * b) > 4.0 then k := i;
      end;
      if k > 9 then k := k + 7;
      if k > 99 then write(' ');
      if k < 99 then write(chr(48 + k));
    end;
    writeln;
  end
end.

