//
// Created by dahhw on 15.02.2023.
//

#ifndef SYSTEM1_STRUCTURE_H
#define SYSTEM1_STRUCTURE_H

enum {
    GET_DETAILS = 1,
    CALCULATE_NEW_DATE,
    EXIT
};

typedef struct {
    int year;
    int month;
    int day;
} Date;

#endif //SYSTEM1_STRUCTURE_H
