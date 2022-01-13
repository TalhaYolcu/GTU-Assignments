#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<vector>
#include<sstream>
#include "header.h"

vector<int> Hex::hold;				//STATIC VECTOR
int Hex::howmanygame=0;				//STATIC VARIABLE
Hex::Hex(int size,int wuser) 		//FIRST CONSTRUCTOR TAKES 2 PARAMETERS AS SIZE AND USER MODE
:board_size(size) , user(wuser){
	no_arg_constructor=false;
}
Hex::Hex(int size) 					//SECOND CONSTRUCTOR TAKES 1 PARAMETER AS SIZE AND IT ASSIGNS USER MODE BY DEFAULT 2
:board_size(size), user(2) {
	no_arg_constructor=false;
}
Hex::Hex()							//LAST CONSTRUCTOR DOES NOT TAKE ANY PARAMETER AND IT ASSIGNS SIZE AS 6 AND USER MODE 1 BY DEFAULT
:board_size(6), user(1) {
	no_arg_constructor=true;
}
Hex::Cell::Cell() {

}
bool Hex::get_no_arg_constructor() const{			//IF NO ARGUMENT CONSTRUCTER IS CALLED?
	return no_arg_constructor;
}
void Hex::Cell::set_symbol(symbol sym) {		//SETTER AND GETTERS FOR CELL CLASS
	s=sym;
}
symbol Hex::Cell::get_symbol() const{
	return s;
}
inline int Hex::get_size() const{					//SETTER AND GETTERS FOR HEX CLASS'S BOARD SIZE
	return board_size;
}
void Hex::set_size(int size1) {
	board_size=size1;
}
void Hex::set_user(int user1) {				//SETTER AND GETTERS FOR USER MODE AND CURRENT MOVE RIGHT
	user=user1;
}
inline int Hex::get_user() const{
	return user;
}
void Hex::set_move(int move1) {
	move=move1;
}
inline int Hex::get_move() const{
	return move;
}
void Hex::set_x_for_ai(int xai) {			//SETTER AND GETTERS FOR AI'S MOVE THAT TAKES PLAYER1'S MOVES
	xforai=xai;
}
void Hex::set_y_for_ai(int yai) {
	yforai=yai;
}
inline int Hex::get_x_for_ai() const{
	return xforai;
}
inline int Hex::get_y_for_ai() const{
	return yforai;
}
void Hex::play(int yc,int xc) {					//PLAY FUNCTIONS THAT OVERLOADED FIRST ONE TAKES CELL POS. SECOND ONE PLAYS FOR AI
	if(get_move()==1) {
		hexCells[yc][xc].set_symbol(u1);
	}
	else {
		hexCells[yc][xc].set_symbol(u2);
	}
}
void Hex::play() {					//TO PREVENT SO MANY FUNCTION CALL I ASSIGNED VALUES
						//THERE IS README.TXT SO THAT YOU CAN UNDERSTAND WHAT ARE THE SITUATIONS
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	int mysize=get_size();	
	if(xval==0 && yval==0) {														    //SITUATION1
		situation1();
	}
	else if(xval==0 && yval<(mysize-1) && yval>0) {										//SITUATION2
		situation2();
	}
	else if(xval==0 && yval==(mysize-1)) {										//SITUATION3
		situation3();
	}
	else if(xval<(mysize-1) && yval==(mysize-1) && yval>0) {							//SITUATION4
		situation4();
	}
	else if(xval<(mysize-1) && yval==0 && xval>0) {										//SITUATION5
		situation5();
	}
	else if(xval<(mysize-1) && yval<(mysize-1) && xval>0) {							//SITUATION6
		situation6_2();
	}
	else if(xval==(mysize-1) && yval==0) {										//SITUATION7
		situation7(xval,yval);
	}
	else if(xval==(mysize-1) && yval<(mysize-1) && yval>0) {							//SITUATION8
		situation8();
	}
	else if(xval==(mysize-1) && yval==(mysize-1)) {							//SITUATION9
		situation9();
	}	
}
bool Hex::check_validity_2(int xval,int yval) const{	
//CHECK VALIDTY OF THE MACHINES MOVE
	if(hexCells[yval][xval].get_symbol()==d) {
		return true;
	}
	else {
		return false;
	}	
}
void Hex::show(int xval,int yval) {
//IMPLEMENT THE MACHINES MOVE AND PRINT MACHINE'S MOVE
	hexCells[yval][xval].set_symbol(u2);
	cout<<(char)(xval+65)<<" "<<yval+1<<endl;
}
void Hex::situation6(int xval,int yval) {
// IF THERE IS NOT A MOVE THAT MACHINE FIND, MOVE THE MOST CLOSE PLACE
	//IF YOU CAN'T MOVE THE MOST CLOSE PLACE THEN START FROM BEGINNING AND MOVE THE FIRST PLACE THAT YOU FIND
	int i,k;
	double distance=999;
	double temp;
	int mx=-1,my=-1;
	int flag=0;
	for(i=1;i<(get_size()-1);i++) {
		for(k=1;k<(get_size()-1);k++) {
			temp=sqrt((k-xval)*(k-xval)+(i-yval)*(i-yval));
			if(temp<distance) {
				if(check_validity_2(k,i)) {
					mx=k;
					my=i;					
				}	
			}
		}
	}
	if(mx<0) {
		for(i=0;i<get_size();i++) {
			for(k=0;k<get_size();k++) {
				if(hexCells[i][k].get_symbol()==d) {
					show(k,i);
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
		show(mx,my);
	}
}
void Hex::situation1() {
// I IMPLEMENT 9 FUNCTIONS LIKE THAT FOR MACHINE DEPENDS ON THE DIRECTION AND SITUATION
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	if(hexCells[yval][xval+1].get_symbol()==d) {
		show(xval+1,yval);	
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		show(xval,yval+1);
	}
	else if(hexCells[yval+2][xval].get_symbol()==d) {
		show(xval,yval+2);			
	}
	else {
		situation6(xval,yval);
	}
}
void Hex::situation2() {
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();	
	if(hexCells[yval][xval+1].get_symbol()==d) {
		show(xval+1,yval);
	}
	else if(hexCells[yval-1][xval+1].get_symbol()==d) {
		show(xval+1,yval-1);
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		show(xval,yval+1);
	}
	else if(hexCells[yval-1][xval].get_symbol()==d) {
		show(xval,yval-1);
	}
	else {
		situation6(xval,yval);
	}
}
void Hex::situation3() {
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	if(hexCells[yval][xval+1].get_symbol()==d) {
		show(xval+1,yval);	
	}
	else if(hexCells[yval-1][xval+1].get_symbol()==d) {
		show(xval+1,yval-1);
	}
	else if(hexCells[yval][xval+1].get_symbol()==d) {
		show(xval+1,yval);
	}
	else {
		situation6(xval,yval);
	}
}
void Hex::situation4() {
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	if(hexCells[yval][xval+1].get_symbol()==d) {
		show(xval+1,yval);
	}
	else if(hexCells[yval-1][xval+1].get_symbol()==d) {
		show(xval+1,yval-1);
	}
	else if(hexCells[yval-1][xval].get_symbol()==d) {
		show(xval,yval-1);
	}
	else if(hexCells[yval][xval-1].get_symbol()==d) {
		show(xval-1,yval);
	}
	else {
		situation6(xval,yval);
	}
}
void Hex::situation5() {
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	if(hexCells[yval][xval-1].get_symbol()==d) {
		show(xval-1,yval);
	}
	else if(hexCells[yval+1][xval-1].get_symbol()==d) {
		show(xval-1,yval+1);
	}
	else if(hexCells[yval][xval+1].get_symbol()==d) {
		show(xval+1,yval);
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		show(xval,yval+1);
	}
	else {
		situation6(xval,yval);
	}
}
void Hex::situation6_2(){
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	if(hexCells[yval][xval+1].get_symbol()==d) {
		show(xval+1,yval);
	}
	else if(hexCells[yval-1][xval+1].get_symbol()==d) {
		show(xval+1,yval-1);
	}
	else if(hexCells[yval-1][xval].get_symbol()==d) {
		show(xval,yval-1);
	}
	else if(hexCells[yval][xval-1].get_symbol()==d) {
		show(xval-1,yval);
	}
	else if(hexCells[yval+1][xval-1].get_symbol()==d) {
		show(xval-1,yval+1);
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		show(xval,yval+1);
	}
	else {
		situation7(board_size-1,0);
	}
}
void Hex::situation7(int xval,int yval) {
	if(hexCells[yval][xval-1].get_symbol()==d) {
		show(xval-1,yval);
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		show(xval,yval+1);
	}
	else if(hexCells[yval+1][xval-1].get_symbol()==d){
		show(xval-1,yval+1);
	}
	else {
		situation6(xval,yval);
	}
}
void Hex::situation8() {
	int xval=get_y_for_ai();
	int yval=get_x_for_ai();
	if(hexCells[yval-1][xval].get_symbol()==d) {
		show(xval,yval-1);
	}
	else if(hexCells[yval][xval-1].get_symbol()==d) {
		show(xval-1,yval);
	}
	else if(hexCells[yval+1][xval-1].get_symbol()==d) {
		show(xval-1,yval+1);
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		show(xval,yval+1);
	}
	else {
		situation6(xval,yval);
	}
}
void Hex::situation9() {
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	if(hexCells[yval-1][xval].get_symbol()==d) {
		show(xval,yval-1);
	}
	else if(hexCells[yval][xval-1].get_symbol()==d) {
		show(xval-1,yval);
	}
	else {
		situation6(xval,yval);
	}
}
int Hex::save_the_current_game(string input2) const{			//SAVES THE CURRENT GAME INTO THE FILE
	ofstream wr;
	int i;
	int k;
	int ret=-1;
	wr.open(input2);
	if(!wr.is_open()) {
		cerr<<"COULDN'T SAVE IT"<<endl;
	}
	else {
		wr<<get_size()<<endl;					//I ENCODED THE FILE AT FIRST THERE IS BOARD SIZE AND THE USER AND WHO IS GONNA DO THE MOVE COMES
		wr<<get_user()<<endl;								//I DID THE SAME THING LIKE IN THE LOAD FUNCTION
		wr<<get_move()<<endl;
		for(i=0;i<get_size();i++) {									//SAVE THE X'S
			for(k=0;k<get_size();k++) {
				if(hexCells[i][k].get_symbol()==u1) {
					wr<<"l "<<k<<" "<<i<<endl;
				}
			}
		}
		wr<<"-"<<endl;
		for(i=0;i<get_size();i++) {									//SAVE THE O'S
			for(k=0;k<get_size();k++) {
				if(hexCells[i][k].get_symbol()==u2) {
					wr<<"l "<<k<<" "<<i<<endl;
				}
			}
		}
		wr<<"-"<<endl;
		for(i=0;i<get_size();i++) {									//SAVE THE .S
			for(k=0;k<get_size();k++) {
				if(hexCells[i][k].get_symbol()==d) {
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
int Hex::load_a_game(string input2) {				//LOAD A GAME FROM FILE
	ifstream wr2;
	char c;;
	int xval;
	int yval;
	int ret=-1;
	int tempsize;
	int tempuser;
	int tempmove;
	int mycnt=0;	
	wr2.open(input2);
	if(!wr2.is_open()) {
		cerr<<"COULDN'T OPEN THE LOAD FILE"<<endl;			//IF FILE CANNOT OPEN
	}
	else {
		wr2>>tempsize;									//I ENCODED THE FILE AT FIRST THERE IS BOARD SIZE AND THE USER AND WHO IS GONNA DO THE MOVE COMES
		wr2>>tempuser;
		wr2>>tempmove;
		set_size(tempsize);
		set_user(tempuser);
		set_move(tempmove);
		hexCells.resize(get_size()*get_size());
		for(mycnt=0;mycnt<get_size();mycnt++) {
			hexCells[mycnt].resize(get_size());
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
				hexCells[yval][xval].set_symbol(u1);
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
				mycnt+=1;
				wr2>>xval;
				wr2>>yval;
				hexCells[yval][xval].set_symbol(u2);		
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
				hexCells[yval][xval].set_symbol(d);				
			}
		}
		ret=2;//LOADED	
		print_the_board();		
		wr2.close();
		set_marked_cell(mycnt);
		cout<<"LOADED SUCCESSFULLY"<<endl;		
	}
	return ret;
}
int Hex::check_validity(char l, int num) const{		//CHECKING THE VALIDITY OF THE MOVE IF AI HAS THE MOVE THEN NO NEEDED THE CHECK BECAUSE THE MOVE IS NOT DONE YET
	if(get_user()==2 && get_move()==2) {
		return 1;
	}
	else {
		if(hexCells[num-1][(int)l-65].get_symbol()==d) {
			return 1;
		}
		else {
			return 0;
		}		
	}
}
void Hex::correct(bool arr[6],int direction) const{									
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
int Hex::check_control_array(vector < vector < symbol > > control,int xval,int yval,char p) const{
//CHECKING IF WE'VE COME THIS PLACE WHILE WE ARE LOOKING FOR IS THERE A WINNER
	int ret=0;
	if(p=='x') {
		if(control[yval][xval]==u1) {
			ret=1;
		}
	}
	else if(p=='o') {
		if(control[yval][xval]==u2) {
			ret=1;
		}		
	}
	return ret;
}	
int Hex::situation(int xval,int yval,int direction,bool arr[7],vector < vector < symbol > > control,char p) {
//CHECKING DEPEND ON THE DIRECTIONS AND SITUATIONS
//THERE IS TWO TABLE FOR EXPLAINING WHAT IS SITUATION AND DIRECTION IN helper.h
//BOOL ARRAY HOLD THE DIRECTIONS AND P HOLD 'x' or 'o'
	int foo=direction;
	foo+=1;

	int i,ret=-1,c=-1;
	for(i=0;i<6;i++) {
		if(arr[i]==true) {
			switch(i+1) {
				case 1:
					if(p=='x') {
						if(hexCells[yval-1][xval+1].get_symbol()==u1) {
							c=check_control_array(control,xval+1,yval-1,p);
							if(c==0) {							
								control[yval][xval]=u1;	
								ret=is_winner(xval+1,yval-1,1,control,'x');		//1 yönü
							}
						}
					}
					else {
						if(hexCells[yval-1][xval+1].get_symbol()==u2) {
							c=check_control_array(control,xval+1,yval-1,p);
							if(c==0) {							
								control[yval][xval]=u2;	
								ret=is_winner(xval+1,yval-1,1,control,'o');		//1 yönü
							}
						}
					}
					break;
				case 2:																		//2 yönü
					if(p=='x') {
						if(hexCells[yval][xval+1].get_symbol()==u1) {
							c=check_control_array(control,xval+1,yval,p);
							if(c==0) {
								control[yval][xval]=u1;	
								ret=is_winner(xval+1,yval,2,control,'x');
							}
						}
					}
					else {
						if(hexCells[yval][xval+1].get_symbol()==u2) {
							c=check_control_array(control,xval+1,yval,p);
							if(c==0) {
								control[yval][xval]=u2;	
								ret=is_winner(xval+1,yval,2,control,'o');
							}
						}
					}	
					break;		
				case 3:																	//3 yönü
					if(p=='x') {
						if(hexCells[yval+1][xval].get_symbol()==u1) {
							c=check_control_array(control,xval,yval+1,p);
							if(c==0) {
								control[yval][xval]=u1;	
								ret=is_winner(xval,yval+1,3,control,'x');
							}
						}
					}
					else {
						if(hexCells[yval+1][xval].get_symbol()==u2) {
							c=check_control_array(control,xval,yval+1,p);
							if(c==0) {
								control[yval][xval]=u2;	
								ret=is_winner(xval,yval+1,3,control,'o');
							}
						}
					}
					break;
				case 4:
;					if(p=='x') {
						if(hexCells[yval+1][xval-1].get_symbol()==u1) {
							c=check_control_array(control,xval-1,yval+1,p);
							if(c==0) {
								control[yval][xval]=u1;	
								ret=is_winner(xval-1,yval+1,4,control,'x');		//4 yönü
							}
						}
					}
					else {
						if(hexCells[yval+1][xval-1].get_symbol()==u2) {
							c=check_control_array(control,xval-1,yval+1,p);
							if(c==0) {
								control[yval][xval]=u2;	
								ret=is_winner(xval-1,yval+1,4,control,'o');		//4 yönü
							}
						}
					}
					break;
				case 5:
					if(p=='x') {
						if(hexCells[yval][xval-1].get_symbol()==u1) {
							c=check_control_array(control,xval-1,yval,p);
							if(c==0) {
								control[yval][xval]=u1;	
								ret=is_winner(xval-1,yval,5,control,'x');		//5 yönü
							}
						}
					}
					else {
						if(hexCells[yval][xval-1].get_symbol()==u2) {
							c=check_control_array(control,xval-1,yval,p);
							if(c==0) {
								control[yval][xval]=u2;	
								ret=is_winner(xval-1,yval,5,control,'o');		//5 yönü
							}
						}						
					}
					break;								
				case 6:
					if(p=='x') {
						if(hexCells[yval-1][xval].get_symbol()==u1) {
							c=check_control_array(control,xval,yval-1,p);
							if(c==0) {
								control[yval][xval]=u1;	
								ret=is_winner(xval,yval-1,6,control,'x');		//6 yönü
							}
						}
					}
					else {
						if(hexCells[yval-1][xval].get_symbol()==u2) {
							c=check_control_array(control,xval,yval-1,p);
							if(c==0) {
								control[yval][xval]=u2;	
								ret=is_winner(xval,yval-1,6,control,'o');		//6 yönü
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
int Hex::is_winner(int xval,int yval,int direction,vector < vector < symbol > > control,char p) {
	int ret=-1,i;

//IF THERE'S A POSSIBILITY OF THE WINNER CHECK IT DEPEND ON THE SITUATIONS AND DIRECTIONS


	//1 yönü x artar y azalır	//2 yönü x artar y sabit	//3 yönü x sabit y artar	//4 yönü x azalır y artar	//5 yönü x azalır y sabit	//6 yönü x sabit y azalır
	





//HATAAAAAAAAAAAAAAAAAAAAA





	bool arr[7];
	if(p=='x' && xval==(get_size()-1)) {
		ret=1;				
	}
	else if(p=='o' && yval==0) {
		ret=2;				
	}
	else {
		if(xval==0 && yval==0) {							//1
			for(i=1;i<=6;i++) {
				if(i==2) {
					arr[i-1]=true;
				}
				else if(i==3) {
					arr[i-1]=true;					
				}
				else {
					arr[i-1]=false;					
				}
			}
		}
		else if(xval==0 && 0<yval && yval<(get_size()-1)) {			//2
			for(i=1;i<=6;i++) {
				if(i<=3) {
					arr[i-1]=true;
				}
				else if(i==6) {
					arr[i-1]=true;					
				}
				else {
					arr[i-1]=false;					
				}						
			}
		}
		else if(xval==0 && yval==(get_size()-1)) {				//3
			for(i=1;i<=6;i++) {
				if(i<=2) {
					arr[i-1]=true;
				}
				else if(i==6) {
					arr[i-1]=true;					
				}				
				else {
					arr[i-1]=false;
				}			
			}	
		}
		else if(0<xval && xval<(get_size()-1) && yval==(get_size()-1)) {		//4
			for(i=1;i<=6;i++) {
				if(i<=2) {
					arr[i-1]=true;
				}
				else if(i>=5) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;
				}			
			}
		}
		else if(0<xval && xval<(get_size()-1) && yval==0) {				//5
			for(i=1;i<=6;i++) {
				if(i==1) {
					arr[i-1]=false;
				}
				else if(i==6) {
					arr[i-1]=false;					
				}
				else {
					arr[i-1]=true;
				}			
			}
		}
		else if(0<xval && xval<(get_size()-1) && 0<yval && yval<(get_size()-1)) {		//6
			for(i=1;i<=6;i++) {
				arr[i-1]=true;			
			}
		}
		else if(xval==(get_size()-1) && 0<yval && yval<(get_size()-1)) {	//8		
			for(i=1;i<=6;i++) {
				if(i>=3) {
					arr[i-1]=true;
				}
				else {
					arr[i-1]=false;
				}
			}
		}
		else if(xval==(get_size()-1) && yval==(get_size()-1)) {			//9
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
			ret=situation(xval,yval,direction,arr,control,'x');	
		}
		else if(p=='o') {
			ret=situation(xval,yval,direction,arr,control,'o');	
		}								
	}
	switch(ret) {
		case 1:
			hexCells[yval][xval].set_symbol(w1);		//MAKE CAPITAL LETTER
			break;
		case 2:
			hexCells[yval][xval].set_symbol(w2);
			break;			
	}
	return ret;
}
int Hex::ready_to_play() {					//READY TO PLAY ASK FOR USER LOAD SAVE OR MOVE
	string input1;
	string input2;
	stringstream mys1;
	stringstream mys2;
	int win=-1;
	int checkr=0;
	char l;
	int num;
	int i;
	int k;
	int ret=-1;
	int mycnt=0;
	set_marked_cell(0);
	vector < vector < symbol > > control;
	control.resize(get_size()*get_size());
	for(mycnt=0;mycnt<get_size();mycnt++) {				//RESIZE VECTOR
		control[mycnt].resize(get_size());
	}
	string save="SAVE";
	string load="LOAD";	
	set_which_game(howmanygame);						//WHICH GAME ARE WE IN		
	Hex::howmanygame+=1;
	Hex::hold.resize(howmanygame);
	while(win<0) {
		cout<<"MOVE HAS PLAYER"<<get_move()<<"'s"<<endl;
		if(get_user()==2 && get_move()==2) {
			ret=1;
		}
		else {
			cout<<"IF YOU WANT TO SAVE CURRENT GAME,ENTER THIS COMMAND: "<<save<<" and enter the name of the file like FILE.TXT\n";
			cout<<"IF YOU WANT TO LOAD A GAME FROM A FILE, ENTER THIS COMMAND: "<<load<<" and enter the name of the file like FILE.TXT\n";
			cout<<"IF YOU WANT TO MAKE A MOVE YOU CAN DO IT LIKE THAT:A 6\n";
			cin>>input1;
			cin>>input2;
			if(save.compare(input1)==0) {													//CHECKING INPUT FOR LOAD,SAVE OR MOVE
				ret=save_the_current_game(input2);						//SAVE THE GAME
				print_the_board();
			}
			else if(load.compare(input1)==0) {
				ret=load_a_game(input2);								//LOAD THE GAME
			}
			else {
				mys1<<input1;
				mys2<<input2;
				mys2>>num;																	//THIS IS A MOVE INPUT
				mys1>>l;
				mys1=std::stringstream();				//CLEAR THE STRING STREAM OBJECT SO THAT IT CAN READ PROPERLY
				mys2=std::stringstream();
				checkr=check_validity(l,num);					//CHECK IS MOVE VALID
				if(checkr==0) {
					cerr<<"INVALID MOVE"<<endl;
					print_the_board();
					ret=-1;
				}		
				else {
					ret=1;
				}	
			}			
		}
		if(ret==1) {																//IF THERE IS A MOVE INPUT CHECK IS THERE A WINNER
			switch(get_move()) {
				case 1:
					play(num-1,(int)l-65);				//PLAYS FOR 1 STEP
					cout<<"\nAfter player1's move table become:"<<endl;
					set_marked_cell(get_marked_cell()+1);				//RECORD THE MARKED CELL NUMBER
					print_the_board();	
					for(i=0;i<get_size();i++) {											//IF THERE IS AN ELEMENT AT THE LEFT AND RIGHT SIDE OF THE BOARD,CHECK IS A WINNER  
						if(hexCells[i][0].get_symbol()==u1) {
							for(k=0;k<get_size();k++) {
								if(hexCells[k][get_size()-1].get_symbol()==u1) {
									win=is_winner(0,i,0,control,'x');									
									fill_the_empty_board(control);			//CLEAR THE CONTROL ARRAY SO THAT WE CAN CHECK PROPERLY WHO IS WINNER AT THE NEXT MOVE									
									if(win==1) {
										print_the_board();
					
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
					set_move(get_move()+1);
					break;
				case 2:
					if(get_user()==2) {											//IF PLAYER2 IS MACHINE						
						set_x_for_ai((int)l-65);
						set_y_for_ai(num-1);					
						play();						
					}
					else {
						play(num-1,(int)l-65);
					}
					cout<<"\nAfter player2's move table become:"<<endl;	
					set_marked_cell(get_marked_cell()+1);				//RECORD THE MARKED CELL NUMBER
					print_the_board();
					for(i=0;i<board_size;i++) {
						if(hexCells[0][i].get_symbol()==u2) {
							for(k=0;k<board_size;k++) {
								if(hexCells[board_size-1][k].get_symbol()==u2) {
									win=is_winner(k,board_size-1,0,control,'o'); 
									fill_the_empty_board(control);				//CLEAR THE CONTROL ARRAY
									if(win==2) {
										print_the_board();
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
					set_move(get_move()-1);
					break;					
			}
		}
		else {
		}
	}
	cout<<"PLAYER "<<win<<" WON!!"<<endl;
	hold[howmanygame-1]=get_marked_cell();			//RECORD THE MARKED CELL TO THE VECTOR
	return win;
}
void Hex::playGame() {							//INITALIZING THE GAME
	int i;
	int temp;
	if(!get_no_arg_constructor()) {
	}
	else {
		while(1) {
			cout<<"ENTER THE BOARD SIZE (MIN 6)(EXAMPLE:FOR 8X8 type 8)\n";
			cin>>temp;
			if(temp>5) {
				//board_size=temp;
				set_size(temp);
				while(true) {
					cout<<"PLEASE CHOOSE (1)if this a two player game or (2)user versus computer game:"<<endl;
					cin>>temp;
					if(user<=0 || user>2) {
						cerr<<"WRONG OPTION PLS TRY AGAIN:"<<endl;			
					}
					else {
						set_user(temp);
						break;
					}
				}
				break;
			}
			else {
				cerr<<"INVALID COMMAND,TRY AGAIN";	
			}				
		}
	}	
	hexCells.resize(get_size()*get_size());					//SETTINGS FOR VECTOR
	for(i=0;i<get_size();i++) {	
		hexCells[i].resize(get_size());
	}
	fill_the_empty_board();					//FILL THE BOARD WITH .S
	print_the_board();
	set_move(1);
	winner=ready_to_play();
}
void Hex::fill_the_empty_board() {			//FILL THE BOARD WITH DOTS
	int i,k;
	for(i=0;i<(int)hexCells.size();i++) {
		for(k=0;k<(int)hexCells[i].size();k++) {
			hexCells[i][k].set_symbol(d);
		}
	}
}
void Hex::fill_the_empty_board(vector < vector < symbol > > control ) {			//FILL THE BOARD WITH DOTS
	int i,k;
	for(i=0;i<get_size();i++) {
		for(k=0;k<get_size();k++) {
			control[i][k]=d;
		}
	}	
}
void Hex::print_the_board() const{						//DISPLAYS THE CURRENT GAME
	int i,x,y,k;
	cout<<endl;
	cout<<" ";
	for(i=65;i<get_size()+65;i++) {
		cout<<(char)i<<" ";
	}
	cout<<endl;
	for(x=1;x<=get_size();x++) {
		if(x>=10)  {
			cout<<x;
		}
		else {
			cout<<x<<" ";			
		}
		for(y=0;y<x-1;y++) {
			cout<<" ";
		}
		for(k=0;k<get_size();k++) {
			cout<<(char) hexCells[x-1][k].get_symbol()<<" ";				
		}
		cout<<endl;
	}	
}
void Hex::set_marked_cell(int marked1) {			//SETTER AND GETTER FOR MARKED CELL
	markedcell=marked1;
}
inline int Hex::get_marked_cell() const{
	return markedcell;
}
bool Hex::compare(Hex& other) const{	//TRUE FOR IF FIRST GAME HAS MORE MARKED CELLS
	bool ret=false;
	if(get_marked_cell()>other.get_marked_cell()) {
		ret=true;
	}
	return ret;
}
void Hex::set_which_game(int game1) {			//WHICH GAME ARE WE IN
	whichgame=game1;
}
int Hex::get_which_game(){						//WHICH GAME ARE WE IN
	return whichgame;
}