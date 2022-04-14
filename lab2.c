#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#define ADD_MINES 1
#define HIGHLIGHT_MINES 2
#define ALLOWED_CHECKS 2
#define PRINT_FIELD 3
#define EXIT 4

int InputCheck(int lowerLimit)
{
    int number;
    char inputChar = '\n';
    int successInput = scanf("%d%c", &number, &inputChar);
    while (((successInput != ALLOWED_CHECKS) || (inputChar != '\n')) ||
           (number < lowerLimit))
    {
        if (number >= lowerLimit)
        {
            while ((inputChar = getchar()) != '\n');
        }
        printf("Invalid input entered!, enter new input:");
        successInput = scanf("%d%c", &number, &inputChar);
    }
    return number;
}

int main()
{
    int** array = NULL;
    int choice=0;
    int height=10;
    int width=10;
    int freeCells = height * width;


    while (choice != EXIT)
    {
        if (array == NULL)
        {
            array = calloc( sizeof(*array), width );
            for (int i = 0; i < width; i++)
            {
                array[i] = calloc( sizeof(**array), height );
            }
        }

        printf("\n1. Add mines\n");
        printf("2. Highlight number of mines\n");
        printf("3. Print 2D array\n");
        printf("4. Exit\n\n");
        printf("Enter your choice:");
        choice = InputCheck(0);

        switch(choice)
        {
            case ADD_MINES:
                printf("Enter number of mines :");
                int mines = InputCheck(0);
                int resultCells = freeCells - mines;
                srand(time(NULL));
                if (resultCells >= 0)
                {
                    freeCells = resultCells;
                    for (int i = 0; i < mines; i++)
                    {
                        int rndWidth = rand() % width;
                        int rndHeight = rand() % height;
                        if (array[rndWidth][rndHeight] != -1)
                        {
                            array[rndWidth][rndHeight] = -1;
                        }
                        else
                        {
                            --i;
                        }
                    }
                    printf("\n%d mines added!\n", mines);
                    break;
                }
                else
                {
                    printf("Not enough space for mines!\n");
                    break;
                }

            case HIGHLIGHT_MINES:
                for (int j = 0; j < height; j++)
                {
                    for (int i = 0; i < width; i++)
                    {
                        int numberOfMines = 0;
                        if (array[i][j] != -1)
                        {
                            if (j-1 >= 0)
                            {
                                //top
                                if (array[i][j-1] == -1) numberOfMines += 1;
                            }
                            if (j+1 <= height - 1)
                            {
                                //bottom
                                if (array[i][j+1] == -1) numberOfMines += 1;
                            }
                            if (i+1 <= width - 1)
                            {
                                //right
                                if (array[i+1][j] == -1) numberOfMines += 1;
                            }
                            if (i-1 >= 0)
                            {
                                //left
                                if (array[i-1][j] == -1) numberOfMines += 1;
                            }
                        }
                        if (numberOfMines != 0)
                        {
                            array[i][j] = numberOfMines;
                        }
                    }
                }
                printf("Array filled!\n");
                break;
            case PRINT_FIELD:
            {
                int symbolSpace = 2;
                if (array)
                {
                    for(int j=0; j< height; j++)
                    {
                        for(int i=0; i<width; i++)
                        {
                            if (j == 0 & i != 0)
                            {
                                printf("  %*d\t", symbolSpace, array[i][j]);
                            }
                            else
                            {
                                printf("%*d\t", symbolSpace, array[i][j]);
                            }
                        }
                        printf("\n");
                    }
                }
                else
                {
                    printf("Nothing to output, array is empty\n");
                }
                break;
            }

            case EXIT:
            {
                free(array);
                printf("Goodbye!");
                break;
            }

            default:
            {
                printf("Invalid input.\n");
                break;
            }
        }
    }
    return 0;
}
