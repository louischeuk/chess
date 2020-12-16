#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "ChessPiece.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>

class ChessBoard {
private:
	std::vector<ChessPiece*> pieces_captured_; 			/* collect the captured pieces */
	std::map<std::string, ChessPiece*> m_chessboard_; 	/* store the position of ChessPieces */
	Color turn_;
	std::string white_king_pos_;
	std::string black_king_pos_;
private:
	void startGame();
	void createPiecesAndConfigBoard();
	void switchTurn();
	/* undo the temporary move made in isSelfKingInCheck() */
	void undoTempMakeMove(ChessPiece* temp_captured_chesspiece, 
		const std::string source_square, const std::string destination_square);
	/* update the position of King once its position has changed */
	void updateKingPos(const Color self_color, const std::string destination_square);
	void makeMove(const std::string source_square, const std::string destination_square);
	/* respond for making the move when it is a castling move */
	void makeCastlingMove(const std::string source_square, const std::string destination_square);
	
	bool isOutOfBound(const std::string square) const;
	bool isColorDifferent(const std::string source_square, const std::string destination_square);
	bool isFirstMove(const std::string square);
	bool isSelfKingInCheck(const Color self_color, const std::string source_square, const std::string destination_square);
	bool isOpponentKingInCheck(const Color opponent_color, const std::string square);
	bool isOpponentKingInCheckmate(const Color opponent_color, const std::string square_call_check);
	bool isCastlingValid(const Color self_color, const std::string source_square, const std::string destination_square);
	bool isKingInCheckCastling(const Color self_color, const std::string kingPos);
	bool hasAnyLegalMove(const Color opponent_color, const std::string source_square, const std::string destination_square);

	/* return true if any opponent-side chesspiece can capture the self-side chesspiece that calls the check */
	bool isbreakCheckmateStratOneWork(const Color opponent_color, const std::string square_call_check);
	/* return true if any opponent-side chesspiece can block between self-side chesspiece and opponent-side King */
	bool isbreakCheckmateStratTwoWork(const Color opponent_color, const std::string square_call_check);
	/* return true if the opponent-side King can get away from being check by moving a particular square */
	bool isbreakCheckmateStratThreeWork(const Color opponent_color, const std::string square_call_check);

	void printMoveSuccessMessage(const std::string source_square, const std::string destination_square);
	void printMoveFailMessage(const std::string source_square, const std::string destination_square);

	/* get the Piece color by calling getColor() in ChessPiece class */
	Color getPieceColor(const std::string square); 	 
	/* call the Piece type by calling getType() in ChessPiece class */
	Type getPieceType(const std::string square); 	 
public:
	ChessBoard();
	~ChessBoard();	 
	std::map<std::string, ChessPiece*> getChessboard() const;
	void resetBoard();
	void submitMove(const std::string source_square, const std::string destination_square);
};

#endif