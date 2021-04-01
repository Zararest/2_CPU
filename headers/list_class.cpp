#include "list_class.h"

char* my_memcpy(char* line){

    int len = 0;
    char* new_line = NULL;

    if (line == NULL){
        return NULL;
    }

    while (line[len] != '\0'){
        len++;
    }

    new_line = (char*)calloc(len + 1, sizeof(char));

    for(int i = 0; i <= len; i++){
        new_line[i] = line[i];
    }

    return new_line;
}

list::list(){

    root = (elem*)calloc(1, sizeof(elem));
    root->id = -228;
    root->name = (char*)calloc(5, sizeof(char));
    root->name = "root";
    root->next = NULL;

    log = fopen("list_log.txt", "w");
}

list::~list(){

    elem* prev_elem = NULL;
    elem* tmp = root;

    while(tmp->next != NULL){
        free(tmp->name);
        free(prev_elem);
        prev_elem = tmp;
        tmp = tmp->next;
    }

    free(tmp->name);
    free(tmp);

    fprintf(log, "destructor was called\n");
    fclose(log);
}



void list::add_to_root(char* elem_name, int elem_id){

    elem* tmp = (elem*)calloc(1, sizeof(elem));
    tmp->name = my_memcpy(elem_name);
    tmp->id = elem_id;

    tmp->next = root->next;
    root->next = tmp;
    ADD_TO_LOG("elem have been added to the root", tmp->name, tmp->id)
}

void list::add_to_top(char* elem_name, int elem_id){

    elem* tmp = root;

    while(tmp->next != NULL){

        tmp = tmp->next;
    }

    tmp->next = (elem*)calloc(1, sizeof(elem));
    tmp->next->name = my_memcpy(elem_name);
    tmp->next->id = elem_id;
    tmp->next->next = NULL;

    ADD_TO_LOG("elem have been added to the top", tmp->name, tmp->id)
}

void list::delete_root(){

    elem* tmp = NULL;

    if (root->next != NULL){
        
        tmp = root->next;
        ADD_TO_LOG("first elem have been deleted ", tmp->name, tmp->id)
        root->next = tmp->next;
        free(tmp->name);
        free(tmp);
    }

    
}

void list::delete_top(){

    elem* tmp = root;

    if (root->next != NULL){

        while(tmp->next != NULL){

            tmp = tmp->next;
        }
        ADD_TO_LOG("last elem have been deleted", tmp->name, tmp->id)
        free(tmp->name);
        free(tmp);
    } 
}

void list::add_before_greater_elem(char* elem_name, int elem_id){ //if compar equal to 1, programm working

    elem* tmp = root;
    elem* prev_elem = root;

    while((tmp->id < elem_id) && (tmp->next != NULL)){

        prev_elem = tmp;
        tmp = tmp->next;
    }

    tmp = prev_elem->next;
    prev_elem->next = (elem*)calloc(1, sizeof(elem));
    prev_elem->next->name = my_memcpy(elem_name);
    prev_elem->next->id = elem_id;
    prev_elem->next->next = tmp;
    ADD_TO_LOG("elem have been added after greater elem", prev_elem->next->name, prev_elem->next->id)
}

void list::dump(){

    fprintf(log, "\nList dump:\n");

    elem* tmp = root;
    int i = 1;

    fprintf(log, "[0] Root: name:|%s| id:[%i]\n", root->name, root->id);

    while(tmp->next != NULL){

        tmp = tmp->next;
        ADD_TO_DUMP(i, tmp->name, tmp->id)
    }

    fprintf(log, "Dump end\n");
}