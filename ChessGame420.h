//// OOP Final Project - Board Game: Chess //// 
// Author: Thomas Standen, start: 07/04/19, end: 13/05/19 //
// This is the header file for the chess project 
//It contains the Board and Player class definitions and function declarations

#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>


//constant dimensions of the chess board
const int board_rows{ 8 };
const int board_cols{ 8 };
const int RowsInRow{ 4 };

/*enumerate the squares on the board with standard A1 - H8 notation
enum square{
A1 = 0, B1, C1, D1, E1, F1, G1, H1, A2, B2, C2, D2, E2, F2, G2, H2,
A3, B3, C3, D3, E3, F3, G3, H3, A4, B4, C4, D4, E4, F4, G4, H4,
A5, B5, C5, D5, E5, F5, G5, H5, A6, B6, C6, D6, E6, F6, G6, H6,
A7, B7, C7, D7, E7, F7, G7, H7, A8, B8, C8, D8, E8, F8, G8, H8

};*/

//Abstract Base Class: piece
class piece {
protected:
	std::string m_name;
	std::string m_colour;
public:
	//abstract base class for all pieces (no constructors) 
	//piece();
	//copy constructor
	//piece(piece& copied){ m_name = copied.m_name, m_colour = copied.m_colour; }
	virtual ~piece(){};	
	//copy assignment
	/*
	piece& piece::operator=(const piece & copied){
		if ((&copied) == this) { return (*this); }
		m_name = copied.m_name;
		m_colour = copied.m_colour;
		return (*this);
	}
	//move assignment
	piece & piece::operator=(piece && moved){
		//Swap the data
		m_name = std::string(); 
		m_colour = std::string();
		std::swap(m_name, moved.m_name);
		std::swap(m_colour, moved.m_colour);
		return (*this);
	}*/
	//methods
	//virtual void StdMove(square start_pos, square end_pos) =  0; // standard move made by each piece
	std::string GetName() const { return m_name; } //return the name of the piece i.e rook
	std::string GetColour() const { return m_colour; } //return the colour of the piece i.e White
};
//Derived Class: Piece - Pawn
class pawn : public piece{
public:
	pawn(){ m_name = "Pawn", m_colour = "White"; }
	pawn(std::string colour) { m_name = "Pawn", m_colour = colour; }
	//pawn(const pawn& copied){ m_name = copied.m_name, m_colour = copied.m_colour; }
	virtual ~pawn(){}
	
	//void StdMove(square start_pos, square end_pos) override {}; // pawn standard move is one space forward (+8)
};
class rook : public piece{
public:
	rook(){ m_name = "Rook", m_colour = "White"; }
	rook(std::string colour) { m_name = "Rook", m_colour = colour; }
	virtual ~rook(){}
	//void StdMove(square start_pos, square end_pos) override {}; // rook standard move is unlimited forward,back, left and right (+8,-8,+1,-1)*(up to 7)
};
class bishop : public piece{
public:
	bishop(){ m_name = "Bishop", m_colour = "White"; }
	bishop(std::string colour) { m_name = "Bishop", m_colour = colour; }
	virtual ~bishop(){}
	//void StdMove(square start_pos, square end_pos) override {}; // bishop standard move is unlimited diagonal (+9,-9,+7,=-7)*(up to 7)
};
class knight : public piece{
public:
	knight(){ m_name = "Knight", m_colour = "White"; }
	knight(std::string colour) { m_name = "Knight", m_colour = colour; }
	virtual ~knight(){}
	//void StdMove(square start_pos, square end_pos) override {}; // knight standard move is unique (+17,+10,+15,+6,-17,-15,-10,-6)
};
class queen : public piece{
public:
	queen(){ m_name = "Queen", m_colour = "White"; }
	queen(std::string colour) { m_name = "Queen", m_colour = colour; }
	virtual ~queen(){}
	//void StdMove(square start_pos, square end_pos) override {}; // queen standard move is unlimited f,b,l,r and diag (+9,-9,+7,-7,+8,-8,+1,-1)*(up to 7)
};
class king : public piece{
public:
	king(){ m_name = "King", m_colour = "White"; }
	king(std::string colour) { m_name = "King", m_colour = colour; }
	virtual ~king(){}
	//void StdMove(square start_pos, square end_pos) override {}; // king standard move is one space f,b,l,r and diag (+9,-9,+7,-7,+8,-8,+1,-1)
};

///////////////SQUARE CLASS///////////////
class square{
protected:
	//member data - colour of square, what piece is on square
	std::string m_sq_colour;
	piece m_on_square;
	bool m_empty;
public:
	//give the square class access to piece constructors and memeber functions
	friend class piece;
	//Contructors
	square(){ m_sq_colour = "White"; m_empty = true; }
	square(std::string sq_colour, piece on_square){ m_empty = false, m_sq_colour = sq_colour, m_on_square = on_square; }
	~square(){}
	//methods
	std::string GetColour() const { return m_sq_colour; }
	std::string PieceName() const { return m_on_square.GetName(); }
	void SetPiece(piece on_square){ m_on_square = on_square; }
	void SetColour(const std::string& sq_colour){ m_sq_colour = sq_colour; }
	void PrintBorderRow() const;
	void PrintSecondRow() const;
	void PrintThirdRow() const;
	//Move, Copy assignment
	/*square &operator=(square& copied){
		//deep copy one square to another
		//need to block self assingment
		if (&copied == this) { return (*this); }
		//copy data across
		m_sq_colour = copied.m_sq_colour;
		m_on_square.reset();
		m_on_square = std::make_shared<piece>(copied.m_on_square);
		return (*this);
	}
	square &operator=(square&& moved){
		//move a piece from one square to another
		//don't want to move square colour but do want to move piece
		m_on_square.reset();
		m_on_square = std::make_shared<>(moved.m_on_square);
		moved.m_on_square.reset();
		moved.m_on_square = std::make_shared<piece>(nullptr);
		return (*this);
	}*/
};
//IDEA: class for game management
//lost pieces, score, who's turn, how many moves, time taken for last move/each player/total game time, move history
/*board class will keep track of where the pieces are on the board
it will also contain functions for printing out the board and storing which pieces are missing*/
//all member data and functions are precedded with m_ to distinguish from external functions

class board {
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
	//bool empty_check(square pos) const {}; //check if the square has a piece in it, used in valid_move and removing taken pieces
	bool valid_move() const;//piece moving_piece, square start_pos, square end_pos) const {}; //check if the move can be made
	//void update_board(square start_pos, square end_pos) {}; //if valid_move alter the piece locations, and identify any taken pieces
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

