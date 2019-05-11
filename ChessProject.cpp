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
	cout << "********** TOM STANDEN'S C++ OBJECT ORIENTED PROGRAMMING PROJECT: A TWO PLAYER CHESS GAME **************88" << endl << endl;
	cout << "Before the game begins, please enter some information about the two players" << endl;
	game Game{ game() };
	string p1name, p1colour, p2name, p2colour;
	string ans;
	string movefrom, moveto;
	bool gameover = { false };// good_move{ false };
	
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
		if (p1name == p2name){ //ask for second initial to distinguish the players if they have the same name 
			cout << "As you share the same name, Please enter a second initial distinguish between the players" << endl;
			cout << "E.g Tom --> Tom S" << endl;
			string initial;
			getline(cin, initial);
			p1name = p1name + " " + initial;
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
			((p1colour == "White") ? Game.SetTurn(make_shared<player>(Player1), make_shared<player>(Player2)) :
				Game.SetTurn(make_shared<player>(Player2), make_shared<player>(Player1)));
			Game.AddPlayer1(Player1);
			Game.AddPlayer2(Player2);
		}
		if (ans == "Exit"){ exit(0); }

	} while (ans == "Repeat");
	
	while (!gameover){
		//Instantiate board and acknowldge turn
		board Board{ Game.GetBoard() }, last_Board{ Game.LastBoard() };
		shared_ptr<player> turn{ Game.Turn() }, not_turn{ Game.NotTurn() };
		bool good_start{ false }, good_move{ false }, promotion, en_passant;
		//before turn starts assess whether player is check mate or in check
		list < pair<int, int>> defending_pos{ not_turn->AllPos() };
		list < pair<int, int>> attacking_pos{ turn->AllPos() };
		pair<int, int> attack_king_pos{ turn->KingPos() };
		pair<int, int> defend_king_pos{ not_turn->KingPos() };
		pair<int, int> checking_pos;
		set<pair<int, int>> all_defending_moves, all_attacking_moves, path_to_king, noking_attacking_moves;
		shared_ptr<piece> checking_piece;
		pair<set<pair<int, int>>, set<pair<int, int>>> kingmoves;
		int strike{ 0 }, mini_strike{ 0 };
		cout << "Turn number: " << Game.TurnNumber() << ". " << turn->GetName() << " to move" << endl;
		//Are you in check?
		if (turn->GetCheck()){
			//Work out the checking path and see if it can be blocked
			for (auto pos : defending_pos){
				shared_ptr<piece> this_piece{ Board(pos.first, pos.second).Piece() };
				pair<set<pair<int, int>>, set<pair<int, int>>> this_moves{ this_piece->moves(Board, last_Board, pos.first, pos.second, attack_king_pos) };
				all_defending_moves.insert(this_moves.first.begin(), this_moves.first.end());
				if ((this_moves.first).find(attack_king_pos) != this_moves.first.end()){
					checking_piece = this_piece;
					checking_pos = pos;
					path_to_king = this_moves.second;
					//the king position should not be included in path to king
					//this is because an attacking piece cannot move there to block path
					path_to_king.erase(attack_king_pos);
				}
			}
			//Work out the king's potential moves and all attacking piece moves
			kingmoves = (Board(attack_king_pos.first, attack_king_pos.second).Piece())
				->moves(Board, last_Board, attack_king_pos.first, attack_king_pos.second, attack_king_pos);
			for (auto pos : attacking_pos){
				shared_ptr<piece> this_piece{ Board(pos.first, pos.second).Piece() };
				pair<set<pair<int, int>>, set<pair<int, int>>> this_moves{ this_piece->moves(Board, last_Board, pos.first, pos.second, attack_king_pos) };
				all_attacking_moves.insert((this_moves.first).begin(), this_moves.first.end());
				if (this_piece->GetName() != "King"){
					// set of moves of pieces other than king for checking path blocking
					noking_attacking_moves.insert((this_moves.first).begin(), this_moves.first.end());
					
				}
			}
			
			//Can you get out of check? 3 strike system
			// OPTION 1: take checking piece
			if ((all_attacking_moves).find(checking_pos) == (all_attacking_moves).end()){
				//if checking piece can be taken by the king
				//second strike
				strike += 1;
				cout << "YOU CANNOT TAKE THE CHECKING PIECE" << endl;
			}
			else{
				cout << "you might be able to take the checking piece" << endl;
				//if you can take it 
				cout << "checking_pos: " << endl;
				cout << checking_pos.first << checking_pos.second << endl;
				cout << "noking_attacking_moves: " << endl;
				for (auto move : noking_attacking_moves){
					cout << move.first << move.second << endl;
				}
				
				//check that the piece isn't protected
				//if only the king can take it then could be in trouble
				if (noking_attacking_moves.find(checking_pos) == noking_attacking_moves.end()){
					cout << "got here" << endl;
					//if the checking_ppiece is protected then add a strike
					//need to revaluate the defending moves without the checking piece there 
					//then check whether the checking pos is in the new temp moves
					list < pair<int, int>> no_checking_piece_pos{ defending_pos };
					//cout << "got here 2" << endl;
					no_checking_piece_pos.remove(checking_pos);
					//cout << "here3" << endl;
					set<pair<int, int>> no_check_defending_moves;
					cout << "here4" << endl;

					board mate_check{ Board };
					mate_check(checking_pos.first, checking_pos.second) = move(mate_check(attack_king_pos.first, attack_king_pos.second));

					for (auto pos : no_checking_piece_pos){
						// cout << "here5" << endl;
						shared_ptr<piece> this_piece{ Board(pos.first, pos.second).Piece() };
						//cout << "here6" << endl;
						pair<set<pair<int, int>>, set<pair<int, int>>> this_moves{ this_piece->moves(mate_check, Board, pos.first, pos.second, attack_king_pos) };	
						no_check_defending_moves.insert(this_moves.first.begin(), this_moves.first.end());
					}
					cout << "no_check_defending_moves: " << endl;
					for (auto move : no_check_defending_moves){
						cout << move.first << move.second << endl;
					}
					if (no_check_defending_moves.find(checking_pos) != no_check_defending_moves.end()){
						//The checking piece is protected
						strike += 1;
						cout << "The checking piece is protected and no piece other than the king could feasibly take it. So it can't be taken" << endl;
					}	
				}
			}
			//OPTION 2: Block Path to king
			bool block = false;
			for (auto pos : path_to_king){
				//if any of the squares in the path to the king can be moved to then
				//check can be blocked
				if ((noking_attacking_moves).find(pos) != (noking_attacking_moves).end()){
					cout << "The square that can be blocked is " << inputcheck::recode(pos.first, pos.second) << endl;
					block = true;
				}
			}
			if (!block){
				cout << "YOU CANNOT BLOCK THE CHECKING PIECE'S PATH" << endl;
				strike += 1;
			}
			//if all first two strikes are hit must check all spaces the king can move to
			if (strike == 2){ //skip out of while loops and end game
				//do a final check of the availble moves that the king has. Move to them all and re-evaluate check
				//If none of them escape check then the game is mate.
				cout << "Your only option is to move your king out of check" << endl;
				kingmoves.first.erase(checking_pos);
				if ((kingmoves.first).empty()){
					cout << "Oh no! Your King cannot move... that's check mate!" << endl;
					cout << "In the words of TBS - 'How very unfortunate!'" << endl;
					good_move = true;
					gameover = true;
				}
				else{
					//need to check if the other king moves don't place it in check
					//set gameover to true and change if there are still moves to be made
					board mate_check{ Board };
					gameover = true; 
					for (auto pos : kingmoves.first){
						//move the king to its potential space
						cout << "King Move : " << pos.first << pos.second << endl;
						mate_check(pos.first, pos.second) = move(mate_check(attack_king_pos.first, attack_king_pos.second));
						set<pair<int, int>> MovedKing_defendmoves;
						/*list < pair<int, int>> MovedKing_attackpos{ attacking_pos };
						MovedKing_attackpos.remove(attack_king_pos)*/
						//re-evaluate attacking moves given the change in king space
						for (auto space : defending_pos){
							shared_ptr<piece> this_piece{ mate_check(space.first, space.second).Piece() };
							cout << this_piece->GetName();
							pair<set<pair<int, int>>, set<pair<int, int>>> this_moves{ this_piece->moves(mate_check, Board, space.first, space.second, attack_king_pos) };
							MovedKing_defendmoves.insert(this_moves.first.begin(), this_moves.first.end());
						}
						if (MovedKing_defendmoves.find(pos) == MovedKing_defendmoves.end()){
						//for each potential move of the king
						//check if that move is in the list available opposition moves (all_defending_moves)
						//if a move is not covered by the opposition the game is not over
						cout << "There are still moves the king can make so the game is not over!" << endl;
						gameover = false;
						break;
						}
					}
					if (gameover){
						cout << "Oh no! Your King cannot move... that's check mate!" << endl;
						cout << "In the words of TBS - 'How very unfortunate!'" << endl;
						good_move = true;
					}
				}
			}
		}
		while (!good_move){
			Board.print_board();
			cout << endl;
			promotion = false, en_passant = false;
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
				cout << "Please choose a square to move to by entering its Letter:Number code" << endl;
				getline(cin, moveto);
				while (!inputcheck::good_code(moveto)){
					cout << "Sorry, please make sure that you enter a valid square code, [A-H:1-8]" << endl;
					cout << "Square to move to: ";
					getline(cin, moveto);
				}
				pair<int, int> moveto_pair = inputcheck::decode(moveto);
				//save a pointer to the piece we are trying to move
				shared_ptr<piece> moving_piece;
				moving_piece = Board(movefrom_pair.first, movefrom_pair.second).Piece();
				string moving_name = moving_piece->GetName();
				//try to get the possible moves, if they aren't any then throw error
				pair<set<pair<int, int>>, set<pair<int, int>>> move_set = moving_piece->moves(Board, last_Board, movefrom_pair.first, movefrom_pair.second, attack_king_pos);
				
				stringstream ss;
				ss << movefrom << "->" << moveto;
				string complete_move{ ss.str() };

				//if the deisred move is in move_set then proceed with moving piece
				//if not start the process of asking for move again
				if ((move_set.first).find(moveto_pair) == (move_set.first).end()){
					cout << "The requested move: " << complete_move << " could not be executed." << endl;
					if ((move_set.first).empty()){
						cout << "Sorry, the " << moving_name << " at " << movefrom << " has no available moves" << endl;
					}
					else{
						cout << "The available moves for the " << moving_name << " at " << movefrom << " are:" << endl;
						for (auto set_it = (move_set.first).begin(); set_it != (move_set.first).end(); set_it++){
							string possible_mv = inputcheck::recode((*set_it).first, (*set_it).second);
							cout << possible_mv << endl;
						}
					}
				}
				else{
					cout << "That move seems legitimate" << endl;
					Game.SetMoveFrom(movefrom_pair);
					Game.SetMoveTo(moveto_pair);
					//turn->AddMove(complete_move)
					good_start = true;

					//find out the desired promotion
					if (moving_name == "Pawn" && (moveto_pair.first == 7 || moveto_pair.first == 0)){
						turn->SetPromotion(inputcheck::promotioncheck(turn->GetColour()));
						promotion = true;
					}
					//find out if its En passant
					//1) is it a pawn moving, 2) is the square empty
					if (moving_name == "Pawn" && Board(moveto_pair.first,moveto_pair.second).isempty()){
						//if so is it a diagonal move?
						if (movefrom_pair.second != moveto_pair.second){
							en_passant = true;
							cout << "EN PASSANT!" << endl;
						}
					}

				}

			} while (!good_start);

			//Copy a version of the board to a temporary board to update
			board temp_Board(Board);
			list < pair<int, int>> temp_attackpos{ attacking_pos }, temp_defendpos{ defending_pos };
			
			//SPECIAL BOARD UPDATE: CASTLING
			pair<int, int> castlefrom, castleto;
			bool castled{ false };
			//queenside white
			if (Game.MoveFrom() == make_pair(0, 4) && Game.MoveTo() == make_pair(0, 2)){
				temp_Board(0, 3) = move(temp_Board(0, 0));
				castlefrom = make_pair(0, 0);
				castleto = make_pair(0, 3);
				temp_attackpos.remove(castlefrom);
				temp_attackpos.push_back(castleto);
				castled = true;
			}
			//queenside black
			if (Game.MoveFrom() == make_pair(7, 4) && Game.MoveTo() == make_pair(7, 2)){
				temp_Board(7, 3) = move(temp_Board(7, 0));
				castlefrom = make_pair(7, 0);
				castleto = make_pair(7, 3);
				temp_attackpos.remove(castlefrom);
				temp_attackpos.push_back(castleto);
				castled = true;
			}
			//kingside white
			if (Game.MoveFrom() == make_pair(0, 4) && Game.MoveTo() == make_pair(0, 6)){
				temp_Board(0, 5) = move(temp_Board(0, 7));
				castlefrom = make_pair(0, 7);
				castleto = make_pair(0, 5);
				temp_attackpos.remove(castlefrom);
				temp_attackpos.push_back(castleto);
				castled = true;
			}
			//kingside black
			if (Game.MoveFrom() == make_pair(7, 4) && Game.MoveTo() == make_pair(7, 6)){
				temp_Board(7, 5) = move(temp_Board(7, 7));
				castlefrom = make_pair(7, 7);
				castleto = make_pair(7, 5);
				temp_attackpos.remove(castlefrom);
				temp_attackpos.push_back(castleto);
				castled = true;
			}
			//PAWN PROMOTION BOARD UPDATE
			//if the a "Pawn" is moving to the last row (7,#) then need to ask what piece you would like to ask for
			if (promotion){ 
				temp_Board(Game.MoveFrom().first, Game.MoveFrom().second).SetPiece(turn->GetPromotion());
			}
			//EN PASSANT BOARD UPDATE
			if (en_passant){
				//remove pawn that is in the same pre move row and post move column as the moving pawn
				temp_Board(Game.MoveFrom().first, Game.MoveTo().second).SetPiece(nullptr);
				temp_defendpos.remove(make_pair(Game.MoveFrom().first, Game.MoveTo().second));
			}


			//STANDARD BOARD UPDATE
			temp_Board((Game.MoveTo()).first, (Game.MoveTo()).second) = move(temp_Board((Game.MoveFrom()).first, (Game.MoveFrom()).second));
			
			//Now must assess whether the move has put the attacking player in check and therefore the move should be blocked
			cout << "Attacking king pos:" << inputcheck::recode(attack_king_pos.first, attack_king_pos.second) << endl;
			cout << "Game.MoveFrom()" << inputcheck::recode(Game.MoveFrom().first, Game.MoveFrom().second) << endl;
			
			temp_attackpos.remove(Game.MoveFrom());
			temp_attackpos.push_back(Game.MoveTo());
			temp_defendpos.remove(Game.MoveTo());
			pair<int, int> temp_king_pos{ attack_king_pos };
			//if the king has moved then update its temporary position variable
			if (attack_king_pos == Game.MoveFrom()){ temp_king_pos = Game.MoveTo(); }
			//clear the set of all_defending moves
			all_defending_moves.clear();
			cout << "Attacking king pos:" << inputcheck::recode(temp_king_pos.first, temp_king_pos.second) << endl;
			cout << "Defend king pos:" << inputcheck::recode(defend_king_pos.first, defend_king_pos.second) << endl;

			//FINAL CHECK: Make sure you haven't put yourself in check
			//check whether attacking king's position is in the set of enemy moves
			for (auto pos : temp_defendpos){
				cout << inputcheck::recode(pos.first, pos.second);
				shared_ptr<piece> this_piece{ temp_Board(pos.first, pos.second).Piece() };
				cout << this_piece->GetName() << " ";
				pair<set<pair<int, int>>, set<pair<int, int>>> this_moves{ this_piece->moves(temp_Board, Board, pos.first, pos.second, attack_king_pos) };
				all_defending_moves.insert((this_moves.first).begin(), (this_moves.first).end());
			}
			
			cout << endl;
			//IF none of enemy pieces can take king in next move
			//it is allowed
			if (all_defending_moves.find(temp_king_pos) == all_defending_moves.end()){
				good_move = true;
				//change turn, save last board, save new board, player out of check 
				Game.AddTurn();
				//mark the piece as moved so pawns can't double jump and castling can't occur
				shared_ptr<piece> moving_piece;
				moving_piece = Board(Game.MoveFrom().first, Game.MoveFrom().second).Piece();
				moving_piece->Moved();
				turn->SetCheck(false);
				Game.SetBoard(temp_Board);
				Game.SetLastBoard(Board);
				turn->UpdatePos(Game.MoveTo(), Game.MoveFrom());
				turn->UpdateKingPos(temp_king_pos);
				not_turn->RemovePiece(Game.MoveTo());
				//if castled then need to update the castle position as well
				if (castled){ turn->UpdatePos(castleto, castlefrom); }
				//if En Passant need to remove opponents pawn
				if (en_passant){ not_turn->RemovePiece(make_pair(Game.MoveFrom().first, Game.MoveTo().second)); }


				//also evaluate whether you have put the opponent in check
				//to do this
				//evaluate whether defendingkingpos is in all_attacking_moves
				//update all attacking moves
				for (auto pos : temp_attackpos){
					shared_ptr<piece> this_piece{ temp_Board(pos.first, pos.second).Piece() };
					pair<set<pair<int, int>>, set<pair<int, int>>> this_moves{ this_piece->moves(temp_Board, Board, pos.first, pos.second, attack_king_pos) };
					cout << inputcheck::recode(pos.first, pos.second);
					cout << this_piece->GetName() << " ";
					all_attacking_moves.insert((this_moves.first).begin(), (this_moves.first).end());
				}

				if (all_attacking_moves.find(defend_king_pos) != all_attacking_moves.end()){
					cout << "You have put the opponent in Check!" << endl;
					not_turn->SetCheck(true);
				}
				
				Game.ChangeTurn(turn, not_turn);
				cout << "################# END OF TURN #####################" << endl;

			}
			else{
				cout << " THE MOVE YOU CHOSE CANNOT BE EXECUTED AS IT PLACES YOU IN CHECK" << endl;
				cout << "TRY AGAIN" << endl;
			}
	
		}
	}

	return 0;
}
