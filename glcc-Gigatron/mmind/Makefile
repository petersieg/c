ROM=v5a

default: all

all: mmind32.gt1 mmind64.gt1

mmind32.gt1: mmind.c
	../../build/glcc -o $@ mmind.c -DMEM32=1 -map=32k -rom=${ROM}

mmind64.gt1: mmind.c
	../../build/glcc -o $@ mmind.c -DMEM32=0 -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
