#include "King.h"
#include "ChessBoard.h"

King::King(Color color, ChessBoard* board)
	: ChessPiece(KING, color, board, true) {}

King::~King(){}

bool King::isMoveValid(const std::string source_square, const std::string destination_square) {

	int file_distance = abs(source_square[0] - destination_square[0]);
	int rank_distance = abs(source_square[1] - destination_square[1]);

	if ((file_distance == 0 && rank_distance == 1) ||
		(file_distance == 1 && rank_distance == 0) ||
		(file_distance == 1 && rank_distance == 1)) {
			return true;
		}

	// for castling
	if (first_move_ == true) {
		if (file_distance == 2 && rank_distance == 0) {
			signed char file_increment = (source_square[0] < destination_square[0]) ? 1 : - 1;
			std::string passing_square = source_square;

			passing_square[0] = passing_square[0] + file_increment;
			if (isEmpty(passing_square) && isEmpty(destination_square)) {
				return true;
			}
		}
	}

	return false; // King is neither moving one step nor going for castling
}