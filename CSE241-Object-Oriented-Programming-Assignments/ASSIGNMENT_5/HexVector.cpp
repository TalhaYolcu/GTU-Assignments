#include "AbstractHex.h"
#include <iostream>
#include <vector>
#include<string>
#include<fstream>
#include<cmath>
#include<sstream>
#include<cstdlib>
#include "HexVector.h"

using namespace std;

namespace Talha_Abstract_Hex {
	HexVector::HexVector() :AbstractHex(){										//CONSTRUCTORS
		int i;
		hexCells.resize(get_size()*get_size());
		for(i=0;i<get_size();i++) {	
			hexCells[i].resize(get_size());
		}
		setSize(get_size(),get_size());					
	}
	HexVector::HexVector(int size,int user) :AbstractHex(size,user) {		
		int i;
		hexCells.resize(get_size()*get_size());
		for(i=0;i<get_size();i++) {	
			hexCells[i].resize(get_size());
		}				
		setSize(get_size(),get_size());		
}
	HexVector::HexVector(int size) :AbstractHex(size) {
		int i;
		hexCells.resize(get_size()*get_size());
		for(i=0;i<get_size();i++) {	
			hexCells[i].resize(get_size());
		}		
		setSize(get_size(),get_size());		
	}	
	void HexVector::playGame() { 						// ask board_size, user vs user or user vs computer
		int i;
		int temp;
		int temp2;
		int size2=0;		
		if(!get_no_arg_constructor()) {

		}
		else {
			while(1) {
				cout<<"ENTER THE BOARD SIZE (MIN 6)(EXAMPLE:FOR 8X8 type 8 8)\n";				
				try {
					cin>>temp;
					cin>>size2;					
					if(temp==size2 && temp>5) {
						if(temp==get_size()) {

						}
						else {
							set_size(temp);	
							hexCells.resize(get_size()*get_size());
							for(i=0;i<get_size();i++) {	
								hexCells[i].resize(get_size());
							}						
							setSize(temp,size2);
						}					

						while(true) {
							cout<<"PLEASE CHOOSE (1)if this a two player game or (2)user versus computer game:"<<endl;							
							try {
								cin>>temp2;
								if(temp2<=0 || temp2>2) {
									throw wrong_input();			
								}
								else {
									set_user(temp2);
									break;
								}								
							}
							catch(wrong_input &we) {
								cerr<<"ERROR OCCURED: "<<we.what()<<endl;
							}
						}
						break;
					}
					else {
						throw wrong_input();	
					}				
				}
				catch(wrong_input &we) {
					cerr<<"ERROR OCCURED: "<<we.what();
				}			
			}				
		}		
		print();
		set_move(1);							//MOVE HAS PLAYER1'S
		winner=ready_to_play();					//START TO TAKE MOVES		
	}						// ask board_size, user vs user or user vs computer
	int HexVector::writeToFile(string &input2) {				//LOAD A GAME FROM FILE
		char c;
		int xval;
		int yval;
		int tempsize;
		int tempuser;
		int tempmove;
		int mycnt=0;
		int incoming;	
		int i=0;
		int myx=0;
		int myy=0;
		int ret=-1;
		ifstream wr2;
		wr2.open(input2);

		if(!wr2.is_open()) {
			cerr<<"COULDN'T OPEN THE LOAD FILE"<<endl;			//IF FILE CANNOT OPEN
			throw file_error();
		}
		else {			
		
			wr2>>tempsize;									//I ENCODED THE FILE AT FIRST THERE IS BOARD SIZE AND THE USER AND WHO IS GONNA DO THE MOVE COMES
			wr2>>tempuser;
			wr2>>tempmove;
			set_size(tempsize);
			set_user(tempuser);
			set_move(tempmove);
			
			vector<vector<Cell>> temp;
			temp.resize(get_size()*get_size());
			for(mycnt=0;mycnt<get_size();mycnt++) {
				temp[mycnt].resize(get_size()); 
			}

			mycnt=0;
			while(true) {
				wr2>>c;											//I PUT An 'l' at the beginning of the indices lines
				if(c=='-') {									//I SEPERATED WITH TABLE'S VALUES (X-O-.) WITH -
					break;
				}
				else if(c=='\n') {
					continue;
				}
				else if(c=='l') {
					mycnt+=1;
					wr2>>xval;
					wr2>>yval;
					temp[yval][xval].set_symbol(u1);			//READ X'S
				}
			}
			while(true) {										//READ O'S
				wr2>>c;
				if(c=='-') {
					break;
				}
				else if(c=='\n') {
					continue;
				}
				else if(c=='l'){
					mycnt+=1;
					wr2>>xval;
					wr2>>yval;
					temp[yval][xval].set_symbol(u2);		
				}
			}
			while(true) {									//READ .'S'
				wr2>>c;
				if(c=='-') {
					break;
				}
				else if(c=='\n') {
					continue;
				}
				else if(c=='l') {
					wr2>>xval;
					wr2>>yval;
					temp[yval][xval].set_symbol(d);				
				}
			}
			wr2>>incoming;												//READ ORDER OF MOVES
			set_user_counter(incoming);

			while(true) {
				wr2>>myx;
				if(myx==2347) {										//SIGN FOR END OF FILE
					break;
				}
				wr2>>myy;
				i+=1;
			}
			hexCells=temp;
			set_marked_cell(mycnt);
		}
		ret=2;											//LOADED	
		print();	
		wr2.close();
		cout<<"LOADED SUCCESSFULLY"<<endl;		
		return ret;		
	}
	int HexVector::ready_to_play() {
		string input1;							//UNDO SAVE LOAD STRING
		string input2;							//FILENAME.TXT STRING
		stringstream mys1;						
		stringstream mys2;
		Cell temp;
		int win=-1;
		int checkr=0;
		char l;
		int num;
		int i;
		int k;
		int ret=-1;
		int mycnt=0;
		int checksizeforcontrol=0;
		set_marked_cell(0);
		set_user_counter(0);
		Cell temp2;
		Cell temp3;

		symbol ** control=nullptr;									//FOR WINNER CONTROL 		//NULLPTR KEYWORD IS NEEDED IN HOMEWORK

		control=new symbol*[get_size()*get_size()];

		for(mycnt=0;mycnt<get_size();mycnt++) {				
			control[mycnt]=new symbol[get_size()]; 
		}
		string save="SAVE";
		string load="LOAD";	
		string undo="UNDO";											//STATIC VARIBLE THAT HOLDS HOW MANY GAME IS PLAYED UP TO NOW
		while(win<0) {
			set_win(win);
			cout<<"MOVE HAS PLAYER"<<get_move()<<"'s"<<endl;
			if(get_user()==2 && get_move()==2) {
				ret=1;
			}
			else {
				cout<<"IF YOU WANT TO SAVE CURRENT GAME,ENTER THIS COMMAND: "<<save<<" and enter the name of the file like FILE.TXT\n";
				cout<<"IF YOU WANT TO LOAD A GAME FROM A FILE, ENTER THIS COMMAND: "<<load<<" and enter the name of the file like FILE.TXT\n";
				cout<<"IF YOU WANT TO MAKE A MOVE YOU CAN DO IT LIKE THAT:A 6\n";
				cin>>input1;
				if(input1.compare(undo)==0 && get_user_counter()>1) {
					if(get_move()==1) {

					}
					else {

					}
					ret=2;
					print();
				}
				else if(input1.compare(undo)==0 && get_user_counter()<=1){
					cerr<<"THERE IS NOTHING TO UNDO"<<endl;
				}
				else {
					cin>>input2;
					if(save.compare(input1)==0) {													//CHECKING INPUT FOR LOAD,SAVE OR MOVE
						try {
							ret=readFromFile(input2);						//SAVE THE GAME
							print();							
						}
						catch (file_error &fe){
							cerr<<"ERROR OCCURED: "<<fe.what();							
						}

					}
					else if(load.compare(input1)==0) {					//LOAD THE GAME	
						try {
							checksizeforcontrol=get_size();
							ret=writeToFile(input2);
						}

						catch (file_error &fe){
							cerr<<"ERROR OCCURED: "<<fe.what();								
						}
						if(checksizeforcontrol==get_size()) {			//IF SIZE IS NOT CHANGED WE DON'T NEED TO ALLOCATE MEMORY FOR CONTROL ARRAY

						}	
						else {
							for(i=0;i<get_size();i++) {
								delete control[i];
							}
							delete[] control;								//RESIZE CONTROL ARRAY BECAUSE WE'VE LOADED A GAME SIZE MAYBE CHANGED

							control=new symbol*[get_size()*get_size()];
							for(mycnt=0;mycnt<get_size();mycnt++) {				
								control[mycnt]=new symbol[get_size()]; 

							}						
						}											
					}
					else {
						mys1<<input1;								//TAKING THE X AND Y VALUES
						mys2<<input2;
						mys2>>num;																	//THIS IS A MOVE INPUT
						mys1>>l;
						mys1=std::stringstream();				//CLEAR THE STRING STREAM OBJECT SO THAT IT CAN READ PROPERLY
						mys2=std::stringstream();
						
						try {
							checkr=check_validity(l,num);					//CHECK IS MOVE VALID
							if(checkr==0) {
								cerr<<"INVALID MOVE"<<endl;

								print();
								throw wrong_input();
								ret=-1;
							}		
							else {
								ret=1;
							}							
						}
						catch (wrong_input &we) {
							cerr<<"INVALID MOVE: "<<we.what();
						}
	
					}			
				}
			}
			if(ret==1) {	
															//IF THERE IS A MOVE INPUT CHECK IS THERE A WINNER
				switch(get_move()) {
					case 1:
										//PLAYS FOR 1 STEP
						temp2.set_x((int)l-65);
						temp2.set_y(num-1);
						temp2.set_symbol(u1);
						this->x=temp2.get_x();
						this->y=temp2.get_y();
	
						play(temp2);						
						
						set_user_counter(get_user_counter()+1);		//RECORDING THE MOVE (X,Y,SYMBOL) AND ORDER OF THE MOVE
														
						cout<<"\nAfter player1's move table become:"<<endl;
						set_marked_cell(get_marked_cell()+1);				//RECORD THE MARKED CELL NUMBER
						print();	


						for(i=0;i<get_size();i++) {											//IF THERE IS AN ELEMENT AT THE LEFT AND RIGHT SIDE OF THE BOARD,CHECK IS A WINNER  
							if(hexCells[i][0].get_symbol()==u1) {
								for(k=0;k<get_size();k++) {
									if(hexCells[k][get_size()-1].get_symbol()==u1) {
										win=is_winner(0,i,0,control,'x');									
										fill_the_empty_board(control);			//CLEAR THE CONTROL ARRAY SO THAT WE CAN CHECK PROPERLY WHO IS WINNER AT THE NEXT MOVE									
										if(win==1) {
											print();					
											break;
										}
									}
									if(win==1) {
										break;
									}
								}
								if(win==1) {
									break;
								}						
							}
							if(win==1) {
								break;
							}
						}										
						set_move(get_move()+1);				//CHANGE THE WHO IS GONNA MAKE MOVE
						break;
					case 2:
						if(get_user()==2) {											//IF PLAYER2 IS MACHINE						
							set_x_for_ai((int)l-65);
							set_y_for_ai(num-1);					
							temp=play();											//RETURNS CELL 
							this->x=temp.get_x();
							this->y=temp.get_y();			
							set_user_counter(get_user_counter()+1);							
						}
						else {
							temp3.set_x((int)l-65);					//RECORD THE ORDER OF THE MOVE AND X,Y SYMBOL VALUES
							temp3.set_y(num-1);
							temp3.set_symbol(u2);
							play(temp3);				
							set_user_counter(get_user_counter()+1);												
						}																		
						cout<<"\nAfter player2's move table become:"<<endl;	
						set_marked_cell(get_marked_cell()+1);				//RECORD THE MARKED CELL NUMBER
						print();
						for(i=0;i<board_size;i++) {										//CHECK IF THERE IS A POSSIBILITY FOR WINNING
							if(hexCells[0][i].get_symbol()==u2) {						//FROM TOP TO BOTTOM
								for(k=0;k<board_size;k++) {
									if(hexCells[board_size-1][k].get_symbol()==u2) {
										win=is_winner(k,board_size-1,0,control,'o'); 
										fill_the_empty_board(control);					//CLEAR THE CONTROL ARRAY
										if(win==2) {
											print();
											break;
										}
									}
									if(win==2) {
										break;
									}
								}
								if(win==2) {
									break;
								}						
							}
							if(win==2) {
								break;
							}
						}		
						set_move(get_move()-1);					//CHANGE THE WHO IS GONNA MAKE MOVE
						break;					
				}
			}
			else {
			
			}
		}
		cout<<"PLAYER "<<win<<" WON!!"<<endl;
		set_win(win);
		for(int i=0;i<get_size();i++) {
			delete control[i];
		}
		delete[] control;					//DELETE CONTROL ARRAY
		return win;
	}
	Cell& HexVector::operator()(int x,int y) {
		if(x>=get_size() || y>=get_size()) {
			throw outofindex();
		}
		return hexCells[y][x];
	}
}