ROM=v5a

default: all

all: nqueens32.gt1 nqueens64.gt1

nqueens32.gt1: nqueens.c
	../../build/glcc -o $@ nqueens.c -DMEM32=1 -map=32k -rom=${ROM}

nqueens64.gt1: nqueens.c
	../../build/glcc -o $@ nqueens.c -DMEM32=0 -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
