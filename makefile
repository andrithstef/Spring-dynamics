
# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra

# SFML library flags
SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS := main.cpp EntityManager.cpp Weight.cpp Spring.cpp utils.cpp InputHandler.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable name
TARGET := physics_simulation

# Build rule
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(SFML_FLAGS)

# Object file compilation rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
