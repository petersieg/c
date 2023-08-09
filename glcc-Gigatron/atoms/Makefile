ROM=v5a

default: all

all: atoms32.gt1 atoms64.gt1

atoms32.gt1: atoms.c
	../../build/glcc -o $@ atoms.c -Dprintf=mincprintf -map=32k,nochan -rom=${ROM}

atoms64.gt1: atoms.c
	../../build/glcc -o $@ atoms.c -Dprintf=mincprintf -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
