#include "Knight.h"
#include "ChessBoard.h"

Knight::Knight(Color color, ChessBoard* board)
	: ChessPiece(KNIGHT, color, board, true) {}

Knight::~Knight(){}

bool Knight::isMoveValid(const std::string source_square, const std::string destination_square) {

	int file_distance = abs(source_square[0] - destination_square[0]);
	int rank_distance = abs(source_square[1] - destination_square[1]);

	if ( (file_distance == 2 && rank_distance == 1) ||
		 (file_distance == 1 && rank_distance == 2) ) {
			 return true;
		 }

	return false; // Knight is not moving in L shape
}
