#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>

typedef struct stack_struct
{
    unsigned char** array_;
    int array_count;
    int cur_point;
    int size_of_elem;
    int push_count;
    int pop_count;
    int size_of_stack;
    int errors;
    int _hash;
} my_stack;


my_stack* stack_create(int, int, int);
int silent_ok(my_stack*);
int loud_ok(my_stack*);
int dump(my_stack* _stack, void (*type_print)(unsigned char*) );
long int my_hash(my_stack*);
unsigned char* pop(my_stack*);
template <typename T>
int push(my_stack*, T);
void stack_clean(my_stack*);
int silent_ok(my_stack*);
int stack_recovery(my_stack*);
void stack_destruct(my_stack*);

void print_double(unsigned char* elem)
{
    printf("%lf", *( (double*) elem ));
}
