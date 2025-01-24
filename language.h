#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <stdio.h>

enum Type_t {NUM = 1, ID = 2, OP = 3};

enum Operations { 
    ADDITTION             = 1,
    SUBTRACTION           = 2,
    DIVISION              = 3,
    MULTIPLICATION        = 4,
    ELEVATION             = 5,

    COS                   = 6,
    SIN                   = 7,
    LOG                   = 8,
    LN                    = 9,
    EXP                   = 10,
    TAN                   = 11,

    IF                    = 12,
    WHILE                 = 13,
    EQUALS                = 14,

    OPENING_CURLY_BRACKET = 15,
    CLOSING_CURLY_BRACKET = 16,
    OPENING_BRACKET       = 17,
    CLOSING_BRACKET       = 18,

    DECLARATION_ID        = 19,
    DECLARATION_FUNCTION  = 20,
    BEGINING              = 21,
    ENDING                = 22,
    PRE_EQUAL             = 23,
    IN_EQUAL              = 24, 
    SEPARATOR             = 25,

    EQUAL_COMPARE         = 26,
    NOT_EQUALE_COMPARE    = 27,
    LESS                  = 28,
    LESS_OR_EQUALE        = 29,
    MORE                  = 30,
    MORE_OR_EQUAL         = 31,

    BEGIN_PARAM_FUNC      = 32,
    END_PARAM_FUNC        = 33,

};
  
#define TYPE "lg"
#define SCALE 50
#define LENGTH 256 

const int MAX_NAME_ID = 256;

typedef double tal_t;

union Value
{
    double val_num;
    Operations val_op;
    size_t id;
};

struct Node
{
    Type_t type;
    Value value;
    Node* right;
    Node* left;
};

struct NameTable
{
    char name_id [MAX_NAME_ID];
};

struct Language
{
    char* buffer;
    Node* tokenArray;
    NameTable* nameTable;
};

#define DEBUG 1

    #if  (DEBUG == 1) 
        #define DBG( ... ) __VA_ARGS__
        #define PRINT_TOKEN_POINTER printf ("" BLUE  "Token + pointer = %p\n" RESET "", context -> Token_array + context -> pointer)
    #else 
        #define DBG( ... )
        #define PRINT_TOKEN_POINTER     
    #endif         

const int NUM_OF_TOKEN = 128;
const int INIT_NUM_KEY_WORDS  = 1024;

#endif