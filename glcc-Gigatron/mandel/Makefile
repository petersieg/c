ROM=v5a

default: all

all: mandel32.gt1 

mandel32.gt1: mandel.c
	../../build/glcc -o $@ mandel.c -DMEM32=1 -map=32k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
