CXX = g++
CXXFLAGS = -Wall -std=c++11
INCLUDE = -I./include $(shell sdl2-config --cflags) -I/usr/include/SDL2
LIBS = $(shell sdl2-config --libs) -lSDL2_ttf

SRC = src/main.cpp src/graphics.cpp src/particle.cpp src/engine.cpp src/timer.cpp src/texture.cpp
OBJ = $(SRC:src/%.cpp=build/%.o)
TARGET = 2DPhysicsEngine

all: clean $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)
	./$(TARGET)

build/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f build/*.o $(TARGET)
