CXX=g++ -std=c++14 -g -Wall
EXE=ChessMain.o ChessBoard.o ChessPiece.o King.o Queen.o Bishop.o Knight.o Rook.o Pawn.o

chess: $(EXE)
	$(CXX) $(EXE) -o chess

%.o: %.cpp %.h %ChessPiece.h
	$(CXX) -c $<

ChessMain.o: ChessBoard.h
ChessBoard.o: King.h Queen.h Bishop.h Rook.h Knight.h Pawn.h 
ChessPiece.o: ChessBoard.h

clean:
	rm -f *.o chess
