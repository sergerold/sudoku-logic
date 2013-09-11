//SUDOKU PUZZLE
#include "Cell.h"

class Puzzle
{

	private:

	bool solved;
	Cell cell_arr[9][9];


	public:

	Puzzle (int [81]);
	Puzzle (int [9][9]);
	void solve();

	void print ();



};