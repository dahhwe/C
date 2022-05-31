//
// Created by dahhw on 28.05.2022.
//
#include <stdbool.h>
#include "structs.h"

#ifndef LAB7_FUNCTIONS_H
#define LAB7_FUNCTIONS_H

/**
 * \details Добавление русского слова в список
 * @param wordToAdd русское слово
 * @param partOfSpeech часть речи
 * @param wordList список слов
 */
void addRusWord(char *wordToAdd, char *partOfSpeech, EDblLinkedList *wordList);

/**
 * \details Добавление английского слова в список
 * @param wordToAdd английское слово
 * @param partOfSpeech часть речи
 * @param wordList список слов
 */
void addEngWord(char* wordToAdd, char* partOfSpeech, ODblLinkedList* wordList);

/**
 * \details Проверка ввода на число
 * @return True если входное значение является числом
 */
int inputIntCheck(char valueArray[]);

/**
 * \details Дополнительная проверка ввода на число
 * @return True если входное значение является числом
 */
int intInputCheck();

/**
 * \details Удаление списка
 * @param list список
 */
void deleteOdblLinkedList(ODblLinkedList **list);

/**
 * \details
 * Удаление списка
 * @param list список
 */
void deleteEdblLinkedList(EDblLinkedList **list);

/**
 * Связка объектов
   \brief
 * @param eng английское слово
 * @param rus русское слово
 * @return
 */
bool connectNodes(EngNode *eng, RusNode *rus);

/**
 * \details Связь списков
 * \brief
 * @param pList список
 * @param index индекс списка
 * @return
 */
EngNode *getEnglishWord(ODblLinkedList *pList, size_t index);

/**
 * \details вывод русских слов
 * @param pList список слов
 */
void printRusWords(EDblLinkedList *pList);

/**
 * \details вывод английских слов
 * @param pList список слов
 */
void printEngWords(ODblLinkedList *pList);

/**
 * \details Вывод всех слов
 * @param rusWords русские слова
 * @param engWords английские слова
 */
void printAllWords(EDblLinkedList *rusWords, ODblLinkedList *engWords);

/**
 * \details Создание второго списка
 * @return
 */
EDblLinkedList *createEdblLinkedList();

/**
 * \details Создание первого списка
 * @return
 */
ODblLinkedList *createOdblLinkedList();

/**
 * \details динамическое выделение памяти для строки
 * @param string строка
 * @return
 */
char* getDynamicString(char *string);

/**
 * \details получение всех русских слов
 * @param list список
 * @param index индекс слов
 * @return
 */
RusNode* getRussianWord(EDblLinkedList* list, size_t index);

/**
 * \details Вывод меню для выбора вывода данных
 */
void wayToPrintMenu();

/**
 * \details Вывод основного меню
 */
void printMenu();

/**
 * \details меню с дальнейшим выбором метода вывода слов
 * @param rusWords русские слова
 * @param engWords английские слова
 */
void printWords(EDblLinkedList *rusWords, ODblLinkedList *engWords);

/**
 * \details Загрузка объектов в файл
 * @param rusWords русские слова
 * @param engWords английские слова
 */
void loadToFile(EDblLinkedList* rusWords, ODblLinkedList* engWords);


/**
 * Загрузка данных из файла
 */
void downloadFromFile();

/**
 * \details Печать связанных английских слов с русскими
 * @param pNode
 * @param num
 */
void printEngToRus(EngNode *pNode, int num);

/**
 * \details Печать связанных русских слов с английскими
 * @param pNode
 * @param num
 */
void printRusToEng(RusNode *pNode, int num);

#endif //LAB7_FUNCTIONS_H
