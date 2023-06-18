CXX=g++
LD=g++
EXECUTABLE=anisimyk
SOURCES=$(wildcard src/*.cpp)
CXX_FLAGS=-Wall -pedantic -Wextra -std=c++17 -fsanitize=address -g -I/
LIBS= -ljpeg 

all: doc compile 

%.o: %.cpp
	@$(CXX) $(CXX_FLAGS) -c -o $@ -c $< $(LIBS)

compile: $(SOURCES:.cpp=.o)
	@$(CXX) $(CXX_FLAGS) $(SOURCES:.cpp=.o) -o $(EXECUTABLE) $(LIBS)

run: compile
	@./$(EXECUTABLE)

doc:
	doxygen Doxyfile

clean:
	rm anisimyk src/*.o 

