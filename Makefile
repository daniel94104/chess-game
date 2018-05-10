CXX = g++
CXXFLAGS = -Wall -MMD -g -std=c++03
EXEC = Chess
OBJECTS = Main.o Piece.o Controller.o Game.o TextDisplay.o View.o Bishop.o King.o Knight.o Pawn.o Queen.o Rook.o Player.o GraphicDisplay.o window.o Computer1.o Computer2.o
DEPENDS = ${OBJECTS:.o=.d}
CC = gcc

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

