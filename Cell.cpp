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

bool Cell::removeCandidate (int val_to_remove)
{
	for (int it=0;it < candidates.size();it++)
	{
		if (candidates [it] == val_to_remove)
			{
				candidates.erase( candidates.begin() + it);
				return true;
			}		

	}
	
	return false;

}

void Cell::valueFound (int val)
{
	setValue (val);
	candidates.clear();

}