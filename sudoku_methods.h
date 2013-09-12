#include "Cell.h"

//generic methods
void regenerateCandidates (Cell [9][9], int row, int col);
void generateCandidates(Cell  [9][9]);
bool isValidPlacement (Cell  [9][9],int row, int col, int possibleVal);

//solve methods

bool hidden_single (Cell [9][9]);
bool naked_single (Cell [9][9]);

//remove candidates methods

bool disjoint_subsets (Cell [9][9]);