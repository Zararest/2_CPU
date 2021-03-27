#include "table_class.h" 


table_of_matches::table_of_matches(){

        array_undef_obj = NULL;
        array_def_obj = NULL;

        undef_pointer = 0;
        def_pointer = 0;
    }

table_of_matches::~table_of_matches(){

        free(array_def_obj);
        free(array_undef_obj);
        array_undef_obj = NULL;
        array_def_obj = NULL;
        undef_pointer = 0;
        def_pointer = 0;
    }

void table_of_matches::add_new_obj(char* name_of_obj, double* position_of_obj){

       array_undef_obj = (undef_elem*) realloc(array_undef_obj, sizeof(undef_elem) * (undef_pointer + 1) );
       array_undef_obj[undef_pointer].name = name_of_obj;
       array_undef_obj[undef_pointer].position_of_elem = position_of_obj;
       undef_pointer++;
    }

int table_of_matches::number_of_redefinition_of_obj(char* name_of_obj){

        int redefinition_counter = 0, i = 0;

        for (i = 0; i < def_pointer; i++){

            if (strcmp(name_of_obj, array_def_obj[i].name) == 0){

                redefinition_counter++;
            }
        }

        return redefinition_counter;
    }

void table_of_matches::add_defin_of_obj(char* name_of_def_obj, double data_of_obj){

        array_def_obj = (def_elem*) realloc(array_def_obj, sizeof(def_elem) * (def_pointer + 1) );
        array_def_obj[def_pointer].name = name_of_def_obj;
        array_def_obj[def_pointer].data_of_elem = data_of_obj;
        def_pointer++;
    }

void table_of_matches::dump_table(){

        int i = 0;
        printf("\n Dump table:\n");

        printf("table of undefined objects:\n");
        while (i < undef_pointer){

            printf("\t %i) name: |%s| position: |%i|\n", i, array_undef_obj[i].name, array_undef_obj[i].position_of_elem);
            i++;
        }

        i = 0;
        printf("table of definition of objects:\n");
        while (i < def_pointer){

            printf("\t %i) name: |%s| position: |%lf|\n", i, array_def_obj[i].name, array_def_obj[i].data_of_elem);
            i++;
        }
    }

void table_of_matches::match_arrays(){

        int i = 0, j = 0;
        
        for (i = 0; i < undef_pointer; i++){

            j = 0;
            while ( (j < def_pointer) && (strcmp(array_def_obj[j].name, array_undef_obj[i].name) != 0) ){

                j++;
            }

            if (j == def_pointer){

                exit(1);
            } else{

                *(array_undef_obj[i].position_of_elem) = array_def_obj[j].data_of_elem;
            }
        }
    }