#include "Pawn.h"
#include "ChessBoard.h"

Pawn::Pawn(Color color, ChessBoard* board)
	: ChessPiece(PAWN, color, board, true) {}

Pawn::~Pawn(){}

bool Pawn::isMoveValid(const std::string source_square, const std::string destination_square) {

	int file_distance = abs(source_square[0] - destination_square[0]);
	int rank_distance = abs(source_square[1] - destination_square[1]);

	if (color_ == WHITE) {
		if (source_square[1] > destination_square[1]) {
			return false;
		}
	}

	if (color_ == BLACK) {
		if (source_square[1] < destination_square[1]) {
			return false;
		}
	}

	// check if Pawn moves two square ahead at first time moving
	if ((color_ == WHITE && source_square[1] == '2') || 
		(color_ == BLACK && source_square[1] == '7')) {

		if (first_move_ == true && file_distance == 0 && rank_distance == 2) {
			signed char rank_increment = (source_square[1] < destination_square[1]) ? 1 : -1;
			std::string passing_square = source_square;
			passing_square[1] = passing_square[1] + rank_increment;
			
			if (isEmpty(passing_square) && isEmpty(destination_square)) {
				return true;
			}
			return false;
		}
	}
	
	// check if Pawn moves diagonally
	if (file_distance == 1 && rank_distance == 1) {
		if (!isEmpty(destination_square)) {
			return true;
		}
		return false; // Pawn cannot move to empty square diagonally
	}

 	// move one step forwards
	if (file_distance == 0 && rank_distance == 1) {
		if (!isEmpty(destination_square)) {
			return false;
		}
		return true;
	}

	return false; // none of the condition above matches
}
