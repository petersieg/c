ROM=v5a

default: all

all: othello64.gt1

othello64.gt1: othello.c
	../../build/glcc -o $@ othello.c -DMEM32=0 -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
