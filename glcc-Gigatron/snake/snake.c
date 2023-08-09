/*
	Snake, Console Game

	move the snake with w, a, s, d
	terminate with x
	
	Linux-System required!
 
	@author: www.c-howto.de
    Enhanced to a real snake game by: peter.sieg2@gmx.de 03/2019
*/

#include <stdio.h>
#include <string.h>
#include <conio.h>


/* This enables the code that handles simultaneous button presses
   and yet discriminates keypresses from button presses. */
KBGET_AUTOBTN;

#define BLANK ' '
#define HEAD  '0'
#define TAIL  '+'
#define FOOD  '@'
#define WALL  '#'
#define KEY_MOVE_UP    0xf7
#define KEY_MOVE_LEFT  0xfd
#define KEY_MOVE_DOWN  0xfb
#define KEY_MOVE_RIGHT 0xfe
#define WIDTH 26
#define HEIGHT 14
#define DEBUG 0

struct position {
	int x;
	int y;
} pos;

char field[WIDTH][HEIGHT];  /* changed to char for space */

void resetField();
void printField();
int getItem(int, int);
void setItem(int, int, int);
int move(int);

int main () {
	char i;
	int key = 0;
	int lastkey = 0;
	int score = 0;
	
	resetField();
	printField();
	pos.x=WIDTH/2;
	pos.y=HEIGHT/2;
	setItem(pos.x, pos.y, HEAD);
	while(key != 'x') {
		
		if (kbhit())
			key = getch();

		/* This replace usleep.
		   One should monitor the keyboard often
		   enough to avoid losing key press events. */
		if (++i & 0x7f)
			continue;
		
		if (key != 'x') {
			if (key = move(key)) {
				score++;
				lastkey = key;
			} else key = lastkey;
		}
		if(DEBUG) {
			gotoxy(12,15);
			printf("%02x", key);
		}
		gotoxy(1,15);
		printf("Score: %d  ",score);
	}
	return 0;
}

int move(int key) {

	setItem(pos.x, pos.y, TAIL);
	switch(key) {
	case KEY_MOVE_UP:    pos.y--; break;
	case KEY_MOVE_LEFT:  pos.x--; break;
	case KEY_MOVE_DOWN:  pos.y++; break;
	case KEY_MOVE_RIGHT: pos.x++; break;
	default: return 0; // do not display anything.
	}

    if (getItem(pos.x, pos.y) == BLANK)	{
	    setItem(pos.x, pos.y, HEAD);
	    return key;
    } else {
	    textcolor(RED);
	    setItem(pos.x, pos.y, HEAD);
	    return 'x'; // snake has moved to non blank field - game over
    }
}

int getItem(int x, int y) {
	return field[x][y];
}

void setItem(int x, int y, int item) {
	field[x][y] = item;
	gotoxy(x+1,y+1);  // prints on the fly!
	putch(item);
}

void resetField() {
	int x,y;
	for(y=0;y<HEIGHT;y++) {
		for(x=0;x<WIDTH;x++) {
			field[x][y] = WALL;
		}
	}
	for(y=1;y<HEIGHT-1;y++) {
		for(x=1;x<WIDTH-1;x++) {
			field[x][y] = BLANK;
		}
	}
}

void printField() {
	int i,y,x;
	clrscr();
	for(y=0;y<HEIGHT;y++) {
		for(x=0;x<WIDTH;x++) {
			i = field[x][y];
			if (i != BLANK) {
				gotoxy(x+1,y+1);
				putch(i);
			}
		}
	}

	// print debug things
	if(DEBUG >= 2) {
		printf("\n\nX: %3d   Y: %3d", pos.x, pos.y);
		printf("\n\nx: %3d   y: %3d", x, y);
	}
}


