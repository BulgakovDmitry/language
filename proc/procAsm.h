#ifndef PROC_ASSM_H
#define PROC_ASSM_H

#include <myLib.h>
#include "proc.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

const int SPACE   = 1;
const int LEN_REG = 3;
const char* const ASSEMBLER_FILE_NAME = "assemblerFile.txt";

struct CMD_ARRAY      {const char* cmd_array;};

struct IP_MOVE        
{
    const char* const CommandName; 
    int ipShift;
};

const IP_MOVE commandArr[NUMBER_OF_COOMANDS] = {
                                                    {"push", 3}, {"pop", 3}, {"hlt", 1}, {"dump", 1}, {"sdump", 1}, {"add", 1}, 
                                                    {"sub" , 1}, {"mul", 1}, {"div", 1}, {"sqrt", 1}, {"out"  , 1}, {"in" , 1}, 
                                                    {"sin" , 1}, {"cos", 1}, {"ret", 1}, {"jmp" , 2}, {"ja"   , 2}, {"jb" , 2}, 
                                                    {"jae" , 2}, {"jbe", 2}, {"je" , 2}, {"jhe" , 2}, {"call" , 2}, {"tg" , 1},
                                                    {"ctg" , 1}
                                               };

const char* const registerNames[NUMBER_OF_REGISTERS] = {"ax", "bx", "cx", "dx", "ex", "fx", "gx", "hx"};

size_t asembler(SPU* spu);
void  findLabel(SPU* spu, char* buffer, int* i, char command_recognizer[]); // первичный прогон по коду для определения меток

#endif