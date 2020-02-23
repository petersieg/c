#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define W		80
#define H		25
#define STACKSIZE	1000

#define	pcell_t		signed char
#define	scell_t		signed long
#define	scell_fmt	"%ld"

pcell_t	page[H * W];
scell_t	stack[STACKSIZE];
int	x, y, dx, dy, strmode, stackptr;
int	isdebug = 0;

#define POS(y,x)	((y) * W + (x))
#define CUR		page[POS (y, x)]

void	debug (void)
{
	int	i;

	printf ("\nDebug: x=%d y=%d dir='%c' cmd='%c'(%d) stack=|", x, y,
		"^<>v"[(dx + dy * 3 + 3) >> 1], CUR, (int)CUR);
	for (i = 0; i < stackptr; i++)
		printf (scell_fmt "|", stack[i]);
}

void	error (char *msg)
{
	printf ("\nError: %s", msg);
	debug ();
	printf ("\n");
	exit (1);
	/* UNREACH */
}

#define	PUSH(val)				\
	if (stackptr < STACKSIZE) {		\
		scell_t	v = (val);		\
		stack[stackptr++] = v;		\
	} else					\
		error ("stack overflow")	\

#define	POP					\
	(stackptr ? stack[--stackptr] : 0)	\

int	main (int argc, char **argv)
{
	FILE	*f;
	scell_t	a, b;
	int	c, d, ch;

	if (argc < 2) {
		printf ("Usage:\n\t%s befunge-source\n", argv[0]);
		return 1;
	}
	f = fopen (argv[1], "r");
	if (!f)
		error ("couldn't open input file");
	for (y = 0; y < H; y++)
		for (x = 0; x < W; x++)
			CUR = ' ';
	x = y = 0;
	for (;;) {
		ch = fgetc (f);
		if (ch == EOF)
			break;
		if (ch == '\n') {
			x = 0;
			++y;
		} else {
			if (y >= H)
				error ("too many lines");
			if (x >= W)
				error ("line too long");
			CUR = ch;
			x++;
		}
	}
	fclose (f);

	srand (time (0));
	x = y = dy = strmode = stackptr = 0;
	dx = 1;
	while (CUR != '@' || strmode) {
		if (isdebug)
			debug ();
		if (strmode && CUR != '"')
			PUSH (CUR);
		else
			switch (CUR) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				PUSH (CUR - '0'); break;
			case ' ': break;
			case '>': dx =  1; dy =  0; break;
			case '<': dx = -1; dy =  0; break;
			case '^': dx =  0; dy = -1; break;
			case 'v': dx =  0; dy =  1; break;
			case '|': dx = 0; dy = POP ? -1 : 1; break;
			case '_': dx = POP ? -1 : 1; dy = 0; break;
			case '+': PUSH (POP + POP); break;
			case '-': a = POP; PUSH (POP - a); break;
			case '*': PUSH (POP * POP); break;
			case '/':
				a = POP;
				if (!a) error ("divide by zero");
				PUSH (POP / a); break;
			case '%':
				a = POP;
				if(!a) error ("module by zero");
				PUSH (POP % a); break;
			case '\\': a = POP; b = POP; PUSH (a); PUSH (b); break;
			case '.': printf (scell_fmt " ", POP); break;
			case ',': printf ("%c", (char)POP); break;
			case '"': strmode = !strmode; break;
			case ':': a = POP; PUSH (a); PUSH (a); break;
			case '!': PUSH (!POP); break;
			case '`': a = POP; PUSH (POP > a); break;
			case '#': x += dx; y += dy; break;
			case '$': (void)POP; break;
			case '?':
				switch ((rand () >> 5) & 3) {
				case 0: dx =  1; dy =  0; break;
				case 1: dx = -1; dy =  0; break;
				case 2: dx =  0; dy = -1; break;
				case 3: dx =  0; dy =  1; break;
				}
				break;
			case '&': scanf (scell_fmt, &a); PUSH (a); break;
			case '~': PUSH (fgetc (stdin)); break;
			case 'g': case 'p':
				c = (int)POP; d = (int)POP;
				c = POS (c, d);
				if (c < 0 || c >= W * H)
					error ("out of page");
				if (CUR == 'g') PUSH (page[c]);
				else            page[c] = POP;
				break;
			case '{': isdebug = 1; break;
			case '}': isdebug = 0; break;
			default : error ("unknown command");
			}
		x = (x + dx + W) % W;
		y = (y + dy + H) % H;
	}
	return 0;
}
