ROM=v5a

default: all

all: reverse32.gt1 reverse64.gt1

reverse32.gt1: reverse.c
	../../build/glcc -o $@ reverse.c -Dprintf=mincprintf -DMEM32=1 -map=32k -rom=${ROM}

reverse64.gt1: reverse.c
	../../build/glcc -o $@ reverse.c -Dprintf=mincprintf -DMEM32=0 -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
