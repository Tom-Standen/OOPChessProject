//// OOP Final Project - Board Game: Chess //// 
// Author: Thomas Standen, start: 07/04/19, end: 13/05/19 //
// This is the header file for the chess project 
//It contains the Board and Player class definitions and function declarations

#pragma once
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include "piece.h"

class game;
class player;
class board;
class square;


//constant dimensions of the chess board
const int board_rows{ 8 };
const int board_cols{ 8 };
const int RowsInRow{ 4 };

//Namespace for functions that check inputs
namespace inputcheck{
	bool good_colour(std::string&);
	bool repeat_info(std::string&);
	bool in_boardrange(int, int);
	bool good_code(std::string);
	std::pair<int, int> decode(const std::string&);
	std::string recode(int, int);
	std::shared_ptr<piece> promotioncheck(std::string);
}
//Namespace for printing out board header and footer
namespace headerandfooter{
	void board_header();
	void board_footer();
}