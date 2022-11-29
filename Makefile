CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -Wall -g -MMD
EXEC = chess
OBJECTS = main.o ChessBoard.o Game.o Piece.o King.o Queen.o Rook.o Bishop.o Knight.o Pawn.o Move.o Player.o Person.o AI.o AILvl1.o AILvl2.o AILvl3.o AILvl4.o Subject.o Observer.o TextObserver.o GraphicsObserver.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
