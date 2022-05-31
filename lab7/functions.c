//
// Created by dahhw on 28.05.2022.
//

#include "functions.h"
#include "structs.h"
#include "stdbool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <intrin.h>


#define MAX_INPUT_ARRAY_LEN 100


void deleteOdblLinkedList(ODblLinkedList **list)
{
    EngNode *tmp = (*list)->head;
    EngNode *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp->connections);
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void deleteEdblLinkedList(EDblLinkedList** list)
{
    RusNode* tmp = (*list)->head;
    RusNode* next = NULL;
    while (tmp)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

bool connectNodes(EngNode *eng, RusNode *rus)
{
    for (int i = 0; i < eng->connSize; i++)
    {
        if (eng->connections[i] == rus)
        {
            puts("Relation has already been made!");
            return false;
        }
    }
    eng->connections[eng->connSize++] = rus;
    rus->connections[rus->connSize++] = eng;
    return true;
}

EngNode* getEnglishWord(ODblLinkedList* list, size_t index)
{
    EngNode *tmp = list->head;
    size_t i = 0;

    while (tmp && i < index)
    {
        tmp = tmp->next;
        i++;
    }

    return tmp;
}

RusNode* getRussianWord(EDblLinkedList* list, size_t index)
{
    RusNode* tmp = list->head;
    size_t i = 0;

    while (tmp && i < index)
    {
        tmp = tmp->next;
        i++;
    }

    return tmp;
}

void addEngWord(char* wordToAdd, char* partOfSpeech, ODblLinkedList* wordList)
{
    EngWords tmpWord;
    tmpWord.word = wordToAdd;
    tmpWord.partOfSpeech = partOfSpeech;

    EngNode *tmp = (EngNode *) malloc(sizeof(EngNode));

    tmp->value = tmpWord;
    tmp->next = NULL;
    tmp->prev = wordList->tail;
    tmp->connSize = 0;
    tmp->connections = (RusNode **) malloc(1000 * sizeof(RusNode *));

    if (wordList->tail)
    {
        wordList->tail->next = tmp;
    }
    wordList->tail = tmp;

    if (wordList->head == NULL)
    {
        wordList->head = tmp;
    }
    wordList->size++;
}

void addRusWord(char *wordToAdd, char *partOfSpeech, EDblLinkedList *wordList)
{
    RusWords tmpWord;
    tmpWord.word = wordToAdd;
    tmpWord.partOfSpeech = partOfSpeech;

    RusNode *tmp = (RusNode *) malloc(sizeof(RusNode));

    tmp->value = tmpWord;
    tmp->next = NULL;
    tmp->prev = wordList->tail;
    tmp->connSize = 0;
    tmp->connections = (EngNode **) malloc(1000 * sizeof(EngNode *));

    if (wordList->tail)
    {
        wordList->tail->next = tmp;
    }
    wordList->tail = tmp;

    if (wordList->head == NULL)
    {
        wordList->head = tmp;
    }
    wordList->size++;
}

EDblLinkedList* createEdblLinkedList()
{
    EDblLinkedList* tmp = (EDblLinkedList *) malloc(sizeof(EDblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}

ODblLinkedList* createOdblLinkedList()
{
    ODblLinkedList* tmp = (ODblLinkedList *) malloc(sizeof(ODblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}

int inputIntCheck(char valueArray[])
{
    for (int i = 0; i < strlen(valueArray) - 1; ++i)
    {
        if ((valueArray[i] < '0') || (valueArray[i] > '9'))
        {
            return false;
        }
    }
    return true;
}

char* getDynamicString(char* string)
{
    int c;
    string = malloc(sizeof(char));

    string[0] = '\0';
    for(int i=0; i<100 && (c=getchar())!='\n' && c != EOF ; i++)
    {
        string = realloc(string, (i+2)*sizeof(char));
        string[i] = (char) c;
        string[i+1] = '\0';
    }
    return string;
}

void printWords(EDblLinkedList* rusWords, ODblLinkedList* engWords)
{
    int userChoice;

    wayToPrintMenu();
    printf("Enter your choice:\n");
    printf(">");

    userChoice = intInputCheck();
    switch (userChoice)
    {
        case PRINT_ALL:
            printAllWords(rusWords, engWords);
            break;

        case PRINT_RUS:
            printRusWords(rusWords);
            break;

        case PRINT_ENG:
            printEngWords(engWords);
            break;

        case PRINT_RUS_BONDED_TO_ENG:
            puts("Enter the number of Russian word:");
            int rusWordNum = intInputCheck() - 1;

            RusNode* rusPickedWord = (RusNode *) getEnglishWord(engWords,
                                                                rusWordNum);

            if (rusPickedWord == NULL)
            {
                puts("No bonds present at that number");
                break;
            }
            printRusToEng(rusPickedWord, rusWordNum);
            break;

        case PRINT_ENG_BONDED_TO_RUS:
            puts("Enter the number of English word:");
            int engWordNum = intInputCheck() - 1;

            EngNode* engPickedWord = getEnglishWord(engWords, engWordNum);

            if (engPickedWord == NULL)
            {
                puts("No bonds present at that number");
                break;
            }
            printEngToRus(engPickedWord, engWordNum);
            break;

        default:
            puts("Incorrect input entered!");
    }

}

void printRusToEng(RusNode* node, int num)
{
    RusWords russian = node->value;
    printf("\nword No: %d\n", num + 1);
    printf("\tWord: %s\n", russian.word);
    printf("\tPart of speech: %s\n", russian.partOfSpeech);
    if (!node->connSize)
    {
        puts("\nNo connections made to that word!");
        return;
    }
    puts("\tRelated words:");
    RusNode** pRusNode = (RusNode **) node->connections;
    for (int i = 0; i < node->connSize; i++)
    {
        printf("\t\t%s\n", (pRusNode[i]->value).word);
    }
}

void printEngToRus(EngNode* node, int num)
{
    EngWords english = node->value;
    printf("\nword No: %d\n", num + 1);
    printf("\tWord: %s\n", english.word);
    printf("\tPart of speech: %s\n", english.partOfSpeech);
    if (!node->connSize)
    {
        puts("\nNo connections made to that word!");
        return;
    }
    puts("\tRelated words:");
    RusNode** emps = node->connections;
    for (int i = 0; i < node->connSize; i++)
    {
        printf("\t\t%s\n", (emps[i]->value).word);
    }
}

void printAllWords(EDblLinkedList* rusWords, ODblLinkedList* engWords)
{
    int i = 0;
    int j = 0;

    if (engWords->size == 0)
    {
        puts("No English words");
    }
    else
    {
        puts("\nEnglish words:\n");

        EngNode* tmpEng = engWords->head;
        while (tmpEng)
        {
            EngWords eng = tmpEng->value;
            printf("\nword No: %d\n", i+1);
            printf("\tWord: %s\n", eng.word);
            printf("\tPart of speech: %s\n", eng.partOfSpeech);

            tmpEng = tmpEng->next;
            ++i;
        }
    }
    if (rusWords->size == 0)
    {
        puts("No Russian words");
        return;
    }
    else
    {
        puts("\nRussian words:\n");
        RusNode* tmpRus = rusWords->head;
        while (tmpRus)
        {
            RusWords rus = tmpRus->value;
            printf("\nword No: %d\n", j+i+1);
            printf("\tWord: %s\n", rus.word);
            printf("\tPart of speech: %s\n", rus.partOfSpeech);

            tmpRus = tmpRus->next;
            ++j;
        }
    }
}

void printEngWords(ODblLinkedList* engWords)
{
    int i = 0;

    if (engWords->size == 0)
    {
        puts("No English words");
        return;
    }
    EngNode* tmp = engWords->head;

    while (tmp)
    {
        EngWords eng = tmp->value;
        printf("\nword No: %d\n", i+1);
        printf("\tWord: %s\n", eng.word);
        printf("\tPart of speech: %s\n", eng.partOfSpeech);

        tmp = tmp->next;
        ++i;
    }
}

void printRusWords(EDblLinkedList* rusWords)
{
    int i = 0;

    if (rusWords->size == 0)
    {
        puts("No Russian words");
        return;
    }
    RusNode* tmp = rusWords->head;

    while (tmp)
    {
        RusWords rus = tmp->value;
        printf("\nword No: %d\n", i+1);
        printf("\tWord: %s\n", rus.word);
        printf("\tPart of speech: %s\n", rus.partOfSpeech);

        tmp = tmp->next;
        ++i;
    }
}

void wayToPrintMenu()
{
    puts("|-- -- -- -- -- -- -- -- -- -- -- -- -- -- -|");
    puts("|            PRINTING MANAGEMENT            |");
    puts("|-- -- -- -- -- -- -- -- -- -- -- -- -- -- -|");
    puts("1. Print all");
    puts("2. Print all Russian words");
    puts("3. Print all English words");
    puts("4. print Russian bonded to English words");
    puts("5. print English bonded to Russian words");
}

void printMenu()
{
    puts("\n|-------------------------------------------|");
    puts("|       ENGLISH TO RUSSIAN DICTIONARY       |");
    puts("|-------------------------------------------|");
    puts("1. Add an English word");
    puts("2. Add a Russian word");
    puts("3. Delete words");
    puts("4. Print words");
    puts("5. Make many-to-many relationship");
    puts("6. Upload to file");
    puts("7. Download from file");
    puts("8. Exit");
}

int intInputCheck()
{
    char strArrayLen[MAX_INPUT_ARRAY_LEN];
    fgets(strArrayLen, MAX_INPUT_ARRAY_LEN, stdin);
    fflush(stdin);
    if (!(inputIntCheck(strArrayLen))
        || strArrayLen[0] == '\0')
    {
        return -1;
    }
    return strtol(strArrayLen, NULL, 10);
}

void loadToFile(EDblLinkedList* rusWords, ODblLinkedList* engWords)
{

    FILE* file = fopen("dictionary.txt", "w");
    struct _EngNode* tmpEng = (struct _EngNode *) engWords->head;
    struct _RusNode* tmpRus = (struct _RusNode *) rusWords->head;

    if (!engWords->size)
    {
        puts("No English words");
    }
    else
    {
        fprintf(file, "English:\n");
        for (int i = 0; i < engWords->size; i++)
        {
            fprintf(file, "word: %s\n Part of speech: %s\n\n",
                    tmpEng->value.word, tmpEng->value.partOfSpeech);
        }
    }

    if (!rusWords->size)
    {
        puts("No Russian words");
    }
    else
    {
        fprintf(file, "Russian:\n");
        for (int j = 0; j < rusWords->size; j++)
        {
            fprintf(file, "word: %s\n Part of speech: %s\n\n",
                    tmpRus->value.word, tmpRus->value.partOfSpeech);
        }
    }
    fclose(file);
    if (engWords->size && rusWords->size)
        puts("uploaded");
}

void downloadFromFile()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("dictionary.txt", "r+");
    if (fp == NULL)
    {
        puts("Error while reading from file");
    }
    else
    {
        while ((read = getline(&line, &len, fp)) != -1)
        {
            printf("%s", line);
        }
    }
    fclose(fp);
    if (line)
        free(line);
}