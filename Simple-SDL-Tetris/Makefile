CC := gcc

CFLAGS := `sdl2-config --cflags` -O3 --std=c99
LDFLAGS := `sdl2-config --libs` -lm 
EXTRA_FLAGS :=

HDRS :=

SRCS := $(wildcard src/*.c)

OBJS := $(SRCS:.c=.o)

EXEC := game

# Emscripten
EMCC := EMSDK_PYTHON=/usr/bin/python3 emcc
EMSCRIPTEN_ACTIVATE_SCRIPT := ~/emsdk/emsdk_env.sh

EM_BUILD_DIR := dist

EMFLAGS = -sUSE_SDL=2 -sALLOW_MEMORY_GROWTH -s -O3 -s --std=c99

# default recipe
all: compile_run

compile_run: compile
	./$(EXEC)

compile: $(OBJS) $(HDRS) Makefile
	$(CC) -o $(EXEC) $(OBJS) $(LDFLAGS) $(EXTRA_FLAGS)

debug:
	$(MAKE) EXTRA_FLAGS='-ggdb3 -O0 -fsanitize=address,undefined'

%.o: %.c $(HDRS) Makefile
	$(CC) -o $@ -c $< $(CFLAGS) $(EXTRA_FLAGS)

clean:
	rm -f $(EXEC) $(OBJS)
	rm -rf $(EM_BUILD_DIR)

wasm_build_dir:
	mkdir -p $(EM_BUILD_DIR)

wasm: wasm_build_dir
	source $(EMSCRIPTEN_ACTIVATE_SCRIPT)
	cp index.html $(EM_BUILD_DIR)
	$(EMCC) $(SRCS) $(EMFLAGS) -o $(EM_BUILD_DIR)/index.js

wasm_serve: clean wasm
	open http://localhost:8000
	python -m http.server -d $(EM_BUILD_DIR) 8000

publish:
	git checkout gh-pages
	git reset --hard master
	$(MAKE) clean
	$(MAKE) wasm
	mv -f dist/* .
	rm -rf dist/
	git rm -rf src/ README.md preview.gif
	git add --all
	git commit -m "Deploy"
	git push --force origin gh-pages
	git checkout master

.PHONY: all clean compile compile_run debug wasm wasm_serve wasm_build_dir publish
