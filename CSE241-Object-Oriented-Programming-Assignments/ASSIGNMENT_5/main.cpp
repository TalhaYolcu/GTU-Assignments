#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<sstream>
#include<cstdlib>
#include "AbstractHex.h"
#include "HexVector.h"
#include "HexArray1D.h"
#include "HexAdapter.h"
#include "HexAdapter.cpp"
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <cstdlib>

using namespace std;
using namespace Talha_Abstract_Hex;

int main() {
	int i;
	
	HexAdapter<vector> v;
	AbstractHex*ptr=new HexArray1D;
	AbstractHex*ptr2=new HexVector;
	AbstractHex*ptr3;
	AbstractHex*ptr4;

	HexArray1D game1;
	HexVector game2;
	HexAdapter<deque> d;

	ptr3=&game1;
	ptr4=&game2;

	ptr->playGame();

	ptr2->playGame();
	game1.playGame();
	game2.playGame();

	AbstractHex*ptr5[5];

	ptr5[0]=ptr;
	ptr5[1]=ptr2;
	ptr5[2]=ptr3;
	ptr5[3]=ptr4;
	ptr5[4]=nullptr;

	v.playGame();	

	bool*x=new bool[5];
	x=globalfun(ptr5,x,4);

	for(i=0;i<5;i++) {
		cout<<x[i]<<endl;
	}
	for(i=0;i<4;i++) {
		cout<<i+1<<". game IS ENDED? :"<<(ptr5[i])->isEnd()<<endl;
	}
	cout<<i<<". game IS ENDED? :"<<d.isEnd()<<endl;

	if(*ptr==*ptr2) {
		cout<<"THESE TWO GAMES ARE THE SAME"<<endl;
	}
	if(*ptr3==v) {
		cout<<"THESE TWO GAMES ARE THE SAME"<<endl;		
	}

	for(i=0;i<4;i++) {
		cout<<"In the "<<i+1<<" game we have "<<(ptr5[i])->numberOfMoves()<<" moves"<<endl;
	}
	for(i=0;i<4;i++) {
		cout<<"Last move of the "<<i+1<<" . game is: "<<(ptr5[i])->lastMove().get_x()<<" "<<(char)(ptr5[i])->lastMove().get_y()+65<<endl;
	}

}