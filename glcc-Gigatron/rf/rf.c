// converted into simple Gigatron art demo - changes (c) 2024 Peter Sieg CC-BY-SA

#include <gigatron/sys.h>

int main(void)
{
	int c,d,x,y,xd,yd;
	char *p;
	
	// clear screen
	for (p = screenMemory[0]; (int)p >= 0; p += 96)
		do { *p=0; p++; } while (((int)p & 0xff) != 160);

	x=80; y=60; // middle of screen to start
	c = entropy[0] & 63; // random color
	
	for(;;) {
	
		xd= (entropy[0] & 1) - 1;
		yd= (entropy[0] & 1) - 1;
		if ((xd == 0) && (yd == 0)) {
			xd= (entropy[0] & 20);
			yd= (entropy[0] & 20);			
			c = entropy[0] & 63; // random color
		}
		x = x + xd; 
		if ((x >= 160) || (x < 0)) x = 80;
		y = y + yd;
		if ((y >= 120) || (y < 0)) y = 60;

	    screenMemory[y][x] = c;
	}
}

