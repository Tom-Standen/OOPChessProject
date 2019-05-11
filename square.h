//MPhys OOP Chess project: square class
//Each square of the board either has a pointer to a piece
//	or a nullptr depending on the state of the game

#pragma once
#include "piece.h"
#include <string>
#include <memory>

///////////////SQUARE CLASS///////////////
class square{
protected:
	//member data - colour of square, what piece is on square
	std::string m_sq_colour;
	std::shared_ptr<piece> m_on_square;
	
public:
	//Contructors
	square(){ m_sq_colour = "White";}
	square(std::string sq_colour, std::shared_ptr<piece> on_square){ m_sq_colour = sq_colour, m_on_square = on_square; }
	~square(){}
	//methods
	//Get and Set colour of square
	std::string GetColour() const { return m_sq_colour; }
	void SetColour(const std::string& sq_colour){ m_sq_colour = sq_colour; }
	//Get and Set Piece + Get Piece member data
	std::string GetPieceColour() const { return m_on_square->GetColour(); }
	std::string PieceName() const { return m_on_square->GetName(); }
	std::shared_ptr<piece> Piece() const { return m_on_square; }
	void SetPiece(std::shared_ptr<piece> on_square){ m_on_square = on_square; }
	//Is square empty or occupied
	bool isempty() const { return (m_on_square == nullptr) ; }
	//Printing methods for output to U/I
	void PrintBorderRow() const;
	void PrintSecondRow() const;
	void PrintThirdRow() const;
	//Move assignment for moving pieces (but not square colour)
	square &operator=(square&& moved){
		//move a piece from one square to another
		//don't want to move square colour but do want to move piece
		m_on_square.reset();
		m_on_square = moved.m_on_square;
		moved.m_on_square.reset();
		moved.m_on_square = nullptr;
		return (*this);
	}
};
