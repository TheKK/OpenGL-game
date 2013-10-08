CXX = g++
CXXFLAG = -Wall 

SRC = $(PWD)/src/*.cpp
OBJ = main.o timer.o gameMenu.o basicFunctions.o
INCLUDE = -I $(PWD)/include
LIBS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

OUT_EXE = snake

.SUFFIXS:
.SUFFIXS: .o .cpp .h

$(OUT_EXE): $(OBJ)
	$(CXX) $(SRC) $(CXXFLAG) $(INCLUDE) $(LIBS) -g -o $@

%.o: $(PWD)/src/%.cpp 
	$(CXX) $< $(CXXFLAG) $(INCLUDE) $(LIBS) -c
