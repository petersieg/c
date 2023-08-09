ROM=v5a

default: all

all: startrek64.gt1

startrek64.gt1: startrek.c
	../../build/glcc -o $@ startrek.c -DMEM32=0 -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
