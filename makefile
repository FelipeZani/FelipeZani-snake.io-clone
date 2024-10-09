# Compiler
CC := g++

# Directories
IDIR = ./include/headers/
SRCDIR = ./src/

# Compiler and linker flags
CFLAGS = -I$(IDIR) -I/usr/include/SDL2
LDFLAGS = -lSDL2 -lSDL2_image -ljpeg -ltiff

# Source files
SOURCES = $(wildcard $(SRCDIR)*.cpp)

# Target
all: main

main: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

# Run the executable
run:
	./main

# Clean the build
clean:
	rm -f main

