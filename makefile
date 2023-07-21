# Compiler
CC := g++
# Include libraries
INCLUDE := -I$(shell pwd)/include
# Source files
SRCS := $(wildcard $(shell pwd)/src/*.cpp)
# Object files
OBJS := $(SRCS:.cpp=.o)
# Executable name
TARGET := main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -L$(shell pwd)/include -lSDL2_image -lSDL2

%.o: %.cpp
	$(CC) $(INCLUDE) -c $< -o $@

run:
	./$(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)
