#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define ADD_TO_LOG(line, name, id) fprintf(log, "[%i] %s name:|%s| id:[%i]\n", counter, line, name, id);
#define ADD_TO_DUMP(position, name, id) fprintf(log, "[%i] |%s| id:[%i]\n", position, name, id);

typedef struct elem_struct{

    char* name = NULL;
    int id = 0;
    elem* next = NULL;
} elem;

class list{

    elem* root = NULL;
    int number_elems = 0;
    FILE* log = NULL;
    int counter = 0;

    list();

    ~list();

    list(const list&) = delete;
    
    list& operator = (const list&) = delete;

    void add_to_root(char*, int);

    void add_to_top(char*, int);

    void delete_root();

    void delete_top();

    void delete_elem(int);

    void add_before_greater_elem(char*, int);

    void dump();
};