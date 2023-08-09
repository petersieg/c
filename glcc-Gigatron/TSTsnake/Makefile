ROM=v5a
MAP=32k,nochan
CC=../../build/glcc
CFLAGS=-rom=$(ROM) -map=$(MAP)

PROGS= TSTsnake.gt1

all: $(PROGS)

%.gt1: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean: FORCE
	-rm -rf $(PROGS)

FORCE:
