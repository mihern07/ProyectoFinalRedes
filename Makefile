CXX		  := g++
CXX_FLAGS := -Wall -Wno-unknown-pragmas -Wextra -std=c++17 -ggdb 

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
SERVER 	:= server
CLIENT 	:= client

LIBRARIES	:= -lSDL2 -lSDL2main -lpthread -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lGL -g `sdl2-config --cflags --libs` 
EXECUTABLE	:= snake
SERVER_EXE	:= server
SERVER_SRC := server/src
INCLUDE_CLIENT := client/include
INClUDE_SERVER := server/include
CLIENT_SRC 	:= client/src
COMMON 		:= Common

all: $(BIN)/$(EXECUTABLE) $(BIN)/$(SERVER_EXE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)
	./$(BIN)/$(SERVER_EXE)

$(BIN)/$(EXECUTABLE): $(CLIENT_SRC)/*.cpp $(COMMON)/*.cpp  
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_CLIENT) -I$(COMMON) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(SERVER_EXE): $(SERVER_SRC)/*.cpp $(COMMON)/*.cpp  
	$(CXX) $(CXX_FLAGS) -I$(COMMON) -I$(INClUDE_SERVER) -L$(LIB)  $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*