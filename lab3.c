#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FALSE 0
#define TRUE 1
#define REVERSE_POLISH 1
#define ALLOWED_CHECKS 2
#define LOAD_FROM_FILE 2
#define UPLOAD_TO_FILE 3
#define EXIT 4

char stack[100];
int top = -1;

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
        if  (isalpha(successInput))
            break;
        printf("Invalid input entered!, enter new input:");
        successInput = scanf("%d%c", &number, &inputChar);
    }
    return number;
}

void push(char x)
{
    stack[++top] = x;
}

char pop()
{
    if(top == -1)
    {
        return -1;
    }
    else
    {
        return stack[top--];
    }
}

int priority(char x)
{
    if(x == '(')
    {
        return 0;
    }
    if(x == '+' || x == '-')
    {
        return 1;
    }
    if(x == '*' || x == '/')
    {
        return 2;
    }
    return 0;
}

void loadToFile(char *formula, char *reversePolish)
{
    FILE *file = NULL;
    char* fileName = "C:\\Users\\dahhw\\CLionProjects"
                     "\\untitled\\formula.txt";

    file = fopen(fileName, "w");
    printf("Loading: %s to file...\n", reversePolish);
    fputs(reversePolish, file);

    printf("Formula uploaded!\n");

    free(formula);
    fclose(file);
    file = NULL;
}

int GetFileSize()
{
    FILE* file;
    int fileSize;
    char* fileName = "C:\\Users\\dahhw\\CLionProjects"
                     "\\untitled\\formula.txt";

    file = fopen(fileName, "r");

    fseek (file, 0, SEEK_END);
    fileSize = ftell(file);
    fclose(file);
    return fileSize;
}


void loadFromFile()
{
    char* fileName = "C:\\Users\\dahhw\\CLionProjects"
                     "\\untitled\\formula.txt";

    char *text = NULL;
    long int size;
    FILE *file = fopen(fileName, "r");

    printf("Loading formula from file...\n");
    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fseek(file, 0, SEEK_SET);

        text = calloc(size + 1, sizeof(char));
        fread(text, 1, size, file);
        text[size] = '\0';
    }
    else
        printf("\0");

    printf("Formula loaded: %s\n", text);
    free(text);
    fclose(file);
}

int main()
{
    char* expression = NULL;
    char* formula = NULL;
    char* final = NULL;
    char* reversePolish = NULL;
    char x;
    char elementToAdd[] = "";
    int choice = 0;
    bool invalidCharFound = FALSE;

    while (choice != EXIT)
    {
        printf("\n1. Convert formula to reverse polish notation\n");
        printf("2. Load Formula from .txt\n");
        printf("3. Upload Formula to .txt\n");
        printf("4. Exit\n\n");
        printf("Enter your choice:");
        choice = InputCheck(0);
        formula = calloc(100, sizeof(char));
        final = calloc(100, sizeof(char));

        switch(choice)
        {
            case REVERSE_POLISH:
                printf("\nEnter the expression: ");
                scanf("%[^\n]%*c", formula);
                if (strpbrk(formula, "_!@#$%^&=\\][‘;.,{}|:”<>?^") ||
                strchr(formula, ' ') != NULL || strlen(formula) == 0)
                {
                    invalidCharFound = TRUE;
                }
                else
                {
                    invalidCharFound = FALSE;
                }

                printf("\n");
                expression = formula;

                if (invalidCharFound == FALSE)
                {
                    while(*expression != '\0')
                    {
                        if(isalnum(*expression))
                        {
                            elementToAdd[0] = *expression;
                            strncat(final, elementToAdd, 1);
                        }
                        else if(*expression == '(')
                        {
                            push(*expression);
                        }
                        else if(*expression == ')')
                        {
                            while((x = pop()) != '(')
                            {
                                elementToAdd[0] = x;
                                strncat(final, elementToAdd, 1);
                            }
                        }
                        else
                        {
                            while(priority(stack[top]) >= priority(*expression))
                            {
                                elementToAdd[0] = pop();
                                strncat(final, elementToAdd, 1);
                            }
                            push(*expression);
                        }
                        expression++;
                    }
                    while(top != -1)
                    {
                        elementToAdd[0] = pop();
                        strncat(final, elementToAdd, 1);
                    }
                    printf("reverse polish notation: %s\n", final);
                    reversePolish = final;
                }
                else
                {
                    printf("Invalid string was entered!\n");
                }
                break;

            case LOAD_FROM_FILE:
            {

                if (GetFileSize() == 0)
                {
                    printf("File is empty");
                    break;
                }
                else
                {
                    loadFromFile();
                    break;
                }
            }

            case UPLOAD_TO_FILE:
            {
                if (reversePolish != NULL)
                {
                    loadToFile(formula, reversePolish);
                    reversePolish = NULL;
                    free(final);
                }
                else
                {
                    printf("Please convert the formula first!");
                }
                break;
            }
            case EXIT:
            {
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
