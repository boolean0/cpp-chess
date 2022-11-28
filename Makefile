CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -Wall -g -MMD
EXEC = chess
OBJECTS = main.o ChessBoard.o Piece.o King.o Queen.o Rook.o Bishop.o Knight.o Pawn.o Move.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
