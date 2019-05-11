//MPhys OOP Chess project: board class
//Board object has a protected 2D vector of squares 
//The main function of the class is to output the board to the user interface
// and storing where the pieces are in the board
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
	~board() {};
	//copy constructor
	board(const board& b){ m_square_2Dvector = b.m_square_2Dvector;}
	//copy assignment
	board& operator=(board&);

	//methods
	void init(); //initialize the board
	void print_board() const; //output the board to the terminal
	void print_checkerboard() const; //output the main checkers to the terminal
	square & operator()(const int a, const int b){ return m_square_2Dvector[a][b]; }
	//check that the squares not empty and that the piece belongs to the player
	void print_lost(); //some function for printing out lost pieces for either team
	
};