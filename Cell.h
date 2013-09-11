//CELL CLASS
#include <vector>

#ifndef CELL_H
#define CELL_H

class Cell 
{
	private:
		int value;
		std::vector <int> candidates;
		
	public:
		int getValue();
		std::vector <int> getCandidates();

		void setValue(int);
		void resetCandidates (std::vector <int>);
		bool removeCandidate (int);
		bool candidateExists (int);

		void valueFound (int);
		



};

#endif /* CELL_H */