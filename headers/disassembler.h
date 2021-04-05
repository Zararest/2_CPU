#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>

#define CLEAN_ALL for (int j = 1; j <= 25; j++){\
                      free(commands_names[j]);}\
                  for (int j = 1; j <= 14; j++){\
                      free(reg_names[j].reg_name);}\

#define COMMAND_WITH_ONE_PARAM 1
#define COMMAND_WITH_TWO_PARAM 13
#define CODE_OF_FIRST_JMP 17
#define CODE_OF_LAST_JMP 20
#define CODE_OF_CALL 21
#define CODE_OF_FUNC 22
#define CODE_OF_MOV_VR 23
#define CODE_OF_MOV_RV 24
#define CODE_OF_MOV_RD 25

#define BYTE_LEN 1
#define WORD_LEN 2
#define DOUBLE_WORD_LEN 4
#define PRIVATE_LEN 8

char* my_memcpy(char*);            
                  
typedef struct elem_reg_struct{

    char* reg_name = NULL;
    int reg_number = 0;
} elem_reg;

char** commands_names = (char**)calloc(27, sizeof(char*));
elem_reg* reg_names = (elem_reg*)calloc(15, sizeof(elem_reg));

void init(){

    commands_names[1] = my_memcpy("SUB\n");
    commands_names[2] = my_memcpy("DIV\n");
    commands_names[3] = my_memcpy("MUL\n");
    commands_names[4] = my_memcpy("FSQRT\n");
    commands_names[5] = my_memcpy("CMP\n");
    commands_names[6] = my_memcpy("OUT\n");
    commands_names[7] = my_memcpy("OUT_CHR\n");
    commands_names[8] = my_memcpy("HLT\n");
    commands_names[9] = my_memcpy("RET\n");
    commands_names[10] = my_memcpy("END\n");
    commands_names[11] = my_memcpy("NOP\n");
    commands_names[12] = my_memcpy("ADD\n");
    commands_names[13] = my_memcpy("PUSH "); 
    commands_names[14] = my_memcpy("POP "); 
    commands_names[15] = my_memcpy("IN"); 
    commands_names[16] = my_memcpy("GET"); 
    commands_names[17] = my_memcpy("JL "); 
    commands_names[18] = my_memcpy("JG "); 
    commands_names[19] = my_memcpy("JE "); 
    commands_names[20] = my_memcpy("JN "); 
    commands_names[21] = my_memcpy("CALL ");
    commands_names[22] = my_memcpy("function ");
    commands_names[23] = my_memcpy("MOV ");
    commands_names[24] = my_memcpy("MOV ");
    commands_names[25] = my_memcpy("MOV ");

    reg_names[1].reg_name = my_memcpy("B_A");
    reg_names[1].reg_number = 110;
    reg_names[2].reg_name = my_memcpy("B_B");
    reg_names[2].reg_number = 111;
    reg_names[3].reg_name = my_memcpy("B_C");
    reg_names[3].reg_number = 112;
    reg_names[4].reg_name = my_memcpy("W_A");
    reg_names[4].reg_number = 120;
    reg_names[5].reg_name = my_memcpy("W_B");
    reg_names[5].reg_number = 121;   
    reg_names[6].reg_name = my_memcpy("W_C");
    reg_names[6].reg_number = 122;
    reg_names[7].reg_name = my_memcpy("W_D");
    reg_names[7].reg_number = 123;
    reg_names[8].reg_name = my_memcpy("D_A");
    reg_names[8].reg_number = 140;
    reg_names[9].reg_name = my_memcpy("D_B");
    reg_names[9].reg_number = 141;
    reg_names[10].reg_name = my_memcpy("D_C");
    reg_names[10].reg_number = 142;
    reg_names[11].reg_name = my_memcpy("D_D");
    reg_names[11].reg_number = 143;
    reg_names[12].reg_name = my_memcpy("D_E");
    reg_names[12].reg_number = 144;
    reg_names[13].reg_name = my_memcpy("P_F");
    reg_names[13].reg_number = 150;
    reg_names[14].reg_name = my_memcpy("P_R");
    reg_names[14].reg_number = 151;
}

#endif