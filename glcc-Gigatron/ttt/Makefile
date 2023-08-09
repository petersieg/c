ROM=v5a

default: all

all: ttt32.gt1 

ttt32.gt1: ttt.c
	../../build/glcc -o $@ ttt.c -DMEM32=1 -map=32k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
