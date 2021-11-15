//MPhys OOP Chess project: piece class
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
	virtual std::set<std::pair<int, int>> moves(board&, const int&, const int&) = 0; // standard move made by each piece
	std::string GetName() const { return m_name; } //return the name of the piece i.e rook
	std::string GetColour() const { return m_colour; } //return the colour of the piece i.e White
	bool FirstMove() const { return m_first_move; } //boolean to determine wether piece has moved (pawn double, rook & king castle)
	void Moved() { m_first_move = false; } //record the fact the piece has moved
};

//Derived Class: Piece - Pawn
class pawn : public piece{
public:
	pawn(){ m_name = "Pawn", m_colour = "White", m_first_move = true;}
	pawn(std::string colour) { m_name = "Pawn", m_colour = colour; m_first_move = true; }
	//pawn(const pawn& copied){ m_name = copied.m_name, m_colour = copied.m_colour; }
	virtual ~pawn(){}
	std::set<std::pair<int, int>> moves(board&, const int&, const int&) override; // pawn standard move is one space forward (+8)
};
class rook : public piece{
public:
	rook(){ m_name = "Rook", m_colour = "White", m_first_move = true; }
	rook(std::string colour) { m_name = "Rook", m_colour = colour, m_first_move = true; }
	virtual ~rook(){}
	std::set<std::pair<int, int>> moves(board&, const int&, const int&) override; // rook standard move is unlimited forward,back, left and right (+8,-8,+1,-1)*(up to 7)
};
class bishop : public piece{
public:
	bishop(){ m_name = "Bishop", m_colour = "White"; }
	bishop(std::string colour) { m_name = "Bishop", m_colour = colour; }
	virtual ~bishop(){}
	std::set<std::pair<int, int>> moves(board&, const int&, const int&) override; // bishop standard move is unlimited diagonal (+9,-9,+7,=-7)*(up to 7)
};
class knight : public piece{
public:
	knight(){ m_name = "Knight", m_colour = "White"; }
	knight(std::string colour) { m_name = "Knight", m_colour = colour; }
	virtual ~knight(){}
	std::set<std::pair<int, int>> moves(board&, const int&, const int&) override; // knight standard move is unique (+17,+10,+15,+6,-17,-15,-10,-6)
};
class queen : public piece{
public:
	queen(){ m_name = "Queen", m_colour = "White", m_first_move = true; }
	queen(std::string colour) { m_name = "Queen", m_colour = colour, m_first_move = false; }
	virtual ~queen(){}
	std::set<std::pair<int, int>> moves(board&, const int&, const int&) override; // queen standard move is unlimited f,b,l,r and diag (+9,-9,+7,-7,+8,-8,+1,-1)*(up to 7)
};
class king : public piece{
public:
	king(){ m_name = "King", m_colour = "White"; }
	king(std::string colour) { m_name = "King", m_colour = colour; }
	virtual ~king(){}
	std::set<std::pair<int, int>> moves(board&, const int&, const int&) override; // king standard move is one space f,b,l,r and diag (+9,-9,+7,-7,+8,-8,+1,-1)
};
