//
// Created by dahhw on 16.05.2022.
//

#ifndef UNTITLED_STRUCTS_H
#define UNTITLED_STRUCTS_H

enum
{
    ADD_ACC = 1,
    DELETE_ACC,
    PRINT_ALL,
    FILTER_ACC,
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
    char* brand;
    double price;
    double voltage;
    double capacity;
} accumulator;




#endif //UNTITLED_STRUCTS_H
