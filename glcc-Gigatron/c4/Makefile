ROM=v5a

default: all

all: c4_64.gt1 

c4_64.gt1: c4.c
	../../build/glcc -o $@ c4.c -DMEM32=0 -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
