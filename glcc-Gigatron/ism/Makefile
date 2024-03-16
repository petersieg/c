ROM=v5a

all: ism_${ROM}.gt1

ism_${ROM}.gt1: ism.c
	../../build/glcc -o $@ ism.c -rom=${ROM} -map=32k,bare

clean: FORCE
	-rm *.gt1

FORCE:
