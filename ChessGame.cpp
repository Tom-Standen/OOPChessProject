//// OOP Final Project - Board Game: Chess //// 
// Author: Thomas Standen, start: 07/04/19, end: 13/05/19 //
//This the implementation file where all non-template functions for the project are defined
#include "ChessGame.h"
#include "player.h"
#include "square.h"
#include "piece.h"
#include "board.h"
#include <iostream>


//STANDARD NON-MEMBER FUNCTIONS//
//check if a requested square exists on the board
bool inputcheck::in_boardrange(int row, int col){
	//row and col must be between 0-7 to access board squares without error
	if ((row < 0) || (col < 0) || (row > board_rows - 1) || (col > board_cols - 1)){
		return false;
	}
	else{
		return true;
	}
}
//check a valid 
bool inputcheck::good_colour(std::string& colour){
	//check either B,b,black, Black, W,w,white or White was entered 
	if ((colour != "W") && (colour != "w") && (colour != "White") && (colour != "white") &&
		(colour != "B") && (colour != "b") && (colour != "Black") && (colour != "black")){
		return false;
	}
	else{
		if ((colour == "W") || (colour == "w") || (colour == "white")){
			colour = "White";
		}
		else{
			colour = "Black";
		}
		return true;
	}
}
bool inputcheck::repeat_info(std::string& answer){
	if ((answer != "Yes") && (answer != "yes") && (answer != "Y") && (answer != "y") &&
		(answer != "Repeat") && (answer != "repeat") && (answer != "R") && (answer != "r")
		&& (answer != "Exit") && (answer != "exit") && (answer != "X") && (answer != "x")){
		return false;
	}
	else{
		if ((answer == "yes") || (answer == "Y") || (answer == "y")){
			answer = "Yes";
		}
		if ((answer == "repeat") || (answer == "R") || (answer == "r")){
			answer = "Repeat";
		}
		if ((answer == "exit") || (answer == "X") ||(answer == "x")){
			answer = "Exit";
		}
		return true;
	}
}
bool inputcheck::good_code(std::string code){
	std::string col_str = code.substr(0, 1);
	try{
		int row = std::stoi((code.substr(1, 1)));
		//if a value outside of a-h or A-H or outside of 0-7 is given
		if ((((row - 1) < 0) || ((row - 1) > 7)) || (col_str != "A" && col_str != "a" && col_str != "B" && col_str != "b"
			&& col_str != "C" && col_str != "c" && col_str != "D" && col_str != "d" && col_str != "E" && col_str != "e"
			&& col_str != "F" && col_str != "f" && col_str != "G" && col_str != "g" && col_str != "H" && col_str != "h")){
			return false;
		}
		else{
			return true;
		}
	}
	catch (...){
		//if second character wasn't a number it can't be turned into an int
		return false;
	}
}
//Trun the moveinput into integers to be used in program
std::pair<int,int> inputcheck::decode(const std::string& LetNum){
	std::pair<int, int> row_col;
	row_col.first = (std::stoi((LetNum.substr(1, 1))) - 1); //minus 1 for 0-7
	std::string letter = LetNum.substr(0, 1);
	if (letter == "a" || letter == "A"){ row_col.second = 0; }
	if (letter == "b" || letter == "B"){ row_col.second = 1; }
	if (letter == "c" || letter == "C"){ row_col.second = 2; }
	if (letter == "d" || letter == "D"){ row_col.second = 3; }
	if (letter == "e" || letter == "E"){ row_col.second = 4; }
	if (letter == "f" || letter == "F"){ row_col.second = 5; }
	if (letter == "g" || letter == "G"){ row_col.second = 6; }
	if (letter == "h" || letter == "H"){ row_col.second = 7; }
	return row_col;
}
//recode the move for output to the user
std::string inputcheck::recode(int row, int col){
	std::string row_str{ std::to_string(row + 1) };
	std::string col_str;
	if (col == 0){ col_str = "A"; }
	if (col == 1){ col_str = "B"; }
	if (col == 2){ col_str = "C"; }
	if (col == 3){ col_str = "D"; }
	if (col == 4){ col_str = "E"; }
	if (col == 5){ col_str = "F"; }
	if (col == 6){ col_str = "G"; }
	if (col == 7){ col_str = "H"; }
	return (col_str + row_str);
}
///////////PLAYER METHODS//////////////
bool player::MyPiece(const square& sq){
	if (sq.isempty()){
		std::cout << "You selected an empty sqaure" << std::endl;
		return false;
	}
	else {
		if(sq.GetPieceColour() != m_player_colour){
			std::cout << "That's not your piece!" << std::endl;
			return false;
		}
		else{
			return true;
		}
	}
}

/*
//convert input from letter code eg "A1" to two ints
std::pair<int,int> decode(std::string letter_code){
	code["A"] = 0, code["B"] = 1, code["C"] = 2, code["D"] = 3,
		code["E"] = 4, code["F"] = 5, code["G"] = 6, code["H"] = 7;
	

//}
*/


////BOARD METHOD DEFINITIONS////
//constructors
//board::board() { m_init(); }
//function to initialise the board 
void board::init(){
	//set the shape of the board, and initialise all values to be blank white squares
	m_square_2Dvector.resize(board_rows, std::vector<square>(board_cols, square()));
	//Set white pawns on second row
	for (int col = 0; col < board_cols; col++){
		((col % 2 == 0) ? //if col == even: White square, if not : Black square
			m_square_2Dvector[1][col] = square("White", std::make_shared<pawn>("White")) :
			m_square_2Dvector[1][col] = square("Black", std::make_shared<pawn>("White")));
	}
	//Set black pawns on second last row
	for (int col = 0; col < board_cols; col++){
		((col % 2 == 0) ? //if col == even: Black square, if not : White square
			m_square_2Dvector[6][col] = square("Black", std::make_shared<pawn>("Black")) :
			m_square_2Dvector[6][col] = square("White", std::make_shared<pawn>("Black")));
	}
	//Set white pieces on first row 
	m_square_2Dvector[0][0] = square("Black", std::make_shared<rook>("White"));
	m_square_2Dvector[0][1] = square("White", std::make_shared<knight>("White"));
	m_square_2Dvector[0][2] = square("Black", std::make_shared<bishop>("White"));
	m_square_2Dvector[0][3] = square("White", std::make_shared<queen>("White"));
	m_square_2Dvector[0][4] = square("Black", std::make_shared<king>("White"));
	m_square_2Dvector[0][5] = square("White", std::make_shared<bishop>("White"));
	m_square_2Dvector[0][6] = square("Black", std::make_shared<knight>("White"));
	m_square_2Dvector[0][7] = square("White", std::make_shared<rook>("White"));
	//Setet black pieces on last row
	m_square_2Dvector[7][0] = square("White", std::make_shared<rook>("White"));
	m_square_2Dvector[7][1] = square("Black", std::make_shared<knight>("Black"));
	m_square_2Dvector[7][2] = square("White", std::make_shared<bishop>("Black"));
	m_square_2Dvector[7][3] = square("Black", std::make_shared<queen>("Black"));
	m_square_2Dvector[7][4] = square("White", std::make_shared<king>("Black"));
	m_square_2Dvector[7][5] = square("Black", std::make_shared<bishop>("Black"));
	m_square_2Dvector[7][6] = square("White", std::make_shared<knight>("Black"));
	m_square_2Dvector[7][7] = square("Black", std::make_shared<rook>("Black"));
	//Set the colour of the squares in middle four rows
	bool black = true;
	for (int row{ 2 }; row < 6; row++){
		//Third row (row==2) starts with a black square
		((row % 2 == 0) ? black = true : black = false);
		for (int col{ 0 }; col < board_cols; col++){
			if (black == true){
				m_square_2Dvector[row][col].SetColour("Black");
				black = false;
			}
			else{
				m_square_2Dvector[row][col].SetColour("White");
				black = true;
			}
		}
	}
}
//function to print out the header piece of the board with letter codes
namespace headerandfooter{
	void board_header(){
		//create an array containing the letter codes for the middle row
		std::unique_ptr<std::string[]> AtoH(new std::string[board_cols]);
		AtoH[0] = "A"; AtoH[1] = "B"; AtoH[2] = "C"; AtoH[3] = "D";
		AtoH[4] = "E"; AtoH[5] = "F"; AtoH[6] = "G"; AtoH[7] = "H";
		//base_pieces make the top and bottom row
		std::string header_top_piece = "        ||";
		std::string header_bot_piece = "________||";

		//Top row of header
		for (int column_it = 0; column_it < board_cols + 1; column_it++){
			std::cout << header_top_piece;
			//if its the first column print extra | for edge of board
			if (column_it == 0){ std::cout << "|"; }
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols){ std::cout << "        |"; }
			 
		}
		std::cout << std::endl;
		//Middle row of header 
		std::cout << header_top_piece << "|"; //first column same as above
		for (int column_it = 0; column_it < board_cols; column_it++){
			std::cout << "   " << AtoH[column_it] << "    ||";
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols - 1){ std::cout << "        |"; }

		}
		std::cout << std::endl;
		//Bottom row of header
		for (int column_it = 0; column_it < board_cols + 1; column_it++){
			std::cout << header_bot_piece;
			//if its the first column print extra | for edge of board
			if (column_it == 0){ std::cout << "|"; }
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols){ std::cout << "________|"; }
		}
		std::cout << std::endl;
	}
	void board_footer(){
		//same array as above for printing out letters
		std::unique_ptr<std::string[]> AtoH(new std::string[board_cols]);
		AtoH[0] = "A"; AtoH[1] = "B"; AtoH[2] = "C"; AtoH[3] = "D";
		AtoH[4] = "E"; AtoH[5] = "F"; AtoH[6] = "G"; AtoH[7] = "H";
		std::string footer_break_piece = "__________";
		std::string footer_top_piece = "        ||";
		std::string footer_bot_piece = "________||";
		//draw a line between board and footer
		std::cout << "________||";
		for (int column_it = 0; column_it < board_cols; column_it++){
			std::cout << footer_break_piece;
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols -1){ std::cout << "|________|"; }
		}
		std::cout << std::endl;
		//first row of footer
		for (int column_it = 0; column_it < board_cols + 1; column_it++){
			std::cout << footer_top_piece;
			//if its the first column print extra | for edge of board
			if (column_it == 0){ std::cout << "|"; }
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols){ std::cout << "        |"; }
		}
		std::cout << std::endl;
		//middle row of footer 
		std::cout << footer_top_piece << "|"; //first column same as above
		for (int column_it = 0; column_it < board_cols; column_it++){
			std::cout << "   " << AtoH[column_it] << "    ||";
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols -1){ std::cout << "        |"; }
		}
		std::cout << std::endl;
		//Bottom row of footer
		for (int column_it = 0; column_it < board_cols + 1; column_it++){
			std::cout << footer_bot_piece;
			//if its the first column print extra | for edge of board
			if (column_it == 0){ std::cout << "|"; }
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols){ std::cout << "________|"; }
		}
		std::cout << std::endl;
	}
		

	}

void board::print_checkerboard() const{
	//Each row takes up 4 rows on the console
	const int RowsInRow{ 4 };
	//create the side border to the checkerboard
	std::string left_std_piece = "        ||";
	std::string left_bot_piece = "________||";
	std::string rt_std_piece = "|        |";
	std::string rt_bot_piece = "|________|";
	for (int i{ board_rows }; i > 0; i--){
		//count down on rows so the bottom left corner of the board is [0][0]
		for (int k{ 0 }; k < RowsInRow; k++){
			//loop over the 4 rows that make up each row
			//print side left border piece
			if (k == 0 || k == 2){ std::cout << left_std_piece; }
			if (k == 1){ std::cout << "   " << i  << "    ||"; }
			if (k == 3){ std::cout << left_bot_piece; }
			//print the squares
			for (int j{ 0 }; j < board_cols; j++){
				if (k == 0 || k == 3){
					m_square_2Dvector[i-1][j].PrintBorderRow();
				}
				if (k == 1){ m_square_2Dvector[i-1][j].PrintSecondRow(); }
				if (k == 2){ m_square_2Dvector[i-1][j].PrintThirdRow(); }
			}
			//print the right border piece
			if (k == 0 || k == 2){ std::cout << rt_std_piece; }
			if (k == 1){ std::cout << "|   " << i << "    |"; }
			if (k == 3){ std::cout << rt_bot_piece; }
			std::cout << std::endl;
		}
	}
}
void board::print_board() const {
	using namespace std;
	//function to print the board
	headerandfooter::board_header();
	print_checkerboard();
	headerandfooter::board_footer();

}

//////////////END OF BOARD METHODS///////////////////

/////////////SQUARE METHOD DEFINITIONS///////////////

////MOVE/COPY Assingments (C-TORS)////
/*
square &square::operator=(square& copy){
	//deep copy one square to another
	//need to block self assingment
	if (&copy == this) { return (*this); }
	//copy data across
	m_sq_colour = copy.m_sq_colour;
	(*m_on_square) = (*copy.m_on_square);
	return (*this);
}
square &square::operator=(square&& moved){
	//move a piece from one square to another
	//don't want to move square colour but do want to move piece
	m_on_square = moved.m_on_square;
	moved.m_on_square = std::make_shared<piece>(nullptr);
	return (*this);
}
*/
//using namespace std;
void square::PrintBorderRow() const {
	using namespace std;
	//depending on square colour print 10 spaces or hashes
	((m_sq_colour == "White") ? cout << "          " : cout << "##########");
}
void square::PrintSecondRow() const {
	using namespace std;
	//Get the name of the piece to be printed
	if (m_on_square == nullptr){
		if (m_sq_colour == "White"){ std::cout << "          "; }
		if (m_sq_colour == "Black"){ std::cout << "##########"; }
	}
	else{
		string name = m_on_square->GetName();
		//calculate number of characters to border name
		//Queen has 5 char so can't have an even border
		double border;
		((name == "Queen") ? border = 2 : border = (10 - name.length()) / 2);
		//For white squares: print 10 spaces if no piece
		//or print name in middle of row
		if (m_sq_colour == "White"){
			//print the row
			for (int i{ 0 }; i < border; i++){
				cout << " ";
			}
			std::cout << name;
			for (int i{ 0 }; i < border; i++){
				std::cout << " ";
			}
			if (name == "Queen"){ std::cout << " "; }
			//"Queen" is 5 characters so need extra character to complete square

		}
		else{//if black 
			//need one less border character
			// eg for pawn: ## Pawn ##, for bishop: # bishop # 
			border -= 1;
			//print out 10 hashes if no piece
			//if (m_empty){ std::cout << "##########"; }

			for (int i{ 0 }; i < border; i++){
				std::cout << "#";
			}
			std::cout << " " << name << " ";
			for (int i{ 0 }; i < border; i++){
				std::cout << "#";
			}
			//"Queen" is 5 characters so need extra character on end
			//because int arithmetic rounds 1.5 down to 1
			if (name == "Queen"){ std::cout << '#'; }

		}
	}
}
void square::PrintThirdRow() const {
	//output 4 spaces or hashes either side of 2 letter colour code
	std::string sq_colour = m_sq_colour;
	if (sq_colour == "White"){
		if (m_on_square == nullptr){ std::cout << "          "; }
		else{
			std::string piece_colour = m_on_square->GetColour();
			if (piece_colour == "White"){ std::cout << "    Wh    "; }
			if (piece_colour == "Black"){ std::cout << "    Bl    "; }
		}
	}
	if (sq_colour == "Black"){
		if (m_on_square == nullptr){ std::cout << "##########"; }
		else{
			std::string piece_colour = m_on_square->GetColour();
			if (piece_colour == "White"){ std::cout << "### Wh ###"; }
			if (piece_colour == "Black"){ std::cout << "### Bl ###"; }
		}
	}
}

/////////////// CHECK MOVE NAMESPACE ///////////



//GAME MANAGER METHODS

////////////// PIECE ALLOWED MOVES//////////////
//METHOD: 
//Take in a reference to the board and the piece location
//Check spaces accessible to each piece and record list of the available moves to that piece
//Check by looping through (when necessary) the piece's moving channels until another piece is found blocking path
//store the accesible spaces in a list to be returned by the function

/*std::list < std::pair<int, int> > FullColCheck(const board& b, const int& row, const int& col){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> good_move;
	std::list<std::pair<int, int>> available_moves;
	bool path_block = false;
}*/

////////////////ROOK/////////////////////

std::set<std::pair<int, int>> rook::moves(const board& b, const int& row, const int& col){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> good_move;
	//std::pair<int, int> no_move = std::make_pair(8, 8);
	std::set<std::pair<int, int>> available_moves;
	bool path_block = false;
	//check spaces in front of piece (behind if black)
	for (int for_step{ row + 1 }; for_step < (board_rows); for_step++){
		while (!path_block){
			if (b(for_step, col).isempty()){
				good_move.first = for_step;
				good_move.second = col;
				available_moves.insert(good_move);
			}
			else{//the square has a piece on it, so block path
				path_block = true;
				//add the square if enemy piece
				if (moving_colour != b(for_step, col).GetPieceColour()){
					good_move.first = for_step;
					good_move.second = col;
					available_moves.insert(good_move);	
				}
			}
		 }
	}
	//check spaces behind piece (front if black piece)
	//reset path_block
	path_block = false;
	for (int back_step{ row - 1 }; back_step > (-1); back_step--){
		while (!path_block){
			if (b(back_step, col).isempty()){
				good_move.first = back_step;
				good_move.second = col;
				available_moves.insert(good_move);
			}
			else{//the square has a piece on it, so block path 
				path_block = true;
				//add the square if enemy piece
				if (moving_colour != b(back_step, col).GetPieceColour()){
					good_move.first = back_step;
					good_move.second = col;
					available_moves.insert(good_move);
				}
			}
		} 
	}
	//check spaces to the left of rook
	path_block = false;
	for (int left_step{ col - 1 }; left_step > (-1); left_step--){
		while (!path_block){
			if (b(row, left_step).isempty()){
				good_move.first = row;
				good_move.second = left_step;
				available_moves.insert(good_move);
			}
			else{//the square has a piece on it, so block path 
				path_block = true;
				//add the square if enemy piece
				if (moving_colour != b(row, left_step).GetPieceColour()){
					good_move.first = row;
					good_move.second = left_step;
					available_moves.insert(good_move);
				}
			}
		}
	}
	//check spaces to the right of piece
	path_block = false;
	for (int rt_step{ col + 1 }; rt_step < (board_cols); rt_step++){
		while (!path_block){
			if (b(row, rt_step).isempty()){
				good_move.first = row;
				good_move.second = rt_step;
				available_moves.insert(good_move);
			}
			else{//the square has a piece on it, so block path 
				path_block = true;
				//add the square if enemy piece
				if (moving_colour != b(row, rt_step).GetPieceColour()){
					good_move.first = row;
					good_move.second = rt_step;
					available_moves.insert(good_move);
				}
			}
		}
	}
	//if there are no moves need to return something to stop function crashing
	/*
	if (available_moves.empty()){
		available_moves.insert(no_move);
		return available_moves;
	}
	else{
		return available_moves;
	}*/
	return available_moves;
}

//////////////////BISHOP//////////////////////
std::set<std::pair<int, int>> bishop::moves(const board& b, const int& row, const int& col){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> good_move;
	std::set<std::pair<int, int>> available_moves;
	// forward right diagonal (for white)
	bool path_block = false; 
	for (int row_step{ row + 1 }; row_step < (board_rows); row_step++){
		for (int col_step{ col + 1 }; col_step < (board_cols); col_step++){
			if ((row_step - row) == (col_step - col)){ //pick out diagonal
				while (!path_block){
					if (b(row_step, col_step).isempty()){
						good_move.first = row_step;
						good_move.second = col_step;
						available_moves.insert(good_move);
					}
					else{//the square has a piece on it, so block path 
						path_block = true;
						//add the square if enemy piece
						if (moving_colour != b(row_step, col_step).GetPieceColour()){
							good_move.first = row_step;
							good_move.second = col_step;
							available_moves.insert(good_move);
						}
					}

				}
			}
		}
	}
	// forward left diagonal (for white)
	path_block = false;
	for (int row_step{ row + 1 }; row_step < (board_rows); row_step++){
		for (int col_step{ col - 1 }; col_step > -1 ; col_step--){
			if ((row_step - row) == (col - col_step)){ //pick out diagonal
				while (!path_block){
					if (b(row_step, col_step).isempty()){
						good_move.first = row_step;
						good_move.second = col_step;
						available_moves.insert(good_move);
					}
					else{//the square has a piece on it, so block path
						path_block = true;
						//add the square if enemy piece
						if (moving_colour != b(row_step, col_step).GetPieceColour()){
							good_move.first = row_step;
							good_move.second = col_step;
							available_moves.insert(good_move);
						}
					}
				}
			}
		}
	}
	// back left diagonal (for white)
	path_block = false;
	for (int row_step{ row - 1 }; row_step > -1 ; row_step--){
		for (int col_step{ col + 1 }; col_step < (board_cols); col_step++){
			if ((row - row_step) == (col_step - col)){ //pick out diagonal
				while (!path_block){
					if (b(row_step, col_step).isempty()){
						good_move.first = row_step;
						good_move.second = col_step;
						available_moves.insert(good_move);
					}
					else{//the square has a piece on it, so block path 
						path_block = true;
						//add the square if enemy piece
						if (moving_colour != b(row_step, col_step).GetPieceColour()){
							good_move.first = row_step;
							good_move.second = col_step;
							available_moves.insert(good_move);
						}
					}
				}
			}
		}
	}
	// back left diagonal (for white)
	path_block = false;
	for (int row_step{ row - 1 }; row_step > -1; row_step--){
		for (int col_step{ col - 1 }; col_step > 0; col_step--){
			if ((row - row_step) == (col - col_step)){ //pick out diagonal
				while (!path_block){
					if (b(row_step, col_step).isempty()){
						good_move.first = row_step;
						good_move.second = col_step;
						available_moves.insert(good_move);
					}
					else{//the square has a piece on it, so block path 
						path_block = true;
						//add the square if enemy piece
						if (moving_colour != b(row_step, col_step).GetPieceColour()){
							good_move.first = row_step;
							good_move.second = col_step;
							available_moves.insert(good_move);
						}
					}
				} 
			}
		}
	}
	return available_moves;
}
//////////////PAWN//////////////////////
std::set<std::pair<int, int>> pawn::moves(const board& b, const int& row, const int& col){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> good_move;
	std::set<std::pair<int, int>> available_moves;
	int wh_step = row + 1, bl_step = row - 1, left_take = col - 1, rt_take = col + 1;
	//Different rules for White and Black as they can't move backwards
	if (moving_colour == "White"){
		//white pawn standard move
		if (inputcheck::in_boardrange(wh_step, col)){
			if (b(wh_step, col).isempty()){
				good_move.first = wh_step;
				good_move.second = col;
				available_moves.insert(good_move);
			}
		}
		//white pawn right diagonal take
		if (inputcheck::in_boardrange(wh_step, rt_take)){
			if ((!b(wh_step, rt_take).isempty()) &&
				(moving_colour != b(wh_step, rt_take).GetPieceColour())){
				good_move.first = wh_step;
				good_move.second = rt_take;
				available_moves.insert(good_move);
			}
		}
		//white pawn left diagonal take
		if (inputcheck::in_boardrange(wh_step, left_take)){
			if ((!b(wh_step, left_take).isempty()) &&
				(moving_colour != b(wh_step, left_take).GetPieceColour())){
				good_move.first = wh_step;
				good_move.second = left_take;
				available_moves.insert(good_move);
			}
		}
	}
	if (moving_colour == "Black"){
		//black pawn standard move
		if (inputcheck::in_boardrange(bl_step, col)){
			if (b(bl_step, col).isempty()){
				good_move.first = bl_step;
				good_move.second = col;
				available_moves.insert(good_move);
			}
		}
		//white pawn right diagonal take
		if (inputcheck::in_boardrange(bl_step, rt_take)){
			if ((!b(bl_step, rt_take).isempty()) &&
				(moving_colour != b(bl_step, rt_take).GetPieceColour())){
				good_move.first = bl_step;
				good_move.second = rt_take;
				available_moves.insert(good_move);
			}
		}
		//white pawn left diagonal take
		if (inputcheck::in_boardrange(bl_step, left_take)){
			if ((!b(bl_step, left_take).isempty()) &&
				(moving_colour != b(bl_step, left_take).GetPieceColour())){
				good_move.first = bl_step;
				good_move.second = left_take;
				available_moves.insert(good_move);
			}
		}
	}
	return available_moves;
}
////////////////KNIGHT///////////////////
//don't need to worry about path block as knight can jump
//do need to worry about jumping off the board, however.
//8 moves: r+1,col+2; r+2,col+1; r-1,col+2; r-2,col+1;r+1,col-2; r+2,col-1; r-1,c-2; r-2,c-1.
std::set<std::pair<int, int>> knight::moves(const board& b, const int& row, const int& col){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> poss_move;
	std::pair<int, int> good_move;
	std::set<std::pair<int, int>> possible_moves;
	std::set<std::pair<int, int>> available_moves;
	bool empty; //explicit varibale so complier doesn't error getting colour of nullptr (POTENTIAL ERROR)
	
	//USE A FOR EACH FOR THIS BIT
	
	//right forward #1
	int row_step = row + 1, col_step = col + 2;
	if (inputcheck::in_boardrange(row_step, col_step)){
		empty = (b(row_step, col_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(row_step, col_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = row_step;
			good_move.second = col_step;
			available_moves.insert(good_move);
		}
	}
	//right forward #2
	row_step = row + 2, col_step = col + 1;
	if (inputcheck::in_boardrange(row_step, col_step)){
		empty = (b(row_step, col_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(row_step, col_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = row_step;
			good_move.second = col_step;
			available_moves.insert(good_move);
		}
	}
	//forward left #1
	row_step = row + 1, col_step = col -2;
	if (inputcheck::in_boardrange(row_step, col_step)){
		empty = (b(row_step, col_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(row_step, col_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = row_step;
			good_move.second = col_step;
			available_moves.insert(good_move);
		}
	}
	
	//forward left #2
	row_step =row + 2, col_step = col - 1;
	if (inputcheck::in_boardrange(row_step, col_step)){
		empty = (b(row_step, col_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(row_step, col_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = row_step;
			good_move.second = col_step;
			available_moves.insert(good_move);
		}
	}
	//backward right #1 
	row_step =row - 1, col_step = col + 2;
	if (inputcheck::in_boardrange(row_step, col_step)){
		empty = (b(row_step, col_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(row_step, col_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = row_step;
			good_move.second = col_step;
			available_moves.insert(good_move);
		}
	}
	//backward right #2
	row_step = row - 2, col_step = col + 1;
	if (inputcheck::in_boardrange(row_step, col_step)){
		empty = (b(row_step, col_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(row_step, col_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = row_step;
			good_move.second = col_step;
			available_moves.insert(good_move);
		}
	}
	//backward left #1
	row_step = row -1, col_step = col - 2;
	if (inputcheck::in_boardrange(row_step, col_step)){
		empty = (b(row_step, col_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(row_step, col_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = row_step;
			good_move.second = col_step;
			available_moves.insert(good_move);
		}
	}
	//backward left #2
	row_step = row - 2, col_step = col - 1;
	if (inputcheck::in_boardrange(row_step, col_step)){
		empty = (b(row_step, col_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(row_step, col_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = row_step;
			good_move.second = col_step;
			available_moves.insert(good_move);
		}
	}
	return available_moves;
}
//////////////////QUEEN///////////////////////
std::set<std::pair<int, int>> queen::moves(const board& b, const int& row, const int& col){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> good_move;
	std::set<std::pair<int, int>> available_moves;
	bool path_block = false;
	//check spaces in front of piece (behind if black)
	for (int for_step{ row + 1 }; for_step < (board_rows); for_step++){
		while (!path_block){
			if (b(for_step, col).isempty()){
				good_move.first = for_step;
				good_move.second = col;
				available_moves.insert(good_move);
			}
			else{//the square has a piece on it, so block path
				path_block = true;
				//add the square if enemy piece
				if (moving_colour != b(for_step, col).GetPieceColour()){
					good_move.first = for_step;
					good_move.second = col;
					available_moves.insert(good_move);
				}
			}

		}
	}
	//check spaces behind piece (front if black piece)
	//reset path_block
	path_block = false;
	for (int back_step{ row - 1 }; back_step > (-1); back_step--){
		while (!path_block){
			if (b(back_step, col).isempty()){
				good_move.first = back_step;
				good_move.second = col;
				available_moves.insert(good_move);
			}
			else{//the square has a piece on it, so block path
				path_block = true;
				//add the square if enemy piece
				if (moving_colour != b(back_step, col).GetPieceColour()){
					good_move.first = back_step;
					good_move.second = col;
					available_moves.insert(good_move);
				}
			}

		}
	}
	//check spaces to the left of rook
	path_block = false;
	for (int left_step{ col - 1 }; left_step > (-1); left_step--){
		while (!path_block){
			if (b(row, left_step).isempty()){
				good_move.first = row;
				good_move.second = left_step;
				available_moves.insert(good_move);
			}
			else{//the square has a piece on it, so block path 
				path_block = true;
				//add the square if enemy piece
				if (moving_colour != b(row, left_step).GetPieceColour()){
					good_move.first = row;
					good_move.second = left_step;
					available_moves.insert(good_move);
				}
			
			}

		}
	}
	//check spaces to the right of piece
	path_block = false;
	for (int rt_step{ col + 1 }; rt_step < (board_cols - 1); rt_step++){
		while (!path_block){
			if (b(row, rt_step).isempty()){
				good_move.first = row;
				good_move.second = rt_step;
				available_moves.insert(good_move);
			}
			else{//the square has a piece on it, so block path 
				path_block = true;
				//add the square if enemy piece
				if (moving_colour != b(row, rt_step).GetPieceColour()){
					good_move.first = row;
					good_move.second = rt_step;
					available_moves.insert(good_move);
				}
			
			}

		}
	}
	// forward right diagonal (for white)
	path_block = false;
	for (int row_step{ row + 1 }; row_step < (board_rows - 1); row_step++){
		for (int col_step{ col + 1 }; col_step < (board_cols - 1); col_step++){
			if ((row_step - row) == (col_step - col)){ //pick out diagonal
				while (!path_block){
					if (b(row_step, col_step).isempty()){
						good_move.first = row_step;
						good_move.second = col_step;
						available_moves.insert(good_move);
					}
					else{//the square has a piece on it, so block path 
						path_block = true;
						//add the square if enemy piece
						if (moving_colour != b(row_step, col_step).GetPieceColour()){
							good_move.first = row_step;
							good_move.second = col_step;
							available_moves.insert(good_move);
						}
						
					}

				}
			}
		}
	}
	// forward left diagonal (for white)
	path_block = false;
	for (int row_step{ row + 1 }; row_step < (board_rows - 1); row_step++){
		for (int col_step{ col - 1 }; col_step > 0; col_step--){
			if ((row_step - row) == (col - col_step)){ //pick out diagonal
				while (!path_block){
					if (b(row_step, col_step).isempty()){
						good_move.first = row_step;
						good_move.second = col_step;
						available_moves.insert(good_move);
					}
					else{//the square has a piece on it, so block path 
						path_block = true;
						//add the square if enemy piece
						if (moving_colour != b(row_step, col_step).GetPieceColour()){
							good_move.first = row_step;
							good_move.second = col_step;
							available_moves.insert(good_move);
						}
					}

				} 
			}
		}
	}
	// back left diagonal (for white)
	path_block = false;
	for (int row_step{ row - 1 }; row_step > 0; row_step--){
		for (int col_step{ col + 1 }; col_step < (board_cols - 1); col_step++){
			if ((row - row_step) == (col_step - col)){ //pick out diagonal
				while (!path_block){
					if (b(row_step, col_step).isempty()){
						good_move.first = row_step;
						good_move.second = col_step;
						available_moves.insert(good_move);
					}
					else{//the square has a piece on it, so block path 
						path_block = true;
						//add the square if enemy piece
						if (moving_colour != b(row_step, col_step).GetPieceColour()){
							good_move.first = row_step;
							good_move.second = col_step;
							available_moves.insert(good_move);
						}
					}

				}
			}
		}
	}
	// back left diagonal (for white)
	path_block = false;
	for (int row_step{ row - 1 }; row_step > 0; row_step--){
		for (int col_step{ col - 1 }; col_step > 0; col_step--){
			if ((row - row_step) == (col - col_step)){ //pick out diagonal
				while (!path_block){
					if (b(row_step, col_step).isempty()){
						good_move.first = row_step;
						good_move.second = col_step;
						available_moves.insert(good_move);
					}
					else{//the square has a piece on it, so block path 
						path_block = true;
						//add the square if enemy piece
						if (moving_colour != b(row_step, col_step).GetPieceColour()){
							good_move.first = row_step;
							good_move.second = col_step;
							available_moves.insert(good_move);
						}
					}
				} 
			}
		}
	}
	return available_moves;
}
std::set<std::pair<int, int>> king::moves(const board& b, const int& row, const int& col){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> good_move;
	std::set<std::pair<int, int>> available_moves;
	bool empty;
	int for_step = row + 1, bk_step = row - 1, left_step = col - 1, rt_step = col + 1;
	//Check surrounding squares start with one in front and then go clockwise
	//forward step
	if (inputcheck::in_boardrange(for_step, col)){
		empty = (b(for_step, col).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(for_step, col).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = for_step;
			good_move.second = col;
			available_moves.insert(good_move);
		}
	}
	//forward right diagonal
	if (inputcheck::in_boardrange(for_step, rt_step)){
		empty = (b(for_step, rt_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(for_step, rt_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = for_step;
			good_move.second = rt_step;
			available_moves.insert(good_move);
		}
	}
	//right
	if (inputcheck::in_boardrange(row, rt_step)){
		empty = (b(row, rt_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(row, rt_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = row;
			good_move.second = rt_step;
			available_moves.insert(good_move);
		}
	}
	//backward right diagonal
	if (inputcheck::in_boardrange(bk_step, rt_step)){
		empty = (b(bk_step, rt_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(bk_step, rt_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = bk_step;
			good_move.second = rt_step;
			available_moves.insert(good_move);
		}
	}
	//backward
	if (inputcheck::in_boardrange(bk_step, col)){
		empty = (b(bk_step, col).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(bk_step, col).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = bk_step;
			good_move.second = col;
			available_moves.insert(good_move);
		}
	}
	//back left diag
	if (inputcheck::in_boardrange(bk_step, left_step)){
		empty = (b(bk_step, left_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(bk_step, left_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = bk_step;
			good_move.second = left_step;
			available_moves.insert(good_move);
		}
	}
	//left step
	if (inputcheck::in_boardrange(row, left_step)){
		empty = (b(row, left_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(row, left_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = row;
			good_move.second = left_step;
			available_moves.insert(good_move);
		}
	}
	//forward left diag
	if (inputcheck::in_boardrange(for_step, left_step)){
		empty = (b(for_step, left_step).isempty());
		if ((empty) || ((!empty) && (moving_colour != b(for_step, left_step).GetPieceColour()))){
			//^square is empty or contains opposition piece
			good_move.first = for_step;
			good_move.second = left_step;
			available_moves.insert(good_move);
		}
	}
	return available_moves;
}



