// converted into simple Gigatron art demo - changes (c) 2024 Peter Sieg CC-BY-SA

#include <gigatron/sys.h>

/*void drawPixel(int x, int y, int color)
{
    screenMemory[y][x] = color;
}*/

int main(void)
{
	int c,d,x,y;
	char *p;
	
    //_console_clear((char*)0x800, 0x00,120);  /* simple clear screen - 0x00 is the background color */
	// clear screen
	for (p = screenMemory[0]; (int)p >= 0; p += 96)
		do { *p=0; p++; } while (((int)p & 0xff) != 160);

	for(;;) {
    //_console_clear((char*)0x800, 0x00,120);  /* simple clear screen - 0x00 is the background color */
	//c = entropy[0] & 63; // random color
	// clear screen
	for (d=2;d<63;d++) {
	  c = entropy[0] & 63; // random color
	  for (x=0;x<160;x+=d) {
	    for (y=0;y<120;y+=d) {
	      //drawPixel(x,y,c);
	      screenMemory[y][x] = c;
	    }
	  }	
	}
	}
}

