
#ifndef SUDOKO_H_
#define SUDOKO_H_


void setColor(int ForgC);
void printPuzzle(void);
int checkBox(int row,int col, int num);
void IsValidPosition(int row,int col);
void user_scan(int row,int col);
int sudoko_complete(void);
int sudoku_solve (void);


#endif // SUDOKO_H_
