#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include <cassert>

#define NUMBER_B_REGISTERS 3
#define NUMBER_W_REGISTERS 4
#define NUMBER_D_REGISTERS 5
#define NUMBER_P_REGISTERS 2

enum Commands {
 //number of parameters:
    CPU_MOV_VR = 23,  //[3]
    CPU_MOV_RV = 24,  //[3] 
    CPU_MOV_RD = 25,  //[2]

	CPU_PUSH = 13,    //[1]
	CPU_POP = 14,     //[1]
	CPU_IN = 15,      //[1]
	CPU_GET = 16,     //[1]

	CPU_ADD = 12,     //[0]
	CPU_SUB = 1,      //[0]
	CPU_DIV = 2,      //[0]
	CPU_MUL = 3,      //[0]
	CPU_FSQRT = 4,    //[0]

	CPU_JL = 17,      //[1]
	CPU_JG = 18,      //[1]
	CPU_JE = 19,      //[1]
	CPU_JN = 20,      //[1]
	CPU_CALL = 21,    //[1]
	CPU_FUNC_JMP = 22,//[1]

	CPU_CMP = 5,      //[0]
	CPU_OUT = 6,      //[0]
	CPU_OUT_CHR = 7,  //[0]
	CPU_HLT = 8,      //[0]
	CPU_RET = 9,      //[0]

	END = 10,         //[0]
	NOP = 11,         //[0]


};

enum Registers_len{

    byte_len = 1,
    word_len = 2,
    double_word_len = 4,
    private_len = 8,
};

enum Registers {

    PUBL_B_A = 110, 
    PUBL_B_B = 111,
    PUBL_B_C = 112,

    PUBL_W_A = 120, 
    PUBL_W_B = 121,
    PUBL_W_C = 122,
    PUBL_W_D = 123,

    PUBL_DW_A = 140,
    PUBL_DW_B = 141,
    PUBL_DW_C = 142,
    PUBL_DW_D = 143,
    PUBL_DW_E = 144,

    PRIV_F = 150,  
    PRIV_R = 151,   
};

#endif