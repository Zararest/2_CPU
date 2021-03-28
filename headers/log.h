//тут определение кодов ошибок
#ifndef LOG_H
#define LOG_H

#define FILE_IS_NULL 1
#define MEMORY_IS_NULL 9
#define COMMAND_IS_NULL 10
#define BINARY_FILE_TROUBLE 2
#define FILL_BUFFER_TROUBLE 3 
#define WRONG_REG_NAME 4
#define WRONG_MODIFICATOR 5
#define WRONG_DEF_OF_MAS 6
#define WRONG_COMMAND 7
#define WRONG_LINK 8

//тут написание моих макросов(мой ассерт, добавление в лог, создание лога)(в макрос подается информация)
#define CREATE_LOG(name) FILE* log_pointer = fopen(name, "w");
#define ADD_TO_LOG(msg, command_number) fprintf(log_pointer, "[%i] %s\n", command_number, msg);
#define MY_ASSERT(expression, exit_status) if (expression == 0){\
                            fprintf(log_pointer, "In file |%s| in line[%d] exit atatus[%d]\n", __FILE__, __LINE__, exit_status);\
                            fclose(log_pointer);\
                            exit(exit_status);}
#define CLOSE_LOG fclose(log_pointer);

#endif
