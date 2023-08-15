ROM=v5a

default: all

all: lbforth.gt1

lbforth.gt1: lbforth.c
	../../build/glcc -o $@ lbforth.c -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
