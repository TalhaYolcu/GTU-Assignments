#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<sstream>
#include<cstdlib>
#include "AbstractHex.h"

using namespace std;

namespace Talha_Abstract_Hex {
	AbstractHex::AbstractHex(int size,int wuser) :board_size(size) , user(wuser) ,winner(-1){		//CONSTRUCTORS
		no_arg_constructor=false;
	}
	AbstractHex::AbstractHex(int size) :board_size(size), user(2) ,winner(-1){
		no_arg_constructor=false;		
	}
	AbstractHex::AbstractHex() :board_size(6), user(1),winner(-1){	//NO PARAMETER CONSTRUCTOR
		no_arg_constructor=true;		
	}	
	Cell::Cell(){		//CELL CONSTRUCTOR
		s=d;
	}
	bool AbstractHex::get_no_arg_constructor()const{			//IF NO ARGUMENT CONSTRUCTER IS CALLED?
		return no_arg_constructor;
	}
	void AbstractHex::set_move(int move1) {							//SETTER AND GETTER FOR WHO IS GONNA MAKE MOVE
		move=move1;
	}	
	int AbstractHex::get_move()const{
		return move;
	}
	int AbstractHex::get_size()const{					//SETTER AND GETTERS FOR HEX CLASS'S BOARD SIZE
		return board_size;
	}
	void AbstractHex::set_size(int size1) {
		board_size=size1;
	}
	void AbstractHex::set_user(int user1) {				//SETTER AND GETTERS FOR USER MODE 
		user=user1;
	}
	int AbstractHex::get_user()const{
		return user;
	}
	int Cell::get_x()const{		//getter and setter for Cell object's x , y and symbol
		return x;
	}
	int Cell::get_y()const{
		return y;
	}
	void Cell::set_x(int xval) {
		x=xval;
	}
	void Cell::set_y(int yval) {
		y=yval;
	}
	void Cell::set_symbol(symbol sym) {		
		s=sym;
	}
	symbol Cell::get_symbol()const{
		return s;
	}		
	void AbstractHex::set_marked_cell(int marked1) {			//SETTER AND GETTER FOR MARKED CELL
		markedcell=marked1;
	}
	int AbstractHex::get_marked_cell()const{
		return markedcell;
	}
	void AbstractHex::set_x_for_ai(int xai) {			//SETTER AND GETTERS FOR AI'S MOVE THAT TAKES PLAYER1'S MOVES
		xforai=xai;
	}
	void AbstractHex::set_y_for_ai(int yai) {
		yforai=yai;
	}
	int AbstractHex::get_x_for_ai()const{
		return xforai;
	}
	int AbstractHex::get_y_for_ai()const {
		return yforai;
	}
	void AbstractHex::set_win(int win) {			//SETTER-GETTER FOR WINNER
		winner=win;
	}
	int AbstractHex::get_win() {
		return winner;
	}
	void AbstractHex::correct(bool arr[6],int &direction) const{									
	//MAKE A CORRECTION FOR BOOL ARRAY THAT HOLD DIRECTONS
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
	int AbstractHex::check_control_array(symbol ** &control,int xval,int yval,char p) const{
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
	bool AbstractHex::isEnd() {			//NEEDED ISEND FUNCTION
		return !(get_win()==-1);
	}
	int AbstractHex::numberOfMoves() {	//NEEDED NUMBER OF MOVES FUNCTION
		return get_marked_cell();
	}
	void AbstractHex::setSize(int v1,int v2) {		//NEEDED SETSIZE FUNCTION
		set_size(v1);
		reset();
	}
	void AbstractHex::fill_the_empty_board() {			//FILL THE BOARD WITH DOTS
		int i,k;
		try {
			for(i=0;i<get_size();i++) {
				for(k=0;k<get_size();k++) {
					(*this)(k,i).set_symbol(d);
				}
			}			
		}
		catch (outofindex &index) {
			cerr<<"ERROR OCCURED"<<index.what();
		}

	}
	void AbstractHex::fill_the_empty_board(symbol** &control) {			//FILL THE BOARD WITH DOTS 
		//FUNCTION OVERLOADED BECAUSE THIS IS CONTROL ARRAY FOR WINNER SITUATION WE NEED TO MAKE IT EMPTY FOR EVERY CHECK
		int i,k;
		for(i=0;i<get_size();i++) {
			for(k=0;k<get_size();k++) {
				control[i][k]=d;
			}
		}	
	}
	void AbstractHex::print() {
		int i,x,y,k;
		cout<<endl;
		cout<<" ";
		for(i=65;i<get_size()+65;i++) {						//PRINTING OUT THE CURRENT TABLE
			cout<<(char)i<<" ";
		}
		cout<<endl;
		try {
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
					cout<<(char)(*this)(k,x-1).get_symbol()<<" ";				
				}
				cout<<endl;
			}				
		}
		catch (outofindex &index2) {
			cerr<<"ERROR OCCURED"<<index2.what();			
		}			
	}		
	bool AbstractHex::operator==(AbstractHex &other){			//NEEDED OPERATOR OVERLOAD
		bool ret=true;
		int i;
		int k;
		Cell c1;
		Cell c2;
		if(get_size()!=other.get_size()) {
			ret=false;
		}
		else if(get_marked_cell()!=other.get_marked_cell()) {
			ret=false;
		}
		else {
			
			for(i=0;i<get_size();i++) {
				for(k=0;k<get_size();k++) {
					try {
						c1=(*this)(i,k);						
					}
					catch (outofindex &index3) {
						cerr<<"ERROR OCCURED"<<index3.what();			
					}
					try {
						c2=(other)(i,k);
					}
					catch (outofindex &index4) {
						cerr<<"ERROR OCCURED"<<index4.what();			
					}
					if(c1.get_symbol()!=c2.get_symbol()){
						ret=false;
						break;
					}
				}
			}
		}
		return ret;
	}
	int AbstractHex::check_validity(char l, int num){		//CHECKING THE VALIDITY OF THE MOVE IF AI HAS THE MOVE THEN NO NEEDED THE CHECK BECAUSE THE MOVE IS NOT DONE YET
		if(get_user()==2 && get_move()==2) {
			return 1;
		}
		else {
			try {
				if((*this)((int)l-65,num-1).get_symbol()==d) {
					return 1;
				}
				else {
					return 0;
				}				
			}
			catch (outofindex &index4) {
				cerr<<"ERROR OCCURED"<<index4.what();			
			}			
		
		}
	}
	void AbstractHex::reset() {		//NEEDED RESET FUNCTION
		fill_the_empty_board();
	}
	Cell AbstractHex::play() {					//TO PREVENT SO MANY FUNCTION CALL I ASSIGNED VALUES
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
			x=temp.get_x();
			y=temp.get_y();			
		return temp;	
	}
	void AbstractHex::play(Cell &temp) {					//PLAY FUNCTIONS THAT OVERLOADED FIRST ONE TAKES CELL POS. SECOND ONE PLAYS FOR AI
		try {
			(*this)(temp.get_x(),temp.get_y()).set_symbol(temp.get_symbol());
			x=temp.get_x();
			y=temp.get_y();			
		}
		catch (outofindex &index4) {
			cerr<<"ERROR OCCURED"<<index4.what();			
		}
		this->x=temp.get_x();
		this->y=temp.get_y();

	}
	Cell AbstractHex::show(int xval,int yval) {	
	//IMPLEMENT THE MACHINES MOVE AND PRINT MACHINE'S MOVE
		(*this)(xval,yval).set_symbol(u2);
		cout<<(char)(xval+65)<<" "<<yval+1<<endl;
		(*this)(xval,yval).set_x(xval);
		(*this)(xval,yval).set_y(yval);
		return (*this)(xval,yval);
	}
	bool AbstractHex::check_validity_2(int xval,int yval){	
	//CHECK VALIDTY OF THE MACHINES MOVE
		if((*this)(xval,yval).get_symbol()==d) {
			return true;
		}
		else {
			return false;
		}	
	}
	Cell AbstractHex::situation6(int &xval,int &yval) {
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
					if((*this)(k,i).get_symbol()==d) {
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
	Cell AbstractHex::situation1() {
	// I IMPLEMENT 9 FUNCTIONS LIKE THAT FOR MACHINE DEPENDS ON THE DIRECTION AND SITUATION
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		Cell temp;
		if((*this)(xval+1,yval).get_symbol()==d) {
			temp=show(xval+1,yval);	
		}
		else if((*this)(xval,yval+1).get_symbol()==d) {
			temp=show(xval,yval+1);
		}
		else if((*this)(xval,yval+2).get_symbol()==d) {
			temp=show(xval,yval+2);			
		}
		else {
			temp=situation6(xval,yval);
		}
		return temp;
	}
	Cell AbstractHex::situation2() {
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		Cell temp;	
		if((*this)(xval+1,yval).get_symbol()==d) {
			temp=show(xval+1,yval);
		}
		else if((*this)(xval+1,yval-1).get_symbol()==d) {
			temp=show(xval+1,yval-1);
		}
		else if((*this)(xval,yval+1).get_symbol()==d) {
			temp=show(xval,yval+1);
		}
		else if((*this)(xval,yval-1).get_symbol()==d) {
			temp=show(xval,yval-1);
		}
		else {
			temp=situation6(xval,yval);
		}
		return temp;
	}
	Cell AbstractHex::situation3() {
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		Cell temp;
		if((*this)(xval+1,yval).get_symbol()==d) {
			temp=show(xval+1,yval);	
		}
		else if((*this)(xval+1,yval-1).get_symbol()==d) {
			temp=show(xval+1,yval-1);
		}
		else if((*this)(xval+1,yval).get_symbol()==d) {
			temp=show(xval+1,yval);
		}
		else {
			temp=situation6(xval,yval);
		}
		return temp;
	}
	Cell AbstractHex::situation4() {
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		Cell temp;
		if((*this)(xval+1,yval).get_symbol()==d) {
			temp=show(xval+1,yval);
		}
		else if((*this)(xval+1,yval-1).get_symbol()==d) {
			temp=show(xval+1,yval-1);
		}
		else if((*this)(xval,yval-1).get_symbol()==d) {
			temp=show(xval,yval-1);
		}
		else if((*this)(xval-1,yval).get_symbol()==d) {
			temp=show(xval-1,yval);
		}
		else {
			temp=situation6(xval,yval);
		}
		return temp;
	}
	Cell AbstractHex::situation5() {
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		Cell temp;
		if((*this)(xval-1,yval).get_symbol()==d) {
			temp=show(xval-1,yval);
		}
		else if((*this)(xval-1,yval+1).get_symbol()==d) {
			temp=show(xval-1,yval+1);
		}
		else if((*this)(xval+1,yval).get_symbol()==d) {
			temp=show(xval+1,yval);
		}
		else if((*this)(xval,yval+1).get_symbol()==d) {
			temp=show(xval,yval+1);
		}
		else {
			temp=situation6(xval,yval);
		}
		return temp;
	}
	Cell AbstractHex::situation6_2(){
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		Cell temp;
		if((*this)(xval+1,yval).get_symbol()==d) {
			temp=show(xval+1,yval);
		}
		else if((*this)(xval+1,yval-1).get_symbol()==d) {
			temp=show(xval+1,yval-1);
		}
		else if((*this)(xval,yval-1).get_symbol()==d) {
			temp=show(xval,yval-1);
		}
		else if((*this)(xval-1,yval).get_symbol()==d) {
			temp=show(xval-1,yval);
		}
		else if((*this)(xval-1,yval+1).get_symbol()==d) {
			temp=show(xval-1,yval+1);
		}
		else if((*this)(xval,yval+1).get_symbol()==d) {
			temp=show(xval,yval+1);
		}
		else {
			temp=situation7(get_size()-1,0);
		}
		return temp;
	}
	Cell AbstractHex::situation7(int xval,int yval) {
		Cell temp;
		if((*this)(xval-1,yval).get_symbol()==d) {
			temp=show(xval-1,yval);
		}
		else if((*this)(xval,yval+1).get_symbol()==d) {
			temp=show(xval,yval+1);
		}
		else if((*this)(xval-1,yval+1).get_symbol()==d){
			temp=show(xval-1,yval+1);
		}
		else {
			temp=situation6(xval,yval);
		}
		return temp;
	}
	Cell AbstractHex::situation8() {
		int xval=get_y_for_ai();
		int yval=get_x_for_ai();
		Cell temp;
		if((*this)(xval,yval-1).get_symbol()==d) {
			temp=show(xval,yval-1);
		}
		else if((*this)(xval-1,yval).get_symbol()==d) {
			temp=show(xval-1,yval);
		}
		else if((*this)(xval-1,yval+1).get_symbol()==d) {
			temp=show(xval-1,yval+1);
		}
		else if((*this)(xval,yval+1).get_symbol()==d) {
			temp=show(xval,yval+1);
		}
		else {
			temp=situation6(xval,yval);
		}
		return temp;
	}
	Cell AbstractHex::situation9() {
		int xval=get_x_for_ai();
		int yval=get_y_for_ai();
		Cell temp;
		if((*this)(xval,yval-1).get_symbol()==d) {
			temp=show(xval,yval-1);
		}
		else if((*this)(xval-1,yval).get_symbol()==d) {
			temp=show(xval-1,yval);
		}
		else {
			temp=situation6(xval,yval);
		}
		return temp;
	}
	int AbstractHex::is_winner(int xval,int yval,int direction,symbol ** &control,char p) {
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
				(*this)(xval,yval).set_symbol(w1);//MAKE CAPITAL LETTER
				break;
			case 2:
				(*this)(xval,yval).set_symbol(w2);
				break;			
		}
		return ret;
	}
	int AbstractHex::situation(int &xval,int &yval,int &direction,bool arr[7],symbol ** &control,char p) {
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
							if((*this)(xval+1,yval-1).get_symbol()==u1) {
								c=check_control_array(control,xval+1,yval-1,p);
								if(c==0) {							
									control[yval][xval]=u1;	
									ret=is_winner(xval+1,yval-1,1,control,'x');		//1 yönü
								}
							}
						}
						else {
							if((*this)(xval+1,yval-1).get_symbol()==u2) {
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
							if((*this)(xval+1,yval).get_symbol()==u1) {
								c=check_control_array(control,xval+1,yval,p);
								if(c==0) {
									control[yval][xval]=u1;	
									ret=is_winner(xval+1,yval,2,control,'x');
								}
							}
						}
						else {
							if((*this)(xval+1,yval).get_symbol()==u2) {
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
							if((*this)(xval,yval+1).get_symbol()==u1) {
								c=check_control_array(control,xval,yval+1,p);
								if(c==0) {
									control[yval][xval]=u1;	
									ret=is_winner(xval,yval+1,3,control,'x');
								}
							}
						}
						else {
							if((*this)(xval,yval+1).get_symbol()==u2) {
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
							if((*this)(xval-1,yval+1).get_symbol()==u1) {
								c=check_control_array(control,xval-1,yval+1,p);
								if(c==0) {
									control[yval][xval]=u1;	
									ret=is_winner(xval-1,yval+1,4,control,'x');		//4 yönü
								}
							}
						}
						else {
							if((*this)(xval-1,yval+1).get_symbol()==u2) {
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
							if((*this)(xval-1,yval).get_symbol()==u1) {
								c=check_control_array(control,xval-1,yval,p);
								if(c==0) {
									control[yval][xval]=u1;	
									ret=is_winner(xval-1,yval,5,control,'x');		//5 yönü
								}
							}
						}
						else {
							if((*this)(xval-1,yval).get_symbol()==u2) {
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
							if((*this)(xval,yval-1).get_symbol()==u1) {
								c=check_control_array(control,xval,yval-1,p);
								if(c==0) {
									control[yval][xval]=u1;	
									ret=is_winner(xval,yval-1,6,control,'x');		//6 yönü
								}
							}
						}
						else {
							if((*this)(xval,yval-1).get_symbol()==u2) {
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
	void AbstractHex::set_user_counter(int cnt) {				//SETTER AND GETTERS FOR HOW MANY MOVE IS MADE
		usercounter=cnt;
	}
	int AbstractHex::get_user_counter(){
		return usercounter;
	}
	AbstractHex::~AbstractHex() {}			//DESRTUCTOR
	outofindex::outofindex() :runtime_error("OUT OF INDEX TRIED") {}			//EXCEPTIONS
	nolastmove::nolastmove() : runtime_error("THERE IS NO LAST MOVE") {}
	file_error::file_error() : runtime_error("FILE CAN'T OPENED") {}
	wrong_input::wrong_input() : runtime_error("WRONG INPUT ENTERED , TRY AGAIN") {}
	int AbstractHex::readFromFile(string &input2){			//SAVES THE CURRENT GAME INTO THE FILE
		ofstream wr;
		int ret=-1;
		wr.open(input2);
		int i;
		int k;
		if(!wr.is_open()) {
			cerr<<"COULDN'T SAVE IT"<<endl;
			throw file_error();
		}
		else {
			wr<<get_size()<<endl;					//I ENCODED THE FILE AT FIRST THERE IS BOARD SIZE AND THE USER AND WHO IS GONNA DO THE MOVE COMES
			wr<<get_user()<<endl;								//I DID THE SAME THING LIKE IN THE LOAD FUNCTION
			wr<<get_move()<<endl;
			for(i=0;i<get_size();i++) {									//SAVE THE X'S
				for(k=0;k<get_size();k++) {
					if((*this)(k,i).get_symbol()==u1) {
						wr<<"l "<<k<<" "<<i<<endl;
					}
				}
			}
			wr<<"-"<<endl;
			for(i=0;i<get_size();i++) {									//SAVE THE O'S
				for(k=0;k<get_size();k++) {
					if((*this)(k,i).get_symbol()==u2) {
						wr<<"l "<<k<<" "<<i<<endl;
					}
				}
			}
			wr<<"-"<<endl;
			for(i=0;i<get_size();i++) {									//SAVE THE .S
				for(k=0;k<get_size();k++) {
					if((*this)(k,i).get_symbol()==d) {
						wr<<"l "<<k<<" "<<i<<endl;
					}
				}
			}
			wr<<"-"<<endl;
			wr<<usercounter<<endl;
			wr<<"2347"<<endl;						//SIGN FOR END OF FILE
		}
		ret=2;
		wr.close();	
		cout<<"SAVED SUCCESSFULLY"<<endl;
		return ret;
	}
	Cell& AbstractHex::lastMove(){
		if(get_marked_cell()==0) {
			throw nolastmove();
		}
		else {
			
		}
		return (*this)(x,y);
	}	
	bool* globalfun(AbstractHex*ptr3[5],bool* &x,int num) {				//GLOBAL FUNCTIONS
		int i;
		int k;
		int j;
		bool flag=true;
		for(i=0;i<num;i++) {
			flag=true;
			for(k=0;k<(*ptr3[i]).get_size();k++) {
				for(j=0;j<(*ptr3[i]).get_size();j++) {				
					if((*ptr3[i])(j,k).get_symbol()==d) {			//DOT .

					}
					else if((*ptr3[i])(j,k).get_symbol()==u1) {			//x

					}
					else if((*ptr3[i])(j,k).get_symbol()==u2) {			//o
						
					}
					else if((*ptr3[i])(j,k).get_symbol()==w1) {			//X
						
					}
					else if((*ptr3[i])(j,k).get_symbol()==w2) {			//O
						
					}
					else {
						flag=false;
						break;
					}												
				}
			}
			if(flag==false) {
				break;
			}
			x[i]=flag;
		}
		return x;
	}		
}