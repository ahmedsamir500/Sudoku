#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include"sudoko.h"
int sudoku[9][9] =
{
    { 0, 5, 2, 4, 9, 6, 1, 3, 0 },
    { 3, 9, 1, 2, 5, 8, 4, 6, 7 },
    { 4, 8, 6, 7, 3, 1, 9, 5, 2 },
    { 8, 3, 9, 0, 7, 5, 2, 1, 4 },
    { 1, 2, 4, 9, 8, 3, 5, 7, 6 },
    { 6, 0, 5, 1, 4, 2, 8, 9, 3 },
    { 5, 4, 7, 0, 2, 9, 6, 8, 1 },
    { 2, 6, 8, 5, 1, 7, 3, 4, 9 },
    { 9, 1, 3, 8, 6, 4, 7, 0, 0 }
};
int sudoku_copy[9][9] =
{
    { 0, 5, 2, 4, 9, 6, 1, 3, 0 },
    { 3, 9, 1, 2, 5, 8, 4, 6, 7 },
    { 4, 8, 6, 7, 3, 1, 9, 5, 2 },
    { 8, 3, 9, 0, 7, 5, 2, 1, 4 },
    { 1, 2, 4, 9, 8, 3, 5, 7, 6 },
    { 6, 0, 5, 1, 4, 2, 8, 9, 3 },
    { 5, 4, 7, 0, 2, 9, 6, 8, 1 },
    { 2, 6, 8, 5, 1, 7, 3, 4, 9 },
    { 9, 1, 3, 8, 6, 4, 7, 0, 0 }
};

void setColor(int ForgC)
{

    //We will need this handle to get the current background attribute
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    //we use csbi for the wAttributes word.
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute
        //, and add in the foreground color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
void printPuzzle(void)
{
    int i, j, a;
    printf("\n");
    printf("   | 0  1  2 | 3  4  5 | 6  7  8 | X\n");
    printf(" ---------------------------------\n");
    for (i = 0, a = 0; i < 9; i++, a++)
    {
        for(j = 0; j < 9; j++)
        {
            if (j == 0)
            {
                printf(" %d |", a);
            }
            else if ((j) % 3 == 0)
            {
                printf("|");
            }
            if(sudoku[i][j])
            {
                if(sudoku_copy[i][j] == 0)
                {
                    setColor(3);
                    printf(" %d ",sudoku[i][j]);
                    setColor(7);
                }
                else
                {
                    setColor(14);
                    printf(" %d ",sudoku[i][j]);
                    setColor(7);
                }
            }
            else
            {
                printf("   ");
            }
            if (j == 8)
            {
                printf("|");
            }
        }
        printf("\n");
        if((i + 1) % 3 == 0)
            printf(" ---------------------------------\n");
    }
    printf(" Y\n");
}

/*fn return 0 if not valid number in the position(row,col) and return 1 if valid number*/
int checkBox(int row,int col, int num)
{
    for(int i=0; i<9; i++)   //check if the number repeated in the row
    {
        if(sudoku[row][i]==num)
        {
            return 0;
        }
    }
    for(int i=0; i<9; i++)  //check if the number repeated in the col
    {
        if(sudoku[i][col]==num)
        {
            return 0;
        }
    }
    int square_row = row - (row%3);
    int square_col = col - (col%3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)  //check if the number repeated in the square matrix
        {
            if (sudoku[i+square_row][j+square_col] == num)
            {
                return 0;
            }
        }
    }
    return 1;
}
void IsValidPosition(int row,int col)
{
    if (sudoku_copy[row][col]!=0)
    {
        setColor(4);
        printf("It's not valid position, try again!");
        setColor(7);
        sudoku_solve();
    }
    else
    {
        user_scan(row,col);
    }
}
void user_scan(int row,int col)
{
    int num;
    setColor(2);
    printf("Enter the number: ");
    setColor(7);
    scanf("%d",&num);
    while(1)
    {
        if(num>9||num<1)
        {
            setColor(4);
            printf("\nplz enter value in the range (1 to 9)!!\n");
            setColor(7);
            scanf("%d",&num);
        }
        else
        {
            break;
        }
    }
    if(checkBox(row,col,num)==1)
    {
        sudoku[row][col]=num;
    }
    else
    {
        setColor(4);
        printf("U can't insert this value in this coordiante (Repeated number), try again!\n");
        setColor(7);
        user_scan(row, col);
    }
}
int sudoko_complete(void)
{
    int l,m,c=0;
    for(m=0; m<=8; m++)
    {
        for(l=0; l<=8; l++)
        {
            if(sudoku[m][l]!=0)
            {
                c++;
            }
        }
    }
    if(c==81)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int sudoku_solve (void)
{
    if(sudoko_complete()==1)
    {
        setColor(5);
        printf("*** Congratulations ***\n*** Great job ***");
        setColor(7);
        return 1;
    }
    int row,col;
    setColor(2);
    printf("\nEnter the position(row,col):\nrow: \n");
    setColor(7);
    scanf("%d",&row);
    setColor(2);
    printf("col: \n");
    setColor(7);
    scanf("%d",&col);
    if(row>=9||row<0||col>=9||col<0)
    {
        setColor(9);
        printf("\nPosition outside the range of 2D_array ");
        setColor(7);
        sudoku_solve();
    }
    IsValidPosition(row,col);
    return 0;
}

