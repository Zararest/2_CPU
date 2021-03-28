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
                                                   //���������� ����������: //����� ��� ����� ������������
    CPU_MOV_VR = 21,  //����������� ���������� �������� �� ��������        [3]
    CPU_MOV_RV = 19,  //������������ �������� �������� ����������          [3] //�������������� ����� ����� ���� ������ �������� ��� ����� ������������ ������(���������� ��� ����)
    CPU_MOV_RD = 20,  //������������ ������� �������� �����                [2] //���� �������� ��� ��� ������ � ����������

	CPU_PUSH = 1,     // ���������� � ���� ����� �� ������������� �������� [1] ����� ����������� ����� ����������� ����� ����//���� �������� ��� ��� ������ �� �������� � ������� ����� ����� ���� �������������� ��������� � ����������
	CPU_POP = 9,      //����� �� ����� �������� ��� ������������� �������� [1]
	CPU_IN = 2,       //���������� �� ������� � �������                    [1]
	CPU_GET = 26,     //��������� � ������� ���� ������                    [1]

	CPU_ADD = 3,      //�������� ���� ����� � �����                        [0]
	CPU_SUB = 4,      //��������� ���� ����� � �����                       [0]
	CPU_DIV = 5,      //������� ���� ����� � �����                         [0]
	CPU_MUL = 6,      //��������� ���� ����� � �����                       [0]
	CPU_FSQRT = 7,    //������ ���� ����� � �����                          [0]

	CPU_JL = 310,     //������                                             [1]
	CPU_JG = 11,      //������                                             [1]
	CPU_JE = 12,      //�����                                              [1]
	CPU_JN = 13,      //����������� �����(������ �����������)              [1]
	CPU_CALL = 23,    //�������� �������                                   [1]
	CPU_FUNC_JMP = 24,//��������� ����������� ����� �� ��������� RET       [1]

	CPU_CMP = 14,     //��������� ����� �� ����� � ������� � �������       [0]
	CPU_OUT = 15,     //����� �� ����� �� �����                            [0]
	CPU_OUT_CHR = 25, //����� �� ����� ��������� ������                    [0]
	CPU_HLT = 16,     //��������� ����������                               [0]
	CPU_RET = 22,     //����������� � ������ �������                       [0]//��� ���������� ����� fuction ��������� ��������� ����� �� ����� ��� ���������� ��������� RET

	END = 17,         //����� ���������                                    [0]
	NOP = 18,         //������� ����                                       [0]


};

enum Registers_len{

    byte_len = 1,
    word_len = 2,
    double_word_len = 4,
    private_len = 8,
};

enum Registers {

    PUBL_B_A = 110, //��������� ������� �������� ���� ��� B_�
    PUBL_B_B = 111,
    PUBL_B_C = 112,

    PUBL_W_A = 120, //��������� ������� �������� ����� ��� W_�
    PUBL_W_B = 121,
    PUBL_W_C = 122,
    PUBL_W_D = 123,

    PUBL_DW_A = 140,//��������� ������� �������� ������� ����� ��� D_�
    PUBL_DW_B = 141,
    PUBL_DW_C = 142,
    PUBL_DW_D = 143,
    PUBL_DW_E = 144,

    PRIV_F = 150,   //��������� ������� P_F
    PRIV_R = 151,   //��������� ������� P_R
};

#endif