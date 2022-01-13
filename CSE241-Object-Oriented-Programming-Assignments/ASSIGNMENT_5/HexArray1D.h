#ifndef MYHEADER_1DARRAY
#define MYHEADER_1DARRAY

#include "AbstractHex.h"
namespace Talha_Abstract_Hex {
	class HexArray1D : public AbstractHex {
		friend class Cell;
		private:
			Cell*hexCells;
		public:				
			HexArray1D();
			HexArray1D(int size,int user);
			HexArray1D(int size);
				//BIG THREE IS PROVIDED
			HexArray1D(const HexArray1D &other);						//COPY CONSTRUCTOR
			const HexArray1D& operator=(const HexArray1D &other);		//ASSIGNMENT OPERATOR
			~HexArray1D();										//DESTRUCTOR

			void playGame();						// ask board_size, user vs user or user vs computer
			int ready_to_play();											//ASKING LOAD-SAVE OR MOVE		
			int writeToFile(string &filename);							
			Cell& operator()(int x,int y);
	};	
}
#endif