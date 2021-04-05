#include <stdio.h>
#include <iostream>
#include <string>

#include "headers/list_class.h"
#include "headers/table_class.h"

/*#define CREATE_LOG FILE* log_pointer = fopen("log.txt", "w");\
                        printf("FUCK U %d and file %s\n", __LINE__, __FILE__);

#define my_print(name) printf(name);  */      

int sqrt(int& val_func){

    val_func = 0;

    return 1;
}


int main(){

    //list test_list;
    int val = 10;

    printf("sqrt = %i and val = %i\n", sqrt(val), val);
    //test_list.add_to_root("test", 10);
    //test_list.add_to_root("test2", 12);
    //test_list.dump();
}
