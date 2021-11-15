//MPHYS OOP chess project - Game manager class
//Class that sets up the game and holds the active player and board objects
//	also keeps track of turn and the active move

#include "piece.h"

class game {
protected:
	//Member data
	//game and turn counters
	int m_game_counter;
	int m_turn_counter;
	//plyer objects and pointers to them for turn
	player m_player1, m_player2;
	std::shared_ptr<player> m_turn;
	std::shared_ptr<player> m_not_turn;
	//data storing the active move
	std::pair<int, int> m_moveto, m_movefrom;
	//board data
	board m_current_board;
	board m_last_board;

public:
	//Constructors
	game(){ m_game_counter = 1, m_turn_counter = 1, m_current_board = board(), m_last_board = board(); }
	~game(){}
	//Methods
	//Get + Add turn and game 

	int GameNumber() const { return m_game_counter; }
	int TurnNumber() const { return m_turn_counter; }
	void AddTurn() { m_turn_counter += 1; }
	void AddGame() { m_game_counter += 1; }

	//Get + Add players

	void AddPlayer1(player p1) { m_player1 = p1; }
	void AddPlayer2(player p2) { m_player2 = p2; }
	player Player1() { return m_player1; }
	player Player2() { return m_player2; }

	//Set + Get where the moving piece is: Moving From
	std::pair<int, int> MoveFrom(){ return m_movefrom; }
	void SetMoveFrom(std::pair<int, int> movefrompair){ m_movefrom = movefrompair; }
	//Set + Get where the moving piece is: Moving From
	std::pair<int, int> MoveTo(){ return m_moveto; }
	void SetMoveTo(std::pair<int, int> movetopair){ m_moveto = movetopair; }
	//Get + Set Turn
	std::shared_ptr<player> Turn() const { return m_turn; }
	std::shared_ptr<player> NotTurn() const { return m_not_turn; }
	void ChangeTurn(std::shared_ptr<player> currentturn, std::shared_ptr<player> currentnotturn);
	void SetTurn(std::shared_ptr<player> turn_ptr, std::shared_ptr<player> not_turnptr);
	//Get + Set Board data
	board GetBoard() const { return m_current_board; }
	board LastBoard() const { return m_last_board; }
	void SetBoard(board& b){ m_current_board = b; }
	void SetLastBoard(board& b){ m_last_board = b; }
};