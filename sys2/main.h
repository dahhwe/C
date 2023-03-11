//
// Created by dahhw on 09-Mar-23.
//

#ifndef SYS2_1_MAIN_H
#define SYS2_1_MAIN_H

#endif //SYS2_1_MAIN_H

/**
 *  Получение целого числа в заданном диапазоне
 * @param min Минимальный предел
 * @param max Максимальный предел
 * @return Число в диапазоне
 */
int getInputInRange(int min, int max);

/**
 * Запуск экзамена
 * @param arg Студенты
 * @return
 */
void *student(void *arg);

/**
 * Вывод результатов Экзамена
 * @param maxStudents Студенты
 */
void printResults(int maxStudents);

/**
 * Запуск алгоритма
 * @return
 */
int main();
