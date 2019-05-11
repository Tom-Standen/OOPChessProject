//MPhys OOP Chess project: piece class
//Pointers to pieces are stored on square objects
//Class is primarily used in printing out piece names to board
//  and for assessing whether requested moves are allowed
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <set>
#include <utility>

//Abstract Base Class: piece
class game;
class player;
class board;
class square;
class piece {
protected:
	std::string m_name;
	std::string m_colour;
	bool m_first_move;
public:
	//abstract base class for all pieces (no constructors) 
	virtual ~piece(){};
	//methods
	// moves returns a pair of sets.
	//One is the set of all squares that this piece can move to.
	//The other is the set of squares that make up the path to the king
	//It takes a reference to the current board, and the last board (for en passnat)
	// + two integers for piece position and one pair of integers for king position
	virtual std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>> moves(board&, board&, const int&, const int&, std::pair<int,int>) = 0;
	std::string GetName() const { return m_name; } //return the name of the piece i.e rook
	std::string GetColour() const { return m_colour; } //return the colour of the piece i.e White
	bool FirstMove() const { return m_first_move; } //boolean to determine wether piece has moved (pawn double, rook & king castle)
	void Moved() { m_first_move = false; } //record the fact the piece has moved
};

//Derived Classes: 
// Piece - Pawn
class pawn : public piece{
public:
	//Constructors + Destructor
	pawn(){ m_name = "Pawn", m_colour = "White", m_first_move = true;}
	pawn(std::string colour) { m_name = "Pawn", m_colour = colour; m_first_move = true; }
	virtual ~pawn(){}
	//Pawn moves override
	std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>> 
		moves(board&, board&, const int&, const int&, std::pair<int, int>) override; // pawn standard move is one space forward (+8)
};
// Piece - Rook
class rook : public piece{
public:
	//Constructors + Destructor
	rook(){ m_name = "Rook", m_colour = "White", m_first_move = true; }
	rook(std::string colour) { m_name = "Rook", m_colour = colour, m_first_move = true; }
	virtual ~rook(){}
	//Rook moves override
	std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>> 
		moves(board&, board&, const int&, const int&, std::pair<int, int>) override; // rook standard move is unlimited forward,back, left and right (+8,-8,+1,-1)*(up to 7)
};
// Piece - Bishop
class bishop : public piece{
public:
	//Constructors + Destructor
	bishop(){ m_name = "Bishop", m_colour = "White"; }
	bishop(std::string colour) { m_name = "Bishop", m_colour = colour; }
	virtual ~bishop(){}
	//Bishop moves override
	std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>> 
		moves(board&, board&, const int&, const int&, std::pair<int, int>) override; // bishop standard move is unlimited diagonal (+9,-9,+7,=-7)*(up to 7)
};
//Piece - Knight
class knight : public piece{
public:
	//Constructors + Destructor
	knight(){ m_name = "Knight", m_colour = "White"; }
	knight(std::string colour) { m_name = "Knight", m_colour = colour; }
	virtual ~knight(){}
	//knight moves override
	std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>>
		moves(board&, board&, const int&, const int&, std::pair<int, int>) override; // knight standard move is unique (+17,+10,+15,+6,-17,-15,-10,-6)
};
//Piece - Queen
class queen : public piece{
public:
	//Constructors + Destructor
	queen(){ m_name = "Queen", m_colour = "White", m_first_move = true; }
	queen(std::string colour) { m_name = "Queen", m_colour = colour, m_first_move = false; }
	virtual ~queen(){}
	//Queen moves override
	std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>> 
		moves(board&, board&, const int&, const int&, std::pair<int, int>) override; // queen standard move is unlimited f,b,l,r and diag (+9,-9,+7,-7,+8,-8,+1,-1)*(up to 7)
};
//Piece - King
class king : public piece{
public:
	//Constructors + Destructor
	king(){ m_name = "King", m_colour = "White", m_first_move = true; }
	king(std::string colour) { m_name = "King", m_colour = colour, m_first_move = true; }
	virtual ~king(){}
	//King moves override
	std::pair<std::set<std::pair<int, int>>, std::set<std::pair<int, int>>>
		moves(board&, board&, const int&, const int&, std::pair<int, int>) override; // king standard move is one space f,b,l,r and diag (+9,-9,+7,-7,+8,-8,+1,-1)
};


