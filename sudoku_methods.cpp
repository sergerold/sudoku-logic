#include "sudoku_methods.h"
#define UNASSIGNED 0



//HIDDEN SINGLE





























//candidate generation etc




void regenerateCandidates (Cell cell_arr [9][9], int row, int col)
{
	
	//row search
	
	for (int a=0;a <9;a++)
	{
		std::vector <int> temp_candidates;
		if (!cell_arr [row][a].getValue() == UNASSIGNED)
			continue;

		for (int possibleVal = 1; possibleVal <10;possibleVal++)
			if (isValidPlacement (cell_arr,row,a,possibleVal))
				temp_candidates.push_back(possibleVal);
		
		cell_arr[row][a].resetCandidates (temp_candidates);
	}

	//col search

	for (int a=0;a <9;a++)
	{
		std::vector <int> temp_candidates;
		if (!cell_arr [a][col].getValue() == UNASSIGNED)
			continue;

		for (int possibleVal = 1; possibleVal <10;possibleVal++)
			if (isValidPlacement (cell_arr,a,col,possibleVal))
				temp_candidates.push_back(possibleVal);

		cell_arr[a][col].resetCandidates (temp_candidates);
	}

	//box search
	
	for (int a= (row/3)*3; a < ((row/3)*3); a++)
	{
		for (int b= (col/3)*3; b < ((col/3)*3) +3;b++)
		{
			std::vector <int> temp_candidates;
			if (!cell_arr [a][b].getValue() == UNASSIGNED)
				continue;

			for (int possibleVal = 1; possibleVal <10;possibleVal++)
				if (isValidPlacement (cell_arr,a,b,possibleVal))
					temp_candidates.push_back(possibleVal);

			cell_arr[a][b].resetCandidates (temp_candidates);
		}
	}
		
}

void generateCandidates(Cell cell_arr [9][9])
{

	for (int row=0;row<9;row++)
	{
		for (int col=0; col < 9;col++)
		{
			std::vector <int> temp_candidates;

			//check free cell

			if (!cell_arr [row][col].getValue() == UNASSIGNED)
				continue;

			//if not then put every possible value as candidate

			for (int possibleVal=1;possibleVal<10;possibleVal++)
				if (isValidPlacement (cell_arr,row,col,possibleVal))
					temp_candidates.push_back (possibleVal);

			//and add to Cell candidates
			cell_arr[row][col].resetCandidates (temp_candidates);
		}
	}
}

bool isValidPlacement (Cell cell_arr [9][9],int row, int col, int possibleVal)
{
	//check that the possible value is not unassigned 

	if (possibleVal == UNASSIGNED)
		return false;


	//line search

	for (int a = 0; a <9;a++)
		if (cell_arr [row][a].getValue() == possibleVal)
			return false;


	//row search

	for (int a=0;a<9;a++)
		if (cell_arr [a][col].getValue() == possibleVal)
			return false;

		
	//box search

	for (int a= (row/3)*3; a < ((row/3)*3) +3; a++)
	{
		for (int b= (col/3)*3; b < ((col/3)*3) +3;b++)
		{
			if (cell_arr[a][b].getValue() == possibleVal)
				return false;
		}
	}

		
	//else

	return true;
} 