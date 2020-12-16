#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece {
public:
	Knight(Color color, ChessBoard* board);
	~Knight() override;
	bool isMoveValid(const std::string source_square, const std::string destination_square) override;
};

#endif
