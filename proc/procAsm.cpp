#include "procAsm.h"
#include <myLib.h>

static int  ipMove     (char command_recognizer[]);
static int  argInit    (char* argument_recognizer);

static void sintaxError(int num);

static void workWithNum(SPU* spu, char argument_recognizer[], int* shift, int* t_1);
static void workWithRAM(SPU* spu, char argument_recognizer[], int* shift, int t_1);
static void workWithReg(SPU* spu, int* shift, int arg);

static void addLabel   (SPU* spu, char command_recognizer[], size_t len);
static bool searchLabel(SPU* spu, char* buffer, char argument_recognizer[], int* shift, int t_1);

#define CHECKING_FOR_WORKING_WITH_RAM                   \
    if (argument_recognizer[0] == '[')                  \
    {                                                   \
        workWithRAM(spu, argument_recognizer, &shift, t_1); \
        continue;                                       \
    }                                                   \
        
#define CHECKING_FOR_WORKING_WITH_NUM                    \
    else if (arg == 0)                                   \
    {                                                    \
        workWithNum(spu, argument_recognizer, &shift, &t_1); \
        continue;                                        \
    }

#define CHECKING_FOR_WORKING_WITH_REG \
    else                              \
    {                                 \
        workWithReg(spu, &shift, arg);    \
        continue;                     \
    }

#define WORKING_WITH_THREE_ARGUMENT_COMMAND(constNameCommand)  \
    spu->code[spu->ip] = constNameCommand;                     \
    spu->ip++;                                                 \
    shift += t_0 + SPACE;                                          \
    char argument_recognizer[LEN_REG] = "";                    \
    int t_1 = 0;                                               \
    sscanf(buffer + shift, "%s%n", argument_recognizer, &t_1);     \
    int arg = argInit(argument_recognizer);                   

#define ONE_ARGUMENT_COMMAND(command, constNameCommand)                      \
    else if (strcmp(command_recognizer, command) == 0)                       \
    {                                                                        \
        spu->code[spu->ip] = constNameCommand;                               \
        spu->ip++;                                                           \
        shift += t_0 + SPACE;                                                    \
        continue;                                                            \
    }

#define JUMP_TYPE_COMMAND(command, constNameCommand)                             \
    else if (strcmp(command_recognizer, command) == 0)                           \
    {                                                                            \
        spu->code[spu->ip] = constNameCommand;                                   \
        spu->ip++;                                                               \
        shift += t_0 + SPACE;                                                        \
        char argument_recognizer[MAX_LABEL_SIZE] = "";                           \
        int t_1 = 0;                                                             \
        sscanf(buffer + shift, "%s%n", argument_recognizer, &t_1);                   \
        if (isdigit(argument_recognizer[0]) != 0)                                \
        {                                                                        \
            spu->code[spu->ip] = atof(argument_recognizer);                      \
            spu->ip++;                                                           \
            shift += t_1 + SPACE;                                                    \
        }                                                                        \
        else                                                                     \
        {                                                                        \
            bool label = searchLabel(spu, buffer, argument_recognizer, &shift, t_1); \
            if (!label)                                                          \
                sintaxError(3);                                                  \
        }                                                                        \
    } 

#define IGNORE                                   \
    {                                            \
        size_t len = strlen(command_recognizer); \
        shift += (int)len;                           \
        continue;                                \
    }

#define INITIAL_MILEAGE_BY_CODE                     \
    findLabel(spu, buffer, &shift, command_recognizer); \
    shift = 0;                                          \
    spu->ip = 0;                                    \

size_t asembler(SPU* spu)
{
    assert(spu);

    FILE* assembler = fopen(ASSEMBLER_FILE_NAME, "r");               // ОТКРЫТИЕ ФАЙЛА ДЛЯ ЧТЕНИЯ 
    assert(assembler);

    size_t size_file = getFileSize(assembler);  // ПОЛУЧЕНИЕ РАЗМЕРА ФАЙЛА 

    spu->code = (double*)calloc(size_file * 3, sizeof(double));     // СОЗДАНИЕ МАССИВА code
    assert(spu->code);

    char* buffer = readFileToBuffer(assembler, size_file);          // СОЗДАНИЕ БУФФЕРА
    assert(buffer);

    FCLOSE(assembler);

    char command_recognizer[10] = "";
    int shift = 0;  

    INITIAL_MILEAGE_BY_CODE
    
    while (buffer[shift] != '\0')
    {   
        int t_0 = 0;
        sscanf(buffer + shift, "%s%n", command_recognizer, &t_0);

        if (strcmp(command_recognizer, "push") == 0)
        {
            WORKING_WITH_THREE_ARGUMENT_COMMAND(COMMAND_PUSH);
            
            CHECKING_FOR_WORKING_WITH_RAM
            CHECKING_FOR_WORKING_WITH_NUM
            CHECKING_FOR_WORKING_WITH_REG
        }    
            
        else if (strcmp(command_recognizer, "pop") == 0)
        {
            WORKING_WITH_THREE_ARGUMENT_COMMAND(COMMAND_POP);

            CHECKING_FOR_WORKING_WITH_RAM
            CHECKING_FOR_WORKING_WITH_REG 
        }

        else if (strncmp(command_recognizer, "hlt", 3) == 0)                         \
        {                                                                            \
            spu->code[spu->ip] = COMMAND_HLT;                                        \
            spu->ip++;                                                               \
            shift += t_0 + SPACE;                                                        \
            continue;                                                                \
        }

        ONE_ARGUMENT_COMMAND("dump" , COMMAND_DUMP )
        ONE_ARGUMENT_COMMAND("sdump", COMMAND_SDUMP)
        ONE_ARGUMENT_COMMAND("add"  , COMMAND_ADD  )
        ONE_ARGUMENT_COMMAND("sub"  , COMMAND_SUB  )
        ONE_ARGUMENT_COMMAND("mul"  , COMMAND_MUL  )
        ONE_ARGUMENT_COMMAND("div"  , COMMAND_DIV  )
        ONE_ARGUMENT_COMMAND("sqrt" , COMMAND_SQRT )
        ONE_ARGUMENT_COMMAND("out"  , COMMAND_OUT  )
        ONE_ARGUMENT_COMMAND("in"   , COMMAND_IN   )
        ONE_ARGUMENT_COMMAND("sin"  , COMMAND_SIN  )
        ONE_ARGUMENT_COMMAND("cos"  , COMMAND_COS  )
        ONE_ARGUMENT_COMMAND("tg"   , COMMAND_TG   )
        ONE_ARGUMENT_COMMAND("ctg"  , COMMAND_CTG  )
        ONE_ARGUMENT_COMMAND("ret"  , COMMAND_RET  )

        JUMP_TYPE_COMMAND("call", COMMAND_CALL)
        JUMP_TYPE_COMMAND("jmp" , COMMAND_JMP )  
        JUMP_TYPE_COMMAND("ja"  , COMMAND_JA  )
        JUMP_TYPE_COMMAND("jb"  , COMMAND_JB  )
        JUMP_TYPE_COMMAND("jae" , COMMAND_JAE )
        JUMP_TYPE_COMMAND("jbe" , COMMAND_JBE )
        JUMP_TYPE_COMMAND("je"  , COMMAND_JE  )
        JUMP_TYPE_COMMAND("jhe" , COMMAND_JHE )

        else IGNORE
    } 

    FREE(buffer);
    return size_file;
}

#undef ONE_ARGUMENT_COMMAND
#undef JUMP_TYPE_COMMAND

#undef CHECKING_FOR_WORKING_WITH_RAM
#undef CHECKING_FOR_WORKING_WITH_REG
#undef CHECKING_FOR_WORKING_WITH_NUM

#undef WORKING_WITH_THREE_ARGUMENT_COMMAND
#undef IGNORE
#undef INITIAL_MILEAGE_BY_CODE

void findLabel(SPU* spu, char* buffer, int* shift, char command_recognizer[])
{
    assert(spu);
    assert(buffer);
    assert(command_recognizer);

    while (buffer[*shift] != '\0')
    {   
        sscanf(buffer + (*shift), "%s", command_recognizer);
        size_t command_recognizer_len = strlen(command_recognizer);

        spu->ip += ipMove(command_recognizer);

        if (command_recognizer[command_recognizer_len - 1] == ':')
        {
            addLabel(spu, command_recognizer, command_recognizer_len);
            (*shift) += (int)command_recognizer_len + SPACE;
        }
        else    
            (*shift) += (int)command_recognizer_len + SPACE;
    }
}

static void addLabel(SPU* spu, char command_recognizer[], size_t len)
{
    assert(spu);
    assert(command_recognizer);

    command_recognizer[len - 1] = '\0';  // СТИРАНИЕ ДВОЕТОЧИЯ ИЗ НАЗВАНИЯ МЕТКИ
    spu->lb[spu->labelCounter].nameLabel = strdup(command_recognizer);
    spu->lb[spu->labelCounter].ipLabel = spu->ip + 1;
    spu->labelCounter++;
}

static int argInit(char* argument_recognizer)
{
    assert(argument_recognizer);

    int arg = 0;

    for (int i = 0; i < NUMBER_OF_REGISTERS; i++)
    {
        if (strncmp(argument_recognizer, registerNames[i], 2) == 0)
            return i + 1;
    }

    return arg;
}

static void sintaxError(int num)
{
    printf(RED "SINTAX ERROR %d\n" RESET, num);
    abort();
}

static bool searchLabel(SPU* spu, char* buffer, char argument_recognizer[], int* shift, int t_1)
{
    assert(spu);
    assert(buffer);
    assert(argument_recognizer);

    bool metka = false;
    for (int y = 0; y < spu->labelCounter; y++)
    {
        if (strcmp(argument_recognizer, spu->lb[y].nameLabel) == 0)
        {
            spu->code[spu->ip] = (double)spu->lb[y].ipLabel;
            spu->ip++;
            metka = true;
            (*shift) += t_1 + SPACE;
            continue;
        }
    }
    return metka;
} 

static int ipMove(char command_recognizer[])
{
    assert(command_recognizer);
    int ip = 0;
    
    for (int k = 0; k < NUMBER_OF_COOMANDS - 1; k++) // НУЛЕВАЯ КОММАНДА НЕ ВХОДИТ В ЧИСЛО КОРРЕКТНЫХ КОММАНД
    {
        if (strcmp(command_recognizer, commandArr[k].CommandName) == 0) 
        {
            ip += commandArr[k].ipShift;
            continue;
        }
    }
                                                        
    return ip;
}

static void workWithRAM(SPU* spu, char argument_recognizer[], int* shift, int t_1)
{
    assert(spu);
    assert(argument_recognizer);
    (*shift)++;
    spu->code[spu->ip] = ARGTYPE_M;
    spu->ip++;
    argument_recognizer[t_1 - 1] = '\0';
    if (!isalpha(argument_recognizer[1]))
    {
        double argument = atof(argument_recognizer + 1);

        if (argument >= RAM_SIZE || argument < 0)
            sintaxError(6);
        
        spu->code[spu->ip] = argument;
        spu->ip++;

        (*shift) += t_1;
    }
    else
    {
        spu->code[spu->ip - 1] += ARGTYPE_R;
        int argRam = argInit(argument_recognizer + 1);
        int registr = argRam;

        if (!registr)
            sintaxError(8);

        spu->code[spu->ip] = registr;
        spu->ip++;
        (*shift) += t_1;
    }
}

static void workWithReg(SPU* spu, int* shift, int arg)
{
    assert(spu);
    (*shift) += 3;
    int registr = arg;
    spu->code[spu->ip] = ARGTYPE_R;
    spu->ip++;
    spu->code[spu->ip] = registr;
    spu->ip++;
}

static void workWithNum(SPU* spu, char argument_recognizer[], int* shift, int* t_1)
{
    assert(spu);
    assert(argument_recognizer);

    int argument = 0;
    sscanf(argument_recognizer, "%d%n", &argument, t_1);
    spu->code[spu->ip] = ARGTYPE_I; 
    spu->ip++;
    (*shift) += SPACE;
    spu->code[spu->ip] = argument; 
    spu->ip++;
    (*shift) += (*t_1);
}
