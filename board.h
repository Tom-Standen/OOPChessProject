//MPhys OOP Chess project: board class

#pragma once
#include "piece.h"
#include <string>
#include <vector>
#include <memory>

class board{
protected:
	//piece locations will be stored in an 8x8 2D array
	std::vector<std::vector<square>> m_square_2Dvector;
	//piece map keeps a record of the physical pieces and their positions eg {pawn:'A2'}
	//piece map variable
	//white and black lists for storing lost pieces to be potentially output to console
public:
	//constructors and destructors
	board() { init(); }
	// param constructor board(piece, colour){}; Idea to create a board where one team has a handicap (no queen etc)
	~board() {};
	board(board&); //Copy constructor
	board(board&&); //Move constructor
	board& operator=(board&);//Copy assignment
	board& operator=(board&&);//Move assignment
	//methods
	void init(); //initialize the board
	void print_board() const; //output the board to the terminal
	void print_checkerboard() const; //output the main checkers to the terminal
	const square & operator()(const int a, const int b) const { return m_square_2Dvector[a][b]; }
	//check that the squares not empty and that the piece belongs to the player
	bool valid_move() const;//piece moving_piece, square int row, int col, square end_pos) const {}; //check if the move can be made
	//void update_board(square int row, int col, square end_pos) {}; //if valid_move alter the piece locations, and identify any taken pieces
	void print_lost(); //some function for printing out lost pieces for either team
	/*std::unique_ptr<square> &operator()(const int m, const int n){
	//return pointer to the square at requested position. m = row #, n = col #
	if ((m > 0) && (m < board_rows) && (n > 0) && (n < board_cols)){
	std::unique_ptr<square> sq_pointer = std::make_unique<square>(m_square_2Dvector[m][n]);
	return sq_pointer;
	}
	else{
	//index is outside board range
	std::cout << "Error: You requested an square thats not on the board" << std::endl;
	}
	}*/
};
