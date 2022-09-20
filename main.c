#include <stdio.h>
#include <stdlib.h>
#include "sudoko.h"

int main()
{
    while(1)
    {
        int x;
        printPuzzle();
        x=sudoku_solve();
        if(x==1)
            break;
        system("cls");
    }
    return 0;
}
