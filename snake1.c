/*
	Snake, Console Game

	move the snake with w, a, s, d
	terminate with x
	
	Linux-System required!
 
	@author: www.c-howto.de
    Enhanced to by a real snake game: peter.sieg2@gmx.de 03/2019
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>

#define BLANK 0
#define HEAD 1
#define TAIL 2
#define FOOD 9
#define WALL '#'
#define KEY_MOVE_UP 119
#define KEY_MOVE_LEFT 97
#define KEY_MOVE_DOWN 115
#define KEY_MOVE_RIGHT 100
#define WIDTH 60
#define HEIGHT 20
#define DEBUG 0

struct position {
	int x;
	int y;
} pos;

int field[WIDTH][HEIGHT];

void resetField();
void printField();
int getItem(int, int);
void setItem(int, int, int);
int move(int);
bool kbhit(void);
void echoOff(void);
void echoOn(void);

int main () {
	int key = KEY_MOVE_UP, lastkey = KEY_MOVE_UP, score = 0;
	resetField();

	pos.x=WIDTH/2;
	pos.y=HEIGHT/2;
	setItem(pos.x, pos.y, HEAD);
	echoOff();

	while(key != 'x') {
		printField();

        if (kbhit()) {
            key = getchar();
            lastkey = key;
        }
        else key = lastkey;

        usleep(200000);

		if (key != 'x') {
            key = move(key);
            score++;
        }
		if(DEBUG) {
			printf(" %d %c |", key);
		}
	}

	printf("\n\nScore: %i\n",score);
	echoOn();
	return 0;
}

int move(int key) {

	setItem(pos.x, pos.y, TAIL);
	switch(key) {
		case KEY_MOVE_UP: pos.y--; break;
		case KEY_MOVE_LEFT: pos.x--; break;
		case KEY_MOVE_DOWN: pos.y++; break;
		case KEY_MOVE_RIGHT: pos.x++; break;
	}

//	if(pos.y >= HEIGHT) pos.y=0;
//	if(pos.y < 0) pos.y=HEIGHT-1;
//	if(pos.x >= WIDTH) pos.x=0;
//	if(pos.x < 0) pos.x=WIDTH-1;

    if (getItem(pos.x, pos.y) == BLANK)	{
        setItem(pos.x, pos.y, HEAD);
        return 0;
    }
    else return 'x'; // snake has moved to none blank field - game over
}

int getItem(int x, int y) {
	return field[x][y];
}

void setItem(int x, int y, int item) {
	field[x][y] = item;
}

void resetField() {
	int x,y;
	for(y=0;y<HEIGHT;y++) {
		for(x=0;x<WIDTH;x++) {
			field[x][y] = WALL;
		}
	}
	for(y=1;y<HEIGHT-2;y++) {
		for(x=1;x<WIDTH-1;x++) {
			field[x][y] = BLANK;
		}
	}
}

void printField() {
	//clear screen
	fprintf(stdout, "\033[2J");
	fprintf(stdout, "\033[1;1H");

	int i,y,x;
	for(y=0;y<HEIGHT;y++) {
		printf("\n");
		for(x=0;x<WIDTH;x++) {
			i = field[x][y];
			switch(i) {
			case BLANK: printf(" "); break;
			case TAIL: printf("*"); break;
			case HEAD: printf("O"); break;
			case WALL: printf("#"); break;
			}
		}
	}

	// print debug things
	if(DEBUG) {
		printf("\n\nX: %3d   Y: %3d", pos.x, pos.y);
		printf("\n\nx: %3d   y: %3d", x, y);
	}
}

bool kbhit(void)
{
    struct termios original;
    tcgetattr(STDIN_FILENO, &original);

    struct termios term;
    memcpy(&term, &original, sizeof(term));

    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    int characters_buffered = 0;
    ioctl(STDIN_FILENO, FIONREAD, &characters_buffered);

    tcsetattr(STDIN_FILENO, TCSANOW, &original);

    bool pressed = (characters_buffered != 0);

    return pressed;
}

void echoOff(void)
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void echoOn(void)
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

