#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<sstream>
#include "hex.h"
#include<cstdlib>

int Hex::howmanygame=0;				//STATIC VARIABLE

int Hex::Cell::get_x()	const {		//getter and setter for Cell object's x , y and symbol
	return x;
}
int Hex::Cell::get_y() const{
	return y;
}
void Hex::Cell::set_x(int xval) {
	x=xval;
}
void Hex::Cell::set_y(int yval) {
	y=yval;
}
void Hex::Cell::set_symbol(symbol sym) {		
	s=sym;
}
symbol Hex::Cell::get_symbol() const{
	return s;
}
Hex::Hex(int size,int wuser) 									//FIRST CONSTRUCTOR TAKES 2 PARAMETERS AS SIZE AND USER MODE
:board_size(size) , user(wuser){
	no_arg_constructor=false;
	hexCells=new Cell*[get_size()*get_size()];

	for(int i=0;i<get_size();i++) {
		hexCells[i]=new Cell[get_size()];
	}
	usermoves=new Cell[get_size()*get_size()];
}
Hex::Hex(int size) 	//CONVERSION CONSTRUCTOR		//SECOND CONSTRUCTOR TAKES 1 PARAMETER AS SIZE AND IT ASSIGNS USER MODE BY DEFAULT 2
:board_size(size), user(2) {
	no_arg_constructor=false;
	hexCells=new Cell*[get_size()*get_size()];
	
	for(int i=0;i<get_size();i++) {
		hexCells[i]=new Cell[get_size()];
	}
	usermoves=new Cell[get_size()*get_size()];
}
Hex::Hex()							//LAST CONSTRUCTOR DOES NOT TAKE ANY PARAMETER AND IT ASSIGNS SIZE AS 6 AND USER MODE 1 BY DEFAULT
:board_size(6), user(1) {	
	no_arg_constructor=true;
	hexCells=new Cell*[get_size()*get_size()];
	
	for(int i=0;i<get_size();i++) {
		hexCells[i]=new Cell[get_size()];
	}
	usermoves=new Cell[get_size()*get_size()];
}
Hex::Cell::Cell() {/*INTENTIONALLY EMPTY CELL CONSTRUCTOR*/}
Hex::Hex(const Hex &other){						//COPY CONSTRUCTOR
	cout<<"COPY CONSTRUCTOR"<<endl;	

	set_size(other.get_size());					//COPYING INFO 
	winner=other.winner;
	xforai=other.xforai;
	yforai=other.yforai;
	markedcell=other.markedcell;				//NUMBER OF MARKEDCELLS
	usercounter=other.usercounter;				//NUMBER OF MOVES
	set_user(other.get_user());					//USERVSUSER OR USERVSAI
	set_move(other.get_move());					//WHO IS GONNA MAKE MOVE
	no_arg_constructor=other.no_arg_constructor;
	set_score(other.get_score());					//SCORE

	hexCells=new Cell*[other.get_size()*other.get_size()];			//ALLOCATE SPACE FOR BOARD

	for(int i=0;i<get_size();i++) {
		hexCells[i]=new Cell[get_size()];
	}
	usermoves=new Cell[get_size()*get_size()];
	
	for(int i=0;i<get_size();i++) {							//COPYING THE BOARD
		for(int k=0;k<get_size();k++) {
			hexCells[i][k]=other.hexCells[i][k];
		}
	}
	for(int i=0;i<get_size()*get_size();i++) {
		usermoves[i]=other.usermoves[i];
	}	
}				
const Hex& Hex::operator=(const Hex &other) {		//ASSIGNMENT OPERATOR
	int i=0;
	cerr<<"ASSIGNMENT OPERATOR"<<endl;
	if(this==&other) {

	}
	else {
		for(i=0;i<get_size();i++) {					//DELETEING ISSUES
			delete hexCells[i]; 
		}
		delete[] hexCells;
		delete[] usermoves;

		set_size(other.get_size());					//COPYING INFOS
		winner=other.winner;
		xforai=other.xforai;
		yforai=other.yforai;
		markedcell=other.markedcell;
		usercounter=other.usercounter;
		set_user(other.get_user());
		set_move(other.get_move());
		no_arg_constructor=other.no_arg_constructor;
		set_score(other.get_score());					//SCORE

		hexCells=new Cell*[other.get_size()*other.get_size()];

		for(int i=0;i<get_size();i++) {
			hexCells[i]=new Cell[get_size()];
		}
		usermoves=new Cell[get_size()*get_size()];
		
		for(int i=0;i<get_size();i++) {
			for(int k=0;k<get_size();k++) {
				hexCells[i][k]=other.hexCells[i][k];
			}
		}
		for(int i=0;i<get_size()*get_size();i++) {
			usermoves[i]=other.usermoves[i];
		}			
	}
	return *this;
}
Hex::~Hex() {										//DESTRUCTOR
	for(int i=0;i<get_size();i++){
		delete hexCells[i];
	}
	delete[] hexCells;
	delete usermoves; 
}	
Hex& Hex::operator--() {										//UNDO of USER VS COMPUTER	--OPERATOR	 																		
	cout<<"UNDO1 --(*this) is called"<<endl;
	//sıra kullanıcıya geçmeli
	//ai ın hamlesi geri alınacak 
	//kullanıcının hamlesi geri alınacak hamle kullanıcıda olacak
	hexCells[usermoves[get_user_counter()-1].get_y()][usermoves[get_user_counter()-1].get_x()].set_symbol(d);			//AI HAMLESİ
	hexCells[usermoves[get_user_counter()-2].get_y()][usermoves[get_user_counter()-2].get_x()].set_symbol(d);			//BİZİM HAMLEMİZ
	set_user_counter(get_user_counter()-2);
	set_marked_cell(get_marked_cell()-2);
	return *this;
}
Hex Hex::operator--(int) {										//UNDO of USER VS USER OPERATOR--		
	cout<<"UNDO2 (*this)-- is called"<<endl;
	hexCells[usermoves[get_user_counter()-1].get_y()][usermoves[get_user_counter()-1].get_x()].set_symbol(d);	
	set_user_counter(get_user_counter()-1);
	set_marked_cell(get_marked_cell()-1);
	set_move(get_move()-1);
	return *this;
}
ostream& operator<<(ostream &mys,const Hex &myo){						//STREAM INSERTION AND EXTRACTION OPERATION OVERLOADING
	int i,x,y,k;
	mys<<endl;
	mys<<" ";
	for(i=65;i<myo.get_size()+65;i++) {						//PRINTING OUT THE CURRENT TABLE
		mys<<(char)i<<" ";
	}
	mys<<endl;
	for(x=1;x<=myo.get_size();x++) {
		if(x>=10)  {
			mys<<x;
		}
		else {
			mys<<x<<" ";			
		}
		for(y=0;y<x-1;y++) {
			mys<<" ";
		}
		for(k=0;k<myo.get_size();k++) {
			mys<<(char) myo.hexCells[x-1][k].get_symbol()<<" ";				
		}
		mys<<endl;
	}	
	return mys;
}
bool Hex::operator==(Hex& other) const{				//OPERATOR= OVERLOAD FOR COMPARING TWO HEX OBJECTS 
	bool ret=true;
	if(get_marked_cell()>other.get_marked_cell()) {

	}
	else {
		ret=false;
	}
	return ret;
}
ofstream& operator<<(ofstream &wr,Hex &myo){		//OPERATOR OVERLOAD FOR WRITING FILE(SAVE)
	//SAVE
	int i;
	int k;
	if(!wr.is_open()) {
		cerr<<"COULDN'T SAVE IT"<<endl;
		exit(0);
	}
	else {
		wr<<myo.get_size()<<endl;					//I ENCODED THE FILE AT FIRST THERE IS BOARD SIZE AND THE USER AND WHO IS GONNA DO THE MOVE COMES
		wr<<myo.get_user()<<endl;								//I DID THE SAME THING LIKE IN THE LOAD FUNCTION
		wr<<myo.get_move()<<endl;
		for(i=0;i<myo.get_size();i++) {									//SAVE THE X'S
			for(k=0;k<myo.get_size();k++) {
				if(myo.hexCells[i][k].get_symbol()==u1) {
					wr<<"l "<<k<<" "<<i<<endl;
				}
			}
		}
		wr<<"-"<<endl;
		for(i=0;i<myo.get_size();i++) {									//SAVE THE O'S
			for(k=0;k<myo.get_size();k++) {
				if(myo.hexCells[i][k].get_symbol()==u2) {
					wr<<"l "<<k<<" "<<i<<endl;
				}
			}
		}
		wr<<"-"<<endl;
		for(i=0;i<myo.get_size();i++) {									//SAVE THE .S
			for(k=0;k<myo.get_size();k++) {
				if(myo.hexCells[i][k].get_symbol()==d) {
					wr<<"l "<<k<<" "<<i<<endl;
				}
			}
		}
		wr<<"-"<<endl;
		wr<<myo.usercounter<<endl;
		for(i=0;i<myo.usercounter;i++) {							//SAVE THE ORDER OF MOVES
			wr<<myo.usermoves[i].get_x()<<endl;
			wr<<myo.usermoves[i].get_y()<<endl;
		}
		wr<<"2347"<<endl;						//SIGN FOR END OF FILE
	}
	return wr;	
}
ifstream& operator>>(ifstream &wr2,Hex &myo) {					//OPERATOR OVERLOAD FOR READING FILE(LOAD)
	//LOAD
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

	if(!wr2.is_open()) {
		cerr<<"COULDN'T OPEN THE LOAD FILE"<<endl;			//IF FILE CANNOT OPEN
		exit(0);
	}
	else {
		
		for(mycnt=0;mycnt<myo.get_size();mycnt++) {			//DELETEING THE DATA
			delete myo.hexCells[mycnt];
		}
		delete[] myo.hexCells; 
		delete[] myo.usermoves;
	
		wr2>>tempsize;									//I ENCODED THE FILE AT FIRST THERE IS BOARD SIZE AND THE USER AND WHO IS GONNA DO THE MOVE COMES
		wr2>>tempuser;
		wr2>>tempmove;
		myo.set_size(tempsize);
		myo.set_user(tempuser);
		myo.set_move(tempmove);
		
		Hex::Cell ** temp=nullptr;
		
		temp=new Hex::Cell*[myo.get_size()*myo.get_size()];
		for(mycnt=0;mycnt<myo.get_size();mycnt++) {
			temp[mycnt]=new Hex::Cell[myo.get_size()]; 
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
		myo.set_user_counter(incoming);
		myo.usermoves=new Hex::Cell [myo.get_user_counter()];
		while(true) {
			wr2>>myx;
			if(myx==2347) {										//SIGN FOR END OF FILE
				break;
			}
			wr2>>myy;
			myo.usermoves[i].set_x(myx);
			myo.usermoves[i].set_y(myy);
			i+=1;
		}
		myo.hexCells=temp;
		myo.set_marked_cell(mycnt);
	}
	return wr2;	
}
Hex::Cell Hex::play() {					//TO PREVENT SO MANY FUNCTION CALL I ASSIGNED VALUES
						//THERE IS README.TXT SO THAT YOU CAN UNDERSTAND WHAT ARE THE SITUATIONS
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	int mysize=get_size();	
	Cell temp;
	if(xval==0 && yval==0) {														    //SITUATION1
		temp=situation1();
	}
	else if(xval==0 && yval<(mysize-1) && yval>0) {										//SITUATION2
		temp=situation2();
	}
	else if(xval==0 && yval==(mysize-1)) {										//SITUATION3
		temp=situation3();
	}
	else if(xval<(mysize-1) && yval==(mysize-1) && yval>0) {							//SITUATION4
		temp=situation4();
	}
	else if(xval<(mysize-1) && yval==0 && xval>0) {										//SITUATION5
		temp=situation5();
	}
	else if(xval<(mysize-1) && yval<(mysize-1) && xval>0) {							//SITUATION6
		temp=situation6_2();
	}
	else if(xval==(mysize-1) && yval==0) {										//SITUATION7
		temp=situation7(xval,yval);
	}
	else if(xval==(mysize-1) && yval<(mysize-1) && yval>0) {							//SITUATION8
		temp=situation8();
	}
	else if(xval==(mysize-1) && yval==(mysize-1)) {							//SITUATION9
		temp=situation9();
	}
	return temp;	
}
void Hex::play(Cell &temp) {					//PLAY FUNCTIONS THAT OVERLOADED FIRST ONE TAKES CELL POS. SECOND ONE PLAYS FOR AI
	hexCells[temp.get_y()][temp.get_x()].set_symbol(temp.get_symbol());
}
int Hex::is_winner(int xval,int yval,int direction,symbol ** &control,char p) {
	int ret=-1,i;
//IF THERE'S A POSSIBILITY OF THE WINNER CHECK IT DEPEND ON THE SITUATIONS AND DIRECTIONS
//1 yönü x artar y azalır	//2 yönü x artar y sabit	//3 yönü x sabit y artar	//4 yönü x azalır y artar	//5 yönü x azalır y sabit	//6 yönü x sabit y azalır
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
int Hex::situation(int &xval,int &yval,int &direction,bool arr[7],symbol ** &control,char p) {
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
					if(p=='x') {
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
int Hex::check_control_array(symbol ** &control,int xval,int yval,char p) const{
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
void Hex::correct(bool arr[6],int &direction) const{									
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
void Hex::playGame() {							//INITALIZING THE GAME
	int i;
	int temp;
	int temp2;
	if(!get_no_arg_constructor()) {

	}
	else {
		while(1) {
			cout<<"ENTER THE BOARD SIZE (MIN 6)(EXAMPLE:FOR 8X8 type 8)\n";
			cin>>temp;
			if(temp>5) {			
				while(true) {
					cout<<"PLEASE CHOOSE (1)if this a two player game or (2)user versus computer game:"<<endl;
					cin>>temp2;
					if(temp2<=0 || temp2>2) {
						cerr<<"WRONG OPTION PLS TRY AGAIN:"<<endl;			
					}
					else {
						set_user(temp2);
						break;
					}
				}
				break;
			}
			else {
				cerr<<"INVALID COMMAND,TRY AGAIN";	
			}				
		}
		if(temp==get_size()) {

		}
		else {
			set_size(temp);	
			this->hexCells = new Cell*[get_size()*get_size()];				
			for(i=0;i<get_size();i++) {	
				hexCells[i]=new Cell [get_size()];
			}
			this->usermoves= new Cell[get_size()*get_size()];				
		}				
	}		
	fill_the_empty_board();					//FILL THE BOARD WITH .S
	cout<<*this<<endl;						//PRINT THE BOARD
	set_move(1);							//MOVE HAS PLAYER1'S
	winner=ready_to_play();					//START TO TAKE MOVES
}
void Hex::fill_the_empty_board() {			//FILL THE BOARD WITH DOTS
	int i,k;
	for(i=0;i<get_size();i++) {
		for(k=0;k<get_size();k++) {
			hexCells[i][k].set_symbol(d);
		}
	}
}
void Hex::fill_the_empty_board(symbol** &control ) {			//FILL THE BOARD WITH DOTS 
	//FUNCTION OVERLOADED BECAUSE THIS IS CONTROL ARRAY FOR WINNER SITUATION WE NEED TO MAKE IT EMPTY FOR EVERY CHECK
	int i,k;
	for(i=0;i<get_size();i++) {
		for(k=0;k<get_size();k++) {
			control[i][k]=d;
		}
	}	
}
bool Hex::get_no_arg_constructor() const{			//IF NO ARGUMENT CONSTRUCTER IS CALLED?
	return no_arg_constructor;
}
int Hex::save_the_current_game(string &input2){			//SAVES THE CURRENT GAME INTO THE FILE
	ofstream wr;
	int ret=-1;
	wr.open(input2);
	wr<<*this;
	ret=2;
	wr.close();	
	cout<<"SAVED SUCCESSFULLY"<<endl;
	return ret;
}
int Hex::load_a_game(string &input2) {				//LOAD A GAME FROM FILE
	int ret=-1;
	ifstream wr2;
	wr2.open(input2);
	wr2>>*this;
	ret=2;											//LOADED	
	cout<<*this<<endl;		
	wr2.close();
	cout<<"LOADED SUCCESSFULLY"<<endl;		
	return ret;
}
int Hex::ready_to_play() {					//READY TO PLAY ASK FOR USER LOAD SAVE OR MOVE
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
	string undo="UNDO";	
	Hex::howmanygame+=1;										//STATIC VARIBLE THAT HOLDS HOW MANY GAME IS PLAYED UP TO NOW
	while(win<0) {

		cout<<"MOVE HAS PLAYER"<<get_move()<<"'s"<<endl;
		if(get_user()==2 && get_move()==2) {
			ret=1;
		}
		else {
			cout<<"IF YOU WANT TO SAVE CURRENT GAME,ENTER THIS COMMAND: "<<save<<" and enter the name of the file like FILE.TXT\n";
			cout<<"IF YOU WANT TO LOAD A GAME FROM A FILE, ENTER THIS COMMAND: "<<load<<" and enter the name of the file like FILE.TXT\n";
			cout<<"IF YOU WANT TO MAKE A MOVE YOU CAN DO IT LIKE THAT:A 6\n";
			cout<<"IF YOU WANT TO UNDO YOUR MOVE, JUST ENTER UNDO"<<endl;
			cin>>input1;
			if(input1.compare(undo)==0 && get_user_counter()>1) {
				//UNDO
				if(get_move()==1) {
					--(*this);
				}
				else {
					(*this)--;
				}
				ret=2;
				cout<<*this<<endl;
			}
			else if(input1.compare(undo)==0 && get_user_counter()<=1){
				cerr<<"THERE IS NOTHING TO UNDO"<<endl;
			}
			else {
				cin>>input2;
				if(save.compare(input1)==0) {													//CHECKING INPUT FOR LOAD,SAVE OR MOVE
					ret=save_the_current_game(input2);						//SAVE THE GAME
					cout<<*this<<endl;
				}
				else if(load.compare(input1)==0) {					//LOAD THE GAME	
					checksizeforcontrol=get_size();
					ret=load_a_game(input2);
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
					checkr=check_validity(l,num);					//CHECK IS MOVE VALID
					if(checkr==0) {
						cerr<<"INVALID MOVE"<<endl;
						cout<<*this<<endl;
						ret=-1;
					}		
					else {
						ret=1;
					}	
				}			
			}
		}
		if(ret==1) {																//IF THERE IS A MOVE INPUT CHECK IS THERE A WINNER
			switch(get_move()) {
				case 1:
									//PLAYS FOR 1 STEP
					temp2.set_x((int)l-65);
					temp2.set_y(num-1);
					temp2.set_symbol(u1);
					play(temp2);						
					set_user_moves(num-1,(int)l-65);
					set_user_counter(get_user_counter()+1);		//RECORDING THE MOVE (X,Y,SYMBOL) AND ORDER OF THE MOVE
					
					
					cout<<"\nAfter player1's move table become:"<<endl;
					set_marked_cell(get_marked_cell()+1);				//RECORD THE MARKED CELL NUMBER
					cout<<*this<<endl;	
					set_score(get_move());								//GIVE THE SCORE
					cout<<"Player"<<get_move()<<"'s score is: "<<get_score()<<endl;

					for(i=0;i<get_size();i++) {											//IF THERE IS AN ELEMENT AT THE LEFT AND RIGHT SIDE OF THE BOARD,CHECK IS A WINNER  
						if(hexCells[i][0].get_symbol()==u1) {
							for(k=0;k<get_size();k++) {
								if(hexCells[k][get_size()-1].get_symbol()==u1) {
									win=is_winner(0,i,0,control,'x');									
									fill_the_empty_board(control);			//CLEAR THE CONTROL ARRAY SO THAT WE CAN CHECK PROPERLY WHO IS WINNER AT THE NEXT MOVE									
									if(win==1) {
										cout<<*this<<endl;					
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
						set_user_moves(temp.get_y(),temp.get_x());				//RECORD THE ORDER OF THE MOVE AND X,Y SYMBOL VALUES				
						set_user_counter(get_user_counter()+1);							
					}
					else {
						temp3.set_x((int)l-65);					//RECORD THE ORDER OF THE MOVE AND X,Y SYMBOL VALUES
						temp3.set_y(num-1);
						temp3.set_symbol(u2);
						play(temp3);
						set_user_moves(num-1,(int)l-65);						
						set_user_counter(get_user_counter()+1);												
					}																		
					cout<<"\nAfter player2's move table become:"<<endl;	
					set_marked_cell(get_marked_cell()+1);				//RECORD THE MARKED CELL NUMBER
					cout<<*this<<endl;
					set_score(get_move());
					cout<<"Player"<<get_move()<<"'s score is: "<<get_score()<<endl;
					for(i=0;i<board_size;i++) {										//CHECK IF THERE IS A POSSIBILITY FOR WINNING
						if(hexCells[0][i].get_symbol()==u2) {						//FROM TOP TO BOTTOM
							for(k=0;k<board_size;k++) {
								if(hexCells[board_size-1][k].get_symbol()==u2) {
									win=is_winner(k,board_size-1,0,control,'o'); 
									fill_the_empty_board(control);					//CLEAR THE CONTROL ARRAY
									if(win==2) {
										cout<<*this<<endl;
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
	for(int i=0;i<get_size();i++) {
		delete control[i];
	}
	delete[] control;					//DELETE CONTROL ARRAY
	return win;
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
void Hex::set_move(int move1) {							//SETTER AND GETTER FOR WHO IS GONNA MAKE MOVE
	move=move1;
}
inline int Hex::get_move() const{
	return move;
}
inline int Hex::get_size() const{					//SETTER AND GETTERS FOR HEX CLASS'S BOARD SIZE
	return board_size;
}
void Hex::set_size(int size1) {
	board_size=size1;
}
void Hex::set_user(int user1) {				//SETTER AND GETTERS FOR USER MODE 
	user=user1;
}
inline int Hex::get_user() const{
	return user;
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
Hex::Cell Hex::show(int xval,int yval) {	
//IMPLEMENT THE MACHINES MOVE AND PRINT MACHINE'S MOVE
	hexCells[yval][xval].set_symbol(u2);
	cout<<(char)(xval+65)<<" "<<yval+1<<endl;
	hexCells[yval][xval].set_x(xval);
	hexCells[yval][xval].set_y(yval);
	return hexCells[yval][xval];
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
Hex::Cell Hex::situation6(int &xval,int &yval) {
// IF THERE IS NOT A MOVE THAT MACHINE FIND, MOVE THE MOST CLOSE PLACE
	//IF YOU CAN'T MOVE THE MOST CLOSE PLACE THEN START FROM BEGINNING AND MOVE THE FIRST PLACE THAT YOU FIND
	int i,k;
	double distance=999;
	double temp;
	int mx=-1,my=-1;
	int flag=0;
	Cell temp1;
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
					temp1=show(k,i);
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
		temp1=show(mx,my);
	}
	return temp1;
}
Hex::Cell Hex::situation1() {
// I IMPLEMENT 9 FUNCTIONS LIKE THAT FOR MACHINE DEPENDS ON THE DIRECTION AND SITUATION
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	Cell temp;
	if(hexCells[yval][xval+1].get_symbol()==d) {
		temp=show(xval+1,yval);	
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		temp=show(xval,yval+1);
	}
	else if(hexCells[yval+2][xval].get_symbol()==d) {
		temp=show(xval,yval+2);			
	}
	else {
		temp=situation6(xval,yval);
	}
	return temp;
}
Hex::Cell Hex::situation2() {
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	Cell temp;	
	if(hexCells[yval][xval+1].get_symbol()==d) {
		temp=show(xval+1,yval);
	}
	else if(hexCells[yval-1][xval+1].get_symbol()==d) {
		temp=show(xval+1,yval-1);
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		temp=show(xval,yval+1);
	}
	else if(hexCells[yval-1][xval].get_symbol()==d) {
		temp=show(xval,yval-1);
	}
	else {
		temp=situation6(xval,yval);
	}
	return temp;
}
Hex::Cell Hex::situation3() {
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	Cell temp;
	if(hexCells[yval][xval+1].get_symbol()==d) {
		temp=show(xval+1,yval);	
	}
	else if(hexCells[yval-1][xval+1].get_symbol()==d) {
		temp=show(xval+1,yval-1);
	}
	else if(hexCells[yval][xval+1].get_symbol()==d) {
		temp=show(xval+1,yval);
	}
	else {
		temp=situation6(xval,yval);
	}
	return temp;
}
Hex::Cell Hex::situation4() {
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	Cell temp;
	if(hexCells[yval][xval+1].get_symbol()==d) {
		temp=show(xval+1,yval);
	}
	else if(hexCells[yval-1][xval+1].get_symbol()==d) {
		temp=show(xval+1,yval-1);
	}
	else if(hexCells[yval-1][xval].get_symbol()==d) {
		temp=show(xval,yval-1);
	}
	else if(hexCells[yval][xval-1].get_symbol()==d) {
		temp=show(xval-1,yval);
	}
	else {
		temp=situation6(xval,yval);
	}
	return temp;
}
Hex::Cell Hex::situation5() {
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	Cell temp;
	if(hexCells[yval][xval-1].get_symbol()==d) {
		temp=show(xval-1,yval);
	}
	else if(hexCells[yval+1][xval-1].get_symbol()==d) {
		temp=show(xval-1,yval+1);
	}
	else if(hexCells[yval][xval+1].get_symbol()==d) {
		temp=show(xval+1,yval);
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		temp=show(xval,yval+1);
	}
	else {
		temp=situation6(xval,yval);
	}
	return temp;
}
Hex::Cell Hex::situation6_2(){
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	Cell temp;
	if(hexCells[yval][xval+1].get_symbol()==d) {
		temp=show(xval+1,yval);
	}
	else if(hexCells[yval-1][xval+1].get_symbol()==d) {
		temp=show(xval+1,yval-1);
	}
	else if(hexCells[yval-1][xval].get_symbol()==d) {
		temp=show(xval,yval-1);
	}
	else if(hexCells[yval][xval-1].get_symbol()==d) {
		temp=show(xval-1,yval);
	}
	else if(hexCells[yval+1][xval-1].get_symbol()==d) {
		temp=show(xval-1,yval+1);
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		temp=show(xval,yval+1);
	}
	else {
		temp=situation7(board_size-1,0);
	}
	return temp;
}
Hex::Cell Hex::situation7(int xval,int yval) {
	Cell temp;
	if(hexCells[yval][xval-1].get_symbol()==d) {
		temp=show(xval-1,yval);
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		temp=show(xval,yval+1);
	}
	else if(hexCells[yval+1][xval-1].get_symbol()==d){
		temp=show(xval-1,yval+1);
	}
	else {
		temp=situation6(xval,yval);
	}
	return temp;
}
Hex::Cell Hex::situation8() {
	int xval=get_y_for_ai();
	int yval=get_x_for_ai();
	Cell temp;
	if(hexCells[yval-1][xval].get_symbol()==d) {
		temp=show(xval,yval-1);
	}
	else if(hexCells[yval][xval-1].get_symbol()==d) {
		temp=show(xval-1,yval);
	}
	else if(hexCells[yval+1][xval-1].get_symbol()==d) {
		temp=show(xval-1,yval+1);
	}
	else if(hexCells[yval+1][xval].get_symbol()==d) {
		temp=show(xval,yval+1);
	}
	else {
		temp=situation6(xval,yval);
	}
	return temp;
}
Hex::Cell Hex::situation9() {
	int xval=get_x_for_ai();
	int yval=get_y_for_ai();
	Cell temp;
	if(hexCells[yval-1][xval].get_symbol()==d) {
		temp=show(xval,yval-1);
	}
	else if(hexCells[yval][xval-1].get_symbol()==d) {
		temp=show(xval-1,yval);
	}
	else {
		temp=situation6(xval,yval);
	}
	return temp;
}
void Hex::set_marked_cell(int marked1) {			//SETTER AND GETTER FOR MARKED CELL
	markedcell=marked1;
}
inline int Hex::get_marked_cell() const{
	return markedcell;
}
void Hex::set_user_counter(int cnt) {				//SETTER AND GETTERS FOR HOW MANY MOVE IS MADE
	usercounter=cnt;
}
int Hex::get_user_counter() const{
	return usercounter;
}
Hex::Cell& Hex::get_user_moves() const{
	return usermoves[get_user_counter()];
}
void Hex::set_user_moves(int y,int x) {			//TAKE X AND Y OF MOVE AND RECORD THE ARRAY THAT HOLD THE WHOLE MOVES
	usermoves[get_user_counter()].set_x(x);
	usermoves[get_user_counter()].set_y(y);
}
void Hex::set_score(int mymove) {					//SET THE WHAT IS SCORE
	int count=0;
	for(int i=0;i<get_size()-1;i++) {
		for(int k=0;k<get_size()-1;k++) {
			switch(mymove) {
				case 1:
					if(hexCells[i][k+1].get_symbol()==u1) {			//IF WE HAVE AN X AT THE LEFT THEN WE HAVE SCORE 
						count+=1;
					}
				break;
				case 2:
					if(hexCells[i+1][k].get_symbol()==u2) {			//IF WE HAVE AN O AT THE BOTTOM THEN WE HAVE SCORE
						count+=1;
					}
				break;
			}
		}
	}
	this->score=count+1;					
}
int Hex::get_score() const{				//RETURN THE SCORE
	return score;
}