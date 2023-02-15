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


/*!
 * \brief
 * \param year Год
 * \return Является ли високосным годом
 */
int IsLeapYear(int year);

/*!
 * \brief Проверка если дата верная
 * \param validDate Дата
 * \return 1 При корректной дате
 */
int dateCheck(Date *validDate);

/*!
 * \brief Вывод графического меню программы
 */
void print_menu();

/*!
 * \brief Проверка выбора действия от пользователя
 * \param[in] count значение
 * \return Проверенное значение
 */
int get_variant(int count);

/*!
 * \brief Проверка, что число находится в заданном диапазоне
 * \param[in] lowerLimit Нижний предел
 * \param[in] upperLimit Верхний предел
 * \param[in] numToCheck Число для проверки
 * \return Проверенное значение
 */
bool isInRange(int lowerLimit, int upperLimit, int numToCheck);

/*!
 * \brief Возвращает корректный часовой пояс
 * \return часовой пояс
 */
int getTimezone();

/*!
 * \Brief Точка входа
 * \return Завершение программы
 */
int main();


#endif //SYSTEM1_CHILD_H
