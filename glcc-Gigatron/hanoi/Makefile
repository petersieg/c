ROM=v5a

default: all

all: hanoi32.gt1 

hanoi32.gt1: hanoi.c
	../../build/glcc -o $@ hanoi.c -DMEM32=1 -map=32k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
