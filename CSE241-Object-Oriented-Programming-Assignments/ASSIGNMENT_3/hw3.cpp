#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<vector>
#include<sstream>
#include "header.h"

using namespace std;

int main() {
	//AT LEAST 5 OBJECTS OF CLASS HEX
	//CONST STATIC INLINE
	//SUBMIT TWO SAVED FILES
	Hex h1(6,1);
	Hex h2(7,1);
	Hex h3;
	Hex h4(8,2);
	Hex h5(9,2);
	h1.playGame();
	cout<<"MARKED CELL'S: "<<h1.how_many_marked_cell(h1.get_which_game())<<endl;	//
	h2.playGame();
	cout<<"MARKED CELL'S: "<<h2.how_many_marked_cell(h2.get_which_game())<<endl;	//
	h3.playGame();
	cout<<"MARKED CELL'S: "<<h3.how_many_marked_cell(h3.get_which_game())<<endl;	//
	h4.playGame();
	cout<<"MARKED CELL'S: "<<h4.how_many_marked_cell(h4.get_which_game())<<endl;	//
	h5.playGame();
	cout<<"MARKED CELL'S: "<<h5.how_many_marked_cell(h5.get_which_game())<<endl;	//
	cout<<endl;
	cout<<h1.compare(h2)<<endl;
	cout<<h3.compare(h3)<<endl;
	cout<<h4.compare(h5)<<endl;
	cout<<h1.compare(h3)<<endl;
	cout<<h3.compare(h5)<<endl;				



	
}