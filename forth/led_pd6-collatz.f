LED an PD6:
40 2a
40 2b
00 2b

Check whether TOP is equal:
: eq 2 mod 0 = if ." -is equal" else ." -is unequal" then ;

Collatz single step:
: collatz-s dup 2 mod 0 = if 2 / else 3 * 1 + then ;

Collatz sequence:
: collatz begin dup cr . collatz-s dup 1 = until cr . ;
