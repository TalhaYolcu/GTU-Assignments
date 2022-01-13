#include<iostream>
#include<cmath>
#include "headers.h"

using namespace std;

int main() {
	int board_size,i,opt1,num,finish,win;
	char board1[12][12];
	char l;
	cout<<"!!!WELCOME TO HEX GAME!!!\nPlease choose the board size:(MIN 6 MAX 12)(EXAMPLE:FOR 8X8 type 8)"<<endl;
	while(board_size>12 || board_size<6) {                         //CHECKING VALIDITY
		cout<<"Size:";
		cin>>board_size;
		if((board_size>12 || board_size<6)) {
			cout<<"INVALID OPTION PLEASE TRY AGAIN"<<endl;
		}
	}	
	fill_the_empty_board(board1,board_size);						//FILLING THE BOARD WITH DOTS
	print_board(board1,board_size);
	cout<<"PLEASE CHOOSE (1)if this a two player game or (2)user versus computer game:"<<endl;
	cin>>opt1;
	while(opt1!=1 && opt1!=2) {
		cout<<"WRONG OPTION PLS TRY AGAIN:"<<endl;
		cin>>opt1;
	}
	cout<<"WHEN YOU ARE TYPING MOVES YOU CAN DO IT LIKE THAT:A 6\n";
	finish=two_player_game_mod(board1,board_size,opt1);				//GAME MOD
	if(finish==0) {
		//THERE IS NO WINNER
	}
	else if(finish==1) {
		cout<<"PLAYER1 IS WINNER"<<endl;
		//PLAYER1 IS WINNER
	}
	else if(finish==2) {
		cout<<"PLAYER2 IS WINNER"<<endl;
		//PLAYER2 IS WINNER
	}
}
