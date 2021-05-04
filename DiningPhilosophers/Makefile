CXX := g++
CXX_FLAGS := -std=c++17 -ggdb -pthread

BIN := bin
SRC := src 
INCLUDE := include 

LIBRARIES := 
EXECUTABLE := main 

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): src/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
