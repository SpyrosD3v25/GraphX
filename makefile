# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -std=c++11 -Iinclude

# Target library name
LIBRARY = libgraphx.a

# Source files for the library
LIB_SRC = src/graph.cpp src/graphics.cpp src/node.cpp src/pos_gen.cpp src/config.cpp

# Object files for the library
LIB_OBJ = $(LIB_SRC:.cpp=.o)

# Source file for the main program
MAIN_SRC = src/main.cpp

# Target for the final executable
TARGET = op

# Default target
all: $(TARGET)

# Rule to build the library
$(LIBRARY): $(LIB_OBJ)
	@echo "Creating static library $(LIBRARY)"
	ar rcs $@ $^

# Rule to build the main application (executable)
$(TARGET): $(LIBRARY) $(MAIN_SRC)
	@echo "Linking executable $(TARGET)"
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(MAIN_SRC) $(LIBRARY) -lGL -lGLU -lglut

# Rule to compile .cpp files into .o object files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(LIB_OBJ) $(LIBRARY)

