#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<vector>
#include<sstream>

#ifndef MYHEADER3
#define MYHEADER3

using namespace std;

enum symbol {d='.',u1='x',u2='o',w1='X',w2='O'};

class Hex {
	private:
		class Cell {
			private:
				char y;
				int x;
				symbol s;
			public:
				Cell();
				void set_x();
				inline int get_x() const;
				void set_y();
				inline char get_y() const;
				inline symbol get_symbol() const;
				void set_symbol(symbol sym);
		};
		vector<vector< Cell> > hexCells;
		int board_size;	//SIZE OF THE BOARD, THERE IS NO LIMIT,LARGER THAN 5
		int user;		//USERVSUSER OR USERVSCOMPUTER
		int move;		//WHO IS GONNA MAKE MOVE
		bool no_arg_constructor;		//is no argument constructer called?
		int winner;						//who is winner
		int xforai;						//ai takes previous move that made by user
		int yforai;
		int markedcell;					//how many marked cell
		static vector<int> hold;		//holds the how many game in there
		static int howmanygame;			//how many game are there
		int whichgame;					//which game are we playing
	public:	
		Hex(int size,int user);			//CONSTRUCTORS
		Hex(int size);
		Hex();
		void print_the_board() const;										//displays current board
		void play();												//COMPUTER move(single step)
		void play(int xc,int yc);									//USER     move(single step)
		int is_winner(int x,int y,int direction,vector < vector < symbol > > control,char p);			//IS IT ENDED?
		int situation(int xval,int yval,int direction,bool arr[7],vector < vector < symbol > > control,char p);
				//DEPEND ON THE DIRECTIONS CHECKS THE NEIGHBOR CELLS
		int check_control_array(vector < vector < symbol > > control,int xval,int yval,char p) const;
				//CHECKS IF WE HAVE CHECKED BEFORE THIS CELL		
		void correct(bool arr[6],int direction) const;
				//MAKES A CORRECTION DEPEND ON THE EDGES OF THE BOARD					
		void playGame();						// ask board_size, user vs user or user vs computer
		bool compare(Hex& other) const; 			//It returns true is the first game has more marked cells for the user,otherwise it returns false. 
		void fill_the_empty_board();		//FILLS THE EMPTY BOARD TO GET READY TO PLAY
		void fill_the_empty_board(vector < vector < symbol > > control);		//MAKES CLEAN THE CONTROL VECTOR TO CHECK 
																				//WINNER PROPERLY NEXT TIME
		bool get_no_arg_constructor() const;						//WE HAVE CALLED THE CONSTRUCTER THAT TAKES NO ARGUMENTS
		int save_the_current_game(string input2) const;			//SAVES THE CURRENT GAME TO THE GIVEN FILE
		int load_a_game(string input2);						//LOADS THE GAME FROM GIVEN FILE
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
		void machine_s_move(int xval,int yval);			//ai's move
		void show(int xval,int yval);					//makes the ai's move
		bool check_validity_2(int xval,int yval) const;		//checks the validity of the ai's move
		void situation6(int xval,int yval);				//DIFFERENT SITUATIONS FOR AI'S MOVE	
		void situation1();
		void situation2();
		void situation3();
		void situation4();					
		void situation5();
		void situation6_2();
		void situation7(int xval,int yval);
		void situation8();
		void situation9();
		void set_marked_cell(int marked1);				//SETS THE HOW MANY MARKED CELL IN THE CURRENT GAÖE
		inline int get_marked_cell() const;							//GETS
		static int how_many_marked_cell(int game1) {	//RETURNS THE GIVEN INDEX'S MARKED CELL'S
			return hold[game1];
		}
		static int get_how_many_game() {				
			return howmanygame;
		}
		int get_which_game();
		void set_which_game(int game1);
};
#endif