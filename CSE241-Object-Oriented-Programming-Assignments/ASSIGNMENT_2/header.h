#include<iostream>
#include<string>
#include<fstream>
#include<cmath>

#ifndef MYHEADER2
#define MYHEADER2



using namespace std;

enum cell {x='x',o='o',d='.',bx='X',bo='O'};

int is_winner(cell board[12][12],int board_size,int xval,int yval,int direction,cell control[12][12],char p);

void situation7(cell board[12][12],int board_size,int xval,int yval);

void fill_the_empty_board(cell board[12][12],const int& board_size);

void print_board(cell board[12][12],const int& board_size);


int check_validity(cell board[][12], char l,int num,int move,int user);

void correct(bool arr[6],int direction);

int check_control_array(cell control[12][12],int xval,int yval,char p);

int situation(cell board[12][12],int board_size,int xval,int yval,int direction,bool arr[7],cell control[12][12],char p);

int is_winner(cell board[12][12],int board_size,int xval,int yval,int direction,cell control[12][12],char p);

bool check_validity_2(cell board[12][12],int board_size,int xval,int yval);

void show(cell board[12][12],int xval,int yval);

void situation6(cell board[12][12],int board_size,int xval,int yval);


void situation1(cell board[12][12],int board_size,int xval,int yval);

void situation2(cell board[12][12],int board_size,int xval,int yval);

void situation3(cell board[12][12],int board_size,int xval,int yval);

void situation4(cell board[12][12],int board_size,int xval,int yval);

void situation5(cell board[12][12],int board_size,int xval,int yval);

void situation6_2(cell board[12][12],int board_size,int xval,int yval);

void situation7(cell board[12][12],int board_size,int xval,int yval);

void situation8(cell board[12][12],int board_size,int xval,int yval);

void situation9(cell board[12][12],int board_size,int xval,int yval);

void machine_s_move(cell board[12][12],int board_size,int xval,int yval);

int load_a_game(cell board[][12], int& board_size, int& user,int& move);

int save_the_current_game(cell board[][12], int& board_size, int& user,int& move);

int two_player_game_mod(cell board[][12], int& board_size, int&user,int& move,const string& save,string load="LOAD");


#endif










