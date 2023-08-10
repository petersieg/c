ROM=v5a

default: all

all: eliza64.gt1

eliza64.gt1: eliza.c
	../../build/glcc -o $@ eliza.c -Dprintf=mincprintf -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
