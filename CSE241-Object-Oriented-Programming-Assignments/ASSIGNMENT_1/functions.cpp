#include<iostream>
#include<cmath>
#include "headers.h"

void print_board(char board[12][12],int board_size) {		//PRINT THE BOARD WITH NECESSARY SPACES
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
			cout<<board[x-1][k]<<" ";
		}
		cout<<endl;
	}
}
void fill_the_empty_board(char board[12][12],int board_size) {			//FILL THE BOARD WITH DOTS
	int i,k;
	for(i=0;i<board_size;i++) {
		for(k=0;k<board_size;k++) {
			board[i][k]='.';
		}
	}
}
int check_validity(char board[12][12],int board_size,char l,int num) {			//CHECK IF PLAYER'S MOVE IS VALID OR INVALIS
																					//IF IT'S INVALID SEND AN ERROR MESSAGE
	if(board[num-1][(int)l-65]=='.') {
		return 1;
	}
	else {
		cout<<"WRONG OPTION PLS TRY AGAIN"<<endl;
		return 0;
	}
}
int check_is_full(char board[12][12],int board_size) {							//CHECK IS TABLE FULL
	int i,k,flag=1;
	for(i=0;i<board_size;i++) {
		for(k=0;k<board_size;k++) {
			if(board[i][k]=='.') {
				flag=0;
				break;
			}
		}
	}
	return flag;
}
int check_control_array(char control[12][12],int x,int y,char p) {			//CHECKING IF WE'VE COME THIS PLACE WHILE WE ARE LOOKING FOR IS THERE A WINNER
	if(p=='x') {
		if(control[y][x]=='x') {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if(p=='o') {
		if(control[y][x]=='o') {
			return 1;
		}
		else {
			return 0;
		}		
	}
}
int situation(char board[12][12],int board_size,int x,int y,int direction,bool arr[7],char control[12][12],char p) {
//CHECKING DEPEND ON THE DIRECTIONS AND SITUATIONS
//THERE IS TWO TABLE FOR EXPLAINING WHAT IS SITUATION AND DIRECTION IN helper.h
//BOOL ARRAY HOLD THE DIRECTIONS AND P HOLD 'x' or 'o'

	int i,ret=-1,c=-1;
	for(i=0;i<6;i++) {
		if(arr[i]==true) {
			switch(i+1) {
				case 1:
					if(p=='x') {
						if(board[y-1][x+1]=='x') {
							c=check_control_array(control,x+1,y-1,p);
							if(c==0) {							
								control[y][x]='x';	
								ret=is_winner(board,board_size,x+1,y-1,1,control,'x');		//1 yönü
							}
						}
					}
					else {
						if(board[y-1][x+1]=='o') {
							c=check_control_array(control,x+1,y-1,p);
							if(c==0) {							
								control[y][x]='o';	
								ret=is_winner(board,board_size,x+1,y-1,1,control,'o');		//1 yönü
							}
						}
					}
					break;
				case 2:																		//2 yönü
					if(p=='x') {
						if(board[y][x+1]=='x') {
							c=check_control_array(control,x+1,y,p);
							if(c==0) {
								control[y][x]='x';	
								ret=is_winner(board,board_size,x+1,y,2,control,'x');
							}
						}
					}
					else {
						if(board[y][x+1]=='o') {
							c=check_control_array(control,x+1,y,p);
							if(c==0) {
								control[y][x]='o';	
								ret=is_winner(board,board_size,x+1,y,2,control,'o');
							}
						}
					}	
					break;		
				case 3:																	//3 yönü
					if(p=='x') {
						if(board[y+1][x]=='x') {
							c=check_control_array(control,x,y+1,p);
							if(c==0) {
								control[y][x]='x';	
								ret=is_winner(board,board_size,x,y+1,3,control,'x');
							}
						}
					}
					else {
						if(board[y+1][x]=='o') {
							c=check_control_array(control,x,y+1,p);
							if(c==0) {
								control[y][x]='o';	
								ret=is_winner(board,board_size,x,y+1,3,control,'o');
							}
						}
					}
					break;
				case 4:
					if(p=='x') {
						if(board[y+1][x-1]=='x') {
							c=check_control_array(control,x-1,y+1,p);
							if(c==0) {
								control[y][x]='x';	
								ret=is_winner(board,board_size,x-1,y+1,4,control,'x');		//4 yönü
							}
						}
					}
					else {
						if(board[y+1][x-1]=='o') {
							c=check_control_array(control,x-1,y+1,p);
							if(c==0) {
								control[y][x]='o';	
								ret=is_winner(board,board_size,x-1,y+1,4,control,'o');		//4 yönü
							}
						}
					}
					break;
				case 5:
					if(p=='x') {
						if(board[y][x-1]=='x') {
							c=check_control_array(control,x-1,y,p);
							if(c==0) {
								control[y][x]='x';	
								ret=is_winner(board,board_size,x-1,y,5,control,'x');		//5 yönü
							}
						}
					}
					else {
						if(board[y][x-1]=='o') {
							c=check_control_array(control,x-1,y,p);
							if(c==0) {
								control[y][x]='o';	
								ret=is_winner(board,board_size,x-1,y,5,control,'o');		//5 yönü
							}
						}						
					}
					break;								
				case 6:
					if(p=='x') {
						if(board[y-1][x]=='x') {
							c=check_control_array(control,x,y-1,p);
							if(c==0) {
								control[y][x]='x';	
								ret=is_winner(board,board_size,x,y-1,6,control,'x');		//6 yönü
							}
						}
					}
					else {
						if(board[y-1][x]=='o') {
							c=check_control_array(control,x,y-1,p);
							if(c==0) {
								control[y][x]='o';	
								ret=is_winner(board,board_size,x,y-1,6,control,'o');		//6 yönü
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
int is_winner(char board[12][12],int board_size,int x,int y,int direction,char control[12][12],char p) {
	int ret=-1,i;

//IF THERE'S A POSSIBILITY OF THE WINNER CHECK IT DEPEND ON THE SITUATIONS AND DIRECTIONS


	//1 yönü x artar y azalır	//2 yönü x artar y sabit	//3 yönü x sabit y artar	//4 yönü x azalır y artar	//5 yönü x azalır y sabit	//6 yönü x sabit y azalır
	bool arr[7];
	if(p=='x' && x==(board_size-1)) {
		ret=1;				
	}
	else if(p=='o' && y==0) {
		ret=2;				
	}
	else {
		if(x==0 && y==0) {
			for(i=1;i<=6;i++) {
				if(i==2 || i==3) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;					
				}
			}
		}
		else if(x==0 && 0<y<(board_size-1)) {
			for(i=1;i<=6;i++) {
				if(i<=3 || i==6) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;					
				}						
			}
		}
		else if(x==0 && y==(board_size-1)) {
			for(i=1;i<=6;i++) {
				if(i<=2 || i==6) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;
				}			
			}	
		}
		else if(0<x<(board_size-1) && y==(board_size-1)) {
			for(i=1;i<=6;i++) {
				if(i<=2 || i>=5) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;
				}			
			}
		}
		else if(0<x<(board_size-1) && y==0) {
			for(i=1;i<=6;i++) {
				if(i!=1 || i!=6) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;
				}			
			}
		}
		else if(0<x<(board_size-1) && 0<y<(board_size-1)) {
			for(i=1;i<=6;i++) {
				arr[i-1]=true;			
			}
		}
		else if(x==(board_size-1) && 0<y<(board_size-1)) {
			for(i=1;i<=6;i++) {
				if(i>=3) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;
				}
			}
		}
		else if(x==(board_size-1) && y==(board_size-1)) {
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
			ret=situation(board,board_size,x,y,direction,arr,control,'x');	
		}
		else if(p=='o') {
			ret=situation(board,board_size,x,y,direction,arr,control,'o');	
		}								
	}
	switch(ret) {
		case 1:
			board[y][x]='X';		//MAKE THE CAPITAL
			break;
		case 2:
			board[y][x]='O';
			break;			
	}
	return ret;
}
bool check_validity_2(char board[12][12],int board_size,int x,int y) {
//CHECK VALIDTY OF THE MACHINES MOVE
	if(board[y][x]=='.') {
		return true;
	}
	else {
		return false;
	}	
}
void show(char board[12][12],int x,int y) {
//IMPLEMENT THE MACHINES MOVE AND PRINT MACHINE'S MOVE
	board[y][x]='o';
	cout<<(char)(x+65)<<" "<<y+1<<endl;
}
void situation6(char board[12][12],int board_size,int x,int y) {
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
			temp=sqrt((k-x)*(k-x)+(i-y)*(i-y));
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
				if(board[i][k]=='.') {
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
void situation1(char board[12][12],int board_size,int x,int y) {
// I IMPLEMENT 9 FUNCTIONS LIKE THAT FOR MACHINE DEPENDS ON THE DIRECTION AND SITUATION
	int mx=-1;
	int my=-1;
	if(board[y][x+1]=='.') {
		show(board,x+1,y);	
	}
	else if(board[y+1][x]=='.') {
		show(board,x,y+1);
	}
	else if(board[y+2][x]=='.') {
		show(board,x,y+2);			
	}
	else {
		situation6(board,board_size,x,y);
	}
}
void situation2(char board[12][12],int board_size,int x,int y) {
	if(board[y][x+1]=='.') {
		show(board,x+1,y);
	}
	else if(board[y-1][x+1]=='.') {
		show(board,x+1,y-1);
	}
	else if(board[y+1][x]=='.') {
		show(board,x,y+1);
	}
	else if(board[y-1][x]=='.') {
		show(board,x,y-1);
	}
	else {
		situation6(board,board_size,x,y);
	}
}
void situation3(char board[12][12],int board_size,int x,int y) {
	int mx=-1;
	int my=-1;
	if(board[y][x+1]=='.') {
		show(board,x+1,y);	
	}
	else if(board[y-1][x+1]=='.') {
		show(board,x+1,y-1);
	}
	else if(board[y][x+1]=='.') {
		show(board,x+1,y);
	}
	else {
		situation6(board,board_size,x,y);
	}
}
void situation4(char board[12][12],int board_size,int x,int y) {
	if(board[y][x+1]=='.') {
		show(board,x+1,y);
	}
	else if(board[y-1][x+1]=='.') {
		show(board,x+1,y-1);
	}
	else if(board[y-1][x]=='.') {
		show(board,x,y-1);
	}
	else if(board[y][x-1]=='.') {
		show(board,x-1,y);
	}
	else {
		situation6(board,board_size,x,y);
	}
}
void situation5(char board[12][12],int board_size,int x,int y) {
	if(board[y][x-1]=='.') {
		show(board,x-1,y);
	}
	else if(board[y+1][x-1]=='.') {
		show(board,x-1,y+1);
	}
	else if(board[y][x+1]=='.') {
		show(board,x+1,y);
	}
	else if(board[y+1][x]=='.') {
		show(board,x,y+1);
	}
	else {
		situation6(board,board_size,x,y);
	}
}
void situation6_2(char board[12][12],int board_size,int x,int y){
	if(board[y][x+1]=='.') {
		show(board,x+1,y);
	}
	else if(board[y-1][x+1]=='.') {
		show(board,x+1,y-1);
	}
	else if(board[y-1][x]=='.') {
		show(board,x,y-1);
	}
	else if(board[y][x-1]=='.') {
		show(board,x-1,y);
	}
	else if(board[y+1][x-1]=='.') {
		show(board,x-1,y+1);
	}
	else if(board[y+1][x]=='.') {
		show(board,x,y+1);
	}
	else {
		situation7(board,board_size,board_size-1,0);
	}
}
void situation7(char board[12][12],int board_size,int x,int y) {
	if(board[y][x-1]=='.') {
		show(board,x-1,y);
	}
	else if(board[y+1][x]=='.') {
		show(board,x,y+1);
	}
	else if(board[y+1][x-1]=='.'){
		show(board,x-1,y+1);
	}
	else {
		situation6(board,board_size,x,y);
	}
}
void situation8(char board[12][12],int board_size,int x,int y) {
	if(board[y-1][x]=='.') {
		show(board,x,y-1);
	}
	else if(board[y][x-1]=='.') {
		show(board,x-1,y);
	}
	else if(board[y+1][x-1]=='.') {
		show(board,x-1,y+1);
	}
	else if(board[y+1][x]=='.') {
		show(board,x,y+1);
	}
	else {
		situation6(board,board_size,x,y);
	}
}
void situation9(char board[12][12],int board_size,int x,int y) {
	if(board[y-1][x]=='.') {
		show(board,x,y-1);
	}
	else if(board[y][x-1]=='.') {
		show(board,x-1,y);
	}
	else {
		situation6(board,board_size,x,y);
	}
}
void machine_s_move(char board[12][12],int board_size,int x,int y) {
//DIRECT THE MACHINE WHERE PLAYER1'S FIRST PLACE
	if(x==0 && y==0) {														    //SITUATION1
		situation1(board,board_size,x,y);
	}
	else if(x==0 && y<(board_size-1) && y>0) {										//SITUATION2
		situation2(board,board_size,x,y);
	}
	else if(x==0 && y==(board_size-1)) {										//SITUATION3
		situation3(board,board_size,x,y);
	}
	else if(x<(board_size-1) && y==(board_size-1) && y>0) {							//SITUATION4
		situation4(board,board_size,x,y);
	}
	else if(x<(board_size-1) && y==0 && x>0) {										//SITUATION5
		situation5(board,board_size,x,y);
	}
	else if(x<(board_size-1) && y<(board_size-1) && x>0) {							//SITUATION6
		situation6_2(board,board_size,x,y);
	}
	else if(x==(board_size-1) && y==0) {										//SITUATION7
		situation7(board,board_size,x,y);
	}
	else if(x==(board_size-1) && y<(board_size-1) && y>0) {							//SITUATION8
		situation8(board,board_size,x,y);
	}
	else if(x==(board_size-1) && y==(board_size-1)) {							//SITUATION9
		situation9(board,board_size,x,y);
	}	
}
int two_player_game_mod(char board[12][12],int board_size,int opt1) {
//PLAY THE GAME IF THERE IS A WINNER END THE GAME AND RETURN WHO IS WINNER
	int num,win=-1,flag,checkr=0,player=1,i,k,counter=1;
	int record[12][12];
	char l;
	char control[12][12];
	while(win<0) {
		checkr=0;
		flag=check_is_full(board,board_size);
		if(flag==0) {
			switch(counter%2) {
				case 1:
					cout<<"player1's move:"<<endl;
					while(checkr!=1) {
						cin>>l>>num;
						checkr=check_validity(board,board_size,l,num);					//CHECK IS MOVE VALID
					}
					checkr=0;
					board[num-1][((int)l-65)]='x';
					cout<<"\nAfter player1's move table become:"<<endl;	
					print_board(board,board_size);
					for(i=0;i<board_size;i++) {											//IF THERE IS AN ELEMENT AT THE LEFT AND RIGHT SIDE OF THE BOARD,CHECK IS A WINNER  
						if(board[i][0]=='x') {
							for(k=0;k<board_size;k++) {
								if(board[k][board_size-1]=='x') {
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
					counter+=1;
					break;						
				case 0:
					cout<<"player2's move:"<<endl;
					if(opt1==2) {											//IF PLAYER2 IS MACHINE
						machine_s_move(board,board_size,(int)l-65,num-1);
						checkr=0;
					}
					else {
						while(checkr!=1) {
							cin>>l>>num;
							checkr=check_validity(board,board_size,l,num);		//CHECK IS MOVE VALID
						}
						board[num-1][((int)l-65)]='o';						
					}
					cout<<"\nAfter player2's move table become:"<<endl;
					print_board(board,board_size);
					for(i=0;i<board_size;i++) {
						if(board[0][i]=='o') {
							for(k=0;k<board_size;k++) {
								if(board[board_size-1][k]=='o') {
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
					counter+=1;
					break;				
			}
		}
		else {
			win=3;//TIE
		}
	}
	return win;
}