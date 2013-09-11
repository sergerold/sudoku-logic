#include "sudoku_methods.h"
#define UNASSIGNED 0

#include <iostream>

//HIDDEN SINGLE


bool hidden_single (Cell cell_arr [9][9])
{
	bool progressed = false;
	for (int row=0; row<9; row++)
	{
		for (int col=0;col <9;col++)
		{
			if (!cell_arr [row][col].getValue() == UNASSIGNED)
				continue;
			
			//as only single candidate then must be hidden single --> set this as value
			if (cell_arr[row][col].getCandidates().size() == 1)
			{
				cell_arr[row][col].valueFound (cell_arr[row][col].getCandidates()[0]);
				regenerateCandidates (cell_arr,row,col);
				row = 0, col =-1;
				progressed =true;

			}
		
		}

	}
	return progressed;
}



//NAKED SINGLE

bool naked_single (Cell cell_arr [9][9])
{
	bool progressed = false;
	
	//row check
	
	int unique_row, unique_col;	

	for (int possible_candidate =1; possible_candidate < 10; possible_candidate++)
	{
		for (int row = 0; row < 9; row++)
		{
			int count =0;		
			
			for (int col = 0; col < 9; col++)
			{
				if (count >1)
					break;				

				if (cell_arr[row][col].candidateExists (possible_candidate))
				{
					count++;
					unique_row = row, unique_col = col;
				}
			}
			//naked single found
			if (count ==1)
			{
				cell_arr[unique_row][unique_col].valueFound (possible_candidate);
				regenerateCandidates(cell_arr,unique_row,unique_col);
				progressed = true;
				
			}

		}

	}

	//col check

	for (int possible_candidate =1; possible_candidate < 10; possible_candidate++)
	{
		for (int col = 0; col < 9; col++)
		{
			int count =0;		
			
			for (int row = 0; row < 9; row++)
			{
				if (count >1)
					break;				

				if (cell_arr[row][col].candidateExists (possible_candidate))
				{
					count++;
					unique_row = row, unique_col = col;
				}
			}
			//naked single found
			if (count ==1)
			{
				cell_arr[unique_row][unique_col].valueFound (possible_candidate);
				regenerateCandidates(cell_arr,unique_row,unique_col);
				progressed = true;
				
			}

		}

	}
	
	//mini-box

	for (int possible_candidate =1; possible_candidate < 10; possible_candidate++)
	{

		for (int row=0; row< 9;row= row +3)
    		{

       		 for (int col = 0 ; col <9;col = col+3)
       		 {
				//mini-box
				int count = 0;

          	 		 for (int i_row =row ; i_row < (row+3);i_row++)
          			  {
            	  			  for (int i_col = col;i_col < (col+3);i_col++)
             	  			 {
					

						if (count >1)
							break;				

						if (cell_arr[row][col].candidateExists (possible_candidate))
						{
							count++;
							unique_row = row, unique_col = col;
						}

			
                 			 }

           		 	 }

				//naked single found
				if (count == 1)
				{
					cell_arr[unique_row][unique_col].valueFound (possible_candidate);
					regenerateCandidates(cell_arr,unique_row,unique_col);
					progressed = true;
					
				}

            		}
      		}
  
	}

	


	return progressed;
		

}




















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