CXX = g++
CXXFLAG = -Wall 

SRC = $(PWD)/main.cpp timer.cpp
OBJ = main.o timer.o
LIBS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

OUT_EXE = snake


$(OUT_EXE) : $(OBJ)
	$(CXX) $(CXXFLAG) -g -o $@ $(SRC) $(LIBS)

