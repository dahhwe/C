
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define RANDOM 1
#define USERARRAY 2
#define DELREPEATED 3
#define OUTPUT 4
#define CHANGEARRAY 5
#define EXIT 6
#define ALLOWEDCHECKS 2
#define ARRAYMINVALUE 1
#define ELEMMINVALUE -100
#define True 1
#define False 0

int InputCheck(int lowerLimit)
{
    int number;
    char inputChar = '\n';
    int successInput = scanf("%d%c", &number, &inputChar);
    while (((successInput != ALLOWEDCHECKS) || (inputChar != '\n')) ||
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
    int* array = NULL;
    int arraySize;
    int choice;
    bool arrSpaceGiven = False;

    while (choice != EXIT)
    {
        if (arrSpaceGiven == False)
        {
            printf("Enter array size:");
            arraySize = InputCheck(ARRAYMINVALUE);
            array = (int*) calloc(arraySize , sizeof(int));
            arrSpaceGiven = True;
        }

        printf("1. Generate a random array\n");
        printf("2. Create array with user inputs\n");
        printf("3. Delete repeated elements\n");
        printf("4. Output array\n");
        printf("5. Change array size\n");
        printf("6. Exit\n\n");
        printf("Enter your choice:");
        choice = InputCheck(0);

        switch(choice)
        {
            case RANDOM:
            {
                int lower = -10;
                int upper = 10;

                srand(time(0));

                for (int i = 0; i < arraySize; i++)
                {
                    int num = (rand() % (upper - lower + 1)) + lower;
                    printf("array[%d]=%d\n", i, num);
                    array[i] = num;
                }
                printf("Random array has been generated!\n");
                break;
            }

            case USERARRAY:
            {
                for (int i = 0; i < arraySize; i++)
                {
                    printf("a[%d] =", i);
                    array[i] = InputCheck(ELEMMINVALUE);
                }
                printf("array created!\n");
                break;
            }

            case DELREPEATED:
            {
                int i;
                int j;
                int k;
                bool deleted = 0;

                if (array)
                {
                    for (i = 0; i < arraySize; i ++)
                    {
                        for (j = i + 1; j < arraySize; j++)
                        {
                            if (array[i] == array[j])
                            {
                                printf("%d duplicate has been deleted...\n",
                                       array[i]);
                                deleted = 1;
                                for (k = j; k < arraySize - 1; k++)
                                {
                                    array[k] = array[k + 1];
                                }
                                arraySize--;
                                j--;
                            }
                        }
                    }
                }
                if (deleted == False || !array)
                {
                    printf("Nothing to delete\n");
                }
                break;
            }

            case OUTPUT:
            {
                if (array)
                {
                    printf("Your array: ");
                    for (int i = 0; i < arraySize; i++)
                        printf("%d ", array[i]);
                    printf("\n");
                }
                else
                {
                    printf("Nothing to output, array is empty\n");
                }
                break;
            }

            case CHANGEARRAY:
            {
                arrSpaceGiven = False;
                free(array);
                printf("array cleared!\n");
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
