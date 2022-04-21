#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REVERSE_POLISH 1
#define LOAD_FROM_FILE 2
#define UPLOAD_TO_FILE 3
#define ALLOWED_CHECKS 2
#define EXIT 4
#define TRUE 1
#define FALSE 0

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

int main()
{
    char* expression = NULL;
    char* formula = NULL;
    char* final = NULL;
    char* LoadToFile = NULL;
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
                    LoadToFile = final;
                }
                else
                {
                    printf("Invalid string was entered!\n");
                }
                break;

            case LOAD_FROM_FILE:
            {
                FILE* file;
                char* fileName = "C:\\Users\\dahhw\\CLionProjects"
                                 "\\untitled\\formula.txt";
                char symbol;

                file = fopen(fileName, "r");
                do {
                    symbol = fgetc(file);
                    printf("%c", symbol);

                } while (symbol != EOF);
                printf("\nloaded!");

                fclose(file);
                break;
            }

            case UPLOAD_TO_FILE:
            {
                FILE *file = NULL;
                char* fileName = "C:\\Users\\dahhw\\CLionProjects"
                                 "\\untitled\\formula.txt";

                file = fopen(fileName, "w");
                if (LoadToFile != NULL)
                {
                    printf("Loading: %s to file\n", LoadToFile);
                    fputs(LoadToFile, file);

                    printf("Formula uploaded!\n");

                    free(formula);
                    free(final);
                    fclose(file);
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
