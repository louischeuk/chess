#include "ChessPiece.h"
#include "ChessBoard.h"

/* operator overloading */
std::ostream& operator <<(std::ostream& out, Type type) {
	switch(type){
		case KING:	 std::cout << "King"; 	break;
		case ROOK: 	 std::cout << "Rook";   break;
		case BISHOP: std::cout << "Bishop"; break;
		case QUEEN:  std::cout << "Queen"; 	break;
		case KNIGHT: std::cout << "Knight"; break;
		case PAWN:   std::cout << "Pawn"; 	break;
		default:;
	}
	return out;
}

std::ostream& operator <<(std::ostream& out, Color color) {
	switch(color){
		case BLACK: std::cout << "Black"; break;
		case WHITE: std::cout << "White"; break;
		default:;
	}
	return out;
}


ChessPiece::ChessPiece(Type type, Color color, ChessBoard *chessBoard, bool firstMove):
type_(type), color_(color), chess_board_(chessBoard), first_move_(firstMove) {}

ChessPiece::~ChessPiece(){}

bool ChessPiece::isEmpty(const std::string square) {
	return (chess_board_->getChessboard()[square] != nullptr) ? false : true;
}

Color ChessPiece::getColor() const{
	return color_;
}

Type ChessPiece::getType() const{
	return type_;
}
bool ChessPiece::isFirstMove() const {
	return first_move_;
}

void ChessPiece::setFirstMoveToFalse() {
	first_move_ = false;
}