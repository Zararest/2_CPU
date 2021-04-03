#ifndef ARRAY_CLASS_H
#define ARRAY_CLASS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

const int MAXLEN = 100;

class array_of_commands{

public:
    double* commands = NULL;
    int pointer = 0;
    int counter = 0;

    array_of_commands(const array_of_commands&) = delete;

    array_of_commands& operator = (const array_of_commands&) = delete;

    array_of_commands(int);

    ~array_of_commands();

    void add_command(int, double);

    void increase_pointer(int);

    double* element_access(int);

    double* return_array_of_commands();
};

#endif