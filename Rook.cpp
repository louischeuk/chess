#include "Rook.h"
#include "ChessBoard.h"

Rook::Rook(Color color, ChessBoard* board)
	: ChessPiece(ROOK, color, board, true) {}

Rook::~Rook(){}

bool Rook::isMoveValid(const std::string source_square, const std::string destination_square) {

	int file_distance = abs(source_square[0] - destination_square[0]);
	int rank_distance = abs(source_square[1] - destination_square[1]);
	std::string passing_square = source_square;

	if (source_square[0] != destination_square[0] || 
		source_square[1] != destination_square[1]) {

		// moving along the same file
		if (source_square[0] == destination_square[0]) {
			signed char rank_increment = (source_square[1] < destination_square[1]) ? 1 : - 1;
			for (auto i = 0; i < rank_distance - 1 ; i++) {
				passing_square[1] = passing_square[1] + rank_increment;
				if (!isEmpty(passing_square)) {
					return false;
				}
			}
			return true; // isEmpty(destination_square) == true
		}

		// move along the same rank
		if (source_square[1] == destination_square[1]) {
			signed char fileIncrement = (source_square[0] < destination_square[0]) ? 1 : - 1;
			for (auto i = 0; i < file_distance - 1; i++) {
				passing_square[0] = passing_square[0] + fileIncrement;
				if (!isEmpty(passing_square)) {
					return false;
				}
			}
			return true;
		}
	}
	return false; // Rook is neither moving along file or rank
}
