#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

class Rook : public ChessPiece {
public:
	Rook(Color color, ChessBoard* board);
	~Rook() override;
	bool isMoveValid(const std::string source_square, const std::string destination_square) override;
};

#endif
