CC=g++
CFLAGS=-g
FILES=*.cpp
EXEC=consoleRender

raycaster: $(FILES)
	$(CC) $(FILES) $(CFLAGS) -o $(EXEC)
