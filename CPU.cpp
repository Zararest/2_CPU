#include "src/headers/commands.h"
#include "src/headers/stack_class.h"
#include "src/headers/CPU_class.h"


int main(){

    int size_of_file = 0;
    FILE* input_file = fopen("../bin/machine_commands.bin", "rb");
    assert(input_file != NULL);

    fread(&size_of_file, sizeof(int), 1, input_file);

    CPU_class CPU(size_of_file, size_of_file);

    fread(CPU.machine_code_access(), sizeof(double), size_of_file, input_file);
    fclose(input_file);

    CPU.processor(size_of_file);
}


