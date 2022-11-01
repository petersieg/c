50 REM Pi nach Archimedes 2^26 Eck
60 REM P.Sieg 2013
90 PRINT "Pi Berechnung"
100 A=2*SQR(3)
110 B=3
200 A=2*A*B/(A+B)
220 B=SQR(A*B)
250 PRINT A
260 IF A<>B THEN  GOTO 200

