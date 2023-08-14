ROM=v5a

default: all

all: lisp850.gt1

lisp850.gt1: lisp850.c
	../../build/glcc -o $@ lisp850.c -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
