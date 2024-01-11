ROM=v5a

default: all

all: enigma32.gt1 enigma64.gt1

enigma32.gt1: enigma.c
	../../build/glcc -o $@ enigma.c -map=32k -rom=${ROM}

enigma64.gt1: enigma.c
	../../build/glcc -o $@ enigma.c -map=64k -rom=${ROM}

clean: FORCE
	-rm *.gt1

FORCE:
