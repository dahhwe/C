#include "structs.h"
#include "functions.h"

#include <stdio.h>
#include <stdlib.h>


int main()
{
    /**
     * Главная функция программы с возможностью вывода информации и
     *  выбора дальнейших действий
     */
    DblLinkedList* list = createDblLinkedList();

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
                puts("Enter Accumulators Price:");
                price = intInputCheck();

                puts("Enter Accumulators Voltage:");
                voltage = intInputCheck();

                puts("Enter Accumulators Capacity:");
                capacity = intInputCheck();

                if (price < 0 || voltage < 0 || capacity < 0)
                {
                    puts("Incorrect values entered!");
                    break;
                }
                else
                {
                    addAccumulator(price, voltage, capacity, list);
                    puts("Accumulator created!");
                }
                break;

            case DELETE_ACC:
                if (list->size != 0)
                {
                    printStructs(list);

                    puts("Enter struct number to delete:");
                    int AccNumber = intInputCheck();

                    deleteAcc(AccNumber, list);
                }
                else
                {
                    puts("No structures present");
                }
                break;

            case PRINT_ALL:
                printStructs(list);
                break;

            case REVERSE_ACC:
                if (list->size != 0)
                {
                    reverseList(list);
                    puts("List has been reversed");
                }
                else
                {
                    puts("No structures present");
                }
                break;

            case SAVE_ACC:
                if (list->size != 0)
                {
                    save(list);
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
                deleteDblLinkedList(&list);
                free(list);
                break;

            default:
                puts("Incorrect value!");
        }

    } while (userChoice != EXIT);
    puts("Goodbye!");
    return 0;
}
