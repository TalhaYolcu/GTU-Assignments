#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<sstream>
#include "hex.h"
#include<cstdlib>

using namespace std;

int main() {
	Hex h1(6,2);
	Hex temp3(8,2);
	Hex temp4(9);
	Hex h2(7,1);
	Hex h3;
	Hex h4(8,2);
	Hex h5(9,2);
	temp4=(Hex)8;		//conversion contructor with explicit

	Hex temp2=h1;	//copy constructor will be called
	h1=temp3;		//assignment operator will be called

	
	h1.playGame();
	temp2.playGame();
	temp4.playGame();
	h3.playGame();

	
	if(h1==temp4) {			//compare of marked cells with operator overload=
		cout<<"first games has more marked cells"<<endl;
	}
	if(h1==temp2) {
		cout<<"first games has more marked cells"<<endl;
	}
	if(temp2==h3) {
		cout<<"first games has more marked cells"<<endl;
	}
	cout<<"THERE WAS "<<h1.get_how_many_game()<<"GAMES"<<endl;
}
