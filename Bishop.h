#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public ChessPiece {
public:
	Bishop(Color color, ChessBoard* board);
	~Bishop() override;
	bool isMoveValid(const std::string source_square, const std::string destination_square) override;
};

#endif
