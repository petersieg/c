ROM=v5a

default: all

all: fib32.gt1 fib64.gt1

fib32.gt1: fib.c
	../../build/glcc -o $@ fib.c -DMEM32=1 -map=32k -rom=${ROM}

fib64.gt1: fib.c
	../../build/glcc -o $@ fib.c -DMEM32=0 -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
