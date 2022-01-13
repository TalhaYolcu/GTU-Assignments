#ifndef MYHEADERABSTRACT
#define MYHEADERABSTRACT

#include <iostream>
using namespace std;

namespace Talha_Abstract_Hex {
	enum symbol {d='.',u1='x',u2='o',w1='X',w2='O'};		//enum
	class Cell;
	
	class AbstractHex {
		friend class Cell;
		public:
			AbstractHex(int size,int user);			//CONSTRUCTORS		
			AbstractHex(int size);			
			AbstractHex();						//no argument constructor

			bool get_no_arg_constructor()const;			//IF NO ARGUMENT CONSTRUCTER IS CALLED?								
			void set_move(int move1);						//ensures the first move is going to done by x's
			int get_move()const;							//getter		
			int get_size()const;							//getter size
			void set_size(int size1);						//set the given size
			void set_user(int user1);						//set the user mode
			int get_user()const;							//get the user mode
			void set_marked_cell(int marked1);	//SETTER AND GETTERS THE HOW MANY MARKED CELL IN THE CURRENT GAME
			int get_marked_cell()const;				
			int get_y_for_ai()const;						//ai uses the move that made my user
			int get_x_for_ai()const;
			void set_y_for_ai(int yai);				
			void set_x_for_ai(int xai);
			void set_win(int win);		//who is winner?
			int get_win();				//getter for winner
			void set_user_counter(int cnt);			//SETTER AND GETTER FOR HOW MANY MOVE IS MADE
			int get_user_counter();

			void correct(bool arr[6],int &direction) const;					//makes correction for the control array
			int check_control_array(symbol ** &control,int xval,int yval,char p) const;			//checks the control array if we have go there before
			void setSize(int v1,int v2);			//needed setSize function
			bool isEnd();						//needed isEnd function
			int numberOfMoves();					//number of the moves have been made
			void fill_the_empty_board();		//fill the empty board with dots
			void fill_the_empty_board(symbol** &control);			//fill the given board with dots
			void print();				//neede print function
			bool operator==(AbstractHex &other);				//needed operator=overloading
			int check_validity(char l,int num);					//CHECKS THE VALIDITY OF THE MOVE 
			void reset();			//needed reset function
			Cell play();					//COMPUTER move(single step)
			void play(Cell &temp);			//USER     move(single step)
			Cell show(int xval,int yval);					//makes the ai's move
			bool check_validity_2(int xval,int yval);		//checks the validity of the ai's move
			Cell situation6(int &xval,int &yval);				//DIFFERENT SITUATIONS FOR AI'S MOVE	//DETAILED IN README.TXT
			Cell situation1();
			Cell situation2();
			Cell situation3();
			Cell situation4();					
			Cell situation5();
			Cell situation6_2();
			Cell situation7(int xval,int yval);
			Cell situation8();
			Cell situation9();
			int is_winner(int x,int y,int direction,symbol ** &control,char p);			//IS there any winner
			int situation(int &xval,int &yval,int &direction,bool arr[7],symbol ** &control,char p);	//checker for user move winner
			int readFromFile(string &input2);
			Cell& lastMove();

			friend bool* globalfun(AbstractHex* ptr3[5],bool* &x,int num);		//needed global function
			
			//VIRTUAL FUNCTIONS
			virtual void playGame()=0;			
			virtual int writeToFile(string &filename)=0;							
			virtual Cell& operator()(int x,int y)=0;
			virtual int ready_to_play()=0;											//ASKING LOAD-SAVE OR MOVE	
			virtual ~AbstractHex();		

		protected:
			int board_size;	//SIZE OF THE BOARD, THERE IS NO LIMIT,LARGER THAN 5
			int user;		//USERVSUSER OR USERVSCOMPUTER
			int move;		//WHO IS GONNA MAKE MOVE
			bool no_arg_constructor;		//is no argument constructer called?
			int winner;						//who is winner
			int xforai;						//ai takes previous move that made by user
			int yforai;
			int markedcell;					//how many marked cell
			int usercounter;				//how many move is made
			bool is_reset=false;
			int x;
			int y;
	};
	class Cell {

		public:
		friend class HexVector;
		friend class AbstractHex;
		friend class HexArray1D;
		template<template<typename...>class T>
		friend class HexAdapter;
			Cell();
			void set_x(int xval);				//setters and getters for cell x - y - symbol
			int get_x()const;
			void set_y(int yval);
			int get_y()const;
			symbol get_symbol()const;
			void set_symbol(symbol sym);
			int y;					//holds the x , y and symbol of the cell
			int x;
			symbol s;					//enum
	};		
	//EXCEPTIONS
	class outofindex : public runtime_error {
		public:
		outofindex();
	};	
	class nolastmove : public runtime_error {
	public:
		nolastmove();
	};	
	class file_error: public runtime_error {
	public:
		file_error();
	};
	class wrong_input: public runtime_error {
		public :
		wrong_input();
	};	
}
#endif