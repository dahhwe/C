//
// Created by dahhw on 15.02.2023.
//

#ifndef SYSTEM1_CHILD_H
#define SYSTEM1_CHILD_H

#include <stdio.h>
#include <stdbool.h>
#include "structure.h"

#define MAX_YR  9999
#define MIN_YR  1900

/**
 * Проверка если високосный год
 * @param year Год
 * @return Является ли високосным годом
 */
int IsLeapYear(int year);

/**
 * Проверка если дата верная
 * @param validDate Дата
 * @return 1 При корректной дате
 */
int dateCheck(Date *validDate);

/**
 * Вывод графического меню программы
 */
void print_menu();

/**
 * Проверка выбора действия от пользователя
 * @param count значение
 * @return Проверенное значение
 */
int get_variant(int count);

/**
 * Проверка, что число находится в заданном диапазоне
 * @param lowerLimit Нижний предел
 * @param upperLimit Верхний предел
 * @param numToCheck Число для проверки
 * @return Проверенное значение
 */
bool isInRange(int lowerLimit, int upperLimit, int numToCheck);

/**
 * Возвращает корректный часовой пояс
 * @return
 */
int getTimezone();

/**
 * Главная функция программы выполняюащя алгоритм
 * @return Завершений программы
 */
int main();


#endif //SYSTEM1_CHILD_H
