#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define CLEAN_ALL for (int j = 1; j <= 12; j++){\
                      free(command_names[j])}\
                  for (int j = 1; j <= 14; j++){\
                      free(reg_names[j].reg_name)}\
                
                  
typedef struct elem_struct{

    char* reg_name = NULL;
    int reg_number = 0;
} elem;

char** commands_names = (char**)calloc(13, sizeof(char*));
elem* reg_names = (elem*)calloc(15, sizeof(elem));

void init(){

    for (int i = 1; i <= 12; i++){
        commands_names[i] = (char*)calloc(10, sizeof(char));
    }
    commands_names[1] = "SUB\n";
    commands_names[2] = "DIV\n";
    commands_names[3] = "MUL\n";
    commands_names[4] = "FSQRT\n";
    commands_names[5] = "CMP\n";
    commands_names[6] = "OUT\n";
    commands_names[7] = "OUT_CHR\n";
    commands_names[8] = "HLT\n";
    commands_names[9] = "RET\n";
    commands_names[10] = "END\n";
    commands_names[11] = "NOP\n";
    commands_names[12] = "ADD\n";
    commands_names[13] = "PUSH "; 
    commands_names[14] = "POP "; 
    commands_names[15] = "IN\n"; 
    commands_names[16] = "GET\n"; 
    commands_names[17] = "JL "; 
    commands_names[18] = "JG "; 
    commands_names[19] = "JE "; 
    commands_names[20] = "JN "; 
    commands_names[21] = "CALL ";
    commands_names[22] = "function ";
    commands_names[23] = "MOV ";
    commands_names[24] = "MOV ";
    commands_names[25] = "MOV ";

    for(int k = 1; k <= 14; k++){
        reg_names[k].reg_name = (char*)calloc(4, sizeof(char));
    }

    reg_names[1].reg_name = "B_A";
    reg_names[1].reg_number = 110;
    reg_names[2].reg_name = "B_B";
    reg_names[2].reg_number = 111;
    reg_names[3].reg_name = "B_C";
    reg_names[3].reg_number = 112;
    reg_names[4].reg_name = "W_A";
    reg_names[4].reg_number = 120;
    reg_names[5].reg_name = "W_B";
    reg_names[5].reg_number = 121;   
    reg_names[6].reg_name = "W_C";
    reg_names[6].reg_number = 122;
    reg_names[7].reg_name = "W_D";
    reg_names[7].reg_number = 123;
    reg_names[8].reg_name = "D_A";
    reg_names[8].reg_number = 140;
    reg_names[9].reg_name = "D_B";
    reg_names[9].reg_number = 141;
    reg_names[10].reg_name = "D_C";
    reg_names[10].reg_number = 142;
    reg_names[11].reg_name = "D_D";
    reg_names[11].reg_number = 143;
    reg_names[12].reg_name = "D_E";
    reg_names[12].reg_number = 144;
    reg_names[13].reg_name = "P_F";
    reg_names[13].reg_number = 150;
    reg_names[14].reg_name = "P_R";
    reg_names[14].reg_number = 151;
}
