#include "Queen.h"
#include "ChessBoard.h"

Queen::Queen(Color color, ChessBoard* board)
	: ChessPiece(QUEEN, color, board, true) {}

Queen::~Queen(){}

bool Queen::isMoveValid(const std::string source_square, const std::string destination_square) {

	int file_distance = abs(source_square[0] - destination_square[0]);
	int rank_distance = abs(source_square[1] - destination_square[1]);
	signed char file_increment = (source_square[0] < destination_square[0]) ? 1 : - 1;
	signed char rank_increment = (source_square[1] < destination_square[1]) ? 1 : - 1;
	std::string passing_square = source_square;

	// Queen moving along file or rank
	if (source_square[0] != destination_square[0] || source_square[1] != destination_square[1]) {
		
		// moving along the same file
		if (source_square[0] == destination_square[0]) { 
			for (auto i = 0; i < rank_distance - 1 ; i++) {
				passing_square[1] = passing_square[1] + rank_increment;
				if (!isEmpty(passing_square)) {
					return false;
				}
			}
			return true; // is valid whether destination_square is empty or not
		}
		
		// moving along the same rank 
		if (source_square[1] == destination_square[1]) {
			for (auto i = 0; i < file_distance - 1; i++) {
				passing_square[0] = passing_square[0] + file_increment;
				if (!isEmpty(passing_square)) {
					return false;
				}
			}
			return true; // is valid whether destination_square is empty or not
		}
	}

	// Queen moving diagonally
	if (file_distance == rank_distance) {
		for (auto i = 0; i < file_distance - 1; i++) {
			passing_square[0] = passing_square[0] + file_increment;
			passing_square[1] = passing_square[1] + rank_increment;
			if (!isEmpty(passing_square)) {
				return false;
			}
		}
		return true; // is valid whether destination_square is empty or not
	}

	return false; // Queen is neither moving along rank, file or diagonally
}
