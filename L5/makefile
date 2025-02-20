CXX = g++
CXXFLAGS = -Wall -std=c++20

OBJECTS = main.o threadsafe_stack.o

# Final executable name
TARGET = main

# Rule to build the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Rule to compile main.cpp
main.o: main.cpp threadsafe_stack.o
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Rule to compile threadsafe_stack.cpp
threadsafe_stack.o: threadsafe_stack.cpp
	$(CXX) $(CXXFLAGS) -c threadsafe_stack.cpp -o threadsafe_stack.o

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJECTS) $(TARGET)


