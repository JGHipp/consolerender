CC=g++
CFLAGS=-g
FILES=*.cpp
EXEC=consoleRender

consolerender: $(FILES)
	$(CC) $(FILES) $(CFLAGS) -o $(EXEC)
