//MPhys OOP Chess project: player class
//Player class is used for storing player personal information
// and for storing important in-game information such as:
//	is the player in check, and where its king is currently positioned

#include "piece.h"
#include <string>
#include <vector>
#include <list>

class player {
protected:
	//Member data
	//personal info
	std::string m_player_name;
	std::string m_player_colour;
	//game info
	bool m_in_check;
	std::pair<int, int> m_king_pos;
	std::list<std::pair<int, int>> m_piece_positions;
	std::shared_ptr<piece> m_promotion;
	//advanced feature
	std::vector<std::string> m_past_moves;
public:
	//Methods
	//constructors + destructor
	player(){ m_player_name = "Player1", m_player_colour = "White", m_in_check = false; }
	player(std::string name, std::string colour);
	~player(){};
	//Get + Set personal info
	std::string GetName() const { return m_player_name; }
	std::string GetColour() const { return m_player_colour; }
	void SetColour(std::string colour){ m_player_colour = colour; }
	//Get + Set Check 
	void SetCheck(bool check){ m_in_check = check; }
	bool GetCheck(){ return m_in_check; }
	//Get + Set pawn promotion choice
	std::shared_ptr<piece> GetPromotion() const { return m_promotion; }
	void SetPromotion(std::shared_ptr<piece> upgrade) { m_promotion = upgrade; }
	//Get + Update + Remove piece positions 
	std::pair<int, int> KingPos(){ return m_king_pos; }
	std::list<std::pair<int, int>> AllPos(){ return m_piece_positions; }
	void UpdatePos(std::pair<int, int> newpos, std::pair<int, int> oldpos);
	void UpdateKingPos(std::pair<int, int> newpos){ m_king_pos = newpos; }
	void RemovePiece(std::pair<int, int> pos){ m_piece_positions.remove(pos); }
	//Method for checking the player selects one of their pieces to move
	//defined in ChessGame.cpp
	bool MyPiece(const square& sq);
	//overload of == operator for comparing two player objects
	//const bool &operator==(const player& p){
		//return (m_player_colour == p.GetColour());
	//}

	//advanced move history feature
	void MoveHistory() const;
	void AddMove(std::string move){ m_past_moves.push_back(move); }
};