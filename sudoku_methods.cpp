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

struct box_identity
{
std::vector <int> candidates_to_remove;
std::vector <int> candidates_to_remain_pos_x;
std::vector <int> candidates_to_remain_pos_y;
						
};


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



//DISJOINT SUBSETS

bool disjoint_subsets (Cell cell_arr [9][9])
{






	bool progressed = false;

	for (int row =0; row < 9;row ++)
	{
		for (int base = 0; base <9;base ++)
		{	
			
			std::vector <int> candidates_to_remove;
			std::vector <int> candidates_to_remain_pos;
			bool identical_candidates = false;

			candidates_to_remain_pos.push_back(base);

			if (!cell_arr [row][base].getValue() == UNASSIGNED)
				continue;
	
			for (int compare = 0; compare <9;compare++)
			{
				if (base == compare)
					continue;

				if (!cell_arr [row][compare].getValue() == UNASSIGNED)
					continue;


				
				
				//identical pairs etc
				if (cell_arr [row][base].getCandidates() == cell_arr[row][compare].getCandidates())
				{
					candidates_to_remove = cell_arr [row][base].getCandidates();
					candidates_to_remain_pos.push_back(compare);
					identical_candidates = true;
				
					

				}
			

			}
			
			//check that identical pairs/triplets found (number of identical candidates must == number of cells)
			if (identical_candidates &&  candidates_to_remove.size() == candidates_to_remain_pos.size())
			{
				for (int remove_pos=0; remove_pos< 9; remove_pos++)
				{	
					bool skip =false;
					//do not remove if one of identical pairs
					for (int it=0;it < candidates_to_remain_pos.size();it++)
						if (candidates_to_remain_pos[it] == remove_pos)
							skip =true;

					if (skip)
						continue;
	
					//remove candidates from other cells
					cell_arr[row][remove_pos].removeCandidates(candidates_to_remove);
					
					progressed =true;
					
				}
	

			}

			

		}

	}

	//col check

	for (int col =0; col < 9;col ++)
	{
		for (int base = 0; base <9;base ++)
		{	
			
			std::vector <int> candidates_to_remove;
			std::vector <int> candidates_to_remain_pos;
			bool identical_candidates = false;

			candidates_to_remain_pos.push_back(base);

			if (!cell_arr [base][col].getValue() == UNASSIGNED)
				continue;
	
			for (int compare = 0; compare <9;compare++)
			{
				if (base == compare)
					continue;

				if (!cell_arr [compare][col].getValue() == UNASSIGNED)
					continue;


				
				
				//identical pairs etc
				if (cell_arr [base][col].getCandidates() == cell_arr[compare][col].getCandidates())
				{
					candidates_to_remove = cell_arr [base][col].getCandidates();
					candidates_to_remain_pos.push_back(compare);
					identical_candidates = true;

				}
			

			}

			if (identical_candidates && candidates_to_remove.size() == candidates_to_remain_pos.size())
			{
				
				for (int remove_pos=0; remove_pos< 9; remove_pos++)
				{	
					bool skip =false;
					//do not remove if one of identical pairs
					for (int it=0;it < candidates_to_remain_pos.size();it++)
						if (candidates_to_remain_pos[it] == remove_pos)
							skip =true;

					if (skip)
						continue;
	
					//remove candidates from other cells
					cell_arr[remove_pos][col].removeCandidates(candidates_to_remove);
					

					progressed =true;
				}
	

			}

			

		}

	}

	
	
	//mini-box check

	for (int row=0; row< 9;row= row +3)
   	 {
        	for (int col = 0 ; col <9;col = col+3)
        	{

          		for (int i_row =row ; i_row < (row+3);i_row++)
            		{
              	  	for (int i_col = col;i_col < (col+3);i_col++)
               		{
					

					bool identical_candidates = false;
					box_identity currentbox;
					
					
					currentbox.candidates_to_remain_pos_x.push_back(i_row);
					currentbox.candidates_to_remain_pos_y.push_back(i_col);

					if (!cell_arr [i_row][i_col].getValue() == UNASSIGNED)
						continue;


					for (int i_row_compare = row; i_row_compare < (row+3);i_row_compare++)
					{
						for (int i_col_compare = col; i_col_compare < (col+3);i_col_compare++)
						{
							if (!cell_arr [i_row_compare][i_col_compare].getValue() == UNASSIGNED)
								continue;

							if (i_row == i_row_compare && i_col == i_col_compare)
								continue;

							if (cell_arr [i_row][i_col].getCandidates() == cell_arr[i_row_compare][i_col_compare].getCandidates())
							{
								currentbox.candidates_to_remove = cell_arr [i_row][i_col].getCandidates();
								currentbox.candidates_to_remain_pos_x.push_back(i_row_compare);
								currentbox.candidates_to_remain_pos_y.push_back(i_col_compare);
								identical_candidates = true;
								

							}



						}
		

					}

					if (identical_candidates && currentbox.candidates_to_remove.size() == currentbox.candidates_to_remain_pos_x.size())
					{
						
						for (int i_row =row ; i_row < (row+3);i_row++)
						{
							for (int i_col = col;i_col < (col+3);i_col++)
							{
								bool skip =false;

								//do not remove if one of identical pairs
								for (int it=0;it < currentbox.candidates_to_remain_pos_x.size();it++)
									if (currentbox.candidates_to_remain_pos_x[it] == i_row && currentbox.candidates_to_remain_pos_y[it] == i_col )
										skip =true;

	
								if (skip)
									continue;
	
								//remove candidates from other cells
								cell_arr[i_row][i_col].removeCandidates(currentbox.candidates_to_remove);
					

								progressed =true;



							}

						}
	

					}
	


					


               	 	}

            		}


              }

    	}
	

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