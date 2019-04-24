//// OOP Final Project - Board Game: Chess //// 
// Author: Thomas Standen, start: 07/04/19, end: 13/05/19 //
// This is the header file for the chess project 
//It contains the Board and Player class definitions and function declarations

#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>


//constant dimensions of the chess board
const int board_rows{ 8 };
const int board_cols{ 8 };
const int RowsInRow{ 4 };

//Create a set that covnerts Letter codes into integer values and back
//std::unordered_map<std::string, int> code;
//std::unordered_map<int, std::string> decode;


//enumerate the squares on the board with standard A1 - H8 notation
/*enum code{
	A1 = 0, B1, C1, D1, E1, F1, G1, H1, A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3, A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5, A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7, A8, B8, C8, D8, E8, F8, G8, H8

};*/
//funcitons that check inputs
namespace inputcheck{
	bool good_colour(std::string&);
	bool repeat_info(std::string&);
	bool in_boardrange(int, int);
	bool good_code(std::string);
	std::pair<int, int> decode(const std::string&);
	std::string recode(int, int);
}
namespace movecheck{
}
