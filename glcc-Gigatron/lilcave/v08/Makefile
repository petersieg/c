ROM=v5a
GLCC=../../build/glcc

default: all

all: lilcave.gt1

lilcave.gt1: object.c misc.c noun.c location.c parsexec.c move.c inventory.c main.c
	${GLCC} -o $@ object.c misc.c noun.c location.c parsexec.c move.c inventory.c main.c -map=64k -rom=${ROM}


clean: FORCE
	-rm *.gt1

FORCE:
