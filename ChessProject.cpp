//// OOP Final Project - Board Game: Chess //// 
// Author: Thomas Standen, start: 07/04/19, end: 13/05/19 //
// This is a C++ project for a two-player game of Chess //
// Its purpose is to demonstrate effective use of Object-oriented programming for PHYS30762 
// 50% of the marks are for basic functionality and class demonstration
// 50% of the marks are for advanced features and functionality such as: 
// smart pointers, exceptions, Lambda funcitons, Templates, namespaces Static data etc
// Key Concepts are:
// Encapsulation (storing data/privacy)
// Inheritance (Derived classes/ Abstract base classes)
// Polymorphism (One structure, multiple methods) 
// Class and Function Templates 
// Organisation and good practice
//This is the source file in which the U/I is developed and where the program is run// 

#include "square.h"
#include "board.h"
#include "piece.h"
#include "player.h"
#include "Game.h"
#include "ChessGame.h"
#include <iostream>


using namespace std;

int main(){
	cout << "********** TOM STANDEN'S C++ OBJECT ORIENTED PROGRAMMING PROJECT: A TWO PLAYER CHESS GAME " << endl;
	cout << "Before the game begins, please enter some information about the two players" << endl;
	game Game{ game() };
	string p1name, p1colour, p2name, p2colour;
	string ans;
	string movefrom, moveto;
	do{
		cout << "Please enter the name of the first player: " << endl;
		getline(cin, p1name);
		cout << "Please enter the colour that " << p1name << " will be playing as ('W' for white or 'B' for black)" << endl;
		getline(cin, p1colour);
		while (!inputcheck::good_colour(p1colour)){
			cout << "Sorry, please enter either White(W) or Black(B)" << endl;
			getline(cin, p1colour);
		}
		((p1colour == "White") ? p2colour = "Black" : p2colour = "White");
		cout << "Great! Now, could you please enter the name of the second player, who will be playing as " << p2colour << endl;
		getline(cin, p2name);
		if (p1name == p2name){ //add "Black" and "White" to the player names if they players have same name 
			cout << "As you share the same name, I'll use the piece colour to distinguish between the players" << endl;
			cout << "E.g Tom --> Tom White" << endl;
			p1name = p1name + " " + p1colour;
			p2name = p2name + " " + p2colour;
		}
		cout << "Player 1: Name - " << p1name << ", Colour - " << p1colour << "." << endl;
		cout << "Player 2: Name - " << p2name << ", Colour - " << p2colour << "." << endl;
		cout << "If the above information is correct, you are ready to begin the game!" << endl;
		cout << "ENTER: Yes(Y) to begin the game, Repeat(R) to repeat the player information or Exit(X) to quit the program" << endl;
		getline(cin, ans);
		while (!inputcheck::repeat_info(ans)){
			cout << "Sorry, please enter either Yes(Y), Repeat(R) or Exit(X)" << endl;
			getline(cin, ans);
		}
		if (ans == "Yes"){ //instantiate the two players
			player Player1(p1name, p1colour), Player2(p2name, p2colour);
			((p1colour == "White") ? Game.SetTurn(make_shared<player>(Player1)):
				Game.SetTurn(make_shared<player>(Player2)));
				Game.AddPlayer1(Player1);
				Game.AddPlayer2(Player2);	
		}
		if (ans == "Exit"){ exit(0); }

	} while (ans == "Repeat");

	board Board{ board() };
	Board.print_board();
	cout << endl;
	shared_ptr<player> turn = Game.Turn();
	cout << "It is " << turn->GetName()<< "'s turn" << endl;
	bool good_move{ false };
	//do while for if the move has been requested successfully
	do{
		cout << "Please choose a piece or pawn to move by entering the Letter:Number code displayed on the side of the board" << endl;
		getline(cin, movefrom);
		while (!inputcheck::good_code(movefrom)){
			cout << "Sorry, please make sure that you enter a valid square code, [A-H:1-8]" << endl;
			cout << "Piece to move: ";
			getline(cin, movefrom);
		}
		pair<int, int> movefrom_pair = inputcheck::decode(movefrom);
		//check that the player has selected a square with a piece and that it belongs to them
		while (!(turn->MyPiece(Board(movefrom_pair.first, movefrom_pair.second)))){
			cout << "There is no " << turn->GetColour() << " piece that you can move at " << movefrom << endl;
			cout << "Please choose another square" << endl;
			getline(cin, movefrom);
			while (!inputcheck::good_code(movefrom)){
				cout << "Sorry, please make sure that you enter a valid square code, [A-H:1-8]" << endl;
				cout << "Piece to move: ";
				getline(cin, movefrom);
			}
			movefrom_pair = inputcheck::decode(movefrom);
		}
		cout << movefrom_pair.first << movefrom_pair.second << endl;
		cout << "Please choose a square to move to by entering its Letter:Number code" << endl;
		getline(cin, moveto);
		while (!inputcheck::good_code(moveto)){
			cout << "Sorry, please make sure that you enter a valid square code, [A-H:1-8]" << endl;
			cout << "Square to move to: ";
			getline(cin, moveto);
		}
		pair<int, int> moveto_pair = inputcheck::decode(moveto);
		cout << moveto_pair.first << moveto_pair.second << endl;
		//save a pointer to the piece we are trying to move
		std::shared_ptr<piece> moving_piece;
		moving_piece = Board(movefrom_pair.first, movefrom_pair.second).Piece();
		std::string moving_name = moving_piece->GetName();
		//try to get the possible moves, if they aren't any then throw error
		set<pair<int, int>> move_set = moving_piece->moves(Board, movefrom_pair.first, movefrom_pair.second);
		
		for (auto set_it = move_set.begin(); set_it != move_set.end(); set_it++){
			std::string possible_mv = inputcheck::recode((*set_it).first, (*set_it).second);
			cout << possible_mv << endl;
		}

		stringstream ss;
		ss << movefrom << "->" << moveto;
		std::string complete_move{ ss.str() };


		//if the deisred move is in move_set then proceed with moving piece
		//if not start the process of asking for move again
		if (move_set.find(moveto_pair) == move_set.end()){
			cout << "The requested move: " << complete_move << " could not be executed." << endl;
			if (move_set.empty()){
				cout << "Sorry, the " << moving_name << " at " << movefrom << " has no available moves" << endl;
			}
			else{
				cout << "The available moves for the " << moving_name << " at " << movefrom << " are:" << endl;
				for (auto set_it = move_set.begin(); set_it != move_set.end(); set_it++){
					std::string possible_mv = inputcheck::recode((*set_it).first, (*set_it).second);
					cout << possible_mv << endl;
				}
			}
		}
		else{
			cout << "Yes that move can be made" << endl;
			turn->AddMove(complete_move);
			good_move = true;
		}
	
	} while (!good_move);


	/*unique_ptr<string[]> AtoH(new string[board_cols]);
	AtoH[0] = "A"; AtoH[1] = "B"; AtoH[2] = "C"; AtoH[3] = "D";
	AtoH[4] = "E"; AtoH[5] = "F"; AtoH[6] = "G"; AtoH[7] = "H";

	//"B", "C", "D", "E", "F", "G", "H"
	//vector<string> AtoH;
	//AtoH.push_back("A");
	*/
	return 0;
}





/*
//might have to do this in its own c++ file so that I can test the output frequently
void board::m_print_board() const {
//Create a top and bottom border of hyphens

"        ||        ||        ||        ||"
"        ||   A    ||   B    ||   C    ||"
"________||________||________||________||_____";
"        |##########          ########## ";
"   8    |## Rook ##  Knight  # Bishop # ";
"   	 |### Bk ###    Bl    ### Wh ### ";
"________|##########          ##########";
"        |          ##########           ";;
"	7  	 |   Pawn   ## Pawnn##   Pawn    ";
"	   	 |    Wh    ### Wh ###    Wh    ";
"________|          ##########          ";
"        |##########          ########## ";
"   6    |##########          ##########       ";
"        |##########          ########## ";
"________|##########          ##########";
"______________________________________
"        ||
"        ||   A
"        ||
}*/
