ROM=v5a

default: all

all: reversi32.gt1 reversi64.gt1

reversi32.gt1: reversi.c
	../../build/glcc -o $@ reversi.c -DMEM32=1 -map=32k -rom=${ROM}

reversi64.gt1: reversi.c
	../../build/glcc -o $@ reversi.c -DMEM32=0 -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
