
#ifndef MYHEADER2
#define MYHEADER2

using namespace std;

void print_board(char board[12][12],int board_size);								//PRINTS THE CURRENT BOARD

void fill_the_empty_board(char board[12][12],int board_size);						//FILLS THE BOARD WITH DOTS

int check_validity(char board[12][12],int board_size,char l,int num);				//CHECK IF THE MOVE IS VALID

int check_is_full(char board[12][12],int board_size);								//IF THE BOARD IS FULL FINISH THE GAME

int check_control_array(char control[12][12],int x,int y,char p);					/*WHEN LOOKING FOR IS THERE A WINNER 
																					  WE NEED TO CHECK IF WE WERE CAME HERE BEFORE*/

int situation(char board[12][12],int board_size,int x,int y,int direction,bool arr[7],char control[12][12],char p);		
//CHECKING THE CURRENT SITUATION DEPEND ON THE DIRECTIONS
/*I DECIDED THE DIRECTIONS LIKE THAT:
     . 6 1 .  
      5 x 2 .  
       4 3 . 

I DECIDED THE SITUATIONS LIKE THAT
A B C D E F G H 
 1 5 5 5 5 5 5 7
  2 6 6 6 6 6 6 8
   2 6 6 6 6 6 6 8	
    2 6 6 6 6 6 6 8	
     2 6 6 6 6 6 6 8	
      2 6 6 6 6 6 6 8	
       2 6 6 6 6 6 6 8	
        3 4 4 4 4 4 4 9	
*/

void correct(bool arr[6],int direction);			
//AFTER THE FIND THE DIRECTION WE NEED TO CORRECT IT'S COMPLIMENT LIKE 1'S COMPLIMENT IS 4 2'S 5 3'S 6 LIKE THAT

int is_winner(char board[12][12],int board_size,int x,int y,int direction,char control[12][12],char p);
//CHECKING IS THERE A WINNER WITH USING X Y AND DIRECTIONS

bool check_validity_2(char board[12][12],int board_size,int x,int y);
//CHECKING VALIDITY OF THE MACHINE'S MOVE IF THE MOVE IS INVALID WE DON'T NEED TO SEND ERROR MESSAGE BUT IN CHECK VALIDITY FUNCTION THERE IS AN ERROR MESSAGE

void show(char board[12][12],int x,int y);
//AFTER FINDING A VALID MOVE FOR MACHINE, ADD THIS MOVE TO THE BOARD
void situation6(char board[12][12],int board_size,int x,int y);    //CHECKING THE POSSIBLE MOVES FOR MACHINES FOR 9 SITUATIONS I'VE EXPLAINED THE ABOVE
void situation1(char board[12][12],int board_size,int x,int y);
void situation3(char board[12][12],int board_size,int x,int y);
void situation4(char board[12][12],int board_size,int x,int y);
void situation5(char board[12][12],int board_size,int x,int y);
void situation6_2(char board[12][12],int board_size,int x,int y);
void situation7(char board[12][12],int board_size,int x,int y);
void situation8(char board[12][12],int board_size,int x,int y);
void situation9(char board[12][12],int board_size,int x,int y);
int two_player_game_mod(char board[12][12],int board_size,int opt1);	//START THE GAME


#endif
