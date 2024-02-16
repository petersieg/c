ROM=v5a

default: all

all: arecibo64.gt1 

arecibo64.gt1: arecibo.c
	../../build/glcc -o $@ arecibo.c --no-runtime-bss -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
