#include "Cell.h"


int Cell::getValue()
{

	return value;
}

std::vector <int> Cell::getCandidates()
{

	return candidates;
}

void Cell::setValue (int new_val)
{
	
	value = new_val;
}

void Cell::resetCandidates (std::vector <int> new_candidates)
{
	candidates = new_candidates;

}

bool Cell::removeCandidates (std::vector <int> candidates_to_remove)
{
	bool removed =false;
	for (int it=0;it < candidates.size();it++)
	{
		for (int a=0; a <candidates_to_remove.size();a++)
		{
			if (candidates [it] == candidates_to_remove [a])
				{
					candidates.erase( candidates.begin() + it);
					removed = true;
				}		
		}
	}
	
	return false;

}

bool Cell::candidateExists (int possible_candidate)
{
	for (int it =0; it <candidates.size();it++)
		if (candidates[it] == possible_candidate)
			return true;

	return false;

}

void Cell::valueFound (int val)
{
	setValue (val);
	candidates.clear();

}
