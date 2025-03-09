CXX = g++
CXXFLAGS = -std=gnu++20 -Wall -Wextra -Wshadow -O2 -pedantic -Wno-sign-conversion -I /Users/kutay/CP/ac-library 
DEBUGFLAGS = -fsanitize=address -fsanitize=undefined -DLOCAL -DDEBUG -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
CXXFLAGS += $(DEBUGFLAGS)

# Compile and run a file specified via command-line argument
# Usage: make run FILE=myfile.cpp
run:
ifndef FILE
	@echo "Error: Please specify a file using FILE=<filename>"
	@echo "Example: make run FILE=myfile.cpp"
else
	$(CXX) $(CXXFLAGS) $(FILE) -o $(basename $(FILE)).out
	./$(basename $(FILE)).out
endif

.PHONY: run