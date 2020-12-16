#include"ChessBoard.h"
#include<iostream>
using std::cout;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb;
	cout << '\n';

	// cb.submitMove("A1", "B1"); 
	// cout << '\n';

	// cb.submitMove("E8", "G8"); 
	// cout << '\n';

	// cb.submitMove("B1", "A1"); 
	// cout << '\n';

	// cb.submitMove("A8", "B8"); 
	// cout << '\n';

	// cb.submitMove("E1", "C1"); 
	// cout << '\n';


	/* castling trials */

	// cb.submitMove("H1", "G1"); // white 
	// cout << '\n';

	// cb.submitMove("A7", "A5"); // black
	// cout << '\n';

	// cb.submitMove("G1", "H1"); // white
	// cout << '\n';

	// cb.submitMove("B7", "B5"); // black
	// cout << '\n';

	// cb.submitMove("E1", "G1"); // black
	// cout << '\n';

	// cb.submitMove("G1", "G2"); // white
	// cout << '\n';

	// cb.submitMove("D8", "E8"); // black
	// cout << '\n';
	
	// cb.submitMove("E8", "D8"); // black
	// cout << '\n';
	
	///////////////////////////////////////
 
	// cb.submitMove("D7", "D7");
	// cout << '\n';

	// cb.submitMove("A1", "B1");
	// cout << '\n';

	// cb.submitMove("a1", "B1");
	// cout << '\n';

	// cb.submitMove("A1", "b1");
	// cout << '\n';

	/////////////////



	cb.submitMove("D7", "D6");
	cout << '\n';

	cb.submitMove("D4", "H6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cout << '\n';
	
	cb.submitMove("F8", "B4");
	cout << '\n';

	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("E7", "E6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("F8", "B4");
	cout << '\n';

	cb.submitMove("F1", "D3");
	cb.submitMove("B4", "C3");
	cout << '\n';

	cb.submitMove("B2", "C3");
	cb.submitMove("H7", "H6");
	cout << '\n';

	cb.submitMove("C1", "A3");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("D1", "E2");
	cb.submitMove("D5", "E4");
	cout << '\n';

	cb.submitMove("D3", "E4");
	cb.submitMove("G8", "F6");
	cout << '\n';

	cb.submitMove("E4", "D3");
	cb.submitMove("B7", "B6");
	cout << '\n';

	cb.submitMove("E2", "E6");
	cb.submitMove("F7", "E6");
	cout << '\n';

	cb.submitMove("D3", "G6");
	cout << '\n';

	//////////



	// cb.resetBoard();
	// cout << '\n';
	// //////
	// cb.submitMove("D2", "D4");
	// cb.submitMove("D7", "D5");
	// cout << '\n';

	// cb.submitMove("C2", "C4");
	// cb.submitMove("C7", "C6");
	// cout << '\n';

	// cb.submitMove("B1", "C3");
	// cb.submitMove("G8", "F6");
	// cout << '\n';

	// cb.submitMove("E2", "E3");
	// cb.submitMove("E7", "E6");
	// cout << '\n';



	// cb.submitMove("G1", "F3");
	// cb.submitMove("B8", "D7");
	// cout << '\n';

	// cb.submitMove("D1", "C2");
	// cb.submitMove("F8", "D6");
	// cout << '\n';

	// cb.submitMove("E3", "E4");
	// cb.submitMove("F6", "E4");
	// cout << '\n';

	// cb.submitMove("C3", "E4");
	// cb.submitMove("D5", "E4");
	// cout << '\n';


	// cb.submitMove("C2", "E4");
	// cb.submitMove("C6", "C5");
	// cout << '\n';

	// cb.submitMove("C1", "G5");
	// cb.submitMove("D8", "A5");
	// cout << '\n';

	// cb.submitMove("G5", "D2"); //// problem here
	// cb.submitMove("A5", "C7");
	// cout << '\n';

	// cb.submitMove("E1", "C1");
	// cb.submitMove("D7", "F6");
	// cout << '\n';


	// cb.submitMove("E4", "H4");
	// cb.submitMove("C5", "D4");
	// cout << '\n';

	// cb.submitMove("F3", "D4");
	// cb.submitMove("C8", "D7");
	// cout << '\n';

	// cb.submitMove("C1", "B1");
	// cb.submitMove("A7", "A6");
	// cout << '\n';

	// cb.submitMove("F1", "D3");
	// cb.submitMove("E8", "C8");
	// cout << '\n';



	// cb.resetBoard();
	// cout << '\n';
	// ////
	// cb.submitMove("E2", "E4");
	// cb.submitMove("E7", "E5");
	// cout << '\n';

	// cb.submitMove("G1", "F3");
	// cb.submitMove("B8", "C6");
	// cout << '\n';

	// cb.submitMove("F1", "B5");
	// cb.submitMove("A7", "A6");
	// cout << '\n';

	// cb.submitMove("B5", "A4");
	// cb.submitMove("G8", "F6");
	// cout << '\n';


	// cb.submitMove("E1", "G1");
	// cb.submitMove("F8", "E7");
	// cout << '\n';

	// cb.submitMove("F1", "E1");
	// cb.submitMove("B7", "B5");
	// cout << '\n';

	// cb.submitMove("A4", "B3");
	// cb.submitMove("E8", "G8");
	// cout << '\n';

	// cb.submitMove("C2", "C3");
	// cb.submitMove("D7", "D6");
	// cout << '\n';



	// cb.submitMove("H2", "H3");
	// cb.submitMove("C6", "A5");
	// cout << '\n';

	// cb.submitMove("B3", "C2");
	// cb.submitMove("C7", "C5");
	// cout << '\n';

	// cb.submitMove("D2", "D4");
	// cb.submitMove("D8", "C7");
	// cout << '\n';

	// cb.submitMove("B1", "D2");
	// cb.submitMove("C8", "B7");
	// cout << '\n';




	// cb.submitMove("D4", "D5");
	// cb.submitMove("B7", "C8");
	// cout << '\n';

	// cb.submitMove("D2", "F1");
	// cb.submitMove("C8", "D7");
	// cout << '\n';

	// cb.submitMove("B2", "B3");
	// cb.submitMove("A5", "B7");
	// cout << '\n';

	// cb.submitMove("C3", "C4");
	// cb.submitMove("F8", "B8");
	// cout << '\n';



	// cb.submitMove("F1", "E3");
	// cb.submitMove("E7", "F8");
	// cout << '\n';

	// cb.submitMove("E3", "F5");
	// cb.submitMove("B7", "D8");
	// cout << '\n';

	// cb.submitMove("F3", "H2");
	// cb.submitMove("F6", "E8");
	// cout << '\n';

	// cb.submitMove("H3", "H4");
	// cb.submitMove("F7", "F6");
	// cout << '\n';



	// cb.submitMove("H4", "H5");
	// cb.submitMove("D8", "F7");
	// cout << '\n';

	// cb.submitMove("E1", "E3");
	// cb.submitMove("F7", "G5");
	// cout << '\n';

	// cb.submitMove("F5", "H4");
	// cb.submitMove("C7", "D8");
	// cout << '\n';

	// cb.submitMove("E3", "G3");
	// cb.submitMove("E8", "C7");
	// cout << '\n';



	// cb.submitMove("H2", "F3");
	// cb.submitMove("H7", "H6");
	// cout << '\n';

	// cb.submitMove("H4", "G6");
	// cb.submitMove("A6", "A5");
	// cout << '\n';


	return 0;
}
