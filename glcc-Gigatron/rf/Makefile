ROM=v5a

all: rf_${ROM}.gt1

rf_${ROM}.gt1: rf.c
	../../build/glcc -o $@ rf.c -rom=${ROM} -map=32k,bare

clean: FORCE
	-rm *.gt1

FORCE:
