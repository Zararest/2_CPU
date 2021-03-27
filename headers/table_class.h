#ifndef TABLE_CLASS_H
#define TABLE_CLASS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>


typedef struct type_undef_elem{

    char* name;
    double* position_of_elem;

} undef_elem;

typedef struct type_def_elem{

    char* name;
    double data_of_elem;

} def_elem;


class table_of_matches{

public:
    undef_elem* array_undef_obj = NULL;
    def_elem* array_def_obj = NULL;
    int undef_pointer = 0;
    int def_pointer = 0;

    table_of_matches(const table_of_matches&) = delete;

    table_of_matches& operator = (const table_of_matches&) = delete;

    table_of_matches();

    ~table_of_matches();

    void add_new_obj(char*, double*);

    int number_of_redefinition_of_obj(char*);

    void add_defin_of_obj(char*, double);

    void dump_table();

    void match_arrays();
};

#endif