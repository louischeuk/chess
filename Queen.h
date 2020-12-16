#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

class Queen : public ChessPiece {
public:
	Queen(Color color, ChessBoard* board);
	~Queen() override;
	bool isMoveValid(const std::string source_square, const std::string destination_square) override;
};

#endif
