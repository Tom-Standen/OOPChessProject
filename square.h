//MPhys OOP Chess project: square class

#pragma once
#include "piece.h"
#include <vector>
#include <string>
#include <memory>

///////////////SQUARE CLASS///////////////
class square{
protected:
	//member data - colour of square, what piece is on square
	std::string m_sq_colour;
	std::shared_ptr<piece> m_on_square;
	bool m_empty;
public:
	//give the square class access to piece constructors and memeber functions
	friend class piece;
	//Contructors
	square(){ m_sq_colour = "White"; m_empty = true; }
	square(std::string sq_colour, std::shared_ptr<piece> on_square){ m_empty = false, m_sq_colour = sq_colour, m_on_square = on_square; }
	~square(){}
	//methods
	std::string GetColour() const { return m_sq_colour; }
	std::string GetPieceColour() const { return m_on_square->GetColour(); }
	std::string PieceName() const { return m_on_square->GetName(); }
	bool isempty() const { return (m_on_square == nullptr) ; }
	void SetPiece(std::shared_ptr<piece> on_square){ m_on_square = on_square; }
	void SetColour(const std::string& sq_colour){ m_sq_colour = sq_colour; }
	std::shared_ptr<piece> Piece() const { return m_on_square; }
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
	m_on_square = copied.m_on_square;
	return (*this);
	}
	/*
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
