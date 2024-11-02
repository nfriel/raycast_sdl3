main: src/main.c src/lib/start.h src/lib/loop.h src/lib/board.h src/lib/cast.h
	clang src/main.c -o main -lSDL3
	./main
