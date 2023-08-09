ROM=v5a

default: all

all: snake32.gt1 snake64.gt1

snake32.gt1: snake.c
	../../build/glcc -o $@ snake.c -Dprintf=mincprintf -map=32k,nochan -rom=${ROM}

snake64.gt1: snake.c
	../../build/glcc -o $@ snake.c -Dprintf=mincprintf -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
