#ifndef MYHEADER_ADAPTERN
#define MYHEADER_ADAPTERN

#include "AbstractHex.h"
namespace Talha_Abstract_Hex {
	template<template<typename...>class T>
	class HexAdapter : public AbstractHex {
		friend class Cell;
		private:
			T<T<Cell>> hexCells;
		public:				
			HexAdapter();
			HexAdapter(int size,int user);
			HexAdapter(int size);
			void playGame();						// ask board_size, user vs user or user vs computer
			int ready_to_play();											//ASKING LOAD-SAVE OR MOVE		
			int writeToFile(string &filename);							
			Cell& operator()(int x,int y);
	};	
}
#endif