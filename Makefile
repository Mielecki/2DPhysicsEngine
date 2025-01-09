CXX = g++
CXXFLAGS = -Wall -std=c++11
INCLUDE = -I./include
LIBS = `sdl2-config --libs`

SRC = src/main.cpp src/graphics.cpp src/circle.cpp src/engine.cpp src/timer.cpp
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
