#include "headers/array_class.h"

array_of_commands::array_of_commands(int size){

        pointer = 0;
        commands = (double*) calloc(size, sizeof(double));
    }

void array_of_commands::add_command(int pointer_modificator, double new_command){

        commands[pointer + pointer_modificator] = new_command;
    }

void array_of_commands::increase_pointer(int increment){

        pointer = pointer + increment;
    }

double* array_of_commands::element_access(int pointer_modification){

        return &commands[pointer + pointer_modification];
    }

double* array_of_commands::return_array_of_commands(){

        return commands;
    }

array_of_commands::~array_of_commands(){

        pointer = 0;
    }
