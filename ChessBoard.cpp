#include "ChessBoard.h"
#include "Queen.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"

ChessBoard::ChessBoard() {
	createPiecesAndConfigBoard();
	startGame();
}

ChessBoard::~ChessBoard() {
	std::map<std::string,ChessPiece*>::iterator it = m_chessboard_.begin();
	while (it != m_chessboard_.end()) {
		delete it->second;
		it++;
	}

	for (unsigned i=0; i < pieces_captured_.size(); i++) {
		delete pieces_captured_[i];
	}
}

/* ======= private functions ======= */
void ChessBoard::startGame() {
	std::vector<ChessPiece*> pieces_captured_ = {nullptr};
	turn_ = WHITE;
	white_king_pos_ = "E1";
	black_king_pos_ = "E8";
	std::cout << "A new chess game is started!\n";
}

void ChessBoard::createPiecesAndConfigBoard() {

	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("A1", new Rook(WHITE, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("B1", new Knight(WHITE, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("C1", new Bishop(WHITE, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("D1", new Queen(WHITE, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("E1", new King(WHITE, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("F1", new Bishop(WHITE, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("G1", new Knight(WHITE, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("H1", new Rook(WHITE, this)));

	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("A8", new Rook(BLACK, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("B8", new Knight(BLACK, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("C8", new Bishop(BLACK, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("D8", new Queen(BLACK, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("E8", new King(BLACK, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("F8", new Bishop(BLACK, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("G8", new Knight(BLACK, this)));
	m_chessboard_.insert(std::pair<std::string, ChessPiece*>("H8", new Rook(BLACK, this)));

	std::string pawn_square_white = "A2";
	std::string pawn_square_black = "A7";
	for (char file = 'A'; file <= 'H'; file++) {
		pawn_square_white[0] = file;
		pawn_square_black[0] = file;
		m_chessboard_.insert(std::pair<std::string, ChessPiece*>(pawn_square_white, new Pawn(WHITE, this)));
		m_chessboard_.insert(std::pair<std::string, ChessPiece*>(pawn_square_black, new Pawn(BLACK, this)));
	}

	std::string empty_square = "A3";
	for (char rank = '3'; rank <= '6'; rank++) {
		empty_square[1] = rank;
		for (char file = 'A'; file <= 'H'; file++) {
			empty_square[0] = file;
			m_chessboard_.insert(std::pair<std::string, ChessPiece*>(empty_square, nullptr));
		}
	}
}

void ChessBoard::switchTurn() {
	turn_ = (turn_ == WHITE) ? BLACK : WHITE;
}

void ChessBoard::undoTempMakeMove(ChessPiece* temp_captured_chesspiece, 
	const std::string source_square, const std::string destination_square) {
	m_chessboard_[source_square] = m_chessboard_[destination_square];
	m_chessboard_[destination_square] = temp_captured_chesspiece;
}


void ChessBoard::updateKingPos(const Color self_color, const std::string destination_square) {
	if (self_color == WHITE) {
		white_king_pos_ = destination_square;
	} else {
		black_king_pos_ = destination_square;
	}
}

void ChessBoard::makeMove(const std::string source_square, const std::string destination_square) {
	if (m_chessboard_[destination_square] != nullptr) {
		pieces_captured_.push_back(m_chessboard_[destination_square]); // collect the captured chess piece
	}
	m_chessboard_[destination_square] = m_chessboard_[source_square];
	m_chessboard_[source_square] = nullptr;
}

void ChessBoard::makeCastlingMove(const std::string source_square, const std::string destination_square){

	std::string rook_before_castling, rook_after_castling;

	if (source_square == "E1") { 	   /* WHITE */
		rook_before_castling = (destination_square == "G1") ? "H1" : "A1";
		rook_after_castling = (destination_square == "G1") ? "F1" : "D1";
		
	} else if (source_square == "E8") { /* BLACK */
		rook_before_castling = (destination_square == "G8") ? "H8" : "A8";
		rook_after_castling = (destination_square == "G8") ? "F8" : "D8";
	}

	// King moves
	m_chessboard_[destination_square] = m_chessboard_[source_square];
	m_chessboard_[source_square] = nullptr;
	// Rook moves
	m_chessboard_[rook_after_castling] = m_chessboard_[rook_before_castling];
	m_chessboard_[rook_before_castling] = nullptr;
}

bool ChessBoard::isOutOfBound(const std::string square) const {
	if (square.length() != 2) {
		return true;
	}
	if (square[0] < 'A' || square[0] > 'H' || square[1] < '1' || square[1] > '8') {
		return true;
	}
	return false;
}

bool ChessBoard::isColorDifferent(const std::string source_square, const std::string destination_square) {
	// cannot be same color
	if (getPieceColor(source_square) != getPieceColor(destination_square)) {
		return true;
	}
	return false;
}

bool ChessBoard::isFirstMove(const std::string square) {
	return m_chessboard_[square]->isFirstMove();
}

bool ChessBoard::isSelfKingInCheck(const Color self_color, const std::string source_square, const std::string destination_square) {
	
	/*  loop through the map to see if
		the self king is being checked by any of the opponent chessPiece */

	std::string self_king_pos;
	if (getPieceType(source_square) == KING) {
		self_king_pos = destination_square;
	} else {
		self_king_pos = (self_color == WHITE) ? white_king_pos_ : black_king_pos_;
	}

	// temporary makeMove
	ChessPiece* temp_captured_chesspiece = m_chessboard_[destination_square]; // can be nullptr
	m_chessboard_[destination_square] = m_chessboard_[source_square];
	m_chessboard_[source_square] = nullptr;

	std::map<std::string, ChessPiece*>::iterator it = m_chessboard_.begin();
	while( it != m_chessboard_.end()) {
		if (it->first != self_king_pos && it->second != nullptr &&
			it->first != source_square && it->first != destination_square) {
			if (it->second->getColor() != self_color) {
				if (it->second->isMoveValid(it->first, self_king_pos)) {
					undoTempMakeMove(temp_captured_chesspiece, source_square, destination_square);
					return true;
				}
			}
		}
		it++;
	}
	undoTempMakeMove(temp_captured_chesspiece, source_square, destination_square);
	return false; // none of the opponent ChessPiece can capture the King
}

bool ChessBoard::isOpponentKingInCheck(const Color opponent_color, const std::string square) {
	std::string opponent_king_pos;
	opponent_king_pos = (opponent_color == WHITE) ? white_king_pos_ : black_king_pos_;

	if (m_chessboard_[square]->isMoveValid(square, opponent_king_pos)) {
		return true; 
	}
	return false;
}

bool ChessBoard::isOpponentKingInCheckmate(const Color opponent_color, const std::string square_call_check) {
	/*	
		there are three strategies to break 'checkmate':
		1. any opponent-side chesspiece can capture the self-side chesspiece that calls the check
		2. any opponent-side chesspiece can sit between the self-side chesspiece and opponent-side King
		3. the opponent-side King can get away from being check by having a move
		
		if one of the above strategies works, checkmate is not successful. 
	*/
	if (isbreakCheckmateStratOneWork(opponent_color, square_call_check) ||
		isbreakCheckmateStratTwoWork(opponent_color, square_call_check) ||
		isbreakCheckmateStratThreeWork(opponent_color, square_call_check)) {
		return false;
	}
	return true;
}

bool ChessBoard::isbreakCheckmateStratOneWork(const Color opponent_color, const std::string square_call_check) {
	/*	
		strategy 1:
		use any opponent-side chesspiece to capture the self-side chesspiece 
		that calls the check. After that, if opponent-side king is not being checked,
		then the threat of being checked is solved.
		In the case, this strategy is successful 
	*/
	std::map<std::string, ChessPiece*>::iterator it = m_chessboard_.begin();
	while (it != m_chessboard_.end()) {
		if (it->second != nullptr && it->second->getColor() == opponent_color) {
				if (m_chessboard_[it->first]->isMoveValid(it->first, square_call_check) &&
					!isSelfKingInCheck(opponent_color, it->first, square_call_check)) {
					return true; // the threat that calls checkmate is gone
				}
			}
			it++; // increment to the next available chesspiece
	}
	return false;
}


bool ChessBoard::isbreakCheckmateStratTwoWork(const Color opponent_color, const std::string square_call_check) {
	/*	
		strategy 2:
		any opponent-side chesspiece can sit between the self-side chesspiece and 
		opponent-side King. The purpose is to block the check.
		If this works, this strategy is successful. 
	*/
	std::string opponent_king_pos = (opponent_color == WHITE) ? white_king_pos_ : black_king_pos_;
	std::map<std::string, ChessPiece*>::iterator it = m_chessboard_.begin();
	std::map<std::string, ChessPiece*>::iterator j = m_chessboard_.begin();
	while(it != m_chessboard_.end()) {
		if (it->second != nullptr 					 && 
			it->second->getColor() == opponent_color && 
			it->first != opponent_king_pos) { 
			// here, we find an opponent-side chesspiece

			while(j != m_chessboard_.end()) {
				if ( j->second == nullptr) {
					// here, we find a empty square an opponent-side chesspiece can move to
					if (m_chessboard_[it->first]->isMoveValid(it->first, j->first)) {
						// after the move, see if that chesspiece can block the inital check
						if (!(m_chessboard_[square_call_check]->isMoveValid(square_call_check, opponent_king_pos))) {
							return true;
						}
					}
				}
				j++;
 			}
		}
		it++;
	}
	return false;
}

bool ChessBoard::isbreakCheckmateStratThreeWork(const Color opponent_color, const std::string square_call_check) {
	/*	
		strategy 3:
		move the opponent-side King to a particular square that can get away from being checked
		If this works, then the threat is solved. This strategy is also successful 
	*/
	std::string opponent_king_pos = (opponent_color == WHITE) ? white_king_pos_ : black_king_pos_;
	bool king_survive; // record whether opponent-side King is in check
	
	// move opponent King to one of the possible square
	std::map<std::string, ChessPiece*>::iterator it = m_chessboard_.begin();
	while (it != m_chessboard_.end()) {
		if ((it->second == nullptr) 	   || 
			(it->second != nullptr 		   && 
			it->first != square_call_check  && 
			it->second->getColor() != opponent_color)) {
			if (m_chessboard_[opponent_king_pos]->isMoveValid(opponent_king_pos, it->first)) {
				// here, King moves to 'tempKingpos'
				std::string tempKingPos = it->first;

				// also need to check if opponent king can break the check by Castling
				if (abs(opponent_king_pos[0] - tempKingPos[0]) == 2) {
					if (isCastlingValid(opponent_color, opponent_king_pos, tempKingPos)) {
						return true;
					}
					return false;

				} else {
 					// remains true as long as no self chesspiece captures
					king_survive = true;

					// if one of the self chesspiece can still capture, king_survive becomes false
					std::map<std::string, ChessPiece*>::iterator j = m_chessboard_.begin();
					while( j != m_chessboard_.end()) {
						if (j->second != nullptr && j->first != tempKingPos) {
							if (j->second->getColor() != opponent_color) {
								if(j->second->isMoveValid(j->first, tempKingPos)) {
									king_survive = false;
									break;
								}
							}
						}
						j++; // go to next chesspiece for testing
					}
					/*  king_survive will remains true when after King moves to a particular square, 
						none of the opponent chesspiece can capture King (inner loop completes). 
						So, checkmate is not successful */
					if (king_survive == true) {
						return true;
					}
				}
			}
		}
		it++; // King tries to move to another possible square
	}
	return false;
}

bool ChessBoard::isCastlingValid(const Color self_color, const std::string source_square, const std::string destination_square) {
	
	// cannot castle while in check
	if (isKingInCheckCastling(self_color, source_square)) {
		// printf("you cannot castle when you are in check\n");
		return false;
	}

	/*	if WHITE King moves to "G1" (King side) - that rook should be at "H1"
		if WHITE King moves to "C1" (Queen side) - that rook should be at "A1" */				
	std::string rook_before_castling;
	
	if (getPieceColor(source_square) == WHITE && source_square == "E1") {
		if (destination_square == "G1") { // WHITE King side
			if (getPieceType("H1") == ROOK) {
				rook_before_castling = "H1"; 
			} else {
				return false; // the required Rook is not there
			}
		} else if (destination_square == "C1") { // WHITE Queen side
			if (getPieceType("A1") == ROOK) {
				rook_before_castling = "A1"; 
			} else {
				return false; // the required Rook is not there
			}
		} else {
			return false; // King is neither moving to 'G1' nor 'C1'
		}

	/*	if BLACK King moves to "G8" (King side) - that rook should be at "H8"
		if BLACK King moves to "C8" (Queen side) - that rook should be at "A8" */
	} else if (getPieceColor(source_square) == BLACK && source_square == "E8") {
		if (destination_square == "G8") { // BLACK King side
			if (getPieceType("H8") == ROOK) {
				rook_before_castling = "H8"; 
			} else {
				return false; // the required Rook is not there
			}
		} else if (destination_square == "C8") { // BLACK Queen side
			if (getPieceType("A8") == ROOK) {
				rook_before_castling = "A8"; 
			} else {
				return false; // the required Rook is not there
			}
		} else {
			return false; // King is neither moving to 'G8' nor 'C8'		
		}
	} else {
		return false; // King is neither moving to 'E8' nor 'E1'
	}

	if (isFirstMove(source_square) && isFirstMove(rook_before_castling)) {
		/*	
			Two conditions which the King fails to castle:
			1. when King goes through a check (ie. if 1st step lands to a check)
			2. after the 2nd step), the king lands to a check
		*/
		signed char file_increment = (source_square[0] < destination_square[0]) ? 1 : - 1;
		std::string passing_square = source_square;
		passing_square[0] = passing_square[0] + file_increment;

		// King cannot moves through check or lands on check
		if (!isKingInCheckCastling(self_color, passing_square) && 
			!isKingInCheckCastling(self_color, destination_square)) {
			return true; 
		}
		return false; // King cannot moves through check or lands on check
	}
	return false; // either king or root is not first time moving
}

bool ChessBoard::isKingInCheckCastling(const Color self_color, const std::string kingPos) {
	/*  loop through the map to see if
		the self king is being checked by any of the opponent chessPiece */

	std::map<std::string, ChessPiece*>::iterator it = m_chessboard_.begin();
	while(it != m_chessboard_.end()) {
		if (it->second != nullptr && it->first != kingPos) {
			if (it->second->getColor() != self_color) {
				if(it->second->isMoveValid(it->first, kingPos)) {
					return true;
				}
			}
		}
		it++;
	}
	return false; // none of the opponent ChessPiece can capture the King
}

bool ChessBoard::hasAnyLegalMove(const Color opponent_color, const std::string source_square, const std::string destination_square) {
	
	// for any of the opponent chesspiece
	std::map<std::string, ChessPiece*>::iterator it = m_chessboard_.begin();
	while(it != m_chessboard_.end()) {
		if (it->second != nullptr && it->second->getColor() == opponent_color) {

			// test any legal move and at the same time, King wont be in check
			std::map<std::string, ChessPiece*>::iterator j = m_chessboard_.begin();
			while(j != m_chessboard_.end()) {
				if ((j->second == nullptr) ||
					(j->second != nullptr && j->second->getColor() != opponent_color)) {

						if (getPieceType(it->first) == KING) {
							int file_distance = abs(it->first[0] - j->first[0]);
							int rank_distance = abs(it->first[1] - j->first[1]);
							Color self_color = (opponent_color == WHITE) ? BLACK : WHITE;

							if (file_distance == 2 && rank_distance == 0) {
								if (it->second->isMoveValid(it->first, j->first) && 
									isCastlingValid(self_color, it->first, j->first)) {
									return true;
								} else {
									/* once king jumps in the condition, it should not jump to
									   the normal case check */
									j++;
									continue; 
								}
							}
						}
						if (it->second->isMoveValid(it->first, j->first) &&
						!isSelfKingInCheck(opponent_color, it->first, j->first)) {
							return true;
							} 
				}
				j++; // go to next possible move
			}
		}
		it++; // go to next chesspiece for testing
	}
	return false;
}


void ChessBoard::printMoveSuccessMessage(const std::string source_square, const std::string destination_square) {
	// operator overloading of the Color and Type are used here
	std::cout << getPieceColor(source_square) << "'s ";
	std::cout << getPieceType(source_square) << " moves from ";
	std::cout << source_square << " to " << destination_square;
	
	if (m_chessboard_[destination_square] != nullptr) {
		std::cout << " taking " << getPieceColor(destination_square);
		std::cout << "'s " << getPieceType(destination_square) << "\n";
	} else {
		std::cout << "\n";
	}
}

void ChessBoard::printMoveFailMessage(const std::string source_square, const std::string destination_square) {
	// operator overloading of the Color and Type are used here
	std::cout << getPieceColor(source_square) << "'s ";
	std::cout << getPieceType(source_square) << " cannot move to ";
	std::cout << destination_square << "!\n";
}


Color ChessBoard::getPieceColor(const std::string square) {
	return m_chessboard_[square]->getColor();
}

Type ChessBoard::getPieceType(const std::string square) {
	return m_chessboard_[square]->getType();
}


/* ======= public functions ======= */
std::map<std::string, ChessPiece*> ChessBoard::getChessboard() const{
	return m_chessboard_;
}

void ChessBoard::resetBoard() {
	std::map<std::string,ChessPiece*>::iterator it = m_chessboard_.begin();
	while (it != m_chessboard_.end()) {
		delete it->second;
		it++;
	}
	m_chessboard_.clear();

	for (unsigned i=0; i < pieces_captured_.size(); i++) {
		delete pieces_captured_[i];
	}
	pieces_captured_.clear();

	createPiecesAndConfigBoard();
	startGame();
}

void ChessBoard::submitMove(const std::string source_square, const std::string destination_square) {

	if (isOutOfBound(source_square)) {
		std::cerr << "Invalid input " << source_square << std::endl;
		return;
	} else if (isOutOfBound(destination_square)) {
		std::cerr << "Invalid input " << destination_square << std::endl;
		return;
	}

	if (m_chessboard_[source_square] == nullptr) { // is there chesspiece on source_square
		std::cerr << "There is no piece at position " << source_square << "!\n";
		return;
	}

	if (source_square == destination_square) {
		std::cerr << "Move you chess piece at " << source_square << std::endl;
		return;
	}
	
	if (turn_ != getPieceColor(source_square)) {
		std::cerr << "It is not " << getPieceColor(source_square); // operator overloaded
		std::cerr << "'s turn to move!" << std::endl;
		return;	
	}

	if (m_chessboard_[destination_square] != nullptr) { // you cannot dereference a nullptr
		if (!isColorDifferent(source_square, destination_square)) {
			std::cerr << "You cannot capture the self piece at ";
			std::cerr << destination_square << std::endl;
			return;
		}
	}

	// check if move is valid
	if (m_chessboard_[source_square]->isMoveValid(source_square, destination_square)) { 
		/*  
			check if the self-side king is in check under the assumption that after make is made.
			if not valid, should not proceed to the actual move
			This then will be a forbidden move. 
		*/
		if(isSelfKingInCheck(turn_, source_square, destination_square)) {
			// Move is forbitten since it will put self-side King in check
			printMoveFailMessage(source_square, destination_square);

		} else { // isMoveValid() == true

			/* start of check for castling conditon */
			int file_distance = abs(source_square[0] - destination_square[0]);
			int rank_distance = abs(source_square[1] - destination_square[1]);
			bool castlingFlag = false;

			if (getPieceType(source_square) == KING && file_distance == 2 && rank_distance == 0) {
				if (isCastlingValid(turn_, source_square, destination_square)) {
					castlingFlag = true;
				} else {
					printMoveFailMessage(source_square, destination_square);
					return; // leave submitMove()
				}
			}
			/* end of check for castling conditon */
			
			/* ------ before actual move and turn switch ------ */
			printMoveSuccessMessage(source_square, destination_square);

			if (castlingFlag) {
				makeCastlingMove(source_square, destination_square);	/* castling move */
			} else {
				makeMove(source_square, destination_square); 			/* major move */
			}	
			
			if (m_chessboard_[destination_square]->isFirstMove()) {
				m_chessboard_[destination_square]->setFirstMoveToFalse();
			}

			/* update king position if needed */
			if (getPieceType(destination_square) == KING) {
				updateKingPos(turn_, destination_square);
			}

			switchTurn();
			/* ------ after actual move and turn switch ------ */

			// check if opponent king is in check or even in checkmate */
			if (isOpponentKingInCheck(turn_, destination_square)) {
				std::string opponent_color = (turn_ == WHITE) ? "White" : "Black";
				std::cout << opponent_color << " is in ";
				if (isOpponentKingInCheckmate(turn_, destination_square)) {
					std::cout << "checkmate" << std::endl;
				} else {
					std::cout << "check" << std::endl;
				}
			} else {
 				if (!hasAnyLegalMove(turn_, source_square, destination_square)) {
					std::cout << "Stalemate occurs. Game is a draw." << std::endl;
				}
			}
		}
	} else { // move is not valid
		printMoveFailMessage(source_square, destination_square);
	}
}