CXX = g++
ifndef VIEW
	CXXFLAGS = -std=c++14 -Wall -g -MMD
else
	CXXFLAGS = -std=c++14 -Wall -g -MMD -DVIEW=1
endif 
EXEC = chess
OBJECTS = main.o ChessBoard.o Game.o Piece.o King.o Queen.o Rook.o Bishop.o Knight.o Pawn.o Move.o Player.o Person.o AI.o AILvl1.o AILvl2.o AILvl3.o AILvl4.o AILvl5.o Subject.o Observer.o TextObserver.o GraphicsObserver.o Window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
ifndef VIEW
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 
else 
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11
endif 
	
-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
