/* simple SDL demo
   (C) 2021 P. Sieg CC-BY-SA
   
   moving sprites routines seen at: http://gamedevgeek.com/tutorials/moving-sprites-with-sdl/
   inprint routines from: https://github.com/driedfruit/SDL_inprint
   
   V0.1 Initial version 9/2021
   V0.2 + colored flowers 10/2021
*/   
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "inprint.h"

#define FAST_MACHINE  // use at fast machine to delay some screens
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SCREEN_DEPTH 8
#define SPRITE_SIZE    32
#define CLR 255 /* color used for clearing */

SDL_Surface *screen, *temp, *sprite, *sprite2, *sky;
SDL_Rect rcSprite, rcSprite2, rcSky;
int colorkey;

// Exit the game (terminate the process).
void quit(int status) {
    SDL_Quit();
    exit(status);
}

// handle events
void update() {
    SDL_Event event;
    while (SDL_PollEvent(&event) == 1) {
        if (event.type == SDL_QUIT) {
            // the window was closed.
            quit(0);
        } else if (event.type == SDL_KEYDOWN) {
            SDLKey k = event.key.keysym.sym;
            // check if we need to quit.
            if (k == SDLK_ESCAPE || k == SDLK_q) {
                quit(0);
            }
        }
        continue;
    }
}

void wait_a_bit() {
  int c;
  for (c=0; c<5; c++) {
    SDL_Delay(1000);
    update();
  }
}

void draw_bmp() {
  /* load bitmap to temp surface */
  SDL_Surface* temp = SDL_LoadBMP("rect.bmp");

  /* convert bitmap to display format */
  SDL_Surface* bg = SDL_DisplayFormat(temp);

  /* free the temp surface */
  SDL_FreeSurface(temp);

  /* draw the background */
  SDL_BlitSurface(bg, NULL, screen, NULL);

  /* update the screen */
  SDL_UpdateRect(screen, 0, 0, 0, 0);
  
  /* free the background surface */
  SDL_FreeSurface(bg);
}

void clear() {
     SDL_Rect rect1 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
     SDL_FillRect(screen, &rect1, CLR);
     /* update the screen (aka double buffering) */
     SDL_Flip(screen);
     SDL_Delay(1000);
}

void draw_1rect(int x, int y, int c) {
     SDL_Rect rect = {x, y, 20, 15};
     SDL_FillRect(screen, &rect, c);
}

void draw_4rect(int c, int d) {
     int         x = 0; //x coordinate of our pixel
     int         y = 0; //y coordinate of our pixel
     int         x1= 0; //x coordinate of our pixel
     int         y1= 0; //y coordinate of our pixel
     int	 i = 0;

     /* Top - Left */
     /* not in multiple of w=20 and y=15 */
     /* x = rand()%(SCREEN_WIDTH/2); */
     /* y = rand()%(SCREEN_HEIGHT/2); */
     /* in multiple of w=20 and y=15 */
     x = (rand()%(SCREEN_WIDTH/2/20)*20);
     y = (rand()%(SCREEN_HEIGHT/2/15)*15);
     SDL_Rect rect1 = {x, y, 20, 15};
     SDL_FillRect(screen, &rect1, c);
     
     /* Top - right */
     x1 = SCREEN_WIDTH-x; 
     SDL_Rect rect2 = {x1, y, 20, 15};
     SDL_FillRect(screen, &rect2, c);

     /* Bot - Left */
     y1 = SCREEN_HEIGHT-y;
     SDL_Rect rect3 = {x, y1, 20, 15};
     SDL_FillRect(screen, &rect3, c);

     /* Bot - Right */
     x1 = SCREEN_WIDTH-x; 
     y1 = SCREEN_HEIGHT-y;
     SDL_Rect rect4 = {x1, y1, 20, 15};
     SDL_FillRect(screen, &rect4, c);

     /* update the screen (aka double buffering) */
     SDL_Flip(screen);
     for (i=0; i<5; i++) {
       SDL_Delay(d);
       update();
     }
}

void draw_flower(int c, int d) {
     int         x = 0; //x coordinate of our pixel
     int         y = 0; //y coordinate of our pixel
     int         x1= 0; //x coordinate of our pixel
     int         y1= 0; //y coordinate of our pixel
     int	 i = 0;

     /* Left */
     /* not in multiple of w=20 and y=15 */
     /* x = rand()%(SCREEN_WIDTH); */
     /* y = rand()%(SCREEN_HEIGHT); */
     /* in multiple of w=20 and y=15 */
     x = (rand()%(SCREEN_WIDTH/20)*20);
     y = (rand()%(SCREEN_HEIGHT/15)*15);
     SDL_Rect rect1 = {x, y, 20, 15};
     SDL_FillRect(screen, &rect1, c);
     
     /* Right */
     x1 = x+40; 
     SDL_Rect rect2 = {x1, y, 20, 15};
     SDL_FillRect(screen, &rect2, c);

     /* Bot */
     x1 = x+20; 
     y1 = y+15;
     SDL_Rect rect3 = {x1, y1, 20, 15};
     SDL_FillRect(screen, &rect3, c);

     /* Top */
     y1 = y-15;
     SDL_Rect rect4 = {x1, y1, 20, 15};
     SDL_FillRect(screen, &rect4, c);

     /* update the screen (aka double buffering) */
     SDL_Flip(screen);
     for (i=0; i<5; i++) {
       SDL_Delay(d);
       update();
     }
}

void buzzword(int j, int x, int y) {
     switch (j) {
	    case 0: inprint(screen, "GOD", x, y); break;
	    case 1: inprint(screen, "SUN", x, y); break;
	    case 2: inprint(screen, "EARTH", x, y); break;
	    case 3: inprint(screen, "UNIVERSE", x, y); break;
	    case 4: inprint(screen, "LOVE", x, y); break;
	    case 5: inprint(screen, "SPIRIT", x, y); break;
	    case 6: inprint(screen, "FREEDOM", x, y); break;
	    case 7: inprint(screen, "ENERGY", x, y); break;
	    case 8: inprint(screen, "2BE", x, y); break;
	    case 9: inprint(screen, "PEACE", x, y); break;
     }
}

int main(int argc, char *argv[]) {
     time_t t;
     Uint32	 fg;
     Uint8       *p;
     int         x = 0; //x coordinate of our pixel
     int         y = 0; //y coordinate of our pixel
     int	 c = 0;
     int	 i = 0;
     int	 j = 0;
     
     /* Intializes random number generator */
     srand((unsigned) time(&t));

     /* Initialize SDL */
     SDL_Init(SDL_INIT_VIDEO);
     
     /* Initialize the screen / window */
     screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_SWSURFACE);
     
     /* load sky */
     temp  = SDL_LoadBMP("sky.bmp");
     sky = SDL_DisplayFormat(temp);
     SDL_FreeSurface(temp);
     
     /* load sprite */
     temp   = SDL_LoadBMP("sprite.bmp");
     sprite = SDL_DisplayFormat(temp);
     SDL_FreeSurface(temp);

     /* setup sprite colorkey and turn on RLE */
     colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
     SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

     /* set sprite position */
     rcSprite.x = rand()%14*20;
     rcSprite.y = rand()%14*15;

     for (i=0;i<100;i++) {

	/* draw the sky */
	for (x = 0; x < SCREEN_WIDTH/SPRITE_SIZE; x++) {
		for (y = 0; y <= SCREEN_HEIGHT/SPRITE_SIZE; y++) {
			rcSky.x = x * SPRITE_SIZE;
			rcSky.y = y * SPRITE_SIZE;
			SDL_BlitSurface(sky, NULL, screen, &rcSky);
		}
	}
	/* draw the sprite */
	SDL_BlitSurface(sprite, NULL, screen, &rcSprite);

	/* update the screen */
	SDL_UpdateRect(screen,0,0,0,0);
	
	x=((rand()%3)-1)*20;
	y=((rand()%3)-1)*15;

	rcSprite.x = rcSprite.x + x;
	rcSprite.y = rcSprite.y + y;
	
	/* collide with edges of screen */
	if ( rcSprite.x < 0 ) {
		rcSprite.x = SCREEN_WIDTH-SPRITE_SIZE;
	}
	else if ( rcSprite.x > SCREEN_WIDTH-SPRITE_SIZE ) {
		rcSprite.x = 0;
	}
	if ( rcSprite.y < 0 ) {
		rcSprite.y = SCREEN_HEIGHT-SPRITE_SIZE;
	}
	else if ( rcSprite.y > SCREEN_HEIGHT-SPRITE_SIZE ) {
		rcSprite.y = 0;
	}
#ifdef FAST_MACHINE
        SDL_Delay(100);
#endif
     }

     clear();

     /* show sdl logo */
     draw_bmp();
     wait_a_bit();
     clear();

     // buzzwords bw
     prepare_inline_font();
	
     incolor(0xFFFFFF, 0x000000);

	for (i=0; i<30; i++) {
	  j = rand()%10;
	  x = (rand()%25)*10+20;
	  y = (rand()%20)*10+30;
	  buzzword(j,x,y);
	  SDL_Flip(screen); 
	  SDL_Delay(500);
	}

     wait_a_bit();
     clear();
     
     // buzzwords color
     //prepare_inline_font();
	
	for (i=0; i<30; i++) {
	  j = rand()%10;
	  x = (rand()%25)*10+20;
	  y = (rand()%20)*10+30;
	  fg= rand()%0xFFFF00;
          incolor(0xFFFFFF, fg);
	  buzzword(j,x,y);
	  SDL_Flip(screen); 
	  SDL_Delay(500);
	}

     wait_a_bit();
     kill_inline_font();
     clear();
     
     /* load sprite 1 */
     temp   = SDL_LoadBMP("maze1.bmp");
     sprite = SDL_DisplayFormat(temp);
     SDL_FreeSurface(temp);

     /* load sprite 2 */
     temp   = SDL_LoadBMP("maze2.bmp");
     sprite2= SDL_DisplayFormat(temp);
     SDL_FreeSurface(temp);

     /* draw the maze */
     for (i=0; i<3; i++) {
        for (y = 0; y <= SCREEN_HEIGHT/SPRITE_SIZE; y++) {
           for (x = 0; x < SCREEN_WIDTH/SPRITE_SIZE; x++) {
		c = rand()%200;
		if (c>=100) { 
		  rcSprite.x = x * SPRITE_SIZE;
		  rcSprite.y = y * SPRITE_SIZE;
		  SDL_BlitSurface(sprite, NULL, screen, &rcSprite);
		}
		else {
		  rcSprite2.x = x * SPRITE_SIZE;
		  rcSprite2.y = y * SPRITE_SIZE;
		  SDL_BlitSurface(sprite2, NULL, screen, &rcSprite2);
		}
		/* update the screen */
		SDL_UpdateRect(screen,0,0,0,0);
		update();
	   }
        }
        for (c=0; c<100; c++) {
           SDL_Delay(100);
           update();
        }
     }
     clear();
     SDL_FreeSurface(sprite);
     SDL_FreeSurface(sprite2);
    
     /* draw all color flowers */
     for (i=100;i>50;i--) draw_flower(rand()%255,i);
     wait_a_bit();
     clear();
     
     /* draw blue and green rects caleidoscope */
     for (i=100;i>0;i--) draw_4rect(rand()%10+5,i);

     /* slowly clear caleidoscope */
     for (i=110;i>0;i--) draw_4rect(CLR,i);

     /* draw all color rects caleidoscope */
     for (i=100;i>0;i--) draw_4rect(rand()%255,i);

     /* slowly clear caleidoscope */
     for (i=110;i>0;i--) draw_4rect(CLR,i);
     
     clear();
     
     for (y=0; y<SCREEN_HEIGHT; y+=15) {
       for (x=0; x<SCREEN_WIDTH; x+=20) {
         c = rand() % 255; /* color */
         draw_1rect(x,y,c);
       }
     }
     /* update the screen (aka double buffering) */
     SDL_Flip(screen);
     for (c=0; c<100; c++) {
       SDL_Delay(100);
       update();
     }

     clear();
     SDL_Quit();
     return 0;
}


