//
// Created by dahhw on 28.05.2022.
//
#include <stdbool.h>
#include "structs.h"

#ifndef LAB7_FUNCTIONS_H
#define LAB7_FUNCTIONS_H

/**
 * инвертирование списка
 * @param list
 */
void reverseList();

void addRusWord(char *wordToAdd, char *partOfSpeech, EDblLinkedList *wordList);

void addEngWord(char* wordToAdd, char* partOfSpeech, ODblLinkedList* wordList);

/**
 * Функция массив DblLinkedList
 * @return
 */
void deleteDblLinkedList();


/**
 * Добавления структуры аккумулятора в двусвязный массив
 * @param gapNumber номер аккумулятора для добавления
 * @param list двусвязный массив
 */
void addAccumulator(double price, double voltage, double capacity);

/**
 * Уменьшение двусвязного массива после удаления структуры
 * @param list двусвязный массив
 */
void deleteAcc(size_t gapNumber);





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

char* getString();

void deleteOdblLinkedList(ODblLinkedList **list);

void deleteEdblLinkedList(EDblLinkedList **list);

bool connectNodes(EngNode *eng, RusNode *rus);

EngNode *getEnglishWord(ODblLinkedList *pList, size_t index);

void printRusWords(EDblLinkedList *pList);

void printEngWords(ODblLinkedList *pList);

void printAllWords(EDblLinkedList *rusWords, ODblLinkedList *engWords);

EDblLinkedList *createEdblLinkedList();

ODblLinkedList *createOdblLinkedList();

char* getDynamicString(char *string);


RusNode* getRussianWord(EDblLinkedList* list, size_t index);

/**
 * Вывод меню для выбора вывода данных
 */
void wayToPrintMenu();

/**
 *  Вывод основного меню
 */
void printMenu();

void printWords(EDblLinkedList *rusWords, ODblLinkedList *engWords);

/**
 *  Вывод структур
 */
void printStructs();

/**
 *
 *  Сохранение структур в файл
 */
int save();

#endif //LAB7_FUNCTIONS_H
