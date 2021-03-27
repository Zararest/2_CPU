#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>

const int MAXLEN = 100;

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

template <typename T>
int push(my_stack*, T);

my_stack* stack_create(int, int, int);
int silent_ok(my_stack*);
int loud_ok(my_stack*);
int dump(my_stack* _stack, void (*type_print)(unsigned char*) );
long int my_hash(my_stack*);
unsigned char* pop(my_stack*);
void stack_resize(my_stack*);
void stack_clean(my_stack*);
int silent_ok(my_stack*);
int stack_recovery(my_stack*);
void stack_destruct(my_stack*);

/*void print_double(unsigned char* elem)
{
    printf("%lf", *( (double*) elem ));
}*/

template <typename T>
int push(my_stack* _stack, T val)
{
    /*
    0 - ��� ���������
    1 - ���� ������������
    2 - ������������ ���
    */

    if ( silent_ok(_stack) != 0)
    {
        exit(4);
    }

    int i = 0, j = 0;
    char* str = (char*) calloc(MAXLEN, sizeof(char));

    if (sizeof(val) == _stack->size_of_elem)
    {

        if ( ( _stack->size_of_stack - 1) * _stack->size_of_elem >= _stack->cur_point )
        {

            for (i = 0; i < _stack->size_of_elem; i++)
            {

                for(j = 0; j < _stack->array_count; j++ )
                {
                    _stack->array_[j] [ _stack->cur_point + i ] =  ((unsigned char*) &val)[i];
                }

            }

            _stack->cur_point += i;
            _stack->push_count++;
            _stack->_hash = my_hash(_stack);

             return 0;

        } else
        {
            stack_resize(_stack);

            for (i = 0; i < _stack->size_of_elem; i++)
            {

                for(j = 0; j < _stack->array_count; j++ )
                {
                    _stack->array_[j] [ _stack->cur_point + i ] =  ((unsigned char*) &val)[i];
                }

            }

            _stack->cur_point += i;
            _stack->push_count++;
            _stack->_hash = my_hash(_stack);

            return 1;
        }

    } else
    {
        return 2;
    }

}
