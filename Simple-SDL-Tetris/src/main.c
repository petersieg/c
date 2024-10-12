// Source from: https://github.com/olzhasar/sdl-tetris
// 2024-10 P. Sieg:
// Just took out sdl_ttf requirements and report score to SCORE.TXT
// (Because sdl_ttf has huge dependencies)

#include "definitions.h"
#include "game.h"

//#ifdef __EMSCRIPTEN__
//void run_loop() { game_loop(); }
//#endif

#if defined(_WIN32) || defined(_WIN64)
        char os[25] = "Windows";
#else
#ifdef __linux
        char os[25]  = "Linux";
#else
#if defined(__APPLE__) && defined(__MACH__)
        char os[25]  = "MacOS";
#else
        char os[25]  = "Unknown";
#endif
#endif
#endif

int main(int argc, char **argv) {
//#ifndef __EMSCRIPTEN__
  srand(time(NULL)); // seed the random number generator
//#endif
  strcpy(progname,argv[0]);
  if (init_game() != 0) {
    SDL_LogError(0, "Failed to start game\n");
    return 1;
  };

//#ifdef __EMSCRIPTEN__
//  emscripten_set_main_loop(run_loop, 0, 1);
//#else
  while (1) {
    int res = game_loop();

    if (res != 0) {
      if (res < 0) {
        SDL_LogError(0, "Unexpected error occured\n");
      }
      break;
    }
  }
//#endif

  if (terminate_game() != 0) {
    SDL_LogError(0, "Error while terminating game\n");
  };

  return 0;
}
