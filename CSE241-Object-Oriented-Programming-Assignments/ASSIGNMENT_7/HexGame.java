package yyolcu2018_1801042609;

import yyolcu2018_1801042609.Cell;

public interface HexGame {
	void fill_the_empty_board();
	void fill_the_empty_board(symbol[][] control);
	void play();
	int is_winner(int x,int y,int direction,symbol[][] control,char p);
	int situation(int xval,int yval,int direction,boolean[] arr,symbol[][] control,char p);
	int check_control_array(symbol[][] control,int xval,int yval,char p);	
	void correct(boolean[] arr,int direction);
					//LOADS THE GAME FROM GIVEN FILE
									//ASKING LOAD-SAVE OR MOVE
	boolean check_validity(int xval,int yval);					//CHECKS THE VALIDITY OF THE MOVE 
									//GETTER FOR MOVE
	int get_size();					//returns the current board size
	void set_size(int size1);				//sets the game size by given parameter				//sets the user mod pvp or pvc
	int get_y_for_ai();						//ai uses the move that made my user
	int get_x_for_ai();
	void set_y_for_ai(int yai);				
	void set_x_for_ai(int xai);
	void show(int xval,int yval);					//makes the ai's move

	boolean check_validity_2(int xval,int yval);		//checks the validity of the ai's move
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
	int get_numof_moves();
	void set_numofmoves(int x);
}