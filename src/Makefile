CC=g++-5
CFLAGS=-c -std=c++11
LDFLAGS=
SOURCES=main.cpp eight_puzzle.cpp search_tree_node.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=eightpuzzle
BUILD_DIR=./bin

all: $(SOURCES) $(EXECUTABLE)
	
debug: CFLAGS += -DDEBUG -g
debug: $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) copy
	mkdir -p $(BUILD_DIR)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BUILD_DIR)/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm *.o
	rm -rf $(BUILD_DIR)
	
copy:
	mkdir -p $(BUILD_DIR)
	cp -f ./Makefile $(BUILD_DIR)/Makefile
	
check:
	./$(EXECUTABLE)
	
check_d:
	gdb --args $(EXECUTABLE)