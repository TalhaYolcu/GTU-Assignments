
#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include "header.h"

void fill_the_empty_board(cell board[12][12],const int& board_size) {			//FILL THE BOARD WITH DOTS
	int i,k;
	for(i=0;i<board_size;i++) {
		for(k=0;k<board_size;k++) {
			board[i][k]=d;
		}
	}
}
void print_board(cell board[12][12],const int& board_size) {		//PRINT THE BOARD WITH NECESSARY SPACES
	int i,x,y,k;
	cout<<endl;
	cout<<" ";
	for(i=65;i<board_size+65;i++) {
		cout<<(char)i<<" ";
	}
	cout<<endl;
	for(x=1;x<=board_size;x++) {
		if(x>=10)  {
			cout<<x;
		}
		else {
			cout<<x<<" ";			
		}
		for(y=0;y<x-1;y++) {
			cout<<" ";
		}
		for(k=0;k<board_size;k++) {
			cout<<(char)board[x-1][k]<<" ";				
		}
		cout<<endl;
	}
}
int check_validity(cell board[][12], char l,int num,int move,int user) {		//CHECKING THE VALIDITY OF THE MOVE IF AI HAS THE MOVE THEN NO NEEDED THE CHECK BECAUSE THE MOVE IS NOT DONE YET
	if(user==2 && move==2) {
		return 1;
	}
	else {
		if(board[num-1][(int)l-65]==d) {
			return 1;
		}
		else {
			return 0;
		}		
	}
}
void correct(bool arr[6],int direction) {						
//MAKE A CORRECTION FOR BOOL ARRAY THAT HOLD DIRECTONS
	//I'VE EXPLAINED ALSO WHY WE NEED TO CORRECT THE BOOL ARRAY IN helper2.h
	if(direction==0) {

	}
	else {
		if(direction>3) {
			arr[direction-4]=false;
		}
		else if(direction==3) {
			arr[5]=false;
		}
		else if(direction<3){
			arr[5-direction]=false;
		}			
	}
}
int check_control_array(cell control[12][12],int xval,int yval,char p) {			//CHECKING IF WE'VE COME THIS PLACE WHILE WE ARE LOOKING FOR IS THERE A WINNER
	if(p=='x') {
		if(control[yval][xval]==x) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if(p=='o') {
		if(control[yval][xval]==o) {
			return 1;
		}
		else {
			return 0;
		}		
	}
}
int situation(cell board[12][12],int board_size,int xval,int yval,int direction,bool arr[7],cell control[12][12],char p) {
//CHECKING DEPEND ON THE DIRECTIONS AND SITUATIONS
//THERE IS TWO TABLE FOR EXPLAINING WHAT IS SITUATION AND DIRECTION IN helper.h
//BOOL ARRAY HOLD THE DIRECTIONS AND P HOLD 'x' or 'o'

	int i,ret=-1,c=-1;
	for(i=0;i<6;i++) {
		if(arr[i]==true) {
			switch(i+1) {
				case 1:
					if(p=='x') {
						if(board[yval-1][xval+1]==x) {
							c=check_control_array(control,xval+1,yval-1,p);
							if(c==0) {							
								control[yval][xval]=x;	
								ret=is_winner(board,board_size,xval+1,yval-1,1,control,'x');		//1 yönü
							}
						}
					}
					else {
						if(board[yval-1][xval+1]==o) {
							c=check_control_array(control,xval+1,yval-1,p);
							if(c==0) {							
								control[yval][xval]=o;	
								ret=is_winner(board,board_size,xval+1,yval-1,1,control,'o');		//1 yönü
							}
						}
					}
					break;
				case 2:																		//2 yönü
					if(p=='x') {
						if(board[yval][xval+1]==x) {
							c=check_control_array(control,xval+1,yval,p);
							if(c==0) {
								control[yval][xval]=x;	
								ret=is_winner(board,board_size,xval+1,yval,2,control,'x');
							}
						}
					}
					else {
						if(board[yval][xval+1]==o) {
							c=check_control_array(control,xval+1,yval,p);
							if(c==0) {
								control[yval][xval]=o;	
								ret=is_winner(board,board_size,xval+1,yval,2,control,'o');
							}
						}
					}	
					break;		
				case 3:																	//3 yönü
					if(p=='x') {
						if(board[yval+1][xval]==x) {
							c=check_control_array(control,xval,yval+1,p);
							if(c==0) {
								control[yval][xval]=x;	
								ret=is_winner(board,board_size,xval,yval+1,3,control,'x');
							}
						}
					}
					else {
						if(board[yval+1][xval]==o) {
							c=check_control_array(control,xval,yval+1,p);
							if(c==0) {
								control[yval][xval]=o;	
								ret=is_winner(board,board_size,xval,yval+1,3,control,'o');
							}
						}
					}
					break;
				case 4:
					if(p=='x') {
						if(board[yval+1][xval-1]==x) {
							c=check_control_array(control,xval-1,yval+1,p);
							if(c==0) {
								control[yval][xval]=x;	
								ret=is_winner(board,board_size,xval-1,yval+1,4,control,'x');		//4 yönü
							}
						}
					}
					else {
						if(board[yval+1][xval-1]==o) {
							c=check_control_array(control,xval-1,yval+1,p);
							if(c==0) {
								control[yval][xval]=o;	
								ret=is_winner(board,board_size,xval-1,yval+1,4,control,'o');		//4 yönü
							}
						}
					}
					break;
				case 5:
					if(p=='x') {
						if(board[yval][xval-1]==x) {
							c=check_control_array(control,xval-1,yval,p);
							if(c==0) {
								control[yval][xval]=x;	
								ret=is_winner(board,board_size,xval-1,yval,5,control,'x');		//5 yönü
							}
						}
					}
					else {
						if(board[yval][xval-1]==o) {
							c=check_control_array(control,xval-1,yval,p);
							if(c==0) {
								control[yval][xval]=o;	
								ret=is_winner(board,board_size,xval-1,yval,5,control,'o');		//5 yönü
							}
						}						
					}
					break;								
				case 6:
					if(p=='x') {
						if(board[yval-1][xval]==x) {
							c=check_control_array(control,xval,yval-1,p);
							if(c==0) {
								control[yval][xval]=x;	
								ret=is_winner(board,board_size,xval,yval-1,6,control,'x');		//6 yönü
							}
						}
					}
					else {
						if(board[yval-1][xval]==o) {
							c=check_control_array(control,xval,yval-1,p);
							if(c==0) {
								control[yval][xval]=o;	
								ret=is_winner(board,board_size,xval,yval-1,6,control,'o');		//6 yönü
							}
						}
					}
					break;	
			}
		}
		if(ret==1 || ret==2) {
			break;
		}
	}
	return ret;
}
int is_winner(cell board[12][12],int board_size,int xval,int yval,int direction,cell control[12][12],char p) {
	int ret=-1,i;

//IF THERE'S A POSSIBILITY OF THE WINNER CHECK IT DEPEND ON THE SITUATIONS AND DIRECTIONS


	//1 yönü x artar y azalır	//2 yönü x artar y sabit	//3 yönü x sabit y artar	//4 yönü x azalır y artar	//5 yönü x azalır y sabit	//6 yönü x sabit y azalır
	bool arr[7];
	if(p=='x' && xval==(board_size-1)) {
		ret=1;				
	}
	else if(p=='o' && yval==0) {
		ret=2;				
	}
	else {
		if(xval==0 && yval==0) {
			for(i=1;i<=6;i++) {
				if(i==2 || i==3) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;					
				}
			}
		}
		else if(xval==0 && 0<yval<(board_size-1)) {
			for(i=1;i<=6;i++) {
				if(i<=3 || i==6) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;					
				}						
			}
		}
		else if(xval==0 && yval==(board_size-1)) {
			for(i=1;i<=6;i++) {
				if(i<=2 || i==6) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;
				}			
			}	
		}
		else if(0<xval<(board_size-1) && yval==(board_size-1)) {
			for(i=1;i<=6;i++) {
				if(i<=2 || i>=5) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;
				}			
			}
		}
		else if(0<xval<(board_size-1) && yval==0) {
			for(i=1;i<=6;i++) {
				if(i!=1 || i!=6) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;
				}			
			}
		}
		else if(0<xval<(board_size-1) && 0<yval<(board_size-1)) {
			for(i=1;i<=6;i++) {
				arr[i-1]=true;			
			}
		}
		else if(xval==(board_size-1) && 0<yval<(board_size-1)) {
			for(i=1;i<=6;i++) {
				if(i>=3) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;
				}
			}
		}
		else if(xval==(board_size-1) && yval==(board_size-1)) {
			for(i=1;i<=6;i++) {
				if(i>=5) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;
				}
			}
		}
		correct(arr,direction);		
		if(p=='x') {
			ret=situation(board,board_size,xval,yval,direction,arr,control,'x');	
		}
		else if(p=='o') {
			ret=situation(board,board_size,xval,yval,direction,arr,control,'o');	
		}								
	}
	switch(ret) {
		case 1:
			board[yval][xval]=bx;		//MAKE CAPITAL LETTER
			break;
		case 2:
			board[yval][xval]=bo;
			break;			
	}
	return ret;
}
bool check_validity_2(cell board[12][12],int board_size,int xval,int yval) {		
//CHECK VALIDTY OF THE MACHINES MOVE
	if(board[yval][xval]==d) {
		return true;
	}
	else {
		return false;
	}	
}
void show(cell board[12][12],int xval,int yval) {
//IMPLEMENT THE MACHINES MOVE AND PRINT MACHINE'S MOVE
	board[yval][xval]=o;
	cout<<(char)(xval+65)<<" "<<yval+1<<endl;
}
void situation6(cell board[12][12],int board_size,int xval,int yval) {
// IF THERE IS NOT A MOVE THAT MACHINE FIND, MOVE THE MOST CLOSE PLACE
	//IF YOU CAN'T MOVE THE MOST CLOSE PLACE THEN START FROM BEGINNING AND MOVE THE FIRST PLACE THAT YOU FIND
	int i,k;
	double distance=999;
	double temp;
	int mx=-1,my=-1;
	int checkr=-1;
	int flag=0;
	for(i=1;i<(board_size-1);i++) {
		for(k=1;k=(board_size-1);k++) {
			temp=sqrt((k-xval)*(k-xval)+(i-yval)*(i-yval));
			if(temp<distance) {
				if(check_validity_2(board,board_size,k,i)) {
					mx=k;
					my=i;					
				}
	
			}
		}
	}
	if(mx<0) {
		for(i=0;i<board_size;i++) {
			for(k=0;k<board_size;k++) {
				if(board[i][k]==d) {
					show(board,k,i);
					flag=1;
					break;
				}
			}
			if(flag==1) {
				break;
			}
		}
	}
	else {
		show(board,mx,my);
	}
}
void situation1(cell board[12][12],int board_size,int xval,int yval) {
// I IMPLEMENT 9 FUNCTIONS LIKE THAT FOR MACHINE DEPENDS ON THE DIRECTION AND SITUATION
	if(board[yval][xval+1]==d) {
		show(board,xval+1,yval);	
	}
	else if(board[yval+1][xval]==d) {
		show(board,xval,yval+1);
	}
	else if(board[yval+2][xval]==d) {
		show(board,xval,yval+2);			
	}
	else {
		situation6(board,board_size,xval,yval);
	}
}
void situation2(cell board[12][12],int board_size,int xval,int yval) {
	if(board[yval][xval+1]==d) {
		show(board,xval+1,yval);
	}
	else if(board[yval-1][xval+1]==d) {
		show(board,xval+1,yval-1);
	}
	else if(board[yval+1][xval]==d) {
		show(board,xval,yval+1);
	}
	else if(board[yval-1][xval]==d) {
		show(board,xval,yval-1);
	}
	else {
		situation6(board,board_size,xval,yval);
	}
}
void situation3(cell board[12][12],int board_size,int xval,int yval) {
	if(board[yval][xval+1]==d) {
		show(board,xval+1,yval);	
	}
	else if(board[yval-1][xval+1]==d) {
		show(board,xval+1,yval-1);
	}
	else if(board[yval][xval+1]==d) {
		show(board,xval+1,yval);
	}
	else {
		situation6(board,board_size,xval,yval);
	}
}
void situation4(cell board[12][12],int board_size,int xval,int yval) {
	if(board[yval][xval+1]==d) {
		show(board,xval+1,yval);
	}
	else if(board[yval-1][xval+1]==d) {
		show(board,xval+1,yval-1);
	}
	else if(board[yval-1][xval]==d) {
		show(board,xval,yval-1);
	}
	else if(board[yval][xval-1]==d) {
		show(board,xval-1,yval);
	}
	else {
		situation6(board,board_size,xval,yval);
	}
}
void situation5(cell board[12][12],int board_size,int xval,int yval) {
	if(board[yval][xval-1]==d) {
		show(board,xval-1,yval);
	}
	else if(board[yval+1][xval-1]==d) {
		show(board,xval-1,yval+1);
	}
	else if(board[yval][xval+1]==d) {
		show(board,xval+1,yval);
	}
	else if(board[yval+1][xval]==d) {
		show(board,xval,yval+1);
	}
	else {
		situation6(board,board_size,xval,yval);
	}
}
void situation6_2(cell board[12][12],int board_size,int xval,int yval){
	if(board[yval][xval+1]==d) {
		show(board,xval+1,yval);
	}
	else if(board[yval-1][xval+1]==d) {
		show(board,xval+1,yval-1);
	}
	else if(board[yval-1][xval]==d) {
		show(board,xval,yval-1);
	}
	else if(board[yval][xval-1]==d) {
		show(board,xval-1,yval);
	}
	else if(board[yval+1][xval-1]==d) {
		show(board,xval-1,yval+1);
	}
	else if(board[yval+1][xval]==d) {
		show(board,xval,yval+1);
	}
	else {
		situation7(board,board_size,board_size-1,0);
	}
}
void situation7(cell board[12][12],int board_size,int xval,int yval) {
	if(board[yval][xval-1]==d) {
		show(board,xval-1,yval);
	}
	else if(board[yval+1][xval]==d) {
		show(board,xval,yval+1);
	}
	else if(board[yval+1][xval-1]==d){
		show(board,xval-1,yval+1);
	}
	else {
		situation6(board,board_size,xval,yval);
	}
}
void situation8(cell board[12][12],int board_size,int xval,int yval) {
	if(board[yval-1][xval]==d) {
		show(board,xval,yval-1);
	}
	else if(board[yval][xval-1]==d) {
		show(board,xval-1,yval);
	}
	else if(board[yval+1][xval-1]==d) {
		show(board,xval-1,yval+1);
	}
	else if(board[yval+1][xval]==d) {
		show(board,xval,yval+1);
	}
	else {
		situation6(board,board_size,xval,yval);
	}
}
void situation9(cell board[12][12],int board_size,int xval,int yval) {
	if(board[yval-1][xval]==d) {
		show(board,xval,yval-1);
	}
	else if(board[yval][xval-1]==d) {
		show(board,xval-1,yval);
	}
	else {
		situation6(board,board_size,xval,yval);
	}
}
void machine_s_move(cell board[12][12],int board_size,int xval,int yval) {
//DIRECT THE MACHINE WHERE PLAYER1'S FIRST PLACE
	if(xval==0 && yval==0) {														    //SITUATION1
		situation1(board,board_size,xval,yval);
	}
	else if(xval==0 && yval<(board_size-1) && yval>0) {										//SITUATION2
		situation2(board,board_size,xval,yval);
	}
	else if(xval==0 && yval==(board_size-1)) {										//SITUATION3
		situation3(board,board_size,xval,yval);
	}
	else if(xval<(board_size-1) && yval==(board_size-1) && yval>0) {							//SITUATION4
		situation4(board,board_size,xval,yval);
	}
	else if(xval<(board_size-1) && yval==0 && xval>0) {										//SITUATION5
		situation5(board,board_size,xval,yval);
	}
	else if(xval<(board_size-1) && yval<(board_size-1) && xval>0) {							//SITUATION6
		situation6_2(board,board_size,xval,yval);
	}
	else if(xval==(board_size-1) && yval==0) {										//SITUATION7
		situation7(board,board_size,xval,yval);
	}
	else if(xval==(board_size-1) && yval<(board_size-1) && yval>0) {							//SITUATION8
		situation8(board,board_size,xval,yval);
	}
	else if(xval==(board_size-1) && yval==(board_size-1)) {							//SITUATION9
		situation9(board,board_size,xval,yval);
	}	
}
int load_a_game(cell board[][12], int& board_size, int& user,int& move) {		//THIS FUNCTIONS LOADS THE GAME FROM GIVEN FILE
	ifstream wr2;
	char c;
	int i;
	int k;
	int xval;
	int yval;
	int ret=-1;
	string filename;

	cin>>filename;
	
	wr2.open(filename);
	if(!wr2.is_open()) {
		cerr<<"COULDN'T OPEN THE LOAD FILE"<<endl;			//IF FILE CANNOT OPEN
	}
	else {
		wr2>>board_size;									//I ENCODED THE FILE AT FIRST THERE IS BOARD SIZE AND THE USER AND WHO IS GONNA DO THE MOVE COMES
		wr2>>user;
		wr2>>move;
		while(true) {
			wr2>>c;											//I PUT An 'l' at the beginning of the indices lines
			if(c=='-') {									//I SEPERATED WITH TABLE'S VALUES (X-O-.) WITH -
				break;
			}
			else if(c=='\n') {
				continue;
			}
			else if(c=='l') {
				wr2>>xval;
				wr2>>yval;
				board[yval][xval]=x;
			}
		}
		while(true) {
			wr2>>c;
			if(c=='-') {
				break;
			}
			else if(c=='\n') {
				continue;
			}
			else if(c=='l'){
				wr2>>xval;
				wr2>>yval;
				board[yval][xval]=o;		
			}
		}
		while(true) {
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
				board[yval][xval]=d;				
			}
		}
		ret=2;//LOADED	
		print_board(board,board_size);		
		wr2.close();
		cout<<"LOADED SUCCESSFULLY"<<endl;		
	}
	return ret;
}
int save_the_current_game(cell board[][12], int& board_size, int& user,int& move) {		//THIS FUNCTIONS SAVES THE CURRENT GAME TO THE GIVEN FILE
	ofstream wr;
	int i;
	int k;
	string filename;
	cin>>filename;
	int ret=-1;

	wr.open(filename);

	if(!wr.is_open()) {
		cerr<<"COULDN'T SAVE IT"<<endl;
	}
	else {
		wr<<board_size<<endl;					//I ENCODED THE FILE AT FIRST THERE IS BOARD SIZE AND THE USER AND WHO IS GONNA DO THE MOVE COMES
		wr<<user<<endl;								//I DID THE SAME THING LIKE IN THE LOAD FUNCTION
		wr<<move<<endl;
		for(i=0;i<board_size;i++) {
			for(k=0;k<board_size;k++) {
				if(board[i][k]==x) {
					wr<<"l "<<k<<" "<<i<<endl;
				}
			}
		}
		wr<<"-"<<endl;
		for(i=0;i<board_size;i++) {
			for(k=0;k<board_size;k++) {
				if(board[i][k]==o) {
					wr<<"l "<<k<<" "<<i<<endl;
				}
			}
		}
		wr<<"-"<<endl;
		for(i=0;i<board_size;i++) {
			for(k=0;k<board_size;k++) {
				if(board[i][k]==d) {
					wr<<"l "<<k<<" "<<i<<endl;
				}
			}
		}
		wr<<"-"<<endl;		
		wr.close();	
		ret=2;
		cout<<"SAVED SUCCESSFULLY"<<endl;	
	}
	return ret;
}
int two_player_game_mod(cell board[][12], int& board_size, int&user,int& move,const string& save,string load) {
	string input;
	int win=-1;
	int checkr=0;
	char l;
	int num;
	int i;
	int k;
	int ret=-1;
	cell control[12][12];									//ENUM TYPE

	while(win<0) {
		cout<<"MOVE HAS PLAYER"<<move<<"'s"<<endl;
		if(user==2 && move==2) {
			ret=1;
		}
		else {
			cout<<"IF YOU WANT TO SAVE CURRENT GAME,ENTER THIS COMMAND: "<<save<<" and enter the name of the file like FILE.TXT\n";
			cout<<"IF YOU WANT TO LOAD A GAME FROM A FILE, ENTER THIS COMMAND: "<<load<<" and enter the name of the file like FILE.TXT\n";
			cout<<"IF YOU WANT TO MAKE A MOVE YOU CAN DO IT LIKE THAT:A 6\n";

			cin>>input;
			if(save.compare(input)==0) {													//CHECKING INPUT FOR LOAD,SAVE OR MOVE
				ret=save_the_current_game(board,board_size,user,move);						//SAVE THE GAME
				print_board(board,board_size);
			}
			else if(load.compare(input)==0) {
				ret=load_a_game(board,board_size,user,move);								//LOAD THE GAME
			}
			else {
				cin>>num;																	//THIS IS A MOVE INPUT
				l=(char)input[0];
				checkr=check_validity(board,l,num,move,user);					//CHECK IS MOVE VALID
				if(checkr==0) {
					cerr<<"INVALID MOVE"<<endl;
					print_board(board,board_size);
					ret=-1;
				}		
				else {
					ret=1;
				}	
			}			
		}
		if(ret==1) {																//IF THERE IS A MOVE INPUT CHECK IS THERE A WINNER
			switch(move) {
				case 1:
					board[num-1][(int)l-65]=x;
					cout<<"\nAfter player1's move table become:"<<endl;	
					print_board(board,board_size);
					for(i=0;i<board_size;i++) {											//IF THERE IS AN ELEMENT AT THE LEFT AND RIGHT SIDE OF THE BOARD,CHECK IS A WINNER  
						if(board[i][0]==x) {
							for(k=0;k<board_size;k++) {
								if(board[k][board_size-1]==x) {
									win=is_winner(board,board_size,0,i,0,control,'x');
									fill_the_empty_board(control,board_size);
									if(win==1) {
										print_board(board,board_size);
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
					move++;
					break;
				case 2:
					if(user==2) {											//IF PLAYER2 IS MACHINE
						machine_s_move(board,board_size,(int)l-65,num-1);
					}
					else {
						board[num-1][(int)l-65]=o;
					}
					cout<<"\nAfter player2's move table become:"<<endl;	
					print_board(board,board_size);
					for(i=0;i<board_size;i++) {
						if(board[0][i]==o) {
							for(k=0;k<board_size;k++) {
								if(board[board_size-1][k]==o) {
									win=is_winner(board,board_size,k,board_size-1,0,control,'o'); 
									fill_the_empty_board(control,board_size);				//CLEAR THE CONTROL ARRAY
									if(win==2) {
										print_board(board,board_size);
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
					move--;
					break;					
			}
		}
		else {

		}
	}
	return win;	
}
