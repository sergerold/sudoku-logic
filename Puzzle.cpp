#include "Puzzle.h"
#include "sudoku_methods.h"

#include <iostream>
#define UNASSIGNED 0

Puzzle::Puzzle (int lin_arr[81])
{
	int count =0;
	for (int row=0;row<9;row++)
	{
		for (int col=0;col<9;col++)
		{
			if (lin_arr[count] >48 && lin_arr[count] <57)
				cell_arr[row][col].setValue(lin_arr[count]-48);

			else
				cell_arr[row][col].setValue (UNASSIGNED);
	
			count++;
		}
	}

}

Puzzle::Puzzle (int multi_arr [9][9])
{
	for (int row=0;row<9;row++)
	{
		for (int col=0;col<9;col++)
		{
			if (multi_arr[row][col] >0 && multi_arr[row][col] <10)
				cell_arr[row][col].setValue(multi_arr[row][col]);

			else
				cell_arr[row][col].setValue (UNASSIGNED);
	
		}
	}

}



void Puzzle::solve()
{
	
	generateCandidates(cell_arr);

	//solve methods

	//eliminate candidates methods

	
}


