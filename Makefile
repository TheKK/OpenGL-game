CXX = g++
CXXFLAG = -Wall 

SRC = $(PWD)/src/*.cpp
OBJ = main.o timer.o gameStart.o basicFunctions.o
INCLUDE = -I $(PWD)/include
LIBS = -lSDL2 -lSDL2main -lSDL_image -lSDL_ttf -lSDL_mixer

OUT_EXE = snake

.SUFFIXS:
.SUFFIXS: .o .cpp .h

$(OUT_EXE): $(OBJ)
	$(CXX) $(SRC) $(CXXFLAG) $(INCLUDE) $(LIBS) -g -o $@

%.o: $(PWD)/src/%.cpp 
	$(CXX) $< $(CXXFLAG) $(INCLUDE) $(LIBS) -c
