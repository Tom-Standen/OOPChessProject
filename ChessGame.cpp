//// OOP Final Project - Board Game: Chess //// 
// Author: Thomas Standen, start: 07/04/19, end: 13/05/19 //
//Source file where:
//Non-Method function definitions and longer methods are defined
//Including (but not limited to):
//methods for outputting the board
//functions for checking User input
//methods for piece moves

#include "ChessGame.h"
#include "player.h"
#include "square.h"
#include "piece.h"
#include "board.h"
#include "Game.h"
#include <iostream>



////////// Namepsace - inputcheck:: definitions//////////////
// functions that validate the user inputs

bool inputcheck::in_boardrange(int row, int col){
	//check if a requested square exists on the board
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
std::shared_ptr<piece> inputcheck::promotioncheck(std::string colour){
	std::cout << "Would you like the normal promotion: Pawn -> Queen? (Y/N)" << std::endl;
	std::string normal;
	getline(std::cin, normal);
	while (normal != "Yes" && normal != "No" && normal != "Y" && normal != "N" && normal != "y" && normal != "n" &&
		normal != "yes" && normal != "no"){
		std::cout << "Please answer Yes or No" << std::endl;
		getline(std::cin, normal);
	}
	if (normal == "No" || normal == "N" || normal == "no" || normal == "n"){
		std::cout << "Please indicate which piece you would like: R for (R)ook, N for k(N)ight, B for (B)ishop" << std::endl;
		std::string promote;
		getline(std::cin, promote);
		while (promote != "N" && promote != "n" && promote != "R" && promote != "r" && promote != "B" && promote != "b"){
			std::cout << "Please repsond : R, B or N" << std::endl;
			getline(std::cin, promote);
		}
		if (promote == "N" || promote == "n"){ return std::make_shared<knight>(colour); }
		else{ 
			if (promote == "B" || promote == "b"){ return std::make_shared<bishop>(colour); }
			else{ return std::make_shared<rook>(colour); }	
		}
	}
	else{ return std::make_shared<queen>(colour); }
}
//////// End of Namespace - inputcheck:: definitions///////////
//////// Start  Namespace - headerandfooter:: definitions/////////////
void headerandfooter::board_header(){
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
void headerandfooter::board_footer(){
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
		if (column_it == board_cols - 1){ std::cout << "|________|"; }
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
		if (column_it == board_cols - 1){ std::cout << "        |"; }
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
///////////// End of Namespace - headerandfooter:: definitions/////
//////////////   GAME METHODS   ////////////////
void game::SetTurn(std::shared_ptr<player> turn_ptr, std::shared_ptr<player> not_turnptr){
	m_turn = turn_ptr, m_not_turn = not_turnptr;
}
void game::ChangeTurn(std::shared_ptr<player> currentturn, std::shared_ptr<player> currentnotturn){
	m_turn = currentnotturn, m_not_turn = currentturn;
}
/////////////// END GAME METHODS/////////////////
///////////////// Start:  PLAYER METHODS     //////////////

bool player::MyPiece(const square& sq){
	//Determining whether player selected a valid square for moving
	if (sq.isempty()){
		std::cout << "You selected an empty sqaure" << std::endl;
		return false;
	}
	else {
		if(sq.GetPieceColour() != m_player_colour){
			std::cout << "That's not your piece!" << std::endl;
			return false;
		}
		else{ return true; }
	}
}
//Paramterised Constructor
player::player(std::string name, std::string colour){
	m_player_colour = colour;
	m_player_name = name;
	m_in_check = false;
	//add the starting piece positions 00-17 fow white and 60,77 for black
	std::vector<int> white_rows{ 0, 1 };
	std::vector<int> black_rows{ 6, 7 };
	if (colour == "White"){
		for (auto row_it = white_rows.begin(); row_it != white_rows.end(); row_it++){
			for (int col_it{ 0 }; col_it < board_cols; col_it++){
				m_piece_positions.push_back(std::make_pair((*row_it), col_it));
			}
		}
		m_king_pos = std::make_pair(0, 4);
	}
	if (colour == "Black"){
		for (auto row_it = black_rows.begin(); row_it != black_rows.end(); row_it++){
			for (int col_it{ 0 }; col_it < board_cols; col_it++){
				m_piece_positions.push_back(std::make_pair((*row_it), col_it));
			}
		}
		m_king_pos = std::make_pair(7, 4);
	}
}
void player::UpdatePos(std::pair<int, int> newpos, std::pair<int, int> oldpos){
	m_piece_positions.remove(oldpos);
	m_piece_positions.push_back(newpos);
}


////BOARD METHOD DEFINITIONS////
//copy assignment
board& board::operator=(board& b){
	if (&b == this){ return (*this); }
	m_square_2Dvector = b.m_square_2Dvector;
	return (*this);
}
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
	m_square_2Dvector[7][0] = square("White", std::make_shared<rook>("Black"));
	m_square_2Dvector[7][1] = square("Black", std::make_shared<knight>("Black"));
	m_square_2Dvector[7][2] = square("White", std::make_shared<bishop>("Black"));
	m_square_2Dvector[7][3] = square("Black", std::make_shared<queen>("Black"));
	m_square_2Dvector[7][4] = square("White", std::make_shared<king>("Black"));
	m_square_2Dvector[7][5] = square("Black", std::make_shared<bishop>("Black"));
	m_square_2Dvector[7][6] = square("White", std::make_shared<knight>("Black"));
	m_square_2Dvector[7][7] = square("Black", std::make_shared<rook>("Black"));
	//Set the colour of the squares in middle four rows
	bool black;
	for (int row{ 0 }; row < 8; row++){
		//Third row (row==2) starts with a black square
		//other way than I thought but still works
		(((row % 2) == 0) ? black = false : black = true);
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
//////// END SQUARE METHODS /////////////////

////////////// PIECE ALLOWED MOVES//////////////
//METHOD: 
//Take in a reference to the board and the piece location
//Check spaces accessible to each piece and record list of the available moves to that piece
//Check by looping through (when necessary) the piece's moving channels until another piece is found blocking path
//store the accesible spaces in a list to be returned by the function


////////////////ROOK/////////////////////

std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>> rook::moves(board& b, board& last_b,
	const int& row, const int& col, std::pair<int, int> king_pos){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> good_move;
	std::set<std::pair<int, int>> available_moves, king_path;
	std::set<std::pair<int, int>> for_path, back_path, left_path, right_path;
	bool path_block = false;
	//check spaces in front of piece (behind if black)
	for (int for_step{ row + 1 }; for_step < (board_rows); for_step++){
		if (b(for_step, col).isempty()){
			good_move.first = for_step;
			good_move.second = col;
			for_path.insert(good_move);
			available_moves.insert(good_move);
		}
		else{//the square has a piece on it, so block path
			path_block = true;
			//add the square if enemy piece
			if (moving_colour != b(for_step, col).GetPieceColour()){
				good_move.first = for_step;
				good_move.second = col;
				for_path.insert(good_move);
				available_moves.insert(good_move);
			}
		}
		if (path_block){ break; }
	}
	//check to see if king lies in this path
	if (for_path.find(king_pos) != for_path.end()){ 
		std::cout << "king in front of you" << std::endl;
		king_path = for_path;
		//remove the king's position from the path to it
		
	}
	
	//check spaces behind piece (front if black piece)
	//reset path_block
	path_block = false;
	for (int back_step{ row - 1 }; back_step > (-1); back_step--){
		if (b(back_step, col).isempty()){
			good_move.first = back_step;
			good_move.second = col;
			back_path.insert(good_move);
			available_moves.insert(good_move);
		}
		else{//the square has a piece on it, so block path 
			path_block = true;
			//add the square if enemy piece
			if (moving_colour != b(back_step, col).GetPieceColour()){
				good_move.first = back_step;
				good_move.second = col;
				back_path.insert(good_move);
				available_moves.insert(good_move);
			}
		}
		if (path_block) { break; }
	}
	if (back_path.find(king_pos) != back_path.end()){ 
		std::cout << "King behind you" << std::endl;
		king_path = back_path; 
		
	}
	
	//check spaces to the left of rook
	path_block = false;
	for (int left_step{ col - 1 }; left_step > (-1); left_step--){
		if (b(row, left_step).isempty()){
			good_move.first = row;
			good_move.second = left_step;
			left_path.insert(good_move);
			available_moves.insert(good_move);
		}
		else{//the square has a piece on it, so block path 
			path_block = true;
			//add the square if enemy piece
			if (moving_colour != b(row, left_step).GetPieceColour()){
				good_move.first = row;
				good_move.second = left_step;
				left_path.insert(good_move);
				available_moves.insert(good_move);
			}
		}
		if (path_block) { break; }
	}
	if (left_path.find(king_pos) != left_path.end()){ 
		king_path = left_path;
		
		std::cout << "King to your left" << std::endl;
	}
	
	//check spaces to the right of piece
	path_block = false;
	for (int rt_step{ col + 1 }; rt_step < (board_cols); rt_step++){
		if (b(row, rt_step).isempty()){
			good_move.first = row;
			good_move.second = rt_step;
			right_path.insert(good_move);
			available_moves.insert(good_move);
		}
		else{//the square has a piece on it, so block path 
			path_block = true;
			//add the square if enemy piece
			if (moving_colour != b(row, rt_step).GetPieceColour()){
				good_move.first = row;
				good_move.second = rt_step;
				right_path.insert(good_move);
				available_moves.insert(good_move);
			}
		}
		if (path_block) { break; }
	}
	if (right_path.find(king_pos) != right_path.end()){ 
		std::cout << "King to your right" << std::endl;
		king_path = right_path;
		
	}
	
	
	return std::make_pair(available_moves,king_path);
}

//////////////////BISHOP//////////////////////
std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>> bishop::moves(board& b, board& last_b,
	const int& row, const int& col, std::pair<int, int> king_pos){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> good_move;
	std::set<std::pair<int, int>> available_moves, king_path;
	std::set<std::pair<int, int>> for_rt_path, for_left_path, back_rt_path, back_left_path;
	// forward right diagonal (for white)
	bool path_block = false; 
	for (int row_step{ row + 1 }; row_step < (board_rows); row_step++){
		for (int col_step{ col + 1 }; col_step < (board_cols); col_step++){
			if ((row_step - row) == (col_step - col)){ //pick out diagonal
				if (b(row_step, col_step).isempty()){
					good_move.first = row_step;
					good_move.second = col_step;
					for_rt_path.insert(good_move);
					available_moves.insert(good_move);
				}
				else{//the square has a piece on it, so block path 
					path_block = true;
					//add the square if enemy piece
					if (moving_colour != b(row_step, col_step).GetPieceColour()){
						good_move.first = row_step;
						good_move.second = col_step;
						for_rt_path.insert(good_move);
						available_moves.insert(good_move);
					}
				}
			}
			if (path_block){ break; }
		}
		if (for_rt_path.find(king_pos) != for_rt_path.end()){ 
			king_path = for_rt_path; 
			
		}
	}
	// forward left diagonal (for white)
	path_block = false;
	for (int row_step{ row + 1 }; row_step < (board_rows); row_step++){
		for (int col_step{ col - 1 }; col_step > -1 ; col_step--){
			if ((row_step - row) == (col - col_step)){ //pick out diagonal
				if (b(row_step, col_step).isempty()){
					good_move.first = row_step;
					good_move.second = col_step;
					for_left_path.insert(good_move);
					available_moves.insert(good_move);
				}
				else{//the square has a piece on it, so block path
					path_block = true;
					//add the square if enemy piece
					if (moving_colour != b(row_step, col_step).GetPieceColour()){
						good_move.first = row_step;
						good_move.second = col_step;
						for_left_path.insert(good_move);
						available_moves.insert(good_move);
					}
				}
			}
			if (path_block){ break; }
		}
		if (for_left_path.find(king_pos) != for_left_path.end()){ 
			king_path = for_left_path; 
			
		}
	}
	// back right diagonal (for white)
	path_block = false;
	for (int row_step{ row - 1 }; row_step > -1 ; row_step--){
		for (int col_step{ col + 1 }; col_step < (board_cols); col_step++){
			if ((row - row_step) == (col_step - col)){ //pick out diagonal
				if (b(row_step, col_step).isempty()){
					good_move.first = row_step;
					good_move.second = col_step;
					back_rt_path.insert(good_move);
					available_moves.insert(good_move);
				}
				else{//the square has a piece on it, so block path 
					path_block = true;
					//add the square if enemy piece
					if (moving_colour != b(row_step, col_step).GetPieceColour()){
						good_move.first = row_step;
						good_move.second = col_step;
						back_rt_path.insert(good_move);
						available_moves.insert(good_move);
					}
				}
			}
			if (path_block){ break; }
		}
		if (back_rt_path.find(king_pos) != back_rt_path.end()){
			king_path = back_rt_path; 
			
		}
	}
	// back left diagonal (for white)
	path_block = false;
	for (int row_step{ row - 1 }; row_step > -1; row_step--){
		for (int col_step{ col - 1 }; col_step > -1; col_step--){
			if ((row - row_step) == (col - col_step)){ //pick out diagonal
				if (b(row_step, col_step).isempty()){
					good_move.first = row_step;
					good_move.second = col_step;
					back_left_path.insert(good_move);
					available_moves.insert(good_move);
				}
				else{//the square has a piece on it, so block path 
					path_block = true;
					//add the square if enemy piece
					if (moving_colour != b(row_step, col_step).GetPieceColour()){
						good_move.first = row_step;
						good_move.second = col_step;
						back_left_path.insert(good_move);
						available_moves.insert(good_move);
					}
				}
			}
			if (path_block){ break; }
		}
		if (back_left_path.find(king_pos) != back_left_path.end()){
			king_path = back_left_path; 
			
		}
	}
	return std::make_pair(available_moves, king_path);
}
//////////////PAWN//////////////////////
std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>> pawn::moves(board& b, board& last_b,
	const int& row, const int& col, std::pair<int, int> king_pos){
	std::string moving_colour{ b(row, col).GetPieceColour() };
	std::pair<int, int> good_move;
	std::set<std::pair<int, int>> available_moves, king_path;
	std::shared_ptr<piece> pwn{ b(row, col).Piece() };
	//The pawn may move one space forward if that space is empty, or 
	//one space diagonally to take an enemy piece
	//If the pawn is yet to move then it may jump two spaces
	int wh_step = row + 1, bl_step = row - 1, left_take = col - 1, rt_take = col + 1;
	int firstwh_step = row + 2, firstbl_step = row - 2;
	//Different rules for White and Black as they can't move backwards
	if (moving_colour == "White"){
		//white pawn standard move
		if (inputcheck::in_boardrange(wh_step, col)){
			if (b(wh_step, col).isempty()){
				good_move.first = wh_step;
				good_move.second = col;
				available_moves.insert(good_move);
				if (inputcheck::in_boardrange(firstwh_step, col)){
					if (b(firstwh_step, col).isempty() && (pwn->FirstMove())){
						good_move.first = firstwh_step;
						good_move.second = col;
						available_moves.insert(good_move);
					}
				}
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
			//en passant
			//has to be on 5th row, and opposing pawn must have jumped next to it
			if (row == 4){
				if (!last_b(row + 2, rt_take).isempty() && last_b(row, rt_take).isempty()){
					if (b(row + 2, rt_take).isempty() && !b(row, rt_take).isempty()){
						if (last_b(row + 2, rt_take).PieceName() == "Pawn"){
							good_move.first = wh_step;
							good_move.second = rt_take;
							available_moves.insert(good_move);
						}
					}
				}
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
			if (row == 4){
				if (!last_b(row + 2, left_take).isempty() && last_b(row, left_take).isempty()){
					if (b(row + 2, left_take).isempty() && !b(row, left_take).isempty()){
						if (last_b(row + 2, left_take).PieceName() == "Pawn"){
							good_move.first = wh_step;
							good_move.second = left_take;
							available_moves.insert(good_move);
						}
					}
				}
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
				if (inputcheck::in_boardrange(firstbl_step, col)){
					if (b(firstbl_step, col).isempty() && (pwn->FirstMove())){
						good_move.first = firstbl_step;
						good_move.second = col;
						available_moves.insert(good_move);
					}
				}
			}
		}
		//black pawn right diagonal take
		if (inputcheck::in_boardrange(bl_step, rt_take)){
			if ((!b(bl_step, rt_take).isempty()) &&
				(moving_colour != b(bl_step, rt_take).GetPieceColour())){
				good_move.first = bl_step;
				good_move.second = rt_take;
				available_moves.insert(good_move);
			}
			//En Passant
			if (row == 3){
				if (!last_b(row - 2, rt_take).isempty() && last_b(row, rt_take).isempty()){
					if (b(row - 2, rt_take).isempty() && !b(row, rt_take).isempty()){
						if (last_b(row - 2, rt_take).PieceName() == "Pawn"){
							good_move.first = bl_step;
							good_move.second = rt_take;
							available_moves.insert(good_move);
						}
					}
				}
			}
		}
		//black pawn left diagonal take
		if (inputcheck::in_boardrange(bl_step, left_take)){
			if ((!b(bl_step, left_take).isempty()) &&
				(moving_colour != b(bl_step, left_take).GetPieceColour())){
				good_move.first = bl_step;
				good_move.second = left_take;
				available_moves.insert(good_move);
			}
			if (row == 3){
				if (!last_b(row - 2, left_take).isempty() && last_b(row, left_take).isempty()){
					if (b(row - 2, left_take).isempty() && !b(row, left_take).isempty()){
						if (last_b(row - 2, left_take).PieceName() == "Pawn"){
							good_move.first = bl_step;
							good_move.second = left_take;
							available_moves.insert(good_move);
						}
					}
				}
			}
		}
	}
	return std::make_pair(available_moves, king_path);
}
////////////////KNIGHT///////////////////
//don't need to worry about path block as knight can jump
//do need to worry about jumping off the board, however.
//8 moves: r+1,col+2; r+2,col+1; r-1,col+2; r-2,col+1;r+1,col-2; r+2,col-1; r-1,c-2; r-2,c-1.
std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>> knight::moves(board& b, board& last_b,
	const int& row, const int& col, std::pair<int, int> king_pos){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> poss_move;
	std::pair<int, int> good_move;
	std::set<std::pair<int, int>> available_moves, king_path;
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
	return std::make_pair(available_moves, king_path);
}
//////////////////QUEEN///////////////////////
std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>> queen::moves(board& b, board& last_b,
	const int& row, const int& col, std::pair<int, int> king_pos){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> good_move;
	std::set<std::pair<int, int>> available_moves, king_path;
	std::set<std::pair<int, int>> for_path, back_path, left_path, right_path;
	std::set<std::pair<int, int>> for_rt_path, back_rt_path, for_left_path, back_left_path;
	bool path_block = false;
	//check spaces in front of piece (behind if black)
	for (int for_step{ row + 1 }; for_step < (board_rows); for_step++){
		if (b(for_step, col).isempty()){
			good_move.first = for_step;
			good_move.second = col;
			for_path.insert(good_move);
			available_moves.insert(good_move);
		}
		else{//the square has a piece on it, so block path
			path_block = true;
			//add the square if enemy piece
			if (moving_colour != b(for_step, col).GetPieceColour()){
				good_move.first = for_step;
				good_move.second = col;
				for_path.insert(good_move);
				available_moves.insert(good_move);
			}
		}
		if (path_block){ break; }
	}
	if (for_path.find(king_pos) != for_path.end()){ 
		king_path = for_path; 
		
	}
	//check spaces behind piece (front if black piece)
	//reset path_block
	path_block = false;
	for (int back_step{ row - 1 }; back_step > (-1); back_step--){
		if (b(back_step, col).isempty()){
			good_move.first = back_step;
			good_move.second = col;
			back_path.insert(good_move);
			available_moves.insert(good_move);
		}
		else{//the square has a piece on it, so block path
			path_block = true;
			//add the square if enemy piece
			if (moving_colour != b(back_step, col).GetPieceColour()){
				good_move.first = back_step;
				good_move.second = col;
				back_path.insert(good_move);
				available_moves.insert(good_move);
			}
		}
		if (path_block){ break; }
	}
	if (back_path.find(king_pos) != back_path.end()){
		king_path = back_path; 
		
	}
	//check spaces to the left of queen
	path_block = false;
	for (int left_step{ col - 1 }; left_step > (-1); left_step--){
		if (b(row, left_step).isempty()){
			good_move.first = row;
			good_move.second = left_step;
			left_path.insert(good_move);
			available_moves.insert(good_move);
		}
		else{//the square has a piece on it, so block path 
			path_block = true;
			//add the square if enemy piece
			if (moving_colour != b(row, left_step).GetPieceColour()){
				good_move.first = row;
				good_move.second = left_step;
				left_path.insert(good_move);
				available_moves.insert(good_move);
			}
			
		}
		if (path_block){ break; }
	}
	if (left_path.find(king_pos) != left_path.end()){ 
		king_path = left_path; 
		
	}
	//check spaces to the right of piece
	path_block = false;
	for (int rt_step{ col + 1 }; rt_step < (board_cols); rt_step++){
		if (b(row, rt_step).isempty()){
			good_move.first = row;
			good_move.second = rt_step;
			right_path.insert(good_move);
			available_moves.insert(good_move);
		}
		else{//the square has a piece on it, so block path 
			path_block = true;
			//add the square if enemy piece
			if (moving_colour != b(row, rt_step).GetPieceColour()){
				good_move.first = row;
				good_move.second = rt_step;
				right_path.insert(good_move);
				available_moves.insert(good_move);
			}
		}
		if (path_block){ break; }
	}
	if (right_path.find(king_pos) != right_path.end()){ 
		king_path = right_path; 
		
	}
	// forward right diagonal (for white)
	path_block = false;
	for (int row_step{ row + 1 }; row_step < (board_rows); row_step++){
		for (int col_step{ col + 1 }; col_step < (board_cols); col_step++){
			if ((row_step - row) == (col_step - col)){ //pick out diagonal
				if (b(row_step, col_step).isempty()){
					good_move.first = row_step;
					good_move.second = col_step;
					for_rt_path.insert(good_move);
					available_moves.insert(good_move);
				}
				else{//the square has a piece on it, so block path 
					path_block = true;
					//add the square if enemy piece
					if (moving_colour != b(row_step, col_step).GetPieceColour()){
						good_move.first = row_step;
						good_move.second = col_step;
						for_rt_path.insert(good_move);
						available_moves.insert(good_move);
					}	
				}
			}
			if (path_block){ break; }
		}
	}
	if (for_rt_path.find(king_pos) != for_rt_path.end()){ 
		king_path = for_rt_path; 
		
	}
	// forward left diagonal (for white)
	path_block = false;
	for (int row_step{ row + 1 }; row_step < (board_rows); row_step++){
		for (int col_step{ col - 1 }; col_step > -1; col_step--){
			if ((row_step - row) == (col - col_step)){ //pick out diagonal
				if (b(row_step, col_step).isempty()){
					good_move.first = row_step;
					good_move.second = col_step;
					for_left_path.insert(good_move);
					available_moves.insert(good_move);
				}
				else{//the square has a piece on it, so block path 
					path_block = true;
					//add the square if enemy piece
					if (moving_colour != b(row_step, col_step).GetPieceColour()){
						good_move.first = row_step;
						good_move.second = col_step;
						for_left_path.insert(good_move);
						available_moves.insert(good_move);
					}
				}
			}
			if (path_block){ break; }
		}
	}
	if (for_left_path.find(king_pos) != for_left_path.end()){ 
		king_path = for_left_path; 
		
	}
	// back right diagonal (for white)
	path_block = false;
	for (int row_step{ row - 1 }; row_step > -1; row_step--){
		for (int col_step{ col + 1 }; col_step < (board_cols); col_step++){
			if ((row - row_step) == (col_step - col)){ //pick out diagonal
				if (b(row_step, col_step).isempty()){
					good_move.first = row_step;
					good_move.second = col_step;
					back_rt_path.insert(good_move);
					available_moves.insert(good_move);
				}
				else{//the square has a piece on it, so block path 
					path_block = true;
					//add the square if enemy piece
					if (moving_colour != b(row_step, col_step).GetPieceColour()){
						good_move.first = row_step;
						good_move.second = col_step;
						back_rt_path.insert(good_move);
						available_moves.insert(good_move);
					}
				}
			}
			if (path_block){ break; }
		}
	}
	if (back_rt_path.find(king_pos) != back_rt_path.end()){
		king_path = back_rt_path; 
		
	}
	// back left diagonal (for white)
	path_block = false;
	for (int row_step{ row - 1 }; row_step > -1; row_step--){
		for (int col_step{ col - 1 }; col_step > -1; col_step--){
			if ((row - row_step) == (col - col_step)){ //pick out diagonal
				if (b(row_step, col_step).isempty()){
					good_move.first = row_step;
					good_move.second = col_step;
					back_left_path.insert(good_move);
					available_moves.insert(good_move);
				}
				else{//the square has a piece on it, so block path 
					path_block = true;
					//add the square if enemy piece
					if (moving_colour != b(row_step, col_step).GetPieceColour()){
						good_move.first = row_step;
						good_move.second = col_step;
						back_left_path.insert(good_move);
						available_moves.insert(good_move);
					}
				}
			} 
			if (path_block){ break; }
		}
	}
	if (back_left_path.find(king_pos) != back_left_path.end()){ 
		king_path = back_left_path; 
		
	}
	return std::make_pair(available_moves, king_path);
}
////////KING MOVES//////////
std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>> king::moves(board& b, board& last_b,
	const int& row, const int& col, std::pair<int, int> king_pos){
	std::string moving_colour = b(row, col).GetPieceColour();
	std::pair<int, int> good_move;
	std::set<std::pair<int, int>> available_moves, king_path;
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
	//castling
	//white castle (Hard code) 
	//need: 1)the king not to have moved
	if (m_first_move){
		if (moving_colour == "White"){
			//LONG castle
			//need: 1)the king not to have moved 2) left castle(0,0) not to have moved 3) 01,02,03 to be empty
			//add 02 to available moves
			if (!b(0,0).isempty()){
				if (b(0, 0).Piece()->FirstMove() && b(0, 1).isempty() && b(0, 2).isempty() && b(0, 3).isempty()){
					available_moves.insert(std::make_pair(0, 2));
				}
			}
			//SHORT castle
			//need: 1) king not to have moved 2) right castle (0,7) not to have moved 3) 06, 07 to be empty
			//add 06
			//need to check that the piece isn't empty, if it is then will throw exception
			if (!b(0, 7).isempty()){
				if (b(0, 7).Piece()->FirstMove() && b(0, 6).isempty() && b(0, 5).isempty()){
					available_moves.insert(std::make_pair(0, 6));
				}
			}
		}
		if (moving_colour == "Black"){
			//LONG castle
			//need: 1)the king not to have moved 2) left castle(7,0) not to have moved 3) 71,72,73 to be empty
			//add 02 to available moves
			if (!b(7, 0).isempty()){
				if (b(7, 0).Piece()->FirstMove() && b(7, 1).isempty() && b(7, 2).isempty() && b(7, 3).isempty()){
					available_moves.insert(std::make_pair(7, 2));
				}
			}
			//SHORT castle
			//need: 1) king not to have moved 2) right castle (7,7) not to have moved 3) 76, 77 to be empty
			//add 06
			if (!b(7, 7).isempty()){
				if (b(7, 7).Piece()->FirstMove() && b(7, 6).isempty() && b(7, 5).isempty()){
					available_moves.insert(std::make_pair(7, 6));
				}
			}
		}
	}
	return std::make_pair(available_moves, king_path);
}