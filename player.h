//MPhys OOP Chess project: player class

#include "piece.h"
#include <string>
#include <vector>
#include <map>
class player {
protected:
	std::string m_player_name;
	std::string m_player_colour;
	std::vector<std::string> m_past_moves;
	bool m_in_check;
	std::pair<int, int> m_king_pos;
	std::vector<std::pair<int, int>> m_piece_positions;
public: 
	player(){ m_player_name = "Player1", m_player_colour = "White"; }
	player(std::string name, std::string colour);
	~player(){};
	std::string GetName() const { return m_player_name; }
	std::string GetColour() const { return m_player_colour; }
	void MoveHistory() const ;
	void AddMove(std::string move){ m_past_moves.push_back(move); }
	void SetColour(std::string colour){ m_player_colour = colour; }
	bool MyPiece(const square& sq);
	const bool &operator==(const player& p){ 
		return (m_player_colour == p.m_player_colour);
	}
	std::pair<int, int> KingPos(){ return m_king_pos; }
	std::vector<std::pair<int, int>> AllPos(){ return m_piece_positions; }
};