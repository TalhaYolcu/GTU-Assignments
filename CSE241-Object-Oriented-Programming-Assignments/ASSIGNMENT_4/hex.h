#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<sstream>
#include<cstdlib>

#ifndef MYHEADER4
#define MYHEADER4

using namespace std;

enum symbol {d='.',u1='x',u2='o',w1='X',w2='O'};		//enum

class Hex {
	public:
		class Cell {
			private:
				int y;					//holds the x , y and symbol of the cell
				int x;
				symbol s;
			public:
				Cell();
				void set_x(int xval);				//setters and getters for cell x - y - symbol
				inline int get_x() const;
				void set_y(int yval);
				inline int get_y() const;
				inline symbol get_symbol() const;
				void set_symbol(symbol sym);			
		};								//end of Cell Class
		Hex(int size,int user);			//CONSTRUCTORS		
		explicit Hex(int size);			//Conversion constructor
		Hex();							//no argument constructor
													//BIG THREE IS PROVIDED
		Hex(const Hex &other);						//COPY CONSTRUCTOR
		const Hex& operator=(const Hex &other);		//ASSIGNMENT OPERATOR
		~Hex();										//DESTRUCTOR

		friend ostream& operator<<(ostream& mys,const Hex &myo);	//stream insertion and extraction operator overloads
		bool operator==(Hex& other) const;							//compare 
		friend ofstream& operator<<(ofstream &mys,Hex &myo);
		friend ifstream& operator>>(ifstream &mys,Hex &myo);
		void playGame();						// ask board_size, user vs user or user vs computer
		static int get_how_many_game() {		//static function says how man game at the end of the game			
			return howmanygame;
		}		
	private:
		Cell ** hexCells;		//dynamic array board
		int board_size;	//SIZE OF THE BOARD, THERE IS NO LIMIT,LARGER THAN 5
		int user;		//USERVSUSER OR USERVSCOMPUTER
		int move;		//WHO IS GONNA MAKE MOVE
		bool no_arg_constructor;		//is no argument constructer called?
		int winner;						//who is winner
		int xforai;						//ai takes previous move that made by user
		int yforai;
		int markedcell;					//how many marked cell
		static int howmanygame;			//how many game are there
		Cell * usermoves;				//holds the moves ordered
		int usercounter;				//how many move is made
		int score;						//what is the score

		Hex& operator--();				//UNDO for player vs computer
		Hex operator--(int);			//UNDO for player vs player
		void fill_the_empty_board();		//FILLS THE EMPTY BOARD TO GET READY TO PLAY
		void fill_the_empty_board(symbol ** &control);		//MAKES CLEAN THE CONTROL VECTOR TO CHECK 
																				//WINNER PROPERLY NEXT TIME
		Cell play();					//COMPUTER move(single step)
		void play(Cell &temp);			//USER     move(single step)
		int is_winner(int x,int y,int direction,symbol ** &control,char p);			//IS IT ENDED?
		int situation(int &xval,int &yval,int &direction,bool arr[7],symbol ** &control,char p);
				//DEPEND ON THE DIRECTIONS CHECKS THE NEIGHBOR CELLS
		int check_control_array(symbol ** &control,int xval,int yval,char p) const;
				//CHECKS IF WE HAVE CHECKED BEFORE THIS CELL		
		void correct(bool arr[6],int &direction) const;
				//MAKES A CORRECTION DEPEND ON THE EDGES OF THE BOARD		
		bool get_no_arg_constructor() const;						//WE HAVE CALLED THE CONSTRUCTER THAT TAKES NO ARGUMENTS
		int save_the_current_game(string &input2);			//SAVES THE CURRENT GAME TO THE GIVEN FILE
		int load_a_game(string &input2);						//LOADS THE GAME FROM GIVEN FILE
		int ready_to_play();								//ASKING LOAD-SAVE OR MOVE
		int check_validity(char l,int num) const;					//CHECKS THE VALIDITY OF THE MOVE 
		inline int get_move() const;										//GETTER FOR MOVE
		void set_move(int move1);							//SETTER FOR MOVE
		inline int get_size() const;					//returns the current board size
		void set_size(int size1);				//sets the game size by given parameter
		void set_user(int user1);				//sets the user mod pvp or pvc
		inline int get_user() const;							//getter for user mod
		inline int get_y_for_ai() const;						//ai uses the move that made my user
		inline int get_x_for_ai() const;
		void set_y_for_ai(int yai);				
		void set_x_for_ai(int xai);
		Cell show(int xval,int yval);					//makes the ai's move
		bool check_validity_2(int xval,int yval) const;		//checks the validity of the ai's move
		Cell situation6(int &xval,int &yval);				//DIFFERENT SITUATIONS FOR AI'S MOVE	
		Cell situation1();
		Cell situation2();
		Cell situation3();
		Cell situation4();					
		Cell situation5();
		Cell situation6_2();
		Cell situation7(int xval,int yval);
		Cell situation8();
		Cell situation9();
		void set_marked_cell(int marked1);	//SETTER AND GETTERS THE HOW MANY MARKED CELL IN THE CURRENT GAME
		inline int get_marked_cell() const;	
		void set_user_counter(int cnt);			//SETTER AND GETTER FOR HOW MANY MOVE IS MADE
		inline int get_user_counter() const;
		Cell& get_user_moves() const;			//SETTER AND GETTER FOR EACH MOVE
		void set_user_moves(int y,int x);
		inline int get_score() const;			//SETTER AND GETTER FOR SCORE
		void set_score(int mymove);		
};
#endif