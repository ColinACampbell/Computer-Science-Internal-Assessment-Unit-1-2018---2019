#include <stdio.h>
#include <stdlib.h>
#include "screens.h"
#define NEWLINE "\n"

// @author Colin A. Campbell

// Entry point for program is here
int main()
{

    int exit = 0; // sentinel value for the while loop
    int option = 0; // value returned to from menu

    printf("---------- Oakland Group of Schools Information System ----------\n\n");

    while ( exit == 0)
    {
        char decision = 0;
        option = menu();
        switch (option)
        {
            case 1 : addClass();
            break;
            case 2 : removeClass();
            break;
            case 3 : getClassRpt();
            break;
            case 4 : mngClass();
            break;
            case 5: break;
        }

        printf("\nWould you like to terminate the program ? y/n ");
        fflush(stdin); // flush the buffer so it can store other values
        scanf("%c",&decision);

        if ( decision == 'y')
            exit = 1; // 1 means true
        else if (decision  == 'n')
            exit = 0; // 0 mean false
        else
        {
            // Ask the user a second time, if the first input for decision is not recognised
            printf("Sorry the input is not regonised, try using lower case, not upper case letters");
            printf("Would you like to terminate the program ? y/n ");
            fflush(stdin);
            scanf("%c",&decision);

            if ( decision == 'y')
                exit = 1; // 1 means true
            else if (decision  == 'n')
                exit = 0;
        }
        printf(NEWLINE);
    }
}
