//
// Created by dahhw on 28.05.2022.
//
#include <stdlib.h>

#ifndef LAB7_STRUCTS_H
#define LAB7_STRUCTS_H

enum
{
    ADD_ENG_WORD = 1,
    ADD_RUS_WORD,
    DELETE_WORDS,
    PRINT_WORDS,
    MAKE_MANY_TO_MANY_BOND,
    UPLOAD_TO_FILE,
    DOWNLOAD_FROM_FILE,
    EXIT
};

enum
{
    PRINT_ALL = 1,
    PRINT_RUS,
    PRINT_ENG,
    PRINT_RUS_BONDED_TO_ENG,
    PRINT_ENG_BONDED_TO_RUS,
};

typedef struct
{
    char* word;
    char* partOfSpeech;
} RusWords;

typedef struct
{
    char* word;
    char* partOfSpeech;
} EngWords;

typedef struct _EngNode
{
    EngWords value;
    int connSize;
    struct _RusNode** connections;
    struct _EngNode* next;
    struct _EngNode* prev;
} EngNode;

typedef struct _EngDblLinkedList
{
    size_t size;
    EngNode* head;
    EngNode* tail;
} ODblLinkedList;

typedef struct _RusNode
{
    RusWords value;
    int connSize;
    struct _EngNode** connections;
    struct _RusNode* next;
    struct _RusNode* prev;
} RusNode;

typedef struct _RusDblLinkedList
{
    size_t size;
    RusNode *head;
    RusNode *tail;
} EDblLinkedList;


#endif //LAB7_STRUCTS_H
