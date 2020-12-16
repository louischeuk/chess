#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece {
public:
	King(Color color, ChessBoard* board);
	~King() override;
	bool isMoveValid(const std::string source_square, const std::string destination_square) override;
};

#endif
