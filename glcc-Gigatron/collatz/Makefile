ROM=v5a

default: all

all: collatz.gt1 

collatz.gt1: collatz.c
	../../build/glcc -o $@ collatz.c -DMEM32=1 -map=32k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
