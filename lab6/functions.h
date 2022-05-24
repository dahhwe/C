//
// Created by dahhw on 16.05.2022.
//

#include "structs.h"

#ifndef UNTITLED_FUNCTIONS_H
#define UNTITLED_FUNCTIONS_H


/**
 * Инвертирование узла
 * @param node
 */
void swap(Node* node);

/**
 * инвертирование списка
 * @param list
 */
void reverseList(DblLinkedList *list);


/**
 * Получение текучей позиции на списке
* @return позиция
 */
DblLinkedList* createDblLinkedList();

/**
 * Cоздаётся двусвязный массив DblLinkedList
 * @param list двусвязный массив
 */
Node* getNode(DblLinkedList *list, size_t index);

/**
 * Функция массив DblLinkedList
 * @return
 */
void deleteDblLinkedList(DblLinkedList **list);

/**
 * Функция возвращает ввод пользователя для названия бренда
 * @param price Цена аккумулятора
 * @param voltage сила тока аккумулятора
 * @param capacity емкость аккумулятора
 * @param list двусвязный список аккумуляторов
 */
char* getBrand();

/**
 * Добавления структуры аккумулятора в двусвязный массив
 * @param gapNumber номер аккумулятора для добавления
 * @param list двусвязный массив
 */
void addAccumulator(double price, double voltage, double capacity, DblLinkedList *list);

/**
 * Уменьшение двусвязного массива после удаления структуры
 * @param list двусвязный массив
 */
void deleteAcc(size_t gapNumber, DblLinkedList* list);

/**
 * Фильтрация структур
 * @return
 */
void filterStructs(DblLinkedList* list);


/**
 * Динамическое выделение памяти для строки
 * @return строка
 */
char *getBrand();

/*
 *  Динамическое выделение памяти для строки
 */
char* getDynamicString();

/**
 * Проверка ввода на число
 * @return True если входное значение является числом
 */
int inputIntCheck(char valueArray[]);

/**
 * Дополнительная проверка ввода на число
 * @return True если входное значение является числом
 */
int intInputCheck();

/**
 * Загрузка структур из файла
 * @param str строка для загрузки
 * @param substr подстрока
 * @return
 */
int load();

/**
 * Вывод количества структур
 */
int meetingsCount(const char* str, const char* substr);

/**
 *  Вывод основного меню
 */
void printMenu();

/**
 *  Вывод меню фильтрации
 */
void printFilterMenu();

/**
 *  Вывод структур
 */
void printStructs(DblLinkedList* list);

/**
 *
 *  Сохранение структур в файл
 */
int save(DblLinkedList* list);


#endif //UNTITLED_FUNCTIONS_H
