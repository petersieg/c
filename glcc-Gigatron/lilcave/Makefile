ROM=v5a
GLCC=../../build/glcc

default: all

all: lilcave.gt1

lilcave.gt1: object.c misc.c match.c noun.c toggle.c location.c move.c reach.c inventory.c inventory2.c openclose.c parsexec.c main.c
	${GLCC} -o $@ object.c misc.c match.c noun.c toggle.c location.c move.c reach.c inventory.c inventory2.c openclose.c parsexec.c main.c -map=64k -rom=${ROM}


clean: FORCE
	-rm *.gt1

FORCE:
