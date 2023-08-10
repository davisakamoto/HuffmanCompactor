CC = g++
CFLAGS = -Wall -g -c -I$(INC)
LIBS = -lm

SRC = src
OBJ = obj
INC = include
BIN = bin

OBJS = $(OBJ)/main.o $(OBJ)/no.o $(OBJ)/lista.o $(OBJ)/arvore.o
HDRS = $(INC)/no.hpp $(INC)/lista.hpp $(INC)/arvore.hpp

EXE = $(BIN)/main

all:  $(EXE)
	$(EXE) $(BIN)/entrada.txt $(BIN)/saida.txt -c
	$(EXE) $(BIN)/saida.txt $(BIN)/entrada.txt -d
	$(EXE) $(BIN)/entrada2.txt $(BIN)/saida2.txt -c
	$(EXE) $(BIN)/saida2.txt $(BIN)/entrada2.txt -d
	$(EXE) $(BIN)/entrada3.txt $(BIN)/saida3.txt -c
	$(EXE) $(BIN)/saida3.txt $(BIN)/entrada3.txt -d
	$(EXE) $(BIN)/entrada4.txt $(BIN)/saida4.txt -c
	$(EXE) $(BIN)/saida4.txt $(BIN)/entrada4.txt -d
	$(EXE) $(BIN)/entrada5.txt $(BIN)/saida5.txt -c
	$(EXE) $(BIN)/saida5.txt $(BIN)/entrada5.txt -d

$(BIN)/main: $(OBJS)
	$(CC) -pg -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp 

$(OBJ)/no.o: $(HDRS) $(SRC)/no.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/no.o $(SRC)/no.cpp

$(OBJ)/lista.o: $(HDRS) $(SRC)/lista.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/lista.o $(SRC)/lista.cpp

$(OBJ)/arvore.o: $(HDRS) $(SRC)/arvore.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/arvore.o $(SRC)/arvore.cpp
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out

run: all 