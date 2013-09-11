//SUDOKU PUZZLE
#include "Cell.h"

class Puzzle
{

	private:

	bool solved;
	Cell cell_arr[9][9];
	bool isValidPlacement (Cell [][9],int row, int col, int val);
	void generateCandidates (Cell [][9]);
	void regenerateCandidates(Cell [][9], int row, int col);


	public:

	Puzzle (int [81]);
	Puzzle (int [9][9]);
	void solve();



};