#ifndef inprint_h
#define inprint_h

#include <SDL/SDL.h>

extern void prepare_inline_font(void);
extern void kill_inline_font(void);

extern void infont(SDL_Surface *font);
extern void incolor(Uint32 fore, Uint32 back); /* Colors must be in 0x00RRGGBB format ! */
extern void inprint(SDL_Surface *dst, const char *str, Uint32 x, Uint32 y);

extern SDL_Surface *get_inline_font(void);

#endif /* inprint_h */
