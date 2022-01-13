#include<iostream>
#include<string>
#include<fstream>
#include<cmath>

#include "header.h"

/*

FILE ENCODING

board_size=6
user=1 (user vs user)
who_is_gonna_make_move=1 (user1)
lthe x's x the x's y
-
lthe o's x the o's y
-
lthe .'s x the .'s y*/

using namespace std;

//enum cell {x='x',o='o',d='.',bx='X',bo='O'};



int main() {
	string input;
	auto load="LOAD";
	decltype(input) save;
	int x=-1;
	int r;
	int opt1;
	int finish;
	cell board[12][12];
	int board_size;
	int user;
	int move=1;

	save="SAVE";
	cout<<"!!!WELCOME TO HEX GAME!!!"<<endl;
		
	//1)LOAD 2)SAVE 3)6

	while(x<0) {
		cout<<"IF YOU WANT TO INITIALIZE THE GAME, ENTER THE BOARD SIZE (MIN 6 MAX 12)(EXAMPLE:FOR 8X8 type 8)\n";
		cout<<"IF YOU WANT TO SAVE CURRENT GAME,ENTER THIS COMMAND: "<<save<<" and enter the name of the file like FILE.TXT\n";
		cout<<"IF YOU WANT TO LOAD A GAME FROM A FILE, ENTER THIS COMMAND: "<<load<< " and enter the name of the file like FILE.TXT\n";
		cin>>input;

		if(input.compare(load)==0) {
			x=load_a_game(board,board_size,user,move);
		}
		else if(((int)input[0]-48)>5 && int(input[0]-48)<10) {
			//play the game
			r=(int)input[0]-48;
			x=1;

		}
		else if(((int)input[0]-96)==1 && ((int)input[1]-96)<3) {
			r=((int)input[0]-48)*10+(int)input[1]-48;
			x=1;
		}
		else {
			if(input.compare(save)==0) {
				cerr<<"NOTHING TO SAVE HERE"<<endl;
			}
			else {
				cerr<<"INVALID COMMAND,TRY AGAIN";
			}		
		}				
	}
	if(x==2) {

	}
	else {
		//INITIALIZE THE GAME
		fill_the_empty_board(board,r);
		print_board(board,r);
		cout<<"PLEASE CHOOSE (1)if this a two player game or (2)user versus computer game:"<<endl;
		cin>>opt1;
		while(opt1!=1 && opt1!=2) {
			cerr<<"WRONG OPTION PLS TRY AGAIN:"<<endl;
			cin>>opt1;
		}
		board_size=r;	
		user=opt1;
		move=1;			
	}
	finish=two_player_game_mod(board,board_size,user,move,save,load);
	switch(finish) {
		case 1:
		cout<<"PLAYER1 IS WINNER"<<endl;
		break;
		case 2:
		cout<<"PLAYER2 IS WINNER"<<endl;
		break;
	}
}