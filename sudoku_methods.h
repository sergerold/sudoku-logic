#include "Cell.h"

//generic methods
void regenerateCandidates (Cell cell_arr [9][9], int row, int col);
void generateCandidates(Cell cell_arr [9][9]);
bool isValidPlacement (Cell cell_arr [9][9],int row, int col, int possibleVal);

//solve methods

bool hidden_single (Cell cell_arr[9][9]);
bool naked_single (Cell cell_arr[9][9]);

//remove candidates methods