#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
#include <map>
#include <iostream>

enum Type { KING, ROOK, BISHOP, QUEEN, KNIGHT, PAWN };
enum Color { WHITE, BLACK };

std::ostream& operator <<(std::ostream& out, Type type); 	/* operator overloading */
std::ostream& operator <<(std::ostream& out, Color color);  /* operator overloading */

class ChessBoard; /* forward declaration of ChessBoard class */

class ChessPiece {
protected:
	Type type_;
	Color color_;
	ChessBoard* chess_board_; /* for accessing the position of the ChessPieces */
	bool first_move_;
public:
	ChessPiece(Type type, Color color, ChessBoard* chessBoard, bool firstMove = true);
	virtual ~ChessPiece();
	virtual bool isMoveValid(const std::string sourceSquare, const std::string destinationSquare) = 0;
	bool isEmpty(const std::string square);
	bool isFirstMove() const;
	void setFirstMoveToFalse();
	Color getColor() const;
	Type getType() const;
};
#endif
