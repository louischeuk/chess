#include "Bishop.h"
#include "ChessBoard.h"

Bishop::Bishop(Color color, ChessBoard* board)
	: ChessPiece(BISHOP, color, board, true) {}

Bishop::~Bishop(){}

bool Bishop::isMoveValid(const std::string source_square, const std::string destination_square) {

	int file_distance = abs(source_square[0] - destination_square[0]);
	int rank_distance = abs(source_square[1] - destination_square[1]);

	if (file_distance == rank_distance) {
		signed char file_increment = (source_square[0] < destination_square[0]) ? 1 : - 1;
		signed char rank_increment = (source_square[1] < destination_square[1]) ? 1 : - 1;
		std::string passing_square = source_square;

		for (auto i = 0; i < file_distance - 1; i++) {
			passing_square[0] = passing_square[0] + file_increment;
			passing_square[1] = passing_square[1] + rank_increment;
			if (!isEmpty(passing_square)) {
				return false;
			}
		}
		return true; // it is valid either destination_square is empty or not
	}

	return false; // Bishop is not moving diagonally
}
