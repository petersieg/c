ROM=v5a
GLCC=../../build/glcc

default: all

all: lisp850.gt1 lisp850sim.gt1

lisp850.gt1: lisp850.c
	${GLCC} -o $@ lisp850.c -map=64k -rom=${ROM}

lisp850sim.gt1: lisp850.c
	${GLCC} -o $@ lisp850.c -map=sim -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
