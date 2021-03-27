#include <stdio.h>
#include <stdlib.h>
#include <iostream>

const int MAXLEN = 100;

class array_of_commands{

public:
    double* commands = NULL;
    int pointer = 0;

    array_of_commands(int size);
    ~array_of_commands();

    void add_command(int, double);
    void increase_pointer(int);
    double* element_access(int);
    double* return_array_of_commands();
};