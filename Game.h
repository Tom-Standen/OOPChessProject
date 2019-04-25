//MPHYS OOP chess project - Game manager class
//Class that sets up the game and gets the player information
//It keeps track of who's turn it is and previous win stats

#include "piece.h"

class game {
protected:
	int m_game_counter;
	int m_turn_counter;
	player m_player1, m_player2;
	std::shared_ptr<player> m_turn;
	std::pair<int, int> m_moveto, m_movefrom;

public:
	//Constructors
	game(){ m_game_counter = 1, m_turn_counter = 1; }
	~game(){}
	//Methods
	int GameNumber() const { return m_game_counter; }
	int TurnNumber() const { return m_turn_counter; }
	void AddTurn() { m_turn_counter += 1; }
	void AddGame() { m_game_counter += 1; }
	void AddPlayer1(player p1) { m_player1 = p1; }
	void AddPlayer2(player p2) { m_player2 = p2; }
	player Player1() { return m_player1; }
	player Player2() { return m_player2; }
	void SetTurn(std::shared_ptr<player> turn_ptr){ m_turn = turn_ptr; }
	void SetMoveFrom(std::pair<int, int> movefrompair){ m_movefrom = movefrompair; }
	std::pair<int,int> MoveFrom(){ return m_movefrom; }
	void SetMoveTo(std::pair<int, int> movetopair){ m_moveto = movetopair; }
	std::pair<int, int> MoveTo(){ return m_moveto; }
	std::shared_ptr<player> Turn() const { return m_turn; }
	//std::string TurnColour() const { return m_turn->GetColour(); }
};