//MPhys OOP Chess project: player class

#include "piece.h"
#include <string>
#include <vector>
class player {
protected:
	std::string m_player_name;
	std::string m_player_colour;
	std::vector<std::string> past_moves;
public: 
	player(){ m_player_name = "Player1", m_player_colour = "White"; }
	player(std::string name, std::string colour){
		m_player_colour = colour;
		m_player_name = name;
	}
	~player(){};
	std::string GetName() const { return m_player_name; }
	std::string GetColour() const { return m_player_colour; }
	void MoveHistory() const ;
	void AddMove(std::string move){ past_moves.push_back(move); }
	void SetColour(std::string colour){ m_player_colour = colour; }
	bool MyPiece(const square& sq);
};
