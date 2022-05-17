//
// Created by dahhw on 16.05.2022.
//

#ifndef UNTITLED_FUNCTIONS_H
#define UNTITLED_FUNCTIONS_H

#include "structs.h"

void addAccumulator(char* brand, double price, double voltage, double capacity,
                    accumulator **end_ptr);
/*
 *  Добавления структуры аккумулятора в динамический массив
 */

void deleteGap(int gapNumber, accumulator *gapArray, accumulator **endPtr);
/*
 *  Уменьшение динамического массива после удаления структуры
 */

void filterStructs(accumulator *accArray, accumulator *endPtr);
/*
 *  Фильтрация структур
 */

char *getBrand();

char* getDynamicString();
/*
 *  Динамическое выделение памяти для строки
 */

int inputIntCheck(char valueArray[]);
/*
 *  роверка ввода на число
 */

int intInputCheck();
/*
 *  Дополнительная проверка ввода на число
 */

int load();
/*
 *  Загрузка структур из файла
 */

int meetingsCount(const char* str, const char* substr);
/*
 *  Вывод количества структур
 */

void printMenu();
/*
 *  Вывод основного меню
 */

void printFilterMenu();
/*
 *  Вывод меню фильтрации
 */

void printStructs(accumulator *gapArray, accumulator *endPtr);
/*
 *  Вывод структур
 */

int save(accumulator *st, int n);
/*
 *  Сохранение структур в файл
 */

#endif //UNTITLED_FUNCTIONS_H
