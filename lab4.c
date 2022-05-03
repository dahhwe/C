#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>

#define MIN_MATRIX_VAL 1
#define DEFINE_MATRIX 1
#define MANDELBROT_VAL 2
#define ALLOWED_CHECKS 2
#define PRINT_MATRIX 3
#define EXIT 4


void print_menu() {
    printf("\n1. Define matrix\n");
    printf("2. Vectorize Mandelbrot set in a matrix\n");
    printf("3. Print the matrix\n");
    printf("4. Exit\n");
    printf(">");
}

int get_variant(int count) {
    int variant;
    char string[100];
    scanf("%s", string);

    while (sscanf(string, "%d", &variant) != 1 || variant < 1 || variant > count)
    {
        printf("Incorrect input. Try again: ");
        scanf("%s", string);
    }

    return variant;
}

int getValidMatrixInput()
{
    int number;
    char inputChar = '\n';
    int successInput = scanf("%d%c", &number, &inputChar);
    while (((successInput != ALLOWED_CHECKS) || (inputChar != '\n')) ||
           (number < MIN_MATRIX_VAL))
    {
        if (number >= MIN_MATRIX_VAL)
        {
            while ((inputChar = getchar()) != '\n');
        }
        if  (isalpha(successInput))
            break;
        printf("Invalid input entered!, enter new input:");
        successInput = scanf("%d%c", &number, &inputChar);
    }
    return number;
}

int** getMatrix(int width, int height)
{
    int** array = NULL;
    printf("width: %d, height: %d\n", width, height);
    array = calloc( sizeof(*array), width );
    for (int i = 0; i < width; i++)
    {
        array[i] = calloc( sizeof(**array), height );
    }
    return array;
}

void printMatrix(char **array, int width, int height)
{
    int spaceSymbol = 2;
    for(int j=0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            printf("%*d\t", spaceSymbol, array[i][j]);
        }
        printf("\n");
    }
}

int getMandelbrotValues(int x, int c, int id)
{
    if (id == 0)
        return x*x+c;
    else if (c == 0)
        return c;
    else
        return getMandelbrotValues(x, c, id-1);
}

void mandelbrotSet(char **matrix, int width, int height)
{
    int mandelbrotVal = 0;
    int midPointX = width/2;
    int midPointY = height/2;

    printf("middle value has index: %d,%d\n ", midPointX, midPointY);

    //matrix[width/2][height/2] = 0;
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            int id = (midPointX-midPointY)*(midPointX-midPointY);
            if (i == midPointX)
            {
                mandelbrotVal = midPointX - j;
                matrix[i][j] = getMandelbrotValues(mandelbrotVal, mandelbrotVal, id);
            }
            else
            {
                mandelbrotVal = i - midPointY + midPointX - j;
                matrix[i][j] = getMandelbrotValues(mandelbrotVal, mandelbrotVal, id);
            }
            printf("%*d\t", 2, matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int variant;
    char** array = NULL;
    int width=0;
    int height=0;
    do
    {
        print_menu();
        variant = get_variant(EXIT);

        switch (variant)
        {
            case DEFINE_MATRIX:
                printf("Enter the width:");
                width = getValidMatrixInput();

                printf("Enter the height:");
                height = getValidMatrixInput();

                array = getMatrix(width, height);
                printf("Matrix defined!");
                break;

            case MANDELBROT_VAL:
                if (array)
                {
                    mandelbrotSet(array, width, height);
                }
                else
                {
                    printf("Matrix is not set!\n");
                }
                break;

            case PRINT_MATRIX:
                if (array)
                {
                    printMatrix(array, width, height);
                }
                else
                {
                    printf("Matrix is not set!\n");
                }
                break;
        }
    } while (variant != EXIT);
    return 0;
}
