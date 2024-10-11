# SDL Tetris

Source from: https://github.com/olzhasar/sdl-tetris

I just took out any sdl_ttf (because of huge dependencies) requirements. Score is appended to file SCORE.TXT at end/quit of game.

An implementation of the classic [Tetris game](https://en.wikipedia.org/wiki/Tetris) in the C programming language using the [SDL-2 library](https://www.libsdl.org/)

## Desktop preview

![Preview](preview.jpeg)

## Installation

1. Clone this repository to your system:

```sh
git clone https://github.com/olzhasar/Simple-SDL-Tetris.git
```

2. [Install](https://wiki.libsdl.org/SDL2/Installation) SDL2 on your machine

- On MacOS you can use Homebrew:

```sh
brew install sdl2
```

3. Compile and run the project code with make

```sh
cd Simple-SDL-Tetris
make
```

## Controls

- Rotate: Up arrow, W
- Move Left: Left arrow, A
- Move Right: Right arrow, D
- Soft Drop: Down arrow, S
- Hard drop: Space
- Quit: ESC

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
