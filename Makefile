CC = gcc
CXX = g++
CFLAG = -g -O3
LFLAG = -c
OMPFLAG = -fopenmp
LIBS = -lm
COMMON_DIR = ./common
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

% : %.o Configuration.o Measurements.o
	mkdir -p $(BIN_DIR)
	$(CXX)  -lpapi $(CFLAG) $(OMPFLAG) $(OBJ_DIR)/$@.o $(OBJ_DIR)/Configuration.o $(OBJ_DIR)/Measurements.o -o $(BIN_DIR)/$@ $(LIBS)

%.o : $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -lpapi $(LFLAG) $(OMPFLAG) $(CFLAG) $< -o $(OBJ_DIR)/$@

Configuration.o: $(COMMON_DIR)/Configuration.cpp $(COMMON_DIR)/Configuration.h
	mkdir -p $(OBJ_DIR)
	$(CXX) $(LFLAG) $(CFLAG) $(COMMON_DIR)/Configuration.cpp -o $(OBJ_DIR)/$@ 

Measurements.o: $(COMMON_DIR)/Measurements.cpp $(COMMON_DIR)/Measurements.h 
	mkdir -p $(OBJ_DIR)
	$(CXX) $(LFLAG) $(CFLAG) $(COMMON_DIR)/Measurements.cpp -o $(OBJ_DIR)/$@ 

clean: 
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*

driver-clean:
	rm -f $(SRC_DIR)/adapt_membench_*.cpp
	rm -f $(SRC_DIR)/*.c
