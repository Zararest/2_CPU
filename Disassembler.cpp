#include "headers/disassembler.h"
#include "headers/list_class.h"

#define GET_REG_NUMBER(digit) while((number_of_reg < 15) && (reg_names[number_of_reg].reg_number != digit )){\
                            number_of_reg++;\
                         }\
                         assert(number_of_reg != 15);\

void disassembler(int number_of_commands, FILE* machine_commands){

    int i = 0, number_of_reg = 1, id_of_fir_elem = 0, id_of_sec_elem = 0, var_was_def = 0;
    double* array_of_commands = (double*)calloc(number_of_commands, sizeof(double));
    FILE* output_file = fopen("disassembler.txt", "w");

    list list_of_var;
    list list_of_funcs;
    list list_of_links;
    
    fread(array_of_commands, sizeof(double), number_of_commands, machine_commands);

    while(i < number_of_commands){

        if ((array_of_commands[i] >= CODE_OF_FIRST_JMP) && (array_of_commands[i] <= CODE_OF_LAST_JMP)){

            if (list_of_links.check_dublicate((int)array_of_commands[i + 1]) == 0){
                list_of_links.add_before_greater_elem(NULL, (int)array_of_commands[i + 1]);
            }
            
            i += 2;
        }

        if (array_of_commands[i] == CODE_OF_CALL){

            i += 2;
        }

        if (array_of_commands[i] == CODE_OF_MOV_VR){

            if (list_of_var.check_dublicate((int)array_of_commands[i + 1]) == 0){
                list_of_var.add_before_greater_elem(NULL, (int)array_of_commands[i + 1]);
            }
            
            i += 4;
        }

        if (array_of_commands[i] == CODE_OF_MOV_RV){
            
            if (list_of_var.check_dublicate((int)array_of_commands[i + 2]) == 0){
                list_of_var.add_before_greater_elem(NULL, (int)array_of_commands[i + 2]);
            }
            
            i += 4;
        }

        if (array_of_commands[i] == CODE_OF_MOV_RD){

            i += 3;
        }

        if (array_of_commands[i] == CODE_OF_FUNC){

            if (list_of_funcs.check_dublicate(i) == 0){//????
                list_of_funcs.add_before_greater_elem(NULL, i);
            }
            
            i += 2;
        }

        if ((array_of_commands[i] >= COMMAND_WITH_ONE_PARAM) &&  (array_of_commands[i] < COMMAND_WITH_TWO_PARAM)){

            i++;
        }

        if ((array_of_commands[i] >= COMMAND_WITH_TWO_PARAM) && (array_of_commands[i] < CODE_OF_FIRST_JMP)){

            i += 2;
        }
    }

    list_of_funcs.name_func();
    list_of_links.name_link();
    list_of_var.name_var();

    i = 0;
    
    while(i < number_of_commands){

        if (list_of_links.get_name(i) != NULL){

            fprintf(output_file, "@%s:\n", list_of_links.get_name(i));
        }

        if (list_of_funcs.get_name(i) != NULL){

            fprintf(output_file, "function %s\n", list_of_funcs.get_name(i));
        }

        if ((array_of_commands[i] >= COMMAND_WITH_ONE_PARAM) && (array_of_commands[i] < COMMAND_WITH_TWO_PARAM)){

            fprintf(output_file, "%s ", commands_names[(int)array_of_commands[i]]);
            i++;
        }

        if ((array_of_commands[i] >= COMMAND_WITH_TWO_PARAM) && (array_of_commands[i] < CODE_OF_FIRST_JMP)){

            fprintf(output_file, "%s ", commands_names[(int)array_of_commands[i]]);

            GET_REG_NUMBER(array_of_commands[i + 1])

            fprintf(output_file, "%s\n", reg_names[number_of_reg].reg_name);

            number_of_reg = 1;
            i += 2;
        }
        
        if ((array_of_commands[i] >= CODE_OF_FIRST_JMP) && (array_of_commands[i] <= CODE_OF_LAST_JMP)){

           fprintf(output_file, "%s ", commands_names[(int)array_of_commands[i]]);

           assert(list_of_links.get_name((int)array_of_commands[i + 1]) != NULL);
           fprintf(output_file, "%s\n", list_of_links.get_name((int)array_of_commands[i + 1])); 

           i += 2;
        }
        
        if (array_of_commands[i] == CODE_OF_CALL){

            fprintf(output_file, "%s ", commands_names[(int)array_of_commands[i]]);
            assert(list_of_funcs.get_name((int)array_of_commands[i + 1]) != NULL);
            fprintf(output_file, "%s\n", list_of_funcs.get_name((int)array_of_commands[i + 1])); 

            i += 2;
        }

        if (array_of_commands[i] == CODE_OF_FUNC){

            fprintf(output_file, "function ");
            assert(list_of_funcs.get_name(i) != NULL);
            fprintf(output_file, "%s\n", list_of_funcs.get_name(i));

            i += 2;
        }

        if (array_of_commands[i] == CODE_OF_MOV_VR){

            fprintf(output_file, "MOV ");
            assert(list_of_var.get_name((int)array_of_commands[i + 1]) != NULL);
            fprintf(output_file, "%s ", list_of_var.get_name((int)array_of_commands[i + 1]));

            if (array_of_commands[i + 2] != 0){

                GET_REG_NUMBER(array_of_commands[i + 2])
                fprintf(output_file, "[%s] ", reg_names[number_of_reg].reg_name);

                number_of_reg = 1;
            }

            GET_REG_NUMBER(array_of_commands[i + 3])

            fprintf(output_file, "%s\n", reg_names[number_of_reg].reg_name);

            number_of_reg = 1;
            i += 4;
        }

        if (array_of_commands[i] == CODE_OF_MOV_RV){

            fprintf(output_file, "MOV ");
            GET_REG_NUMBER(array_of_commands[i + 1])

            fprintf(output_file, "%s ", reg_names[number_of_reg].reg_name);

            number_of_reg = 1;

            assert(list_of_var.get_name((int)array_of_commands[i + 2]) != NULL);
            fprintf(output_file, "%s ", list_of_var.get_name((int)array_of_commands[i + 2])); 

            if (array_of_commands[i + 3] != 0){

                GET_REG_NUMBER(array_of_commands[i + 3])
                fprintf(output_file, " [%s]\n", reg_names[number_of_reg].reg_name);

                number_of_reg = 1;
            }

            i += 4;
        }

        if (array_of_commands[i] == CODE_OF_MOV_RD){

            fprintf(output_file, "MOV ");
            GET_REG_NUMBER(array_of_commands[i + 1])

            fprintf(output_file, "%s ", reg_names[number_of_reg].reg_name);

            number_of_reg = 1;

            fprintf(output_file, "%lf\n", array_of_commands[i + 2]);

            i += 3;
        }
    }

    while(list_of_var.number_of_elems() > 1){
        //printf("number of rlrms = %i\n", list_of_var.number_of_elems());

        id_of_fir_elem = list_of_var.get_id_of_elem_number(1);
        id_of_sec_elem = list_of_var.get_id_of_elem_number(2);
        var_was_def = 0;

        switch (id_of_sec_elem - id_of_fir_elem){

            case BYTE_LEN:
            assert(list_of_var.get_name(id_of_fir_elem) != NULL);
            fprintf(output_file, "%s DB\n", list_of_var.get_name(id_of_fir_elem));
            var_was_def = 1;
            break;

            case WORD_LEN:
            assert(list_of_var.get_name(id_of_fir_elem) != NULL);
            fprintf(output_file, "%s DW\n", list_of_var.get_name(id_of_fir_elem));
            var_was_def = 1;
            break;

            case DOUBLE_WORD_LEN:
            assert(list_of_var.get_name(id_of_fir_elem) != NULL);
            fprintf(output_file, "%s DD\n", list_of_var.get_name(id_of_fir_elem));
            var_was_def = 1;
            break;

            case PRIVATE_LEN:
            assert(list_of_var.get_name(id_of_fir_elem) != NULL);
            fprintf(output_file, "%s DP\n", list_of_var.get_name(id_of_fir_elem));
            var_was_def = 1;
            break;

            if (var_was_def == 0){

                assert(list_of_var.get_name(id_of_fir_elem) != NULL);
                fprintf(output_file, "%s DMAS %i\n", list_of_var.get_name(id_of_fir_elem), id_of_sec_elem - id_of_fir_elem); 
            }

        }

        list_of_var.delete_root();
    }

    id_of_fir_elem = list_of_var.get_id_of_elem_number(1);
    if ((list_of_var.number_of_elems() == 1) && (list_of_var.get_name(id_of_fir_elem) != NULL)){

        fprintf(output_file, "%s DMAS is undef\n", list_of_var.get_name(id_of_fir_elem));
    }

}


int main(){

    init();

    int size_of_file = 0;
    FILE* input_file = fopen("machine_commands.bin", "rb");
    assert(input_file != NULL);

    fread(&size_of_file, sizeof(int), 1, input_file);
    disassembler(size_of_file, input_file);
    
    fclose(input_file);
    CLEAN_ALL
    return 0;
}