ROM=v5a

default: all

all: 2048-32.gt1 2048-64.gt1

2048-32.gt1: 2048.c
	../../build/glcc -o $@ 2048.c -map=32k,nochan -rom=${ROM}

2048-64.gt1: 2048.c
	../../build/glcc -o $@ 2048.c -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
