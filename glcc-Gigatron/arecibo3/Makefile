ROM=v4

all: arecibo_${ROM}.gt1

arecibo_${ROM}.gt1: arecibo.c
	../../build/glcc -o $@ arecibo.c -rom=${ROM} -map=32k,bare

clean: FORCE
	-rm *.gt1

FORCE:
