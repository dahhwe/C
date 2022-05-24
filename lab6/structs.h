//
// Created by dahhw on 16.05.2022.
//

#include <stdlib.h>

#ifndef UNTITLED_STRUCTS_H
#define UNTITLED_STRUCTS_H

enum
{
    ADD_ACC = 1,
    DELETE_ACC,
    PRINT_ALL,
    REVERSE_ACC,
    SAVE_ACC,
    LOAD_ACC,
    EXIT
};

enum
{
    FILTER_BY_BRAND = 1,
    FILTER_BY_PRICE,
    FILTER_BY_VOLTAGE,
    FILTER_BY_CAPACITY,
};

typedef struct
{
    double price;
    double voltage;
    double capacity;
} accumulator;

typedef struct _Node
{
    accumulator value;
    struct _Node* next;
    struct _Node* prev;
} Node;

typedef struct _DblLinkedList
{
    size_t size;
    Node *head;
    Node *tail;
} DblLinkedList;


#endif //UNTITLED_STRUCTS_H
