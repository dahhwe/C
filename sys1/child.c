//
// Created by dahhw on 15.02.2023.
//

#include <stdio.h>
#include <stdbool.h>
#include "structure.h"

#define MAX_YR  9999
#define MIN_YR  1900


int IsLeapYear(int year) {
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}

// Возвращает 1 если дата правильная
int dateCheck(Date *validDate) {
    //проверка дня, месяца и года
    if (validDate->year > MAX_YR ||
        validDate->year < MIN_YR)
        return 0;
    if (validDate->month < 1 || validDate->month > 12)
        return 0;
    if (validDate->day < 1 || validDate->day > 31)
        return 0;
    if (validDate->month == 2) {
        if (IsLeapYear(validDate->year))
            return (validDate->day <= 29);
        else
            return (validDate->day <= 28);
    }
    if (validDate->month == 4 || validDate->month == 6 ||
        validDate->month == 9 || validDate->month == 11)
        return (validDate->day <= 30);
    return 1;
}

void print_menu() {
    printf("\n╭────────────────────────────────────╮\n"
           "│            Главное Меню            │\n"
           "╰────────────────────────────────────╯");
    printf("\n#1 Ввести дату и время\n");
    printf("#2 Узнать дату и время в другом часовом поясе\n");
    printf("#3 Выход\n");
    printf(">");
}

int get_variant(int count) {
    int variant;
    char string[100];
    scanf("%s", string);

    while (sscanf(string, "%d", &variant) != 1 || variant < 1 ||
           variant > count) {
        printf("Incorrect input. Try again: ");
        scanf("%s", string);
    }

    return variant;
}

bool isInRange(int lowerLimit, int upperLimit, int numToCheck) {
    return (lowerLimit <= numToCheck && numToCheck <= upperLimit);
}

int getTimezone() {
    int N;

    printf("\nВведите часовую зону N, в котором необходимо узнать"
           "время и дату в формате, где N число от -12 до +14:\n");
    scanf("%d", &N);
    while (!isInRange(-12, 14, N)) {
        printf("Некорректные значения!\n");
        printf("Введите часовую зону N, в котором необходимо"
               " узнать время и дату в формате, "
               "где N число от -12 до +14:\n");
        scanf("%d", &N);
    }
    return N;
}

#ifndef UNIT_TESTS_LAUNCH

int main(void) {
    int minute = 0, hour = 0, N = 0, timezoneTime, dateValid, choice;
    Date getDate = {0};

    do {
        print_menu();
        choice = get_variant(EXIT);
        switch (choice) {
            case GET_DETAILS:
                printf("Введите дату в формате ДД.ММ.ГГГГ: ");
                scanf("%d.%d.%d", &getDate.day, &getDate.month, &getDate.year);
                dateValid = dateCheck(&getDate);
                while (!dateValid) {
                    printf("Некорректные значения!\n");
                    printf("Введите дату в формате ДД.ММ.ГГГГ: ");
                    scanf("%d.%d.%d", &getDate.day, &getDate.month,
                          &getDate.year);
                    dateValid = dateCheck(&getDate);
                }
                printf("Дата: %02d.%02d.%04d\n", getDate.day, getDate.month,
                       getDate.year);

                printf("Введите местное время в формате ЧЧ.ММ: ");
                scanf("%d.%d", &hour, &minute);
                while (!(isInRange(0, 60, minute) &&
                         (isInRange(1, 23, hour)))) {
                    printf("Некорректные значения!\n");
                    printf("Введите местное время в формате ЧЧ.ММ: ");
                    scanf("%d.%d", &hour, &minute);
                }
                printf("Время %02d:%02d", hour, minute);

                N = getTimezone();
                printf("Часовой пояс: %d", N);
                break;

            case CALCULATE_NEW_DATE:

                printf("Изначальная дата: %02d.%02d.%04d %02d:%02d",
                       getDate.day,
                       getDate.month, getDate.year, hour, minute);

                timezoneTime = hour + N;
                hour = timezoneTime;

                if (timezoneTime > 24) {
                    hour = timezoneTime - 24;
                    if (getDate.day == 28 && getDate.month == 2) {
                        getDate.day = 1;
                    } else {
                        getDate.day += 1;
                    }
                } else if (timezoneTime < 0) {
                    hour = timezoneTime + 24;
                    if (getDate.day == 1 && getDate.month == 3) {
                        getDate.day = 28;
                    } else {
                        getDate.day -= 1;
                    }
                }
                printf("\nНовая дата: %02d.%02d.%04d %02d:%02d", getDate.day,
                       getDate.month, getDate.year, hour, minute);
                break;
        }
    } while (choice != EXIT);
    return 0;
}
#endif
