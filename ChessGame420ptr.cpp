//// OOP Final Project - Board Game: Chess //// 
// Author: Thomas Standen, start: 07/04/19, end: 13/05/19 //
//This the implementation file where all non-template functions for the project are defined
#include "ChessGame.h"

////BOARD METHOD DEFINITIONS////
//constructors
//board::board() { m_init(); }
//function to initialise the board 
void board::init(){
	//set the shape of the board, and initialise all values to be blank white squares
	m_square_2Dvector.resize(board_rows, std::vector<square>(board_cols, square()));
	//Set white pawns on second row
	for (int col = 0; col < board_cols; col++){
		((col % 2 == 0) ? //if col == even: White square, if not : Black square
			m_square_2Dvector[1][col] = square("White", std::make_shared<pawn>("White")) :
			m_square_2Dvector[1][col] = square("Black", std::make_shared<pawn>("White")));
	}
	//Set black pawns on second last row
	for (int col = 0; col < board_cols; col++){
		((col % 2 == 0) ? //if col == even: Black square, if not : White square
			m_square_2Dvector[6][col] = square("Black", std::make_shared<pawn>("Black")) :
			m_square_2Dvector[6][col] = square("White", std::make_shared<pawn>("Black")));
	}
	//Set white pieces on first row 
	m_square_2Dvector[0][0] = square("Black", std::make_shared<rook>("White"));
	m_square_2Dvector[0][1] = square("White", std::make_shared<knight>("White"));
	m_square_2Dvector[0][2] = square("Black", std::make_shared<bishop>("White"));
	m_square_2Dvector[0][3] = square("White", std::make_shared<queen>("White"));
	m_square_2Dvector[0][4] = square("Black", std::make_shared<king>("White"));
	m_square_2Dvector[0][5] = square("White", std::make_shared<bishop>("White"));
	m_square_2Dvector[0][6] = square("Black", std::make_shared<knight>("White"));
	m_square_2Dvector[0][7] = square("White", std::make_shared<rook>("White"));
	//Setet black pieces on last row
	m_square_2Dvector[7][0] = square("White", std::make_shared<rook>("White"));
	m_square_2Dvector[7][1] = square("Black", std::make_shared<knight>("Black"));
	m_square_2Dvector[7][2] = square("White", std::make_shared<bishop>("Black"));
	m_square_2Dvector[7][3] = square("Black", std::make_shared<queen>("Black"));
	m_square_2Dvector[7][4] = square("White", std::make_shared<king>("Black"));
	m_square_2Dvector[7][5] = square("Black", std::make_shared<bishop>("Black"));
	m_square_2Dvector[7][6] = square("White", std::make_shared<knight>("Black"));
	m_square_2Dvector[7][7] = square("Black", std::make_shared<rook>("Black"));
	//Set the colour of the squares in middle four rows
	bool black = true;
	for (int row{ 2 }; row < 6; row++){
		//Third row (row==2) starts with a black square
		((row % 2 == 0) ? black = true : black = false);
		for (int col{ 0 }; col < board_cols; col++){
			if (black == true){
				m_square_2Dvector[row][col].SetColour("Black");
				black = false;
			}
			else{
				m_square_2Dvector[row][col].SetColour("White");
				black = true;
			}
		}
	}
}
//function to print out the header piece of the board with letter codes
namespace headerandfooter{
	void board_header(){
		using namespace std;
		//create an array containing the letter codes for the middle row
		unique_ptr<string[]> AtoH(new string[board_cols]);
		AtoH[0] = "A"; AtoH[1] = "B"; AtoH[2] = "C"; AtoH[3] = "D";
		AtoH[4] = "E"; AtoH[5] = "F"; AtoH[6] = "G"; AtoH[7] = "H";
		//base_pieces make the top and bottom row
		string header_top_piece = "        ||";
		string header_bot_piece = "________||";

		//Top row of header
		for (int column_it = 0; column_it < board_cols + 1; column_it++){
			cout << header_top_piece;
			//if its the first column print extra | for edge of board
			if (column_it == 0){ std::cout << "|"; }
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols){ std::cout << "        |"; }
			 
		}
		cout << endl;
		//Middle row of header 
		cout << header_top_piece << "|"; //first column same as above
		for (int column_it = 0; column_it < board_cols; column_it++){
			cout << "   " << AtoH[column_it] << "    ||";
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols - 1){ std::cout << "        |"; }

		}
		cout << endl;
		//Bottom row of header
		for (int column_it = 0; column_it < board_cols + 1; column_it++){
			cout << header_bot_piece;
			//if its the first column print extra | for edge of board
			if (column_it == 0){ std::cout << "|"; }
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols){ std::cout << "________|"; }
		}
		cout << endl;
	}
	void board_footer(){
		//same array as above for printing out letters
		std::unique_ptr<std::string[]> AtoH(new std::string[board_cols]);
		AtoH[0] = "A"; AtoH[1] = "B"; AtoH[2] = "C"; AtoH[3] = "D";
		AtoH[4] = "E"; AtoH[5] = "F"; AtoH[6] = "G"; AtoH[7] = "H";
		std::string footer_break_piece = "__________";
		std::string footer_top_piece = "        ||";
		std::string footer_bot_piece = "________||";
		//draw a line between board and footer
		std::cout << "________||";
		for (int column_it = 0; column_it < board_cols; column_it++){
			std::cout << footer_break_piece;
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols -1){ std::cout << "|________|"; }
		}
		std::cout << std::endl;
		//first row of footer
		for (int column_it = 0; column_it < board_cols + 1; column_it++){
			std::cout << footer_top_piece;
			//if its the first column print extra | for edge of board
			if (column_it == 0){ std::cout << "|"; }
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols){ std::cout << "        |"; }
		}
		std::cout << std::endl;
		//middle row of footer 
		std::cout << footer_top_piece << "|"; //first column same as above
		for (int column_it = 0; column_it < board_cols; column_it++){
			std::cout << "   " << AtoH[column_it] << "    ||";
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols -1){ std::cout << "        |"; }
		}
		std::cout << std::endl;
		//Bottom row of footer
		for (int column_it = 0; column_it < board_cols + 1; column_it++){
			std::cout << footer_bot_piece;
			//if its the first column print extra | for edge of board
			if (column_it == 0){ std::cout << "|"; }
			//if its on the last column print extra tile for edge of the board
			if (column_it == board_cols){ std::cout << "________|"; }
		}
		std::cout << std::endl;
	}
		

	}

void board::print_checkerboard() const{
	//Each row takes up 4 rows on the console
	const int RowsInRow{ 4 };
	//create the side border to the checkerboard
	std::string left_std_piece = "        ||";
	std::string left_bot_piece = "________||";
	std::string rt_std_piece = "|        |";
	std::string rt_bot_piece = "|________|";
	for (int i{ board_rows }; i > 0; i--){
		//count down on rows so the bottom left corner of the board is [0][0]
		for (int k{ 0 }; k < RowsInRow; k++){
			//loop over the 4 rows that make up each row
			//print side left border piece
			if (k == 0 || k == 2){ std::cout << left_std_piece; }
			if (k == 1){ std::cout << "   " << i  << "    ||"; }
			if (k == 3){ std::cout << left_bot_piece; }
			//print the squares
			for (int j{ 0 }; j < board_cols; j++){
				if (k == 0 || k == 3){
					m_square_2Dvector[i-1][j].PrintBorderRow();
				}
				if (k == 1){ m_square_2Dvector[i-1][j].PrintSecondRow(); }
				if (k == 2){ m_square_2Dvector[i-1][j].PrintThirdRow(); }
			}
			//print the right border piece
			if (k == 0 || k == 2){ std::cout << rt_std_piece; }
			if (k == 1){ std::cout << "|   " << i << "    |"; }
			if (k == 3){ std::cout << rt_bot_piece; }
			std::cout << std::endl;
		}
	}
}
void board::print_board() const {
	using namespace std;
	//function to print the board
	headerandfooter::board_header();
	print_checkerboard();
	headerandfooter::board_footer();

}

//////////////END OF BOARD METHODS///////////////////

/////////////SQUARE METHOD DEFINITIONS///////////////

////MOVE/COPY Assingments (C-TORS)////
/*
square &square::operator=(square& copy){
	//deep copy one square to another
	//need to block self assingment
	if (&copy == this) { return (*this); }
	//copy data across
	m_sq_colour = copy.m_sq_colour;
	(*m_on_square) = (*copy.m_on_square);
	return (*this);
}
square &square::operator=(square&& moved){
	//move a piece from one square to another
	//don't want to move square colour but do want to move piece
	m_on_square = moved.m_on_square;
	moved.m_on_square = std::make_shared<piece>(nullptr);
	return (*this);
}
*/
//using namespace std;
void square::PrintBorderRow() const {
	using namespace std;
	//depending on square colour print 10 spaces or hashes
	((m_sq_colour == "White") ? cout << "          " : cout << "##########");
}
void square::PrintSecondRow() const {
	using namespace std;
	//Get the name of the piece to be printed
	if (m_on_square == nullptr){
		if (m_sq_colour == "White"){ std::cout << "          "; }
		if (m_sq_colour == "Black"){ std::cout << "##########"; }
	}
	else{
		string name = m_on_square->GetName();
		//calculate number of characters to border name
		//Queen has 5 char so can't have an even border
		double border;
		((name == "Queen") ? border = 2 : border = (10 - name.length()) / 2);
		//For white squares: print 10 spaces if no piece
		//or print name in middle of row
		if (m_sq_colour == "White"){
			//print the row
			for (int i{ 0 }; i < border; i++){
				cout << " ";
			}
			cout << name;
			for (int i{ 0 }; i < border; i++){
				cout << " ";
			}
			if (name == "Queen"){ cout << " "; }
			//"Queen" is 5 characters so need extra character to complete square

		}
		else{//if black 
			//need one less border character
			// eg for pawn: ## Pawn ##, for bishop: # bishop # 
			border -= 1;
			//print out 10 hashes if no piece
			//if (m_empty){ std::cout << "##########"; }

			for (int i{ 0 }; i < border; i++){
				cout << "#";
			}
			cout << " " << name << " ";
			for (int i{ 0 }; i < border; i++){
				cout << "#";
			}
			//"Queen" is 5 characters so need extra character on end
			//because int arithmetic rounds 1.5 down to 1
			if (name == "Queen"){ cout << '#'; }

		}
	}
}
void square::PrintThirdRow() const {
	//output 4 spaces or hashes either side of 2 letter colour code
	std::string sq_colour = m_sq_colour;
	if (sq_colour == "White"){
		if (m_on_square == nullptr){ std::cout << "          "; }
		else{
			std::string piece_colour = m_on_square->GetColour();
			if (piece_colour == "White"){ std::cout << "    Wh    "; }
			if (piece_colour == "Black"){ std::cout << "    Bl    "; }
		}
	}
	if (sq_colour == "Black"){
		if (m_on_square == nullptr){ std::cout << "##########"; }
		else{
			std::string piece_colour = m_on_square->GetColour();
			if (piece_colour == "White"){ std::cout << "### Wh ###"; }
			if (piece_colour == "Black"){ std::cout << "### Bl ###"; }
		}
	}
}



int main(){
	using namespace std;
	//using namespace board_output;
	board Board{ board() };
	Board.print_board();
	


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
