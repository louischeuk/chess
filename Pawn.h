#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
public:
	Pawn(Color color, ChessBoard* board);
	~Pawn() override;
	bool isMoveValid(const std::string source_square, const std::string destination_square) override;
};

#endif
