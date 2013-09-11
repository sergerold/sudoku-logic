//SUDOKU_CLASS
#include <vector>

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

		void valueFound (int);
		



};