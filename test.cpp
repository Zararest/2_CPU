#include <stdio.h>
#include <iostream>

#define CREATE_LOG FILE* log_pointer = fopen("log.txt", "w");\
                        printf("FUCK U %d and file %s\n", __LINE__, __FILE__);

#define my_print(name) printf(name);             
int main(){

    if (1 == 1) {printf("yes\n");}
    CREATE_LOG;
    //my_print("jopa", 10);
}
