2 FOR PY=1 TO 15
3 FOR PX=1 TO 31
4 X=0
5 XT=0
6 Y=0
7 FOR I=0 TO 11
8 XT = (X*X)/10 - (Y*Y)/10 + (PX-23)
9 Y = (X*Y)/5 + (10*PY - 75)/8
10 X = XT
11 IF (X/10)*X + (Y/10)*Y >= 400 THEN GOTO 15
12 NEXT I
13 PRINT "X",
14 GOTO 16
15 PRINT " ",
16 NEXT PX
17 PRINT
18 NEXT PY
19 END
