#ifndef MYHEADER_VECTOR
#define MYHEADER_VECTOR

#include "AbstractHex.h"
#include <vector>

namespace Talha_Abstract_Hex {
	class HexVector : public AbstractHex{
		friend class Cell;
		private:
			vector<vector<Cell> > hexCells;
		public:				
			HexVector();					//CONSTRUCTORS
			HexVector(int size,int user);		
			HexVector(int size);
			void playGame();						// ask board_size, user vs user or user vs computer	
			int ready_to_play();											//ASKING LOAD-SAVE OR MOVE		
			int writeToFile(string &filename);			//SAVE							
			Cell& operator()(int x,int y);				//ACCESS TO HEXCELLS
	};	
}
#endif