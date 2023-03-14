#include <stdio.h>
#include "windows.h"
#include "structs.h"
#include "functions.h"

/**
 * Демонстрирует использование функций. Он вызывает add()
 * для добавления двух элементов в список, затем вызывает modify()
 * и delete() для изменения и удаления элементов соответственно.
 * Затем он вызывает read() для чтения элемента и печатает его,
 * а затем вызывает calculateProfitLoss() для вычисления и печати общей прибыли и убытка.
 */
int main() {
    SetConsoleOutputCP(CP_UTF8);
    int userChoice;

    do {
        printMenu();
        printf("Введите ваш выбор:\n");
        printf(">");
        userChoice = getVariant(EXIT);
        switch (userChoice) {
            case ADD_COMPANY:
                add();
                break;

            case MODIFY_COMPANY:
                displayAll();
                modify();
                break;

            case DEL_COMPANY:
                displayAll();
                delete();
                break;

            case READ_COMPANY:
                read();
                break;

            case PROFIT_LOSS:
                calculateProfitLoss();
                break;

            case DISPLAY_ALL:
                displayCompanies();
                break;

            case EXIT:
                puts("До свидания!");
                break;

            default:
                puts("Некорректное значение!");
        }

    } while (userChoice != EXIT);
    return 0;
}