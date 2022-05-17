#include <stdio.h>
#include <stdlib.h>
#include "ctype.h"
#include "structs.h"
#include "string.h"
#include "functions.h"
#include <windows.h>

char *getBrand()
{
    /*
     *  Функция возвращает ввод пользователя для названия бренда
     */
    char* brand;
    puts("Enter Accumulators Name:");
    gets(brand);
    return brand;
}

int main()
{
    /*
     *  Главная функция программы с возможностью вывода информации и
     *  выбора дальнейших действий
     */

    SetConsoleOutputCP(CP_UTF8);

    size_t accSize = sizeof(accumulator);
    accumulator* accArray = malloc(accSize*sizeof(accArray));
    accumulator *endPointer = accArray;

    char* brand;
    double price=0;
    double voltage;
    double capacity;
    int userChoice;

    do
    {
        printMenu();
        printf("Enter your choice:\n");
        printf(">");
        userChoice = intInputCheck();
        switch (userChoice)
        {
            case ADD_ACC:
                brand = getBrand();

                puts("Enter Accumulators Price:");
                price = intInputCheck();

                puts("Enter Accumulators Voltage:");
                voltage = intInputCheck();

                puts("Enter Accumulators Capacity:");
                capacity = intInputCheck();

                if (price < 0 || voltage < 0 || capacity < 0 || brand[0] == '\0')
                {
                    puts("Incorrect values entered!");
                    break;
                }
                else
                {
                    addAccumulator(brand, price, voltage, capacity, &endPointer);
                    puts("Accumulator created!");
                }
                break;

            case DELETE_ACC:
                if (accArray != endPointer)
                {
                    printStructs(accArray, endPointer);

                    puts("Enter struct number to delete:");
                    int gap_number = intInputCheck();
                    deleteGap(gap_number, accArray, &endPointer);
                }
                else
                {
                    puts("No structures present");
                }
                break;

            case PRINT_ALL:
                printStructs(accArray, endPointer);
                break;
            case FILTER_ACC:
                filterStructs(accArray, endPointer);
                break;

            case SAVE_ACC:
                if (accArray != endPointer)
                {
                    save(accArray, endPointer - accArray);
                    printf("Accumulator has been saved!\n");
                }
                else
                {
                    puts("No structures present");
                }
                break;

            case LOAD_ACC:
                load();
                break;

            case EXIT:
                free(accArray);
                break;

            default:
                puts("Incorrect value!");
        }

    } while (userChoice != EXIT);
    puts("Goodbye!");
    return 0;
}
